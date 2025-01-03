﻿#pragma once
#include <iostream>
#include <memory>  
#include <vector>
#include <string>
#include "../Actor.h"

class Entity;

class AnimationState {
protected: 
    std::string entityName;
    std::vector<std::vector<std::string>> textureName;
    float stateTimer = 0.0f;  
    float stateDuration = 0.0f;  
public:


    bool isDurationEnded() {
        return stateTimer >= stateDuration;
    }

    void updateTimer(float deltaTime) {
        if (stateDuration > 0) {
            stateTimer += deltaTime;
        }
    }

    void resetTimer() {
        stateTimer = 0.0f;
    }

    void switchTexture(std::vector<std::vector<std::string>> newTexture);
    AnimationState(const std::string& en, const std::vector<std::vector<std::string>>& tn,const float& sT = 0);
    virtual ~AnimationState() = default;

    virtual void update(Actor* a, float deltaTime) = 0;
    virtual void handle(Actor* a, float deltaTime) = 0;
    void setEntityName(const std::string EntityName);

};


class IdleState : public AnimationState {
public:
 
    IdleState(const std::string& en, const std::vector<std::vector<std::string>>& tn, const float& sT);

    void update(Actor* a, float deltaTime) override;
    void handle(Actor* a, float deltaTime) override;
    
};

class DodgingState: public AnimationState {
public:

    DodgingState(const std::string& en, const std::vector<std::vector<std::string>>& tn, const float& sT);

    void update(Actor* a, float deltaTime);
    void handle(Actor* a, float deltaTime);
};


class PollingState : public AnimationState {
    float timer = 0.f;
    int aniLoop = 0;
    bool firstUpdate = true;
    sf::Vector2f curPos = { 0, 0 };
public:

    PollingState(const std::string& en, const std::vector<std::vector<std::string>>& tn, const float& sT);

    void update(Actor* a, float deltaTime);
    void handle(Actor* a, float deltaTime);
};



class  RunningState : public AnimationState {
    float timer = 0.f;
    int aniLoop = 0;
public:
    RunningState(const std::string& en, const std::vector<std::vector<std::string>>& tn, const float& sT);

    void update(Actor* a, float deltaTime) override;
    void handle(Actor* a, float deltaTime) override;
};

class JumpingState : public AnimationState {
public:
    JumpingState(const std::string& en, const std::vector<std::vector<std::string>>& tn, const float& sT);

    void update(Actor* a, float deltaTime) override;
    void handle(Actor* a, float deltaTime) override;

};


class SlideState : public AnimationState {
public:
    SlideState(const std::string& en, const std::vector<std::vector<std::string>>& tn, const float& sT);

    void update(Actor* a, float deltaTime) override;
    void handle(Actor* a, float deltaTime) override;

};


class KillState : public AnimationState {
public:
    KillState(const std::string& en, const std::vector<std::vector<std::string>>& tn, const float& sT);

    void update(Actor* a, float deltaTime) override;
    void handle(Actor* a, float deltaTime) override;

};


class DeadState : public AnimationState {
public:
    DeadState(const std::string& en, const std::vector<std::vector<std::string>>& tn, const float& sT);

    void update(Actor* a, float deltaTime) override;
    void handle(Actor* a, float deltaTime) override;

};

class TransformState : public AnimationState {
    bool transforming = 0;
    float transformTime = 0;
    int id = 0;
public:
    TransformState(const std::string& en, const std::vector<std::vector<std::string>>& tn, const float& sT);

    void update(Actor* a, float deltaTime) override;
    void handle(Actor* a, float deltaTime) override;
};

// For enemy 
class DefenseState : public AnimationState {
public:
    DefenseState(const std::string& en, const std::vector<std::vector<std::string>>& tn, const float& sT);

    void update(Actor* a, float deltaTime) override;
    void handle(Actor* a, float deltaTime) override;

};


class AttackState : public AnimationState {
public:
    AttackState(const std::string& en, const std::vector<std::vector<std::string>>& tn, const float& sT);

    void update(Actor* a, float deltaTime) override;
    void handle(Actor* a, float deltaTime) override;

};

