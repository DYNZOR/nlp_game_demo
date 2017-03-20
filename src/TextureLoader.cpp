#include "TextureLoader.h"

TextureLoader::TextureLoader()
{

}

bool TextureLoader::loadTexture(std::string location, GLuint &texture, int &width, int &height)
{
	gl::GenTextures(1, &texture);
	//activat the current texture unit before binding
	gl::ActiveTexture(gl::TEXTURE0);
	//bind the texture
	gl::BindTexture(gl::TEXTURE_2D, texture);

	std::string texName = std::string(location);
	Bitmap bmp = Bitmap::bitmapFromFile(texName);

	gl::TexImage2D(gl::TEXTURE_2D, 0, gl::SRGB, bmp.width(), bmp.height(), 0, gl::RGB, gl::UNSIGNED_BYTE, bmp.pixelBuffer());
	width = bmp.width();
	height = bmp.height();
	//set the parameters for the cube map
	gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_WRAP_S, gl::CLAMP_TO_EDGE);
	gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_WRAP_T, gl::CLAMP_TO_EDGE);
	gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MAG_FILTER, gl::LINEAR);
	gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MIN_FILTER, gl::LINEAR);


	//sets the texture to the current texture object
	gl::BindTexture(gl::TEXTURE_2D, 0);
	if (texture != 0)
	{
		return true;
	}
	return false;
}