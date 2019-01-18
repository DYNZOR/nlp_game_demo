#include "AgentStates.h"
#include "State.h"
#include "SceneModel.h"

#include "config.h"
#include <iostream>

#define M_PI       3.14159265358979323846   // pi
#define ToRadian(x) (float)(((x) * M_PI / 180.0f))
#define ToDegree(x) (float)(((x) * 180.0f / M_PI))
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

	//glm::vec3 playerPos = SO->getModelHandle()->getPosition();

	//glm::vec3 normalPos = m_pLocationSO->getModelHandle()->getPos1() - playerPos;

	////float h = sqrt(pow(normalPos.x, 2) + pow(normalPos.z, 2));
	//float fTheta = atan(-normalPos.z / normalPos.x);
	////float fTheta = acos(normalPos.x / h);
	//if (m_pLocationSO->getModelHandle()->getPosition().x < 0) {
	//	SO->getModelHandle()->rotate(ToRadian(90), 0.0, 0.0);
	//}
	//else {
	//	SO->getModelHandle()->rotate(ToRadian(-90), 0.0, 0.0);

	//}
	//SO->getModelHandle()->rotate(fTheta, 0.0, 0.0);

}

void Move_State::Execute(SceneModel* SO, float tInterval)
{
	//SO->getModelHandle()->translate(tInterval* 0.8f, 0, tInterval* 0.8f);
	SO->getModelHandle()->setPosition(m_pLocationSO->getModelHandle()->getPos1());
}

void Move_State::Exit(SceneModel* SO)
{
	std::cout << "Arrived at Location: " << m_pLocationSO->GetDescription().m_sName << std::endl;

	//SO->getModelHandle()->rotate(0, 0, 0);
	//SO->ChangeState(Idle_State::Instance());

	
	//m_pLocationSO = nullptr;
}


// Methods for collect state 

Collect_State* Collect_State::Instance(std::shared_ptr<SceneModel> SO)
{
	static Collect_State instance = Collect_State(SO);
	return &instance;
}

void Collect_State::Enter(SceneModel* SO)
{
	std::cout << "Collecting: " << SO->GetDescription().m_sName << std::endl;
}

void Collect_State::Execute(SceneModel* SO, float tInterval)
{
	//SO->getModelHandle()->setPosition(m_pItemSO->getModelHandle()-;
}

void Collect_State::Exit(SceneModel* SO)
{
	std::cout << "Collected: " << m_pItemSO->GetDescription().m_sName << std::endl;
	SO->getModelHandle()->rotate(0, 0, 0);
}