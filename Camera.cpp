#include "Camera.h"
#include<iostream>
Camera::Camera(glm::vec3 cameraposition, float pitch, float yaw, glm::vec3 worldup)
{
	cameraPosition = cameraposition;
	WorldUp = worldup;
	Pitch = pitch;
	Yaw = yaw;
	//Calculate the x value of the model pointing to the camera vector
	Forward.x = glm::cos(Pitch) * glm::sin(Yaw);
	//Calculate the y value of the model pointing to the camera vector
	Forward.y = glm::sin(Pitch);
	//Calculate the z value of the model pointing to the camera vector
	Forward.z = glm::cos(Pitch) * glm::cos(Yaw);
	//Camera right vector value
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	//Camera up vector value
	Up = glm::normalize(glm::cross(Right, Forward));
}

glm::mat4 Camera::GetViewMatrix()
{
	cameraPosition.y = 0;
	//Forward.y = 0.0f;
	//Calculate viewmaxtrix Camera position, model position, world up
	return glm::lookAt(cameraPosition, cameraPosition + Forward, WorldUp);
}

void Camera::ProcessMouseMovement(float deltaX, float deltaY)
{
	//Update camera pitch (radian)
	Pitch -= deltaY * SenseY;
	//Update camera yaw (radian)
	Yaw -= deltaX * SenseX;
	if (Pitch > 89.0f) {
		Pitch = 89.0f;
	}
	if (Pitch < -89.0f) {
		Pitch = -89.0f;
	}
	UpdataCameraVectors();
}

void Camera::UpdataCameraPos()
{
	if (cameraPosition.x>-17){
		cameraPosition.x = -17;
	}
	if (cameraPosition.z >-30) {
		cameraPosition.z = -30;
	}
	if (cameraPosition.z < -570) {
		cameraPosition.z = -570;
	}
	if (cameraPosition.x < -495) {
		cameraPosition.x = -495;
	}
	//Realize the camera to follow the moving direction
	cameraPosition += Forward * speedZ * 5.0f  + Right * speedX *5.0f;
}
//Get new camera position data and recalculate
void Camera::UpdataCameraVectors()
{
	//Calculate the x value of the model pointing to the camera vector
	Forward.x = glm::cos(Pitch) * glm::sin(Yaw);
	//Calculate the y value of the model pointing to the camera vector
	Forward.y = glm::sin(Pitch);
	//Calculate the z value of the model pointing to the camera vector
	Forward.z = glm::cos(Pitch) * glm::cos(Yaw);
	//Camera right vector value
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	//Camera up vector value
	Up = glm::vec3(0.0f,0.0f,0.0f);
}
