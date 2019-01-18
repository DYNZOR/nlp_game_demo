//#include <iostream>
//#include <glm/gtc/matrix_transform.hpp>
//#include <ft2build.h>
//#include FT_FREETYPE_H 
//
//#include "textRender.h"
//
//textRenderer::textRenderer()
//{
//	// Configure VAO/VBO for texture quads
//	gl::GenVertexArrays(1, &textVAO);
//	gl::BindVertexArray(textVAO);
//	
//	gl::GenBuffers(2, handle);
//	
//	gl::BindBuffer(gl::ARRAY_BUFFER, handle[0]);
//	gl::BufferData(gl::ARRAY_BUFFER, sizeof(float) * 12, NULL, gl::DYNAMIC_DRAW);
//	gl::VertexAttribPointer(0, 2, gl::FLOAT, FALSE, 0, NULL);
//	gl::EnableVertexAttribArray(0);
//
//	gl::BindBuffer(gl::ARRAY_BUFFER, handle[1]);
//	gl::BufferData(gl::ARRAY_BUFFER, sizeof(float) * 12, NULL, gl::DYNAMIC_DRAW);
//	gl::VertexAttribPointer(1, 2, gl::FLOAT, FALSE, 0, NULL);
//	gl::EnableVertexAttribArray(1);
//	
//	//gl::BindBuffer(gl::ARRAY_BUFFER, 0);
//	gl::BindVertexArray(0);
//	AssetManager::AssetManagerInstance()->getShaderProgram("text");
//}
//
//textRenderer* textRenderer::getInstance()
//{
//	static textRenderer *theInstance = new textRenderer();
//	return theInstance;
//}
//
//
//void textRenderer::Load(std::string fontPath, GLuint fontSize)
//{
//	// First clear the previously loaded Characters
//	chars.clear();
//	// Then initialize and load the FreeType library
//	FT_Library libary;
//	FT_Face face;
//
//	int error;
//	error = FT_Init_FreeType(&libary);
//	if (error)
//	{
//		std::cout << "Error failed to load libary file check path" << std::endl;
//	}
//	// Load font as face
//	error = FT_New_Face(libary, fontPath.c_str(), 0, &face);
//	if (error == FT_Err_Unknown_File_Format)
//	{
//		std::cout << "Error failed to load font face check file Format not supported" << std::endl;
//	}
//	else if (error)
//	{
//		std::cout << "Error failed to load font face check file check filepath" << std::endl;
//	}
//
//	error = FT_Set_Pixel_Sizes(face, fontSize, 0);
//	if (error)
//	{
//		std::cout << "pixel size unsupported" << std::endl;
//	}
//
//	// Disable byte-alignment restriction
//	gl::PixelStorei(gl::UNPACK_ALIGNMENT, 1);
//	// Then for the first 128 ASCII characters
//	for (GLubyte i = 0; i < 128; i++)
//	{
//		// Load character glyph 
//		if (FT_Load_Char(face, i, FT_LOAD_RENDER))
//		{
//			std::cout << "Failed to load Glyph check if out of bounds" << std::endl;
//		}
//		// Generate texture
//		GLuint texture;
//		gl::GenTextures(1, &texture);
//		gl::BindTexture(gl::TEXTURE_2D, texture);
//		gl::TexImage2D(gl::TEXTURE_2D, 0, gl::RED, face->glyph->bitmap.width, face->glyph->bitmap.rows,
//							0, gl::RED, gl::UNSIGNED_BYTE, face->glyph->bitmap.buffer);
//		// Set texture options
//		gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_WRAP_S, gl::CLAMP_TO_EDGE);
//		gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_WRAP_T, gl::CLAMP_TO_EDGE);
//		gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MIN_FILTER, gl::LINEAR);
//		gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MAG_FILTER, gl::LINEAR);
//
//		// Now store character in the map
//		letter let;
//		let.texture = texture;
//		let.size = glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows);
//		let.baseLineOffset = glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top);
//		let.nextChar = face->glyph->advance.x;
//
//		chars[i] = let;
//	}
//	//clean up resources
//	gl::BindTexture(gl::TEXTURE_2D, 0);
//	FT_Done_Face(face);
//	FT_Done_FreeType(libary);
//}
//void textRenderer::loadMatrix(glm::vec3 color)
//{
//
//	glm::mat4 projection = glm::ortho(0.0f, 400.f, 0.0f, 400.f);
//	AssetManager::AssetManagerInstance()->getShaderProgram("text")->setUniform("p", projection);
//
//	glm::mat4 model = glm::mat4(1) *glm::translate(glm::vec3(0, 0, 1));
//	AssetManager::AssetManagerInstance()->getShaderProgram("text")->setUniform("m", model);
//	AssetManager::AssetManagerInstance()->getShaderProgram("text")->setUniform("color", color);
//
//}
//
//void textRenderer::getTextSize(std::string text, int &width, int &height)
//{
//	std::string::const_iterator c;
//	for (c = text.begin(); c != text.end(); c++)
//	{
//		letter charater = chars[*c];
//		width += charater.size.x;
//		height += charater.size.y;
//	}
//}
//
//void textRenderer::RenderText(std::string text, glm::vec2 position, GLfloat scale, glm::vec3 color)
//{
//	AssetManager::AssetManagerInstance()->getShaderManager()->setActiveShader("text");
//	loadMatrix(color);
//	// Activate corresponding render state	
//	gl::ActiveTexture(gl::TEXTURE0);
//	gl::BindVertexArray(textVAO);
//
//	// Iterate through all characters
//	std::string::const_iterator c;
//	for (c = text.begin(); c != text.end(); c++)
//	{
//		letter charater = chars[*c];
//
//		GLfloat xpos = position.x + charater.baseLineOffset.x * scale;
//		GLfloat ypos = position.y - (charater.size.y - charater.baseLineOffset.y) * scale;
//
//		GLfloat w = charater.size.x * scale;
//		GLfloat h = charater.size.y * scale;
//		// Update VBO for each character
//
//		GLfloat vertices[6][2] = {
//			{ xpos, ypos + h },
//			{ xpos, ypos },
//			{ xpos + w, ypos },
//
//			{ xpos, ypos + h },
//			{ xpos + w, ypos },
//			{ xpos + w, ypos + h}
//		};
//
//		GLfloat uvdata[6][2] = {
//			{ 0.0, 0.0 },
//			{ 0.0, 1.0 },
//			{ 1.0, 1.0 },
//
//			{ 0.0, 0.0 },
//			{ 1.0, 1.0 },
//			{ 1.0, 0.0 }
//		};
//
//
//		// Render glyph texture over quad
//		gl::BindTexture(gl::TEXTURE_2D, charater.texture);
//		// Update content of VBO memory
//		gl::BindBuffer(gl::ARRAY_BUFFER, handle[0]);
//		gl::BufferSubData(gl::ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData
//
//		gl::BindBuffer(gl::ARRAY_BUFFER, handle[1]);
//		gl::BufferSubData(gl::ARRAY_BUFFER, 0, sizeof(uvdata), uvdata); // Be sure to use glBufferSubData and not glBufferData
//		gl::DrawArrays(gl::TRIANGLES, 0, 6);
//		// Now advance cursors for next glyph
//		position.x += (charater.nextChar >> 6) * scale; // Bitshift by 6 to get value in pixels (1/64th times 2^6 = 64)
//	}
//	gl::BindVertexArray(0);
//	gl::BindTexture(gl::TEXTURE_2D, 0);
//}