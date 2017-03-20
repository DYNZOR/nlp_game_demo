/** \file letter.h
* Header file for the letter class.
*/


#ifndef CHARATERLETTER_H
#define CHARATERLETTER_H

#include <glm/glm.hpp>
//! The letter Class
/*!
This class is a letter
*/
class letter
{
public:
	/** the texture for the letter */
	unsigned int texture;
	/** the size of the letter */
	glm::ivec2 size;
	/** the baseLineOffset of the letter */
	glm::ivec2 baseLineOffset;
	/** the distance to the next char of the letter */
	unsigned int nextChar;
};

#endif CHARATERLETTER_H