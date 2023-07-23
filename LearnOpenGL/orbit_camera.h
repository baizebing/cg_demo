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

#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "camera.h"

class OrbitCamera : public Camera
{
public:
	OrbitCamera(float fRadius, float fHeight);

	void ProcessKeyboard(Movement direction, float deltaTime) override;
	void ProcessMouseMovement(float fXOffset, float fYOffset, bool bConstrainPitch = true) override;

	void SetEye(const glm::vec3& vec3Eye) override;
	void SetLookAt(const glm::vec3& vec3LookAt) override;
	
private:
	float m_fRadius;

	float m_fYawParameter = 0;
};