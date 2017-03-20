#include "Mesh.h"
#include <sstream>

Mesh::Mesh(std::vector<Vertex> verticesIn, std::vector<GLuint> indicesIn, std::vector<Texture*> texturesIn, std::vector<Material*> materialsIn, unsigned int materialIndexIn)
{
	vertices = verticesIn;
	indices = indicesIn;
	textures = texturesIn;
	materials = materialsIn;

	uiMaterialIndex = materialIndexIn;

	initMesh();
}

void Mesh::initMesh()
{
	// Generate vertex array and buffer objects
	gl::GenVertexArrays(1, &vao);
	gl::GenBuffers(1, &vbo);
	gl::GenBuffers(1, &ebo);

	gl::BindVertexArray(vao);

	gl::BindBuffer(gl::ARRAY_BUFFER, vbo);
	gl::BufferData(gl::ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], gl::STATIC_DRAW);

	gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, ebo);
	gl::BufferData(gl::ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], gl::STATIC_DRAW);

	// Vertex positions
	gl::EnableVertexAttribArray(0);
	gl::VertexAttribPointer(0, 3, gl::FLOAT, FALSE, sizeof(Vertex), (GLvoid*)0);

	// Vertex Normals
	gl::EnableVertexAttribArray(1);
	gl::VertexAttribPointer(1, 3, gl::FLOAT, FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));

	// Vertex Texture Coords
	gl::EnableVertexAttribArray(2);
	gl::VertexAttribPointer(2, 2, gl::FLOAT, FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, uvs));

	gl::BindVertexArray(0);
}

void Mesh::render(std::shared_ptr<ShaderProgram> program)
{

	GLuint diffuseNr = 1;
	GLuint specularNr = 1;

	for (GLuint i = 0; i < textures.size(); i++)
	{
		gl::ActiveTexture(gl::TEXTURE0 + i); // Activate proper texture unit before binding

		// Retrieve texture number (the N in diffuse_textureN)
		std::stringstream ss;
		std::string number;
		std::string name = textures[i]->type;

		if (name == "texture_diffuse")
		{
			ss << diffuseNr++;	

		} else if (name == "texture_specular") {

			ss << specularNr++; 
		}
		number = ss.str();

		gl::Uniform1f(gl::GetUniformLocation(program->getHandle(), (name + number).c_str()), i);
		gl::BindTexture(gl::TEXTURE_2D, textures[i]->object());
	}

	gl::ActiveTexture(gl::TEXTURE0);


	program->setUniform("material.Shininess", 16.0f);

	program->setUniform("material.Ka", glm::vec3(0.0f, 0.0f, 0.0f));
	program->setUniform("material.Kd", glm::vec3(1.0f, 1.0f, 1.0f));

	program->setUniform("material.Ks", glm::vec3(0.00f, 0.00f, 0.00f));

	// Draw mesh
	gl::BindVertexArray(vao);
	gl::DrawElements(gl::TRIANGLES, indices.size(), gl::UNSIGNED_INT, 0);
	gl::BindVertexArray(0);


}