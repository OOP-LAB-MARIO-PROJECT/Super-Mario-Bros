#include "Fire.h"
#include <vector>


Fire::Fire(sf::Vector2f pos, sf::Vector2f size) : Enemy(pos, size) {
    isRenderHitbox = true;
    isRenderSprite = true;
    facing = 1;
    setPos({ pos.x, pos.y + 5.f });
    setSize({8, 8});
    std::vector<std::vector<std::string>> a = { {"fire-0", "fire-1"},
                                                {"fire-1", "fire-0"} };

    stateCache["RUN"] = std::make_shared<RunningState>("Fire", a, 0.15f);
    timerToLive = 5;

    
    setState("RUN");
     
}


void Fire::setState(const std::string& stateName) {
    if (stateCache.find(stateName) != stateCache.end()) {
        auto& state = stateCache[stateName];
        if (state != nullptr) {
            currentState = state;
        }
    }
}
void Fire::update(float deltatime) {
    timerToLive -= deltatime;
    if (timerToLive < 0) {
        kill();
        return;
    }

    if (currentState) {
        currentState->handle(this, deltatime);
        currentState->update(this, deltatime);
    }
   if (firstFire) {
        sf::Vector2f tmp;
        for (auto en : otherEntities) {
            if (en->getType() == PLAYER) {
                tmp = sf::Vector2f(en->getHitbox().pos.x, en->getHitbox().pos.y);
                if (en->getHitbox().pos.y > getPos().y) dist = 1;
                else if (getPos().y > en->getHitbox().pos.y) dist = -1;
                else firstFire = false;
                setPos({ getPos().x, getPos().y  + (abs(en->getHitbox().pos.y - getPos().y) + 8.f) * deltatime * dist });
            }
           
        }
        if (tmp.y < getPos().y && getPos().y - tmp.y < 2.f) firstFire = false;
    }

    for (auto en : otherEntities) {
            affectOther(en, deltatime);
    }
    
    setVel({ -50, getVel().y });
    setPos(getPos() + getVel() * deltatime);
}



void Fire::behavior(float deltatime) {
    if (health <= 0 && !isDead) {
        isDead = true;
    }
}



int Fire::getType() {
    return ENEMY;
}

void Fire::inflictDamage() {
    health--;
}

int Fire::getHealth() {
    return health;
}

void Fire::setHealth(int h) {
    health = h;
}



void Fire::affectOther(Entity* other, float deltatime) {
    if (other->getType() == PLAYER) {
        int dir = dynamicRectVsRect(other->getHitbox(), deltatime, other->getHitbox().vel - this->getHitbox().vel, this->getHitbox());
        if (dir == -1) return;
        if (dir == LEFT || dir == RIGHT) {
            other->inflictDamage();
        }
    }
}
