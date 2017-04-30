#include "AgentStates.h"
#include "State.h"
#include "SceneModel.h"

#include "config.h"
#include <iostream>

// Methods for rotate state 

Rotate_State* Rotate_State::Instance()
{
	static Rotate_State instance;
	return &instance;
}

void Rotate_State::Enter(SceneModel* SO)
{
	std::cout << "Rotating: " << SO->GetDescription().m_sName << std::endl;
}

void Rotate_State::Execute(SceneModel* SO)
{
	SO->getModelHandle()->rotate(-PI / 2, 0, 0);
}

void Rotate_State::Exit(SceneModel* SO)
{
	std::cout << "Stopped Rotating: " << SO->GetDescription().m_sName << std::endl;
	SO->getModelHandle()->rotate(0, 0, 0);
}

// Methods for moving state 

// Methods for collect state 

