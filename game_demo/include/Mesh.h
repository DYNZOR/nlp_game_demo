/**
@file Mesh.h
*/

#ifndef MESH_H
#define MESH_H

#include <gl_core_4_3.hpp>
#include "glm\glm.hpp"
#include <Assimp/Importer.hpp>      // C++ importer interface
#include <Assimp/scene.h>           // Output data structure
#include <Assimp/postprocess.h>     // Post processing fla
#include <vector>
#include "Bitmap.h"
#include "Texture.h"
#include "Material.h"
#include "ShaderProgram.h"

/*! \struct Vertex
\brief A struct that stores the data contained in a single vertex 
*/
struct Vertex {
	glm::vec3 position; //!< Vertex position 
	glm::vec3 normal; //!< Vertex normal
	glm::vec2 uvs; //!< Vertex uv's

};

/*! \class Mesh
\brief Class that stores the data of a mesh (section) in a model and renders it. 
*/
class Mesh
{
public:

	Mesh(std::vector<Vertex> verticesIn/*!< Array of vertices to store */, std::vector<GLuint> indicesIn/*!< Array of indices to store */, std::vector<Texture*> texturesIn/*!< Array of textures to store */, std::vector<Material*> /*!< Array of materials to store */ materialsIn, unsigned int materialIndexIn); //!< Mesh constructor that stores the data needed to render a mesh. 

	// Mesh data
	std::vector<Vertex> vertices; //!< A vector of the mesh vertices 
	std::vector<GLuint> indices; //!< A vector of the mesh indices
	std::vector<Texture*> textures; //!< A vector of the textures in the mesh 
	std::vector<Material*> materials; //!< A vector of the materials in the mesh 

	void render(std::shared_ptr<ShaderProgram> program/*!< Shader program to use for rendering */);	//!< Renders the mesh 

	unsigned int uiMaterialIndex;

private:
	GLuint vbo; //!< Stores the vertex buffer object used for sending vertex data to the gpu
	GLuint vao; //!< Vertex array object 
	GLuint ebo; //!< Element buffer object 
	void initMesh(); //!< Sends the vertex and index data to the gpu 
};

#endif