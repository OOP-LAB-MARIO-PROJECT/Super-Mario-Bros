#include "AnimationState.h"


AnimationState::AnimationState(const std::string& en, const std::vector<std::vector<std::string>>& tn, const float& sT) : entityName(en), textureName(tn), stateDuration(sT)  {}


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
	if (timer > 0.15) {
		aniLoop++;
		timer = 0;
	}
}


void RunningState::handle(Actor* a, float deltaTime) {
	
	if (a->getType() == PLAYER) 
	{
		if (a->getVel().x == 0 && a->getIsOnGround()) {
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
	}
	
}


JumpingState::JumpingState(const std::string& en, const std::vector<std::vector<std::string>>& tn, const float& sT) : AnimationState(en, tn, sT) {
}


void JumpingState::update(Actor* a, float deltaTime) {
	bool isRight = a->getFacing() == 1;
	a->setTexture(entityName, textureName[isRight][0]);
}


void JumpingState::handle(Actor* a, float deltaTime) {
	if (a->getVel().x == 0 && a->getIsOnGround()) {
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

	if (a->getType() == ENEMY) a->kill();
	if(a->getType() == PLAYER) a->setState("IDLE");

}


AliveState::AliveState(const std::string& en, const std::vector<std::vector<std::string>>& tn, const float& sT) : AnimationState(en, tn, sT) {
}


void AliveState::update(Actor* a, float deltaTime) {
	bool isRight = a->getFacing() == 1;
	a->setTexture(entityName, textureName[isRight][0]);

}


void AliveState::handle(Actor* a, float deltaTime) {
	updateTimer(deltaTime);
	if (!isDurationEnded()) {
		return;
	}
	else resetTimer();

	a->setState("IDLE");
}