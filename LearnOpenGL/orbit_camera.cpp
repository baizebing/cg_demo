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

#include "orbit_camera.h"
#include <algorithm>
#include <iostream>

OrbitCamera::OrbitCamera(float fRadius, float fHeight) :
	m_fRadius(fRadius), Camera::Camera(glm::vec3(fRadius, fHeight, 0.f),-180,-25)
{
	m_fYaw = -180.f;
	m_fPitch = -25;
	m_fYawParameter = 0;
	UpdateCameraVectors();
}

void OrbitCamera::ProcessKeyboard(Movement direction, float deltaTime)
{
	Camera::ProcessKeyboard(direction, deltaTime);
	m_fRadius = glm::distance(glm::vec2(m_vec3Eye.x, m_vec3Eye.z), glm::vec2(0));
	m_fYawParameter = atan2(m_vec3Eye.z, m_vec3Eye.x) * m_fRadius;
}

void OrbitCamera::ProcessMouseMovement(float fXOffset, float fYOffset, bool bConstrainPitch/* = true*/)
{
	float fOffsetX = fXOffset * m_fMouseSensitivity;
	float fOffsetY = fYOffset * m_fMouseSensitivity;

	m_fYawParameter += fOffsetX;
	float theta = m_fYawParameter / m_fRadius;
	m_vec3Eye.x = m_fRadius * cos(theta);
	m_vec3Eye.z = m_fRadius * sin(theta);

	m_fYaw = atan2(-m_vec3Eye.z, -m_vec3Eye.x)*180*glm::one_over_pi<float>();
	m_fPitch += fOffsetY;
	m_fPitch = bConstrainPitch ? std::clamp(m_fPitch, -89.0f, 89.0f) : m_fPitch;

	UpdateCameraVectors();
}


void OrbitCamera::SetEye(const glm::vec3& vec3Eye)
{
    m_fRadius = glm::distance(vec3Eye, glm::vec3(0.f, vec3Eye.y, 0.f));
    m_fYawParameter = m_fRadius * atan2(m_vec3Eye.z, m_vec3Eye.x);
	m_vec3Eye = vec3Eye;
}

void OrbitCamera::SetLookAt(const glm::vec3& vec3LookAt)
{
	m_vec3LookAt = glm::vec3(0.f,vec3LookAt.y,0.f);
}
