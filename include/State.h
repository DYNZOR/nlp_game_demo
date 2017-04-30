#pragma once

class SceneModel; // CHECK THIS 

class State
{
public: 

	virtual void Enter(SceneModel* SO) = 0;
	virtual void Execute(SceneModel* SO)= 0;
	virtual void Exit(SceneModel* SO) = 0;
};