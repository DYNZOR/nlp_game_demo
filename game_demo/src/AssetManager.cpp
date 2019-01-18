#include "AssetManager.h"

AssetManager* AssetManager::pAssetManager;

	/** sets all the bools to false for the input */
AssetManager::AssetManager() 
{ 
	pShaderManager = ShaderManager::ShaderManagerInstance();
	pModelManager = ModelManager::ModelManagerInstance(); 

}

AssetManager::~AssetManager()
{ 

}


AssetManager* AssetManager::AssetManagerInstance()
{
	if (!pAssetManager)
	{
		return pAssetManager = new AssetManager();
	}
	else {
		return pAssetManager;
	}
}
	