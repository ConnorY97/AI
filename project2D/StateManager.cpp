#pragma once
#include "StateManager.h"
#include "StateMachine.h"

StateManager* StateManager::instance = nullptr;

StateManager::StateManager(){
	if(instance)throw "There can only be One Instance of the State Manager";
	instance = this;
}

StateManager::~StateManager(){
	instance = nullptr;
}

void StateManager::Create(){
	instance = new StateManager();
}

void StateManager::Destroy(){
	delete instance;
}

void StateManager::RegisterMachine(AbstractMachine* machine){
	instance->machines.push(machine);
}

void StateManager::RemoveMachine(AbstractMachine* machine){
	if(instance)
		instance->machines.remove(machine);
}

void StateManager::Update(float deltaTime){
	for(AbstractMachine* machine : instance->machines){
		machine->update(deltaTime);
	}
}