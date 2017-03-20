/**
@file Material.h
*/
#ifndef MATERIAL_H
#define MATERIAL_H

#include "glm\glm.hpp"
/*! \class Material
\brief Material class that stores the ambient, diffuse and
specular colour values of a material. 
*/
class Material {

private:


public: 
	Material();	//!< Default constructor that sets all values to 0

	glm::vec4 kA;	//!< Ambient 
	glm::vec4 kD;	//!< Diffuse
	glm::vec4 kE;	//!< Emissive
	glm::vec3 kS;	//!< Specular
	float fShininess;	//!< Shininess


};

#endif