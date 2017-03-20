#include "Model.h"
#include <iostream>

Model::Model()
{

}

Model::Model(std::string sName)
{
//	vPosition = glm::vec3(0.0f, 0.0f, 0.0f);

	//setPosition(0.0f, 0.0f, 0.0f);

	//vRotation = glm::vec3(0.0f, 0.0f, 0.0f);
	//vScale = glm::vec3(1.0f);
	
	std::string modelFolder = sName.substr(0, sName.find_last_of('.'));

	modelDir = "resources/models/" + modelFolder + "/" + sName;

	//vDirection = glm::vec3(0.0, 0.0, 0.0);

	//// Initialise orientation quaternion 
	//orientation = glm::quat(1.0, 0.0, 0.0, 0.0);

	updateDirection();

	loadModel();
}

void Model::setDirectory(std::string sPath)
{
	modelDir = sPath;
}



void Model::loadModel()
{
	// Initiate importer and read model file in
	Assimp::Importer importer; 
	const aiScene * scene = importer.ReadFile(modelDir, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals /* |aiProcess_CalcTangentSpace | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType */);

	// If scene fails to load, print error message.
	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cout << "Assimp Error: " << importer.GetErrorString() << std::endl;
	}

	// Retrieve file path 
	modelDirectory = modelDir.substr(0, modelDir.find_last_of('/'));

	processNode(scene->mRootNode, scene);

}
void Model::processNode(aiNode* node, const aiScene* scene)
{
	// Process all meshes in the node 
	for (GLuint i = 0; i < node->mNumMeshes; i++) {

		aiMesh * mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}


	// Process all the node's children meshes
	for (GLuint i = 0; i < node->mNumChildren; i++) {
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Material*> materials;
	std::vector<Texture*> textures;

	if (scene->HasMeshes()) {

		// Process vertices
		for (GLuint i = 0; i < mesh->mNumVertices; i++) {

			// Defining vertex struct 
			Vertex vertex;

			// Defining temporary mesh data variables
			glm::vec3 tempPosition;
			glm::vec3 tempNormal;

			// Storing position and normal data from mesh into vertex struct
			tempPosition.x = mesh->mVertices[i].x;
			tempPosition.y = mesh->mVertices[i].y;
			tempPosition.z = mesh->mVertices[i].z;
			vertex.position = tempPosition;

			tempNormal.x = mesh->mNormals[i].x;
			tempNormal.y = mesh->mNormals[i].y;
			tempNormal.z = mesh->mNormals[i].z;
			vertex.normal = tempNormal;

			// Check to see if mesh contains texture coordinates 
			if (mesh->mTextureCoords[0]) {

				// Store UV data in vertex struct 
				glm::vec2 tempUV;
				tempUV.x = mesh->mTextureCoords[0][i].x;
				tempUV.y = mesh->mTextureCoords[0][i].y;
				vertex.uvs = tempUV;
			}
			else {
				vertex.uvs = glm::vec2(0.0f, 0.0f);
			}

			// Push populated vertex into vertices vector
			vertices.push_back(vertex);
		}

		// Process indices 
		for (GLuint i = 0; i < mesh->mNumFaces; i++) {

			// Obtain face 
			aiFace face = mesh->mFaces[i];

			// Iterate through all the indices in the face
			for (GLuint j = 0; j < face.mNumIndices; j++) {

				// Push indices onto vector 
				indices.push_back(face.mIndices[j]);
			}
		}

		if (scene->HasMaterials()) {

			//// Process materials 

			//	for (unsigned int uiMaterialNum = 0; uiMaterialNum < scene->mNumMaterials; ++uiMaterialNum) {

			//		const aiMaterial* material = scene->mMaterials[uiMaterialNum];

			//		Material* pMaterial = new Material();

			//		aiColor3D tempAmbient;
			//		material->Get(AI_MATKEY_COLOR_AMBIENT, tempAmbient);
			//		pMaterial->kA = ColourToVec4(tempAmbient);

			//		aiColor3D tempDiffuse;
			//		material->Get(AI_MATKEY_COLOR_DIFFUSE, tempDiffuse);
			//		pMaterial->kD = ColourToVec4(tempDiffuse);

			//		aiColor3D tempSpecular;
			//		material->Get(AI_MATKEY_COLOR_SPECULAR, tempSpecular);
			//		pMaterial->kS = ColourToVec3(tempSpecular);

			//		float tempShininess;
			//		material->Get(AI_MATKEY_SHININESS, tempShininess);
			//		pMaterial->fShininess = tempShininess;

			//		materials.push_back(pMaterial);
			//	}

				aiMaterial* textureMaterial = scene->mMaterials[mesh->mMaterialIndex];



				std::vector<Texture*> diffuseMaps = loadMaterialTextures(textureMaterial, aiTextureType_DIFFUSE, "texture_diffuse");
				textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

				std::vector<Texture*> specularMaps = loadMaterialTextures(textureMaterial, aiTextureType_SPECULAR, "texture_specular");
				textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

				// Load Normal maps 

				// Load Height maps 



		}

		return Mesh(vertices, indices, textures, materials, mesh->mMaterialIndex);
	}

	
}

std::vector<Texture*> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
	std::vector<Texture*> textures; 

	for (GLuint i = 0; i < mat->GetTextureCount(type); i++) {

		aiString texturePath;
		mat->GetTexture(type, i, &texturePath); 

		std::string filename = std::string(texturePath.C_Str());

		filename = modelDirectory + '/' + filename;

		Bitmap bmp = Bitmap::bitmapFromFile(filename.c_str());
		//bmp.flipVertically();

		// Change 

		Texture* texture = new Texture(bmp, gl::LINEAR_MIPMAP_LINEAR, gl::LINEAR, gl::REPEAT);
		//Texture* texture = new Texture(bmp);

		texture->type = typeName;
		texture->path = texturePath;

		textures.push_back(texture);
	}

	return textures; 
}

void Model::render()
{
	setUpMatrices(getModelMatrix());

	for (GLuint i = 0; i < meshes.size(); i++) {

		meshes[i].render(getActiveShader());
	}
}

glm::vec4 Model::ColourToVec4(aiColor3D colourIn)
{
	return glm::vec4(colourIn.r, colourIn.g, colourIn.b, 1.0);
}

glm::vec3 Model::ColourToVec3(aiColor3D colourIn)
{
	return glm::vec3(colourIn.r, colourIn.g, colourIn.b);

}

void Model::setActiveShader(std::shared_ptr<ShaderProgram> programIn)
{
	setShader(programIn);
}

void Model::setUpMatrices(glm::mat4 modelMatrix)
{
	getActiveShader()->setUniform("mModelMatrix", modelMatrix);
	//getActiveShader()->setUniform("mViewMatrix", camera.getViewMatrix());
	//getActiveShader()->setUniform("mProjectionMatrix", camera.getProjectionMatrix());

}
