#include "Goompa.h"
#include <vector>


Goompa::Goompa(sf::Vector2f pos, sf::Vector2f size) : Enemy(pos, size) {
    isRenderHitbox = true;
	isRenderSprite = true;
	facing = 1;

    std::vector<std::vector<std::string>> a = { {"goompa_ow-0", "goompa_ow-1"},
                                                {"goompa_ow-1", "goompa_ow-0"} };

    stateCache["RUN"] = std::make_shared<RunningState>("Goompa", a, 0.15f);


    a = { {"goompa_ow-2"}, {"goompa_ow-2"} };

    stateCache["DEAD"] = std::make_shared<DeadState>("Goompa", a, 0.3);
  

    setState("RUN");

}


void Goompa::setState(const std::string& stateName) {
    if (stateCache.find(stateName) != stateCache.end()) {
        auto& state = stateCache[stateName];
        if (state != nullptr) {
            currentState = state;
        }
    }
}
void Goompa::update(float deltatime) {
    if (isDeadByOtherThings && timer > 1.f) kill();
    if (health == 0 && !isDeadByOtherThings) isDead = true;
    if (currentState) {
        currentState->handle(this, deltatime);
        currentState->update(this, deltatime);
    }

    if (isDeadByOtherThings) {
        if (getHealth() == 0) setVel({ 0, -120.0f }), health--;
        timer += deltatime;
        setPos(getPos() + getVel() * deltatime);
        setSpriteScale(1.f, -1.f);
        setSpritePos(getPos() + sf::Vector2f(0, 16.f));
        performPhysics(deltatime);
    }

    if (!isDead && !isDeadByOtherThings) {
        for (auto en : otherEntities) {
            Hitbox ob = en->getHitbox();
            ob.vel = sf::Vector2f{ 0.f, 0.f };
            obstacle.push_back(ob);
        }

        int dir = resolveCollideGround(obstacle, deltatime);
        setPos(getPos() + getVel() * deltatime);

        if (dir & (1 << 2)) setVel({ getVel().x, 0 }), isOnGround = true;
        if (dir & (1 << 3)) facing = 1, setVel(sf::Vector2f(50, getVel().y));
        if (dir & (1 << 1)) facing = -1, setVel(sf::Vector2f(-50, getVel().y));

        if (!(dir & (1 << 1)) && !(dir & (1 << 3))) {
            if (facing == 1)
                setVel(sf::Vector2f(50, getVel().y));
            else
                setVel(sf::Vector2f(-50, getVel().y));
        }


        // Follow player

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
            setVel(sf::Vector2f(50, getVel().y));
        else
            setVel(sf::Vector2f(-50, getVel().y));


        for (auto en : otherEntities) {
            affectOther(en, deltatime);
        }
    }

    
    performPhysics(deltatime);
}



void Goompa::behavior(float deltatime) {
    if (health <= 0 && !isDead) {
        isDead = true; 
        GameConfig::getInstance().addScore(200);
    }
}



int Goompa::getType() {
	return ENEMY;
}

void Goompa::inflictDamage() {
	health--;
}

int Goompa::getHealth() {
    return health;
}

void Goompa::setHealth(int h) {
    health = h;
}



void Goompa::affectOther(Entity* other, float deltatime) {
    if (other->getType() == PLAYER && !GameConfig::getInstance().isInvincible) {
        int dir = dynamicRectVsRect(other->getHitbox(), deltatime, other->getHitbox().vel - this->getHitbox().vel, this->getHitbox());
        if (dir == -1) return;
        if (dir == LEFT || dir == RIGHT) {
            other->inflictDamage();
        }
    }
}