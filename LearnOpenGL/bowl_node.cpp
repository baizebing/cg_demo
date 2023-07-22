// Copyright 2023 Cris Bai
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//     http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "bowl_node.h"

BowlNode::BowlNode(float r, int mesh_resolution): m_fRadius(r), m_fA(3.0f)
{
	m_iMeshResolution = mesh_resolution;
	float seg = 2 / static_cast<float>(m_iMeshResolution-1);
	std::vector<Vertex> vecVertices;
	for(int i=0;i<m_iMeshResolution;i++){
		float y = -1 + i*seg;
		for(int j=0;j<m_iMeshResolution;j++){
			float x = -1 + j*seg;
			float posr = glm::distance(glm::vec2(x,y), glm::vec2(0,0));
			float z = 0;
			if(posr>m_fRadius){
				z = m_fA*powf(posr-m_fRadius,2);
			}
			Vertex v;
			v.Position = glm::vec3(x, z, y);
			v.TexCoords = glm::vec2(i*seg / 2,j*seg / 2);
			vecVertices.emplace_back(v);
		}
	}
	SetVertexs(vecVertices);

	std::vector<unsigned int> vecIndices;
	for(int i=0;i<m_iMeshResolution-1;i++){
		for(int j=0;j<m_iMeshResolution-1;j++){
			// 1st triangle
			vecIndices.emplace_back(i*m_iMeshResolution+j);
			vecIndices.emplace_back((i+1)*m_iMeshResolution+j);
			vecIndices.emplace_back((i+1)*m_iMeshResolution+j+1);
			// 2nd triangle
			vecIndices.emplace_back(i*m_iMeshResolution+j);
			vecIndices.emplace_back((i+1)*m_iMeshResolution+j+1);
			vecIndices.emplace_back(i*m_iMeshResolution+j+1);
		}
	}
	SetIndexs(vecIndices);
	SetVAOVBO();
}

BowlNode::~BowlNode()
{

}

void BowlNode::Draw()
{
	Node::Prender();
	BowlNode::Prender();
	Node::Draw();
}

void BowlNode::Prender()
{
	m_spRenderState->ApplyTexture(0);
}
