/**
@file CubeMap.h
*/
#ifndef CUBEMAP_H
#define CUBEMAP_H

#define CUBEMAPRESOURCEPATH "resources/cube_map/" //!< The path to the cube maps 

#include <gl_core_4_3.hpp>
#include "Drawable.h"
#include "Texture.h"
#include <vector>

/*! \class CubeMap
\brief The cube map class which sets up an environment map 
*/
class CubeMap : public Drawable {
private:



	GLuint vboHandles[2];	//!< Handles that store vbos
	GLuint vaoHandle;	//!< Handle for vertex array object
	GLsizei elementsSize;	//!< Stores the size of the index array

	std::vector<GLuint> targets; //!< An array of 6 texture targets for each face of the cube 
	std::vector<const char*> suffixes; //!< An array of 6 suffixes that define the texture direction  


	GLuint textureID;	//!< Texture handle

	std::string sName;	//!< Name of cube map
	std::string sDirectory;	//!< Stores the directory to the cube map textures

	void setUpMatrices(glm::mat4 modelMatrix);

public:
	CubeMap(); //!< Default constructor 
	CubeMap(const std::string& ksCubeMap/*!< String of the cube map name */); //!< Constructor sets up the data needed to load the cube map

	void loadCubeMap();	//!< Loads a cube map into opengl and sets up the textures 

	void render();	//!< Renders cube map

	void setActiveShader(std::shared_ptr<ShaderProgram> programIn);

	GLuint getHandle();	//!< Returns a texture handle 


};

#endif