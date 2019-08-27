#pragma once

#include "atyp_Array.h"
#include "StateManager.h"

template<typename T>class StateMachine;

template<typename T>
class State{
public:
	virtual void init(T*){};
	virtual void exit(T*){};
	virtual void update(float DeltaTime, T*, StateMachine<T>*) = 0;
};


class AbstractMachine{
public:
	virtual ~AbstractMachine(){};
	virtual void update(float) = 0;
};

template <typename T>
class StateMachine : public AbstractMachine{
	T* agent;
	State<T>* currentState = nullptr;

	atyp::Array<State<T>*> states;
public:
	StateMachine(T* target) : agent(target){
		StateManager::RegisterMachine(this);
	}

	~StateMachine(){
		StateManager::RemoveMachine(this);

		for(State<T>* state : states){
			delete state;
		}
	}

	void SetState(State<T>* state){
		if(currentState)currentState->exit(agent);
		if(!state)return;
		currentState = state;
		currentState->init(agent);
	}

	void update(float deltaTime){
		if(currentState)
			currentState->update(deltaTime, agent, this);
	}
};

