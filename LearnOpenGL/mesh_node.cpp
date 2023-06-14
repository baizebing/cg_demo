#include "mesh_node.h"
MeshNode::MeshNode()
{

}

MeshNode::~MeshNode()
{

}

void MeshNode::Prender()
{
	m_spRenderState->ApplyMaterial(m_vecDiffuseColor);
}

void MeshNode::Draw()
{
	Node::Prender();
	MeshNode::Prender();
	Node::Draw();
}

void MeshNode::ProcessMesh(aiMesh* pMesh, const aiScene* pScene,const std::string& strPath)
{
	std::vector<Vertex> vecVertices;
	for (unsigned int i = 0; i < pMesh->mNumVertices; i++)
	{
		Vertex vertex;
		vertex.Position = glm::vec3(pMesh->mVertices[i].x, pMesh->mVertices[i].y, pMesh->mVertices[i].z);
		if (pMesh->HasNormals())
		{
			vertex.Normal = glm::vec3(pMesh->mNormals[i].x, pMesh->mNormals[i].y, pMesh->mNormals[i].z);
		}
		if (pMesh->mTextureCoords[0])
		{
			vertex.TexCoords = glm::vec2(pMesh->mTextureCoords[0][i].x, pMesh->mTextureCoords[0][i].y);
			vertex.Tangent = glm::vec3(pMesh->mTangents[i].x, pMesh->mTangents[i].y, pMesh->mTangents[i].z);
			vertex.Bitangent = glm::vec3(pMesh->mBitangents[i].x, pMesh->mBitangents[i].y, pMesh->mBitangents[i].z);
		}
		vecVertices.emplace_back(vertex);
	}
	SetVertexs(vecVertices);

	std::vector<unsigned int> vecIndices;
	for (unsigned int i = 0; i < pMesh->mNumFaces; i++)
	{
		aiFace aiFace = pMesh->mFaces[i];
		for (unsigned j = 0; j < aiFace.mNumIndices; j++)
		{
			vecIndices.emplace_back(aiFace.mIndices[j]);
		}
	}
	SetIndexs(vecIndices);

	std::string sDirectory = strPath.substr(0, strPath.find_last_of('/'));
	auto& spTexture = m_spRenderState->GetTexture();
	aiMaterial* aiMaterial = pScene->mMaterials[pMesh->mMaterialIndex];
	LoadMaterialTextures(spTexture, aiMaterial, aiTextureType_DIFFUSE, TextureType::DIFFUSE, sDirectory);
	LoadMaterialTextures(spTexture, aiMaterial, aiTextureType_SPECULAR, TextureType::SPECULAR, sDirectory);
	LoadMaterialTextures(spTexture, aiMaterial, aiTextureType_HEIGHT, TextureType::NORMAL, sDirectory);
	LoadMaterialTextures(spTexture, aiMaterial, aiTextureType_AMBIENT, TextureType::HEIGHT, sDirectory);

	LoadMaterialColor(aiMaterial, m_vecDiffuseColor, m_vecSpecularColor, m_vecAmbientColor, m_vecEmissiveColor);
	SetVAOVBO();
}

void MeshNode::LoadMaterialTextures(std::shared_ptr<Texture>&spTexture, aiMaterial* aiMat,
	aiTextureType aiTexture, TextureType eTextureType, const std::string& strPath)
{
	for (unsigned int i = 0; i < aiMat->GetTextureCount(aiTexture); i++)
	{
		aiString path;
		aiMat->GetTexture(aiTexture, i,&path);
		std::string sPath = strPath + "/" + path.C_Str();
		bool skip(false);
		for (unsigned int j = 0; j < spTexture->GetTexures().size(); j++)
		{
			if (std::strcmp(spTexture->GetTexures()[j].sPath.data(), sPath.c_str()) == 0)
			{
				skip = true;
				break;
			}
		}
		if (!skip)
		{
			spTexture->AddTexture(sPath.c_str(), eTextureType, true);
		}
	}
}

void MeshNode::LoadMaterialColor(aiMaterial* aiMat, glm::vec4& diffuse, glm::vec4& specular, glm::vec4& ambient, glm::vec4& emissive)
{
	aiColor4D defaultColor = {1.0f,1.0f, 1.0f, 1.0f};
	aiColor4D matColor;
	auto SetColor = [](aiColor4D in, glm::vec4& color) {
		color.r = in.r;
		color.g = in.g;
		color.b = in.b;
		color.a = in.a;
	};
	if (AI_SUCCESS != aiGetMaterialColor(aiMat, AI_MATKEY_COLOR_DIFFUSE, &matColor)) {
		matColor = defaultColor;
	}
	SetColor(matColor, diffuse);
	if (AI_SUCCESS != aiGetMaterialColor(aiMat, AI_MATKEY_COLOR_SPECULAR, &matColor)) {
		matColor = defaultColor;
	}
	SetColor(matColor, specular);
	if (AI_SUCCESS != aiGetMaterialColor(aiMat, AI_MATKEY_COLOR_AMBIENT, &matColor)) {
		matColor = defaultColor;
	}
	SetColor(matColor, ambient);
	if (AI_SUCCESS != aiGetMaterialColor(aiMat, AI_MATKEY_COLOR_EMISSIVE, &matColor)) {
		matColor = defaultColor;
	}
	SetColor(matColor, emissive);	
}