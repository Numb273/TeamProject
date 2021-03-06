#pragma once

#include "../GraphicsModule.h"
#include "../../Meshes/Mesh.h"

class Camera;

class BasicGeometry : public GraphicsModule
{
public:
	BasicGeometry(const std::string identifier, const Matrix4 projmatrix,
		const Vector2 resolution, Camera* camera, std::vector<SubMesh*>* modelsInFrame);
	~BasicGeometry();

	void linkShaders() override;
	void regenerateShaders() override;

	void initialise() override;
	void apply() override;

private:
	std::vector<SubMesh*>* modelsInFrame;
	void locateUniforms() override;
	Shader* basicShader;

	Camera* camera;
};

