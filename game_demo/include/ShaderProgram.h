
/**
@file ShaderProgram.h
*/
#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#define RESOURCE_FILE_PATH "resources/shaders/" //!< Path to the shaders in the resources folder
#define VERT_SHADER_EXTENSION ".vert" //!< Vertex shader extension 
#define FRAG_SHADER_EXTENSION ".frag" //!< Fragment shader extension 


#include <memory>
#include <vector>
#include <map>
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtx\transform.hpp"
#include "glm\gtc\type_ptr.hpp"
#include <gl_core_4_3.hpp>

#include "Shader.h"

/*! \class ShaderProgram
\brief The shader program class that handles the loading, compiling and linking shaders to shader programs and provides a way of passing data into shaders 
*/
class ShaderProgram {
private:

	std::map<std::string, GLint> uniforms; //!< A map of all the uniforms stored in the particular shader program 

	GLint getUniformLocation(const char* uniformName); 

	GLuint uiProgramHandle; //!< Returns the handle to the shader program 
	bool bisLinked; //!< Is program linked or not 

public:
	ShaderProgram(); //!< Default constructor to create program object 


	void loadShaderFromFile(const char* kcFileName/*!< file path to shader */, GLenum shaderTypeIn /*!< Type of shader */); //!< Loads a shader from a file 
	void compileShader(const std::string& source /*!< The shader source to compile */, const char* kcFileName /*!< shader name */, GLenum shaderTypeIn /*!< type of shader */); //!< Compiles shader 
	void linkProgram(); //!< Links shader 
	void validate(); //!< Validates the shader 
	void useProgram(); //!< Makes this shader program the active shader program 

	GLuint getHandle(); //!< Returns the handle to the shader program 

	void setUniform(const char *name/*!< The name of the uniform variable */, const glm::vec3 & v /*!< Vector to pass in */); //!< Passes a vec3 into the shader program into a uniform variable  
	void setUniform(const char *name/*!< The name of the uniform variable */, const glm::vec4 & v/*!< Vector to pass in */); //!< Passes a vec4 into the shader program into a uniform variable  
	void setUniform(const char *name/*!< The name of the uniform variable */, const glm::mat4 & m/*!< Matrix to pass in */); //!< Passes a mat4 into the shader program into a uniform variable  
	void setUniform(const char *name/*!< The name of the uniform variable */, const glm::mat3 & m/*!< Matrix to pass in */); //!< Passes a mat3 into the shader program into a uniform variable  
	void setUniform(const char *name/*!< The name of the uniform variable */, float val/*!< Float to pass in */); //!< Passes a float into the shader program into a uniform variable  
	void setUniform(const char *name/*!< The name of the uniform variable */, int val/*!< Int to pass in */); //!< Passes a int into the shader program into a uniform variable  
	void setUniform(const char *name/*!< The name of the uniform variable */, bool val/*!< Bool to pass in */); //!< Passes a bool into the shader program into a uniform variable  

};

#endif