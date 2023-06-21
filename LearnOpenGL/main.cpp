#include "scene.h"
#include "gl_resource.h"

const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;
const std::string WINDOW_NAME = "LearnOpenGL";

int main()
{
	//setup with glfw & glad
	auto spGLResource = std::make_shared<GLResource>();
	spGLResource->CreateGLFWWindow(SCR_WIDTH, SCR_HEIGHT, WINDOW_NAME);
	std::cout << "Graphics: " << spGLResource->GetGPUVersion() << std::endl;

	auto spCamera = std::make_shared<Camera>(glm::vec3(0.f, 3.f, 5.f),-90.0f, -25.0f);
	auto spScene = std::make_shared<Scene>(spGLResource, spCamera);
	spScene->SetBackGround(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));

	auto spShader = std::make_shared<Shader>("../resources/shaders/model/vertex.vert", "../resources/shaders/model/fragment.frag");
	auto spBowlShader = std::make_shared<Shader>("../resources/shaders/model/bowl_vertex.vert", "../resources/shaders/model/bowl_fragment.frag");
	auto spTexture = std::make_shared<Texture>();
	// Render state
	auto spRenderState = std::make_shared<RenderState>(spShader, spTexture);
	spRenderState->SetDepthTest(true);
	spRenderState->SetDrawMode(DRAW_MODE::ELEMENT_MODE);
	spRenderState->SetPrimitiveMode(PRIMITIVE_MODE::TRIANGLES_MODE);
	// Bowl Render state
	auto spBowlRenderState = std::make_shared<RenderState>(spBowlShader, std::make_shared<Texture>());
	spBowlRenderState->SetDepthTest(true);
	spBowlRenderState->SetDrawMode(DRAW_MODE::ELEMENT_MODE);
	spBowlRenderState->SetPrimitiveMode(PRIMITIVE_MODE::TRIANGLES_MODE);

	auto spCarEntity = std::make_shared<Entity>();
	auto spBowlEntity = std::make_shared<Entity>();
	auto spCarRenderPass = std::make_shared<RenderPass>(spCarEntity, spRenderState);
	auto spBowlRenderPass = std::make_shared<RenderPass>(spBowlEntity, spBowlRenderState);
	//spCarEntity->AddMeshNode("../resources/objects/backpack/backpack.obj", spRenderState);
	spCarEntity->m_transform = std::make_shared<Transform>();
	spCarEntity->m_transform->SetModelScale(glm::vec3(0.8,0.8,0.8));
	spCarEntity->AddMeshNode("../resources/objects/intelcar/intel.obj", spRenderState);
	spBowlEntity->m_transform = std::make_shared<Transform>();
	spBowlEntity->m_transform->SetModelScale(glm::vec3(3.0,6.0,3.0));
	spBowlEntity->AddMeshNode("../resources/objects/intelcar/bowl_with_texture.obj", spBowlRenderState);

	spScene->AddRenderPass(spCarRenderPass);
	spScene->AddRenderPass(spBowlRenderPass);

	spScene->Draw();
}

