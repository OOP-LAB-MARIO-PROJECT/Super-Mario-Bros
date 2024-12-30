#include "KoopaTroopa.h"
#include <vector>


KoopaTroopa::KoopaTroopa(sf::Vector2f pos, sf::Vector2f size) : Enemy(pos, size) {
    isRenderHitbox = true;
    isRenderSprite = true;
    facing = -1;


    std::vector<std::vector<std::string>> a = { {"kooptroopa_ow_left-1", "kooptroopa_ow_left-0"},
                                                {"kooptroopa_ow_right-1", "kooptroopa_ow_right-2"} };

    stateCache["RUN"] = std::make_shared<RunningState>("KoopaTroopa", a, 0.15f);


    a = { {"kooptroopa_ow_left-2"}, {"kooptroopa_ow_right-0"} };

    stateCache["DEFENSE"] = std::make_shared<DefenseState>("KoopaTroopa", a, 0);

    setState("RUN");

}


void KoopaTroopa::setState(const std::string& stateName) {
    if (stateCache.find(stateName) != stateCache.end()) {
        auto& state = stateCache[stateName];
        if (state != nullptr) {
            currentState = state;
        }
    }
}
void KoopaTroopa::update(float deltatime) {
    if (isDead && timer > 1.f) timer = 0, kill();
    if (currentState) {
        currentState->handle(this, deltatime);
        currentState->update(this, deltatime);
    }


    if (isDeadByOtherThings) {
        isDead = true;
        if (health == 0) setVel({ 0, -120.0f }), health--;
        timer += deltatime;
        setPos(getPos() + getVel() * deltatime);
        setSpriteScale(1.f, -1.f);
        setSpritePos(getPos() + sf::Vector2f(0, 32.f));
        performPhysics(deltatime);
        return;
    }

    if (!isDead && !isDeadByOtherThings) {
        for (auto en : otherEntities) {
            if (en->getType() == HARM_TO_PLAYER) continue;
            Hitbox ob = en->getHitbox();
            ob.vel = sf::Vector2f{ 0.f, 0.f };
            obstacle.push_back(ob);
        }

        int dir = resolveCollideGround(obstacle, deltatime);
        setPos(getPos() + getVel() * deltatime);

            if (dir & (1 << 2)) setVel({ getVel().x, 0 }), isOnGround = true;
            if (dir & (1 << 3)) facing = 1, setVel(sf::Vector2f(speed, getVel().y));
            if (dir & (1 << 1)) facing = -1, setVel(sf::Vector2f(-speed, getVel().y));

            if (!(dir & (1 << 1)) && !(dir & (1 << 3))) {
                if (facing == 1)
                    setVel(sf::Vector2f(speed, getVel().y));
                else
                    setVel(sf::Vector2f(-speed, getVel().y));
            }

            // Follow player
            if (!isDefense) {
                for (auto en : otherEntities) {
                    if (en->getType() == PLAYER) {
                        if ((getPos().x - 128 <= en->getHitbox().pos.x) && (getPos().x + 128 >= en->getHitbox().pos.x)) {
                            isAttack = true;
                            if (getPos().x + 64.f < en->getHitbox().pos.x)
                            {
                                facing = 1;
                            }
                            else if (getPos().x - 64.f > en->getHitbox().pos.x) {
                                facing = -1;
                            }
                        }
                        else {
                            isAttack = false;
                        }

                    }
                }

                if (facing == 1)
                    setVel(sf::Vector2f(speed, getVel().y));
                else
                    setVel(sf::Vector2f(-speed, getVel().y));

            }

            for (auto en : otherEntities) {
                affectOther(en, deltatime);
            }
            
    }

  

    setSpritePos(getPos() - sf::Vector2f(0, 16.f));
    behavior(deltatime);
    performPhysics(deltatime);
}



void KoopaTroopa::behavior(float deltatime) {
    if (health <= 0 && !isDead) {
        isDead = false;
    }
    else if (health <= 1 && GameConfig::getInstance().marioState != INVINCIBLE) speed = 0, isDefense =true, health = 2, cnt++;
}


int KoopaTroopa::getType() {
    if (isDefense) return HARM_TO_ALL;
    return ENEMY;
}

void KoopaTroopa::inflictDamage() {
    health--;
}

void KoopaTroopa::affectOther(Entity* other, float deltatime) {
    if (other->getType() == PLAYER && GameConfig::getInstance().marioState != INVINCIBLE) {
        sf::Vector2f pushback;
        int dir = dynamicRectVsRect(other->getHitbox(), deltatime, other->getHitbox().vel - this->getHitbox().vel, this->getHitbox(), pushback);

        //pushback = sf::Vector2f(16, 0);
        if (dir == -1) return;
        if (isDefense && speed != 0) {
            if (dir == TOP)
            {
                other->setVel({ other->getHitbox().vel.x, -100 });
                setVel({ getVel().x, -200});
                return;
            }
            
        }
        if ( (!isDefense || speed != 0) && (dir == LEFT || dir == RIGHT)) other->inflictDamage();
            else if (isDefense && speed == 0) {
                pushback.y = 0;
                pushback.x = std::abs(pushback.x + 16.f);
                speed = 200;
                if (dir == LEFT || dir == TOP)  facing = 1;
                if (dir == RIGHT) facing = -1;
                if (dir == TOP) other->setVel({ other->getHitbox().vel.x, -100});
                setPos(getPos() + pushback * (float)facing);
            }

    }
    else if (this->getType() == HARM_TO_ALL && other->getType() == ENEMY) {
        int dir = dynamicRectVsRect(other->getHitbox(), deltatime, other->getHitbox().vel - this->getHitbox().vel, this->getHitbox());
        if (dir == -1) return;
        if ((dir == LEFT || dir == RIGHT))
        {
            other->setIsDeadByOtherThings(true);
            other->inflictDamage();
        }
    }
}
