#include "AnimationState.h"


AnimationState::AnimationState(const std::string& en, const std::vector<std::vector<std::string>>& tn, const float& sT) : entityName(en), textureName(tn), stateDuration(sT)  {}

void AnimationState::setEntityName(const std::string EntityName) {
	entityName = EntityName;
}

void AnimationState::switchTexture(std::vector<std::vector<std::string>> newTexture) {
}


IdleState::IdleState(const std::string& en, const std::vector<std::vector<std::string>>& tn, const float& sT) : AnimationState(en, tn) {
	stateDuration = 0.0f;
}


void IdleState::update(Actor* a, float deltaTime) {
	bool isRight = a->getFacing() == 1;
	a->setTexture(entityName, textureName[isRight][0]);
}


void IdleState::handle(Actor* a, float deltaTime) {
	if (a->getIsTransforming()) {
		a->setState("TRANSFORMING");
	} else
	if (a->getVel().x != 0 && a->getIsOnGround()) {
		a->setState("RUN");
	}
	else if (!a->getIsOnGround()) {
		a->setState("JUMP");
	}
	else if (a->getIsDead())
	{
		a->setState("DEAD");
		a->setIsDead(false);
	}

}

RunningState::RunningState(const std::string& en, const std::vector<std::vector<std::string>>& tn, const float& sT) : AnimationState(en, tn, sT) {
}


void RunningState::update(Actor* a, float deltaTime) {
	bool isRight = a->getFacing() == 1;
	a->setTexture(entityName, textureName[isRight][aniLoop % textureName[isRight].size()]);

	timer += deltaTime;
	if (timer > stateDuration) {
		aniLoop++;
		timer = 0;
	}
}


void RunningState::handle(Actor* a, float deltaTime) {
	
	if (a->getType() == PLAYER) 
	{
		if (a->getIsTransforming()) {
			a->setState("TRANSFORMING");
		}
		else if (a->getVel().x == 0 && a->getIsOnGround()) {
			a->setState("IDLE");
		}
		else if (!a->getIsOnGround()) {
			a->setState("JUMP");
		}
		else if (a->getVel().x * a->getFacing() < 0) {
			a->setState("SLIDE");
		}
		else if (a->getIsDead())
		{
			a->setState("DEAD");
			a->setIsDead(false);
		}
	}
	else if (a->getType() == ENEMY) {
		if (a->getIsDead()) a->setState("DEAD");
		else if (a->getIsDeadByOtherEnemy()) a->setState("DEAD_BY_ENEMY");
	}
	else if (a->getType() == HARM_TO_ALL) {
		a->setState("DEFENSE");
	}
	
}


JumpingState::JumpingState(const std::string& en, const std::vector<std::vector<std::string>>& tn, const float& sT) : AnimationState(en, tn, sT) {
}


void JumpingState::update(Actor* a, float deltaTime) {
	bool isRight = a->getFacing() == 1;
	a->setTexture(entityName, textureName[isRight][0]);
}


void JumpingState::handle(Actor* a, float deltaTime) {
	if (a->getIsTransforming()) {
		a->setState("TRANSFORMING");
	} else if (a->getVel().x == 0 && a->getIsOnGround()) {
		a->setState("IDLE");
	} 
	else if (a->getVel().x != 0 && a->getIsOnGround()) {
		a->setState("RUN");
	}
	else if (a->getIsKilling()) {
		a->setState("KILL");
		a->setIsKilling(false);
	}
	else if (a->getIsDead())
	{
		a->setState("DEAD");
		a->setIsDead(false);
	}
}




SlideState::SlideState(const std::string& en, const std::vector<std::vector<std::string>>& tn, const float& sT) : AnimationState(en, tn, sT) {
}


void SlideState::update(Actor* a, float deltaTime) {
	bool isRight = a->getFacing() == 1;
	a->setTexture(entityName, textureName[isRight][0]);

}


void SlideState::handle(Actor* a, float deltaTime) {

	if (a->getIsTransforming()) {
		a->setState("TRANSFORMING");
		return;
	}

	updateTimer(deltaTime);
	if (!isDurationEnded()) {
		return;
	} else resetTimer();


	if (a->getVel().x == 0 && a->getIsOnGround()) {
		a->setState("IDLE");
	}
	else if (a->getVel().x != 0 && a->getIsOnGround()) {
		a->setState("RUN");
	}
	else if (!a->getIsOnGround()) {
		a->setState("JUMP");
	}
}





KillState::KillState(const std::string& en, const std::vector<std::vector<std::string>>& tn, const float& sT) : AnimationState(en, tn, sT) {
}


void KillState::update(Actor* a, float deltaTime) {
	bool isRight = a->getFacing() == 1;
	a->setTexture(entityName, textureName[isRight][0]);

}


void KillState::handle(Actor* a, float deltaTime) {
	updateTimer(deltaTime);
	if (!isDurationEnded()) {
		return;
	}
	else resetTimer();
	
	if (a->getIsTransforming()) {
		a->setState("TRANSFORMING");
	}
	else if (a->getVel().x == 0 && a->getIsOnGround()) {
		a->setState("IDLE");
	}
	else if (a->getVel().x != 0 && a->getIsOnGround()) {
		a->setState("RUN");
	}
	else if (!a->getIsOnGround()) {
		a->setState("JUMP");
	}
}




DeadState::DeadState(const std::string& en, const std::vector<std::vector<std::string>>& tn, const float& sT) : AnimationState(en, tn, sT) {
}


void DeadState::update(Actor* a, float deltaTime) {
	bool isRight = a->getFacing() == 1;
	a->setTexture(entityName, textureName[isRight][0]);
	if (a->getIsDeadByOtherEnemy()) { 
		a->setIsDeadByOtherEnemy(true);
		if (a->getHealth() == 0) a->setVel({ 0, -180.0f }), a->setHealth(-1);
		a->setPos(a->getPos() + a->getVel() * deltaTime);
		a->setSpriteScale(1.f, -1.f);
		a->setSpritePos(a->getPos() + sf::Vector2f(0, 16.f));
		a->performPhysics(deltaTime);
	}
}


void DeadState::handle(Actor* a, float deltaTime) {
	updateTimer(deltaTime);
	if (!isDurationEnded()) {
		return;
	}
	else resetTimer();

	if(a->getType() == PLAYER) a->setState("IDLE");
	if (a->getIsDeadByOtherEnemy() || a->getIsDead()) a->kill();
	
}


DefenseState::DefenseState(const std::string& en, const std::vector<std::vector<std::string>>& tn, const float& sT) : AnimationState(en, tn, sT) {
}


void DefenseState::update(Actor* a, float deltaTime) {
	bool isRight = a->getFacing() == 1;
	a->setTexture(entityName, textureName[isRight][0]);

}


void DefenseState::handle(Actor* a, float deltaTime) {

	a->setState("IDLE");
}


TransformState::TransformState(const std::string& en, const std::vector<std::vector<std::string>>& tn, const float& sT) : AnimationState(en, tn, sT) {

}

void TransformState::update(Actor* a, float deltaTime) {
	stateDuration -= deltaTime;
	bool isRight = a->getFacing() == 1;
	a->setTexture(entityName, textureName[isRight][id]);
}

void TransformState::handle(Actor* a, float deltaTime) {
	if (a->getIsTransforming()) {
		if (!transforming) {
			transforming = 1;
			transformTime = 1.2;
			id = 0;
		}

		transformTime -= deltaTime;

		sf::Vector2f pos = a->getPos();
		sf::Vector2f size = a->getSize();

		if (GameConfig::getInstance().marioState == MARIO_STATE::BIG) {
			if (transformTime < 0.8) id = 0;
			if (transformTime < 0.5) id = 1;
			
			pos.y -= 16.f / 1.2f * deltaTime;
			size.y += 16.f / 1.2f * deltaTime;
		}
		else if (GameConfig::getInstance().marioState == MARIO_STATE::SMALL) {
			if (transformTime < 0.8) id = 1;
			if (transformTime < 0.5) id = 0;

			pos.y += 16.f / 1.2f * deltaTime;
			size.y -= 16.f / 1.2f * deltaTime;
		}
		pos.y -= 2.f;
		a->setSize(size);
		a->setPos(pos);
	}

	if (transformTime <= 0.1) {
		transformTime = 0;
		transforming = 0;
		a->setState("IDLE");
		a->setIsTransforming(false);
	}
}