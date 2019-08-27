#pragma once
#include "atyp_Array.h"

class AbstractMachine;

class StateManager{

	atyp::Array<AbstractMachine*> machines;


	StateManager();

	~StateManager();
public:
	static StateManager* instance;

	static void Create();
	static void Destroy();

	static void RegisterMachine(AbstractMachine* machine);

	static void RemoveMachine(AbstractMachine* machine);

	static void Update(float deltaTime);
};