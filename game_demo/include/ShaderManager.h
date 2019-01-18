#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#define SHADERS_FILEPATH "resources/shaders/"
#define VERTEX_EXTENSION ".vert"
#define FRAGMENT_EXTENSION ".frag"


#include <gl_core_4_3.hpp>
#include <map>
#include <memory>
#include "Shader.h"
#include "VertexShader.h"
#include "FragmentShader.h"

#include "ShaderProgram.h"

class ShaderManager {

private:
	static ShaderManager * shaderManager;

	std::map <const std::string, std::shared_ptr<ShaderProgram>> mShaderPrograms;
	//std::map <const std::string, std::shared_ptr<VertexShader>> mVertShaders;
	//std::map <const std::string, std::shared_ptr<FragmentShader>> mFragShaders;
	ShaderManager();
	~ShaderManager();
public:
	static ShaderManager* ShaderManagerInstance() {
		if (!shaderManager) {
			return shaderManager = new ShaderManager(); 
		} else {
			return shaderManager;
		}
	}

	//const GLchar* getShaderSourceFromPath(const char* kcFilePath);

	std::shared_ptr<ShaderProgram> getShaderProgram(const char* kcFileName);

	void setActiveShader(const char* kcProgName);
	//std::shared_ptr<Shader> getShader(const char* kcFileName);




	// Destructor 


};

#endif