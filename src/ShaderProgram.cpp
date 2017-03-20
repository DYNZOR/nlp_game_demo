#include "ShaderProgram.h"


#include <fstream>
#include <sstream>

ShaderProgram::ShaderProgram() // Create program object 
{
	uiProgramHandle = 0;
	bisLinked = false;
}

void ShaderProgram::loadShaderFromFile(const char* kcFileName, GLenum shaderTypeIn)
{
	//if (!fileExists(kcFileName))
	//{
	//	string message = string("Shader: ") + fileName + " not found.";
	//	throw GLSLProgramException(message);
	//}
		
	if (uiProgramHandle <= 0) {
		uiProgramHandle = gl::CreateProgram();

		if (uiProgramHandle == 0) {
			fprintf(stderr, "Unable to create shader program!");
				
		}
	}

	std::ifstream inFile(kcFileName);

	if (!inFile) {
		fprintf(stderr, "Error opening file: ");
		//exit(1);
	}

	std::stringstream code;
	code << inFile.rdbuf();
	inFile.close();

	compileShader(code.str(), kcFileName, shaderTypeIn);

}

void ShaderProgram::compileShader(const std::string& source, const char* kcFileName, GLenum shaderTypeIn)
{

	if (uiProgramHandle <= 0) {
		uiProgramHandle = gl::CreateProgram();

		if (uiProgramHandle == 0) {
			fprintf(stderr, "Unable to create shader program!");

		}
	}


	GLuint uiShaderHandle = gl::CreateShader(shaderTypeIn);

	// Load the source code into the shader object
	const GLchar* codeArray = { source.c_str() };
	gl::ShaderSource(uiShaderHandle, 1, &codeArray, NULL);

	// Compile shader
	gl::CompileShader(uiShaderHandle);

	GLint result;

	gl::GetShaderiv(uiShaderHandle, gl::COMPILE_STATUS, &result);

	// Check if compilation failed 
	if (FALSE == result) {

		// Obtain log
		GLint iLogLength = 0;
		std::string sLog;

		gl::GetShaderiv(uiShaderHandle, gl::INFO_LOG_LENGTH, &iLogLength);

		if (iLogLength > 0) {
			char * log = (char *)malloc(iLogLength);

			GLsizei written;
			gl::GetShaderInfoLog(uiShaderHandle, iLogLength, &written, log);

			sLog = log;

			free(log);
		}

		std::string logOutputMessage;

		if (kcFileName) {
			logOutputMessage = std::string(kcFileName) + ": Shader compilation failed!\n";
		}
		else {
			logOutputMessage = "Shader compilation failed!\n";
		}

		logOutputMessage += sLog;

		fprintf(stderr, logOutputMessage.c_str());

	}
	// Compilation succesfull 
	else {
		gl::AttachShader(uiProgramHandle, uiShaderHandle);
	}
}

void ShaderProgram::linkProgram()
{
	if (bisLinked) return;
	// Link the program
	if (uiProgramHandle <= 0) {
		fprintf(stderr, "Failed to link shader program!\n");

	}

	gl::LinkProgram(uiProgramHandle);

	// Check for successful linking
	GLint status;
	gl::GetProgramiv(uiProgramHandle, gl::LINK_STATUS, &status);
	if (FALSE == status) {

		GLint logLen = 0;
		std::string sLog;

		gl::GetProgramiv(uiProgramHandle, gl::INFO_LOG_LENGTH, &logLen);

		if (logLen > 0) {
			char * log = (char *)malloc(logLen);

			GLsizei written;
			gl::GetProgramInfoLog(uiProgramHandle, logLen, &written, log);

			sLog = log;

			free(log);
		}

		fprintf(stderr, sLog.c_str() ) ;
	}
	else {
		uniforms.clear();
		bisLinked = true;
	}
}


void ShaderProgram::useProgram() 
{
	if (uiProgramHandle <= 0 || !bisLinked)  {
		fprintf(stderr, "Shader has not been linked");
	}

	gl::UseProgram(uiProgramHandle);

}


GLint ShaderProgram::getUniformLocation(const char* uniformName)
{
	std::map<std::string, int>::iterator pos;
	pos = uniforms.find(uniformName);

	if (pos == uniforms.end()) {
		uniforms[uniformName] = gl::GetUniformLocation(uiProgramHandle, uniformName);
	}

	return uniforms[uniformName];
}

void ShaderProgram::setUniform(const char *name, const glm::vec3 & vecIn)
{
	GLint loc = getUniformLocation(name);
	gl::Uniform3fv(loc, 1, glm::value_ptr(vecIn));

}

void ShaderProgram::setUniform(const char *name, const glm::vec4 & vecIn)
{
	GLint loc = getUniformLocation(name);
	gl::Uniform4fv(loc, 1, glm::value_ptr(vecIn));

}
void ShaderProgram::setUniform(const char *name, const glm::mat4 & matIn)
{
	GLint loc = getUniformLocation(name);
	gl::UniformMatrix4fv(loc, 1, FALSE, glm::value_ptr(matIn));

}
void ShaderProgram::setUniform(const char *name, const glm::mat3 & matIn)
{
	GLint loc = getUniformLocation(name);
	gl::UniformMatrix3fv(loc, 1, FALSE, &matIn[0][0]);
}
void ShaderProgram::setUniform(const char *name, float val)
{
	GLint loc = getUniformLocation(name);
	gl::Uniform1f(loc, val);
}
void ShaderProgram::setUniform(const char *name, int val)
{
	GLint loc = getUniformLocation(name);
	gl::Uniform1ui(loc, val);
}
void ShaderProgram::setUniform(const char *name, bool val)
{
	int loc = getUniformLocation(name);
	gl::Uniform1i(loc, val);
}

GLuint ShaderProgram::getHandle()
{
	return uiProgramHandle;
}