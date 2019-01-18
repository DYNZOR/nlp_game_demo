#include "SceneModel.h"
#include "AgentStates.h"

SceneModel::SceneModel(const std::string sEntityName, const std::string sFileNameIn, 
	const glm::vec3 vPos, glm::quat qRotation, glm::vec3 vScale,
	const char* kcProgName, std::string kcAiBehaviour, glm::vec3 vPos2, float fAi2) : SceneObject(sEntityName)
{
	pModel = AssetManager::AssetManagerInstance()->getModel(sFileNameIn);

	// Setting the initial state to Idle
	m_pCurrentState = Idle_State::Instance();

	//ModelManager::ModelManagerInstance()->getModelByName(sName);
	// std::make_shared<Model>(Model(sName));


	pModel->setActiveShader(AssetManager::AssetManagerInstance()->getShaderProgram(kcProgName));

	pModel->setPosition(vPos);
	pModel->setRotation(qRotation);

	pModel->setScale(vScale);

	pModel->setBehaviour(kcAiBehaviour);
	pModel->setPos2(vPos2);
	pModel->setAi2(fAi2);
	pModel->setPos1(vPos);
	//std::cout << vPos.x << " " << vPos.y << " " << vPos.z << "  --  " << vPos2.x << " " << vPos2.y << " " << vPos2.z << std::endl;
}

SceneModel::~SceneModel()
{

}

void SceneModel::update(float dt)
{
	if (m_pCurrentState)
	{
		m_pCurrentState->Execute(this, dt);

	}
}

void SceneModel::render()
{
	pModel->render();

	//	graphics->update(*this);
}

void SceneModel::updateAI(glm::vec3 playerPos, float t)
{
	std::string behaviour = pModel->getBehaviour();
	if (behaviour == "none")
	{
		//No AI behaviour
	}
	else if (behaviour == "turret")
	{
		turnTowards(playerPos);

		//SHOOT				///TODO

	}
	else if (behaviour == "patrol")
	{
		float speed = 2.f;
		//aggro range,  xz2
		float disX = pModel->getPosition().x - playerPos.x;
		float disZ = pModel->getPosition().z - playerPos.z;
		float dist = sqrt(pow(disX, 2) + pow(disZ, 2));
		if (dist <= pModel->getAi2())
		{
			pModel->setBehaviour("chase");
		}
		if (pModel->getAiDir() == true)
		{
			turnTowards(pModel->getPos2());
			pModel->translate(-t*speed, 0.f, -t*speed);
			
			//towards pos2
			if (pModel->getPosition().x > pModel->getPos2().x - 1 &&
				pModel->getPosition().x < pModel->getPos2().x + 1 &&
				pModel->getPosition().z > pModel->getPos2().z - 1 &&
				pModel->getPosition().z < pModel->getPos2().z + 1)
			{
				pModel->setAiDir(false);
				std::cout << "TOWARDS 1" << std::endl;
			}
			
		}
		else 
		{
			turnTowards(pModel->getPos1());
			pModel->translate(-t*speed, 0.f, -t*speed);
			
			//towards pos1
			if (pModel->getPosition().x > pModel->getPos1().x - 1 &&
				pModel->getPosition().x < pModel->getPos1().x + 1 &&
				pModel->getPosition().z > pModel->getPos1().z - 1 &&
				pModel->getPosition().z < pModel->getPos1().z + 1)
			{
				pModel->setAiDir(true);
				std::cout << "TOWARDS 1" << std::endl;
			}
		}


	}
	else if (behaviour == "chase")
	{
		//speed, follow dist
		//float speed = pModel->getAi2();
		//float followDist = pModel->getPos2().x;
		float speed = 1.f;
		float followDist = pModel->getAi2()*1.5;

		turnTowards(playerPos);
		pModel->translate(-t*speed, 0.f, -t*speed);

		/*if (pModel->getAiDir())
		{
			turnTowards(playerPos);
			pModel->translate(-t*speed, 0.f, -t*speed);

			float disX = pModel->getPosition().x - pModel->getPos1().x;
			float disZ = pModel->getPosition().z - pModel->getPos1().z;
			float dist = sqrt(pow(disX, 2) + pow(disZ, 2));
			if (dist > followDist) pModel->setAiDir(false);
		}
		else
		{
			turnTowards(pModel->getPos1());
			pModel->translate(-t*speed, 0.f, -t*speed);

			if (pModel->getPosition().x > pModel->getPos2().x - 1 &&
				pModel->getPosition().x < pModel->getPos2().x + 1 &&
				pModel->getPosition().z > pModel->getPos2().z - 1 &&
				pModel->getPosition().z < pModel->getPos2().z + 1)
			{
				pModel->setAiDir(true);
				std::cout << "TO 2" << std::endl;
			}
		}*/


	}
	else if (behaviour == "move")
	{
		// xz2, speed
		float speed = pModel->getAi2();
		//aggro range,  xz2
		if (pModel->getAiDir() == true)
		{
			turnTowards(pModel->getPos2());
			pModel->translate(-t*speed, 0.f, -t*speed);

			//towards pos2
			if (pModel->getPosition().x > pModel->getPos2().x - 1 &&
				pModel->getPosition().x < pModel->getPos2().x + 1 &&
				pModel->getPosition().z > pModel->getPos2().z - 1 &&
				pModel->getPosition().z < pModel->getPos2().z + 1)
			{
				pModel->setAiDir(false);
				//std::cout << "TOWARDS 2" << std::endl;
			}

		}
		else
		{
			turnTowards(pModel->getPos1());
			pModel->translate(-t*speed, 0.f, -t*speed);

			//towards pos1
			if (pModel->getPosition().x > pModel->getPos1().x - 1 &&
				pModel->getPosition().x < pModel->getPos1().x + 1 &&
				pModel->getPosition().z > pModel->getPos1().z - 1 &&
				pModel->getPosition().z < pModel->getPos1().z + 1)
			{
				pModel->setAiDir(true);
				//std::cout << "TOWARDS 1" << std::endl;
			}
		}
	}
}


void SceneModel::turnTowards(glm::vec3 target)
{
	float turnSpeed = 0.1f;

	float disX = pModel->getPosition().x - target.x;
	float disZ = pModel->getPosition().z - target.z;
	float dist = sqrt(pow(disX, 2) + pow(disZ, 2));
	float angle = atan(disX / disZ);
	float Y = pModel->getYRot();
	pModel->rotate(-turnSpeed, 0.0, 0.0);
	/*if (angle < Y)
	{
		pModel->rotate(-turnSpeed, 0.0, 0.0);
	}
	if (angle > Y)
	{
		pModel->rotate(turnSpeed, 0.0, 0.0);
	}*/
}

void SceneModel::ChangeState(State* pNewState)
{
	//make sure both states are both valid before attempting to 
	//call their methods
	assert(m_pCurrentState && pNewState);

	//call the exit method of the existing state
	m_pCurrentState->Exit(this);

	//change state to the new state
	m_pCurrentState = pNewState;

	//call the entry method of the new state
	m_pCurrentState->Enter(this);
}
