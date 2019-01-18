/**
@file Drawable.h
*/

#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "ShaderProgram.h"
/*! \class Drawable
\brief An interface for all objects that render to the screen. 
*/
class Drawable
{
protected:

	std::shared_ptr<ShaderProgram> pShaderProgram;

public:
	Drawable() { /*setActiveShader(); */ }
	~Drawable() {}

	virtual void setUpMatrices(glm::mat4 modelMatrix) = 0;

	//virtual void setShaderProgram(std::shared_ptr<ShaderProgram> program);

	virtual void render() = 0; //!< Pure virtual function for rendering using a shader program

	virtual void setActiveShader(std::shared_ptr<ShaderProgram> programIn) { }

	void setShader(std::shared_ptr<ShaderProgram> programIn) { pShaderProgram = programIn;  }

	std::shared_ptr<ShaderProgram> getActiveShader() { return pShaderProgram;  }
};

#endif // DRAWABLE_H
