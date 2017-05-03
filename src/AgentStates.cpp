#include "AgentStates.h"
#include "State.h"
#include "SceneModel.h"

#include "config.h"
#include <iostream>

// Methods for idle state 

Idle_State* Idle_State::Instance()
{
	static Idle_State instance;
	return &instance;
}

void Idle_State::Enter(SceneModel* SO)
{
	std::cout << "Idle: " << SO->GetDescription().m_sName << std::endl;
}

void Idle_State::Execute(SceneModel* SO, float tInterval)
{
}

void Idle_State::Exit(SceneModel* SO)
{
	std::cout << "Stopped Idle: " << SO->GetDescription().m_sName << std::endl;
}

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

void Rotate_State::Execute(SceneModel* SO, float tInterval)
{
	SO->getModelHandle()->rotate(tInterval*0.1f, 0, 0);
}

void Rotate_State::Exit(SceneModel* SO)
{
	std::cout << "Stopped Rotating: " << SO->GetDescription().m_sName << std::endl;
	SO->getModelHandle()->rotate(0, 0, 0);
}

// Methods for moving state 

Move_State* Move_State::Instance(std::shared_ptr<SceneModel> SO)
{
	static Move_State instance = Move_State(SO);
	return &instance;
}

void Move_State::Enter(SceneModel* SO)
{
	std::cout << "Moving: " << SO->GetDescription().m_sName << std::endl;
}

void Move_State::Execute(SceneModel* SO, float tInterval)
{
	SO->getModelHandle()->rotate(tInterval*0.1f, 0, 0);
}

void Move_State::Exit(SceneModel* SO)
{
	std::cout << "Stopped Rotating: " << SO->GetDescription().m_sName << std::endl;
	SO->getModelHandle()->rotate(0, 0, 0);
}


// Methods for collect state 

