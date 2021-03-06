#include "Skybox.h"

#include "../../Shaders/Shader.h"
#include "../../GraphicsCommon.h"

float skyboxVertices[] = {
	// positions          
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	-1.0f,  1.0f, -1.0f,
	1.0f,  1.0f, -1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	1.0f, -1.0f,  1.0f
};

Skybox::Skybox(const std::string identifier, const Matrix4 projmatrix,
	const Vector2 resolution, Matrix4* viewMatrix)
	: GraphicsModule(identifier, projMatrix, resolution)
{
	skyboxShader = new Shader(SHADERDIR"/Skybox/SkyboxVert.glsl", SHADERDIR"/Skybox/SkyboxFrag.glsl");
	this->viewMatrix = viewMatrix;
}

Skybox::~Skybox()
{
	delete skyboxShader;
}

void Skybox::linkShaders()
{
	skyboxShader->LinkProgram();
}

void Skybox::regenerateShaders()
{
	skyboxShader->Regenerate();
}

void Skybox::initialise()
{
	initialiseMesh();
}

void Skybox::apply()
{
	glDepthFunc(GL_LEQUAL);
	glDisable(GL_CULL_FACE);

	glUseProgram(skyboxShader->GetProgram());

	glUniformMatrix4fv(glGetUniformLocation(skyboxShader->GetProgram(),
		"viewMatrix"), 1, false, (float*)viewMatrix);
	glUniformMatrix4fv(glGetUniformLocation(skyboxShader->GetProgram(),
		"projMatrix"), 1, false, (float*)&projMatrix);

	glActiveTexture(GL_TEXTURE0);
	glUniform1i(glGetUniformLocation(skyboxShader->GetProgram(), "skybox"), 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
}

void Skybox::initialiseMesh()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices),
		&skyboxVertices, GL_STATIC_DRAW);

	//Vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
}