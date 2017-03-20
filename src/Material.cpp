#include "Material.h"

Material::Material()
{
	kA = glm::vec4(0.0, 0.0, 0.0, 0.0);	
	kD = glm::vec4(0.0, 0.0, 0.0, 0.0);	
	kE = glm::vec4(0.0, 0.0, 0.0, 0.0);	
	kS = glm::vec3(0.0, 0.0, 0.0);
	fShininess = 0.0f; 
}
