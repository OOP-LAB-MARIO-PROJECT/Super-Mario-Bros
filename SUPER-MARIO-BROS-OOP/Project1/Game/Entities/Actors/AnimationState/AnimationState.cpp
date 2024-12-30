#include "AnimationState.h"


AnimationState::AnimationState(const std::string& en, const std::vector<std::vector<std::string>>& tn, const float& sT) : entityName(en), textureName(tn), stateDuration(sT)  {}

void AnimationState::setEntityName(const std::string EntityName) {
	entityName = EntityName;
}

void AnimationState::switchTexture(std::vector<std::vector<std::string>> newTexture) {
	textureName = newTexture;
}


IdleState::IdleState(const std::string& en, const std::vector<std::vector<std::string>>& tn, const float& sT) : AnimationState(en, tn) {
	stateDuration = 0.0f;
}


void IdleState::update(Actor* a, float deltaTime) {
	bool isRight = a->getFacing() == 1;
	std::vector<std::vector<std::string>> wbTexture = { { "left-small-mario-wb-12" }, {"right-small-mario-wb-1"} };
	//switchTexture(wbTexture);
	
	if (a->getType() == PLAYER && GameConfig::getInstance().isInvincible) {
		static float blinkTimer = 0;
		blinkTimer += deltaTime;

		int alpha = static_cast<int>((std::sin(blinkTimer * 40.0f) + 1.0f) * 77.5f + 100);
		a->sprite.setColor(sf::Color(255, 255, 255, alpha));
	}
	else if (GameConfig::getInstance().marioState == SMALL || GameConfig::getInstance().marioState == BIG || GameConfig::getInstance().marioState == WHITE_BIG) {
		a->sprite.setColor(sf::Color(255, 255, 255, 255));
	}
	a->setTexture(entityName, textureName[isRight][0]);
	
}


void IdleState::handle(Actor* a, float deltaTime) {
	if (a->getIsTransforming()) {
		a->setState("TRANSFORMING");
	} 
	else if (a->getVel().x != 0 && a->getIsOnGround()) {
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
DodgingState::DodgingState(const std::string& en, const std::vector<std::vector<std::string>>& tn, const float& sT) : AnimationState(en, tn) {

}


void DodgingState::update(Actor* a, float deltaTime) {
	if (a->getIsDodge()) {
		sf::Vector2f size = a->getSize();
		size.y = 14.f;
		a->setPos(a->getPos() - size + a->getSize());
		a->setSize(size);
		size.x = 0;
		a->setSpriteOrigin(sf::Vector2f(0, 16));
		bool isRight = a->getFacing() == 1;
		a->setTexture(entityName, textureName[isRight][0]);
	}
}
void DodgingState::handle(Actor* a, float deltaTime) {
	if (a->getIsDead()) {
		a->setState("DEAD");
		return;
	}
	if (!a->getIsDodge()) {
		sf::Vector2f size = a->getSize();
		size.y = 30.f;

		a->setPos(a->getPos() - size + a->getSize());
		a->setSpriteOrigin(sf::Vector2f(0, 0));

		a->setSize(size);
		a->setState("IDLE");
	}
}

RunningState::RunningState(const std::string& en, const std::vector<std::vector<std::string>>& tn, const float& sT) : AnimationState(en, tn, sT) {
}


void RunningState::update(Actor* a, float deltaTime) {
	bool isRight = a->getFacing() == 1;
	if (a->getType() == PLAYER && GameConfig::getInstance().marioState == INVINCIBLE) {
		static float blinkTimer = 0;
		blinkTimer += deltaTime;

		int alpha = static_cast<int>((std::sin(blinkTimer * 40.0f) + 1.0f) * 77.5f + 100);
		a->sprite.setColor(sf::Color(255, 255, 255, alpha));
	}
	else if (GameConfig::getInstance().marioState == SMALL) {
		a->sprite.setColor(sf::Color(255, 255, 255, 255));
	}
	a->setTexture(entityName, textureName[isRight][aniLoop % textureName[isRight].size()]);


	// Cập nhật animation loop
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
		else if (a->getIsAttack()) a->setState("ATTACK");
		else if (a->getIsDeadByOtherThings()) a->setState("DEAD_BY_OTHER_THINGS");
	}
	else if (a->getType() == HARM_TO_ALL) {
		a->setState("DEFENSE");
	}
	
}


JumpingState::JumpingState(const std::string& en, const std::vector<std::vector<std::string>>& tn, const float& sT) : AnimationState(en, tn, sT) {
}


void JumpingState::update(Actor* a, float deltaTime) {
	bool isRight = a->getFacing() == 1;
	if (a->getType() == PLAYER && GameConfig::getInstance().marioState == INVINCIBLE) {
		static float blinkTimer = 0;
		blinkTimer += deltaTime;

		int alpha = static_cast<int>((std::sin(blinkTimer * 40.0f) + 1.0f) * 77.5f + 100);
		a->sprite.setColor(sf::Color(255, 255, 255, alpha));
	}
	else if (GameConfig::getInstance().marioState == SMALL) {
		a->sprite.setColor(sf::Color(255, 255, 255, 255));
	}
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
	if (a->getType() == PLAYER && GameConfig::getInstance().marioState == INVINCIBLE) {
		static float blinkTimer = 0;
		blinkTimer += deltaTime;

		int alpha = static_cast<int>((std::sin(blinkTimer * 40.0f) + 1.0f) * 77.5f + 100);
		a->sprite.setColor(sf::Color(255, 255, 255, alpha));
	}
	else if (GameConfig::getInstance().marioState == SMALL) {
		a->sprite.setColor(sf::Color(255, 255, 255, 255));
	}
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
	if (a->getType() == PLAYER && GameConfig::getInstance().marioState == INVINCIBLE) {
		static float blinkTimer = 0;
		blinkTimer += deltaTime;

		int alpha = static_cast<int>((std::sin(blinkTimer * 40.0f) + 1.0f) * 77.5f + 100);
		a->sprite.setColor(sf::Color(255, 255, 255, alpha));
	}
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
}


void DeadState::handle(Actor* a, float deltaTime) {
	updateTimer(deltaTime);
	if (!isDurationEnded()) {
		return;
	}
	else resetTimer();
	if(a->getType() == PLAYER) a->setState("IDLE");
	if (a->getIsDead()) a->kill();
}


DefenseState::DefenseState(const std::string& en, const std::vector<std::vector<std::string>>& tn, const float& sT) : AnimationState(en, tn, sT) {
}


void DefenseState::update(Actor* a, float deltaTime) {
	bool isRight = a->getFacing() == 1;
	a->setTexture(entityName, textureName[isRight][0]);

}


void DefenseState::handle(Actor* a, float deltaTime) {
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

		if (GameConfig::getInstance().marioState == MARIO_STATE::BIG || GameConfig::getInstance().marioState == MARIO_STATE::WHITE_BIG) {
			if (transformTime < 0.8) id = 0;
			if (transformTime < 0.5) id = 1;
			
			pos.y -= 16.f * deltaTime;
			size.y += 16.f / 1.2f * deltaTime;
		}
		else if (GameConfig::getInstance().marioState == MARIO_STATE::SMALL) {
			if (transformTime < 0.8) id = 1;
			if (transformTime < 0.5) id = 0;

			pos.y += 16.f * deltaTime;
			size.y -= 16.f / 1.2f * deltaTime;
		}
		a->setSize(size);
		a->setPos(pos);
		a->setVel({ 0, 0 });
	}

	if (transformTime <= 0.1) {
		transformTime = 0;
		transforming = 0;
		a->setState("IDLE");
		a->setIsTransforming(false);
	}
}


AttackState::AttackState(const std::string& en, const std::vector<std::vector<std::string>>& tn, const float& sT) : AnimationState(en, tn, sT) {
}


void AttackState::update(Actor* a, float deltaTime) {
	bool isRight = a->getFacing() == 1;
	a->setTexture(entityName, textureName[isRight][0]);

}


void AttackState::handle(Actor* a, float deltaTime) {
	updateTimer(deltaTime);
	if (!isDurationEnded()) {
		return;
	}
	else resetTimer();

	a->setState("RUN");
}



PollingState::PollingState(const std::string& en, const std::vector<std::vector<std::string>>& tn, const float& sT) : AnimationState(en, tn, sT) {
}

void PollingState::update(Actor* a, float deltaTime) {
	timer += deltaTime;
	if (timer > 0.2) timer = 0, aniLoop++;
	bool isRight = a->getFacing();
	a->setTexture(entityName, textureName[isRight][aniLoop % textureName[isRight].size()]);

	if (firstUpdate) {
		curPos = a->getPos();
		firstUpdate = false;
	}

	curPos.y += 60 * deltaTime;
	a->setPos(curPos);
	a->setVel(sf::Vector2f(0, 0));
}

void PollingState::handle(Actor* a, float deltaTime) {
	updateTimer(deltaTime);

	if (isDurationEnded() || a->getPos().y + a->getSize().y + 16 >= GameConfig::getInstance().cameraBase) a->setState("IDLE"), resetTimer(), firstUpdate = true;
	
	if (!isDurationEnded()) {
		return;
	}
	else resetTimer();
}