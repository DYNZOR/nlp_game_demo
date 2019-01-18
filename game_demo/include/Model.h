/**
@file Model.h
*/
#ifndef MODEL_H
#define MODEL_H

#define GLM_FORCE_RADIANS


#include <gl_core_4_3.hpp>
#include "glm\glm.hpp"
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing fla
#include <vector>
#include "Drawable.h"
#include "Transformable.h"
#include "Mesh.h"
#include "Bitmap.h"
#include "Texture.h"
#include "ArtifIntelligent.h"

/*! \class Model
\brief A model class that handles the loading of a model using Assimp and inherits from the Drawable and Transformable interfaces
*/
class Model : public Drawable, public Transformable, public ArtifIntelligent
{

private:

	std::vector<Mesh> meshes; //!< Vector of Mesh objects that together make the model


	std::string modelDir; //!< Full diretory to model file 
	std::string modelDirectory; //!< Model directory used for loading textures

	void loadModel(  /*!< String to the path of the model */); //!< Loads a model from a path using assimp. 

	void processNode(aiNode* node /*!< The assimp node to process  */, const aiScene* scene /*!< The assimp scene the process */); //!< Obtains all the meshes from the assimp scene and processes them into the Mesh class
	Mesh processMesh(aiMesh* mesh /*!< The assimp mesh to process  */, const aiScene* scene/*!< The scene class to obtain data from  */);

	std::vector<Texture*> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
		std::string samplerName /*!< The sampler name in the shader in which to pass texture */); //!< Loads all textures of a particular type on the assimp material into a vector of textures and returns it. 

	glm::vec4 ColourToVec4(aiColor3D colourIn); //!< 
	glm::vec3 ColourToVec3(aiColor3D colourIn);

	void setUpMatrices(glm::mat4 modelMatrix);

	//Model& operator=(const Model& kObj); //!< Override and set the = operator to private to disable copying

public:
	Model(); //!< Default constructor for model 
	Model(std::string sName/*!< File path where model resides */); //!< Model construcor initializes the posirion, rotation, scale and loads model from file path 

	void setActiveShader(std::shared_ptr<ShaderProgram> programIn);

	void setDirectory(std::string sPath);



	void render();	//!< Renders the model




};







#endif 