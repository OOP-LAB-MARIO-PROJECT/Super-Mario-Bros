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
    a = { {"goompa_ow-0"}, {"goompa_ow-1"} };
    stateCache["DEAD_BY_ENEMY"] = std::make_shared<DeadState>("Goompa", a, 1.f);

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
    if (health == 0 && !isDeadByOtherEnemy) isDead = true;
    if (currentState) {
        currentState->handle(this, deltatime);
        currentState->update(this, deltatime);
    }

    

    if (!isDead && !isDeadByOtherEnemy) {
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

        for (auto en : otherEntities) {
            affectOther(en, deltatime);
        }
    }

    
    performPhysics(deltatime);
}



void Goompa::behavior(float deltatime) {
    if (health <= 0 && !isDead) {
        isDead = true; 
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
    if (other->getType() == PLAYER) {
        int dir = dynamicRectVsRect(other->getHitbox(), deltatime, other->getHitbox().vel - this->getHitbox().vel, this->getHitbox());
        if (dir == -1) return;
        if (dir == LEFT || dir == RIGHT) {
            other->inflictDamage();
        }
    }
}