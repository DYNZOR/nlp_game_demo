#ifndef AGENT_STATES_H
#define AGENT_STATES_H

#include "State.h"
#include <memory>

class SceneModel;

class Idle_State : public State
{
private:
	Idle_State() {}

	//copy ctor and assignment should be private
	//Rotate_State(const Rotate_State&);
	//Rotate_State& operator=(const Rotate_State&);
public:
	static Idle_State* Instance();

	void Enter(SceneModel* SO) override;

	void Execute(SceneModel* SO, float tInterval) override;

	void Exit(SceneModel* SO) override;
};

class Rotate_State : public State
{
private:
	Rotate_State() {}

	//copy ctor and assignment should be private
	//Rotate_State(const Rotate_State&);
	//Rotate_State& operator=(const Rotate_State&);
public:
	static Rotate_State* Instance();

	void Enter(SceneModel* SO) override;

	void Execute(SceneModel* SO, float tInterval) override;

	void Exit(SceneModel* SO) override;
};

class Move_State : public State
{
private:
	Move_State(std::shared_ptr<SceneModel> pLocationSO) { m_pLocationSO = pLocationSO; }

	std::shared_ptr<SceneModel> m_pLocationSO;

public:
	static Move_State* Instance(std::shared_ptr<SceneModel> pLocationSO);

	virtual void Enter(SceneModel* SO) override;

	virtual void Execute(SceneModel* SO, float tInterval) override;

	virtual void Exit(SceneModel* SO) override;
};

//class Collect_State : public State
//{
//private:
//	Collect_State() { pModel = SO; }
//
//	SceneModel* pModel;
//
//public:
//	static Collect_State* Instance(SceneModel* SO);
//
//	virtual void Enter(SceneModel* SO) override;
//
//	virtual void Execute(SceneModel* SO, float tInterval) override;
//
//	virtual void Exit(SceneModel* SO) override;
//};



#endif