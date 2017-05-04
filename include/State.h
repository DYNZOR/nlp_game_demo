#pragma once

class SceneModel; // CHECK THIS 

class State
{

protected:

public: 
	//State() {}

	virtual void Enter(SceneModel* SO) = 0;
	virtual void Execute(SceneModel* SO, float tInterval)= 0;
	virtual void Exit(SceneModel* SO) = 0;
};