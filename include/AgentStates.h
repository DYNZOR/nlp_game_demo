#ifndef AGENT_STATES_H
#define AGENT_STATES_H

#include "State.h"

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

//class Collect_State : public State
//{
//private:
//	Collect_State() {}
//
//	//copy ctor and assignment should be private
//	//Rotate_State(const Rotate_State&);
//	//Rotate_State& operator=(const Rotate_State&);
//public:
//	static Collect_State* Instance();
//
//	virtual void Enter(SceneObject* SO) override;
//
//	virtual void Execute(SceneObject* SO) override;
//
//	virtual void Exit(SceneObject* SO) override;
//};



#endif