#pragma once
#include "node.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class MeshNode :public Node
{
public:
	MeshNode();
	~MeshNode();
	void ProcessMesh(aiMesh* pMesh, const aiScene* pScene, const std::string& strPath);
	void Prender() override;
	void Draw() override;

	// material color
	glm::vec4 m_vecDiffuseColor;
	glm::vec4 m_vecSpecularColor;
	glm::vec4 m_vecAmbientColor;
	glm::vec4 m_vecEmissiveColor;
private:
	void LoadMaterialTextures(std::shared_ptr<Texture>&spTexture, aiMaterial* aiMat,
		aiTextureType aiTexture, TextureType eTextureType, const std::string& strPath);
	void LoadMaterialColor(aiMaterial* aiMat, glm::vec4& diffuse, glm::vec4& specular, glm::vec4& ambient, glm::vec4& emissive);
};