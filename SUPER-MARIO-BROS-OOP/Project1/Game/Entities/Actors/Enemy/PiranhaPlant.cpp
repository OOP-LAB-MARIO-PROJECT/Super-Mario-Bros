#include "PiranhaPlant.h"
#include <vector>


PiranhaPlant::PiranhaPlant(sf::Vector2f pos, sf::Vector2f size) : Enemy(pos, size) {
    setSize({ 16, 32 });
    isRenderHitbox = true;
    isRenderSprite = true;
    facing = 1;
    setPos(getPos() + sf::Vector2f(getSize().x / 2.f, 20));

    std::vector<std::vector<std::string>> a = { {"piranhaplant_ow-1", "piranhaplant_ow-0"},
                                                {"piranhaplant_ow-1", "piranhaplant_ow-0"} };

    stateCache["RUN"] = std::make_shared<RunningState>("PiranhaPlant", a, 0.15f);
    dist = 1;


    
    setState("RUN");

}


void PiranhaPlant::setState(const std::string& stateName) {
    if (stateCache.find(stateName) != stateCache.end()) {
        auto& state = stateCache[stateName];
        if (state != nullptr) {
            currentState = state;
        }
    }
}
void PiranhaPlant::update(float deltatime) {



    if (currentState) {
        currentState->handle(this, deltatime);
        currentState->update(this, deltatime);
    }

    for (auto en : otherEntities) {
        if (en->getType() == PLAYER) {


            if ((getPos().x - 28 <= en->getHitbox().pos.x) && (getPos().x + 28 >= en->getHitbox().pos.x))isStop = true;
            else isStop = false;
        }

    }

    if (!isStop) {
        if (tmp != 0) dist = tmp, tmp = 0;
        if (cnt >= 36) {
            timer += deltatime;
            if (timer > 0.5) dist = -1, cnt = 0, timer = 0;
            else dist = 0;
        }
        else if (cnt <= -36) dist = 1, cnt = 0;
        setVel({ 0, 0 });
        setPos(getPos() - sf::Vector2f(0, 14 * deltatime * dist));
        cnt += 14 * deltatime * dist;
    }
    else if (isStop) {
        std::cout << dist;
        if (cnt > 0) {
            if (cnt >= 36) {
                timer += deltatime;
                if (timer > 0.5) dist = -1, cnt = 0, timer = 0;
                else dist = 0;
            }
            setPos(getPos() - sf::Vector2f(0, 14 * deltatime * dist));
            cnt += 14 * deltatime * dist;
        }
        else {
            if (cnt <= -36) tmp = -dist, dist = 0, cnt = 0;
            setPos(getPos() - sf::Vector2f(0, 14 * deltatime * dist));
            cnt += 14 * deltatime * dist;
        }


    }

    setPos(getPos() + getVel() * deltatime);
    for (auto en : otherEntities) {
        affectOther(en, deltatime);
    }
}



void PiranhaPlant::behavior(float deltatime) {
    if (health <= 0 && !isDead) {
        isDead = true;
    }
}



int PiranhaPlant::getType() {
    return ENEMY;
}

void PiranhaPlant::inflictDamage() {
    health--;
}

int PiranhaPlant::getHealth() {
    return health;
}

void PiranhaPlant::setHealth(int h) {
    health = h;
}



void PiranhaPlant::affectOther(Entity* other, float deltatime) {
    if (other->getType() == PLAYER) {
        int dir = dynamicRectVsRect(other->getHitbox(), deltatime, other->getHitbox().vel - this->getHitbox().vel, this->getHitbox());
        if (dir == -1) return;
        if (dir == LEFT || dir == RIGHT) {
            other->inflictDamage();
        }
    }
}
