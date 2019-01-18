#include "ShaderManager.h"

ShaderManager * ShaderManager::shaderManager;

ShaderManager::ShaderManager()
{

}
ShaderManager::~ShaderManager()
{

}


//const GLchar* ShaderManager::getShaderSourceFromPath(const char* kcFilePath)
//{
//
//}

std::shared_ptr<ShaderProgram> ShaderManager::getShaderProgram(const char* kcFileName)
{
	std::shared_ptr<ShaderProgram> pShaderProgram = mShaderPrograms[kcFileName];

	if (!pShaderProgram)
	{
		pShaderProgram = std::make_shared <ShaderProgram>();

		const std::string vertexShaderPath = SHADERS_FILEPATH + std::string(kcFileName) + VERTEX_EXTENSION;
		const std::string fragmentShaderPath = SHADERS_FILEPATH + std::string(kcFileName) + FRAGMENT_EXTENSION;

		pShaderProgram->loadShaderFromFile(vertexShaderPath.c_str(), gl::VERTEX_SHADER);
		pShaderProgram->loadShaderFromFile(fragmentShaderPath.c_str(), gl::FRAGMENT_SHADER);
		pShaderProgram->linkProgram();
		//pShaderProgram->useProgram();

		mShaderPrograms[kcFileName] = pShaderProgram;

		return pShaderProgram;

	}
	else {
		return pShaderProgram;
	}
}

void ShaderManager::setActiveShader(const char* kcProgName)
{
	mShaderPrograms[kcProgName]->useProgram();
}

