#include "Goompa.h"
#include <vector>

Goompa::Goompa(sf::Vector2f pos, sf::Vector2f size) : Enemy(pos, size) {
	isRenderHitbox = true;
	isRenderSprite = true;
	facing = 1;
    
	currentState = MOVE;
	ani[MOVE] = { 
		"KoopaTroopa-Overworld-0",
		"KoopaTroopa-Overworld-1",
	};

	ani[DIE] = { "Goomba-Overworld-2" };


}

void Goompa::update(float deltatime) {
    animation(deltatime);  
    
    
    
    if (isDead && deathTimer > 0.3f) { 
        kill();
    }

    
    if (!isDead) {
        for (auto en : otherEntities) {
            Hitbox ob = en->getHitbox();
            ob.vel = sf::Vector2f{ 0.f, 0.f };
            obstacle.push_back(ob);
        }

        int dir = resolveCollideGround(obstacle, deltatime);
        setPos(getPos() + getVel() * deltatime);

        if (dir & (1 << 2)) setVel({ getVel().x, 0 });
        if (dir & (1 << 3)) facing = 1, setVel(sf::Vector2f(50, getVel().y));
        if (dir & (1 << 1)) facing = -1, setVel(sf::Vector2f(-50, getVel().y));

        if (!(dir & (1 << 1)) && !(dir & (1 << 3))) {
            if (facing == 1)
                setVel(sf::Vector2f(50, getVel().y));
            else
                setVel(sf::Vector2f(-50, getVel().y));
        }
    }

    for (auto en : otherEntities) {
        affectOther(en, deltatime);
    }

    
    behavior(deltatime);
    performPhysics(deltatime);
    setSpritePos(getPos() - sf::Vector2f(0, 16));
}

void Goompa::animation(float deltatime) {
    if (isDead) {
        currentState = DIE;  
        aniLoop = 0;  
    }
    
    setTexture("KoopaTroopa", ani[currentState][aniLoop % ani[currentState].size()]);
    

    
    timer += deltatime;

   
    if (timer > 0.15f) {
        aniLoop++;
        timer = 0;
    }
}

void Goompa::behavior(float deltatime) {
    if (health <= 0 && !isDead) {
        isDead = true;
        deathTimer = 0;  
    }
    deathTimer += deltatime;
}



int Goompa::getType() {
	return ENEMY;
}

void Goompa::inflictDamage() {
	health--;
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
