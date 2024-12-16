#include "KingKoopa.h"
#include <vector>
#include "../../../Utils/EntityManager.h"


KingKoopa::KingKoopa(sf::Vector2f pos, sf::Vector2f size) : Enemy(pos, size) {
    isRenderHitbox = true;
    isRenderSprite = true;
    setSize({ 32,32 });
    facing = 1;

    std::vector<std::vector<std::string>> a = { {"king_koopa_ow-0", "king_koopa_ow-1"},
                                                {"king_koopa_ow-0", "king_koopa_ow-1"} };

    stateCache["RUN"] = std::make_shared<RunningState>("KingKoopa", a, 0.15f);


    

    setState("RUN");

}


void KingKoopa::setState(const std::string& stateName) {
    if (stateCache.find(stateName) != stateCache.end()) {
        auto& state = stateCache[stateName];
        if (state != nullptr) {
            currentState = state;
        }
    }
}
void KingKoopa::update(float deltatime) {
    if (currentState) {
        currentState->handle(this, deltatime);
        currentState->update(this, deltatime);
    }

    attackTimer += deltatime;
    timer += deltatime;

    if (attackTimer > 1.f) {
        attackTimer = 0;
       // EntityManager::getInstance().addEntity(new Fire((getPos() + sf::Vector2f(0, getPos().y / 4.f)), sf::Vector2f(8, 8) ));
    }

    for (auto en : otherEntities) {
        Hitbox ob = en->getHitbox();
        ob.vel = sf::Vector2f{ 0.f, 0.f };
        obstacle.push_back(ob);
    }

    int dir = resolveCollideGround(obstacle, deltatime);
    setPos(getPos() + getVel() * deltatime);

    if (dir & (1 << 2)) setVel({ getVel().x, 0 }), isOnGround = true;
    if (dir & (1 << 3)) facing = 1, setVel(sf::Vector2f(20, getVel().y));
    if (dir & (1 << 1)) facing = -1, setVel(sf::Vector2f(-20, getVel().y));

    if (!(dir & (1 << 1)) && !(dir & (1 << 3))) {
        if (facing == 1)
            setVel(sf::Vector2f(20, getVel().y));
        else
            setVel(sf::Vector2f(-20, getVel().y));

       
    }

    if (!isOnGround) {
        setVel({ 0 * (float)facing, getVel().y });
    }

    for (auto en : otherEntities) {
        affectOther(en, deltatime);
    }

    if (timer > 1.5f) {
        setVel({ getVel().x, -80 });
        timer = 0;
        facing *= -1;
        isOnGround = false;
        performPhysics(deltatime);
    }

    performPhysics(deltatime);

}

void KingKoopa::behavior(float deltatime) {
    if (health <= 0 && !isDead) {
        isDead = true;
    }
}



int KingKoopa::getType() {
    return ENEMY;
}

void KingKoopa::inflictDamage() {
    health--;
}

int KingKoopa::getHealth() {
    return health;
}

void KingKoopa::setHealth(int h) {
    health = h;
}



void KingKoopa::affectOther(Entity* other, float deltatime) {
    if (other->getType() == PLAYER) {
        int dir = dynamicRectVsRect(other->getHitbox(), deltatime, other->getHitbox().vel - this->getHitbox().vel, this->getHitbox());
        if (dir == -1) return;
        if (dir == LEFT || dir == RIGHT) {
            other->inflictDamage();
        }
    }
}
