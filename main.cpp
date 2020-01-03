#pragma comment( linker, "/subsystem:windows /entry:mainCRTStartup" )
#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include <ctime>
#include<glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include"Shader.h"
#include"Camera.h"
#include"SkyBox.h"
#include"Module.h"
#include<Windows.h>

glm::mat4 modelMat = glm::mat4(1.0f);
glm::mat4 viewMat = glm::mat4(1.0f);
glm::mat4 projMat = glm::mat4(1.0f);
glm::mat4 skyViewMat = viewMat;

glm::mat4 GunModelMat = modelMat;
glm::mat4 GunViewMat = viewMat;

glm::mat4 HouseModelMat = modelMat;
glm::mat4 HouseModelMat2 = modelMat;
glm::mat4 HouseModelMat3 = modelMat;
glm::mat4 HouseModelMat4 = modelMat;
glm::mat4 AimModelMat = modelMat;
glm::mat4 AimViewMat = viewMat;

glm::mat4 HandModelMat = modelMat;
glm::mat4 HandViewMat = viewMat;
glm::mat4 rockModelMat = modelMat;

Module gun = Module();
Module hand = Module();
Module aim = Module();
Module house = Module();
Module ground = Module();
Module rock = Module();
float deltaX = 0, deltaY = 0;
bool boot = true;
bool firstBoold = false;
unsigned int bootCount = 0;
float x = 0;
float z = -300.0f;
float rockX;
float rockZ;
float rockSpeed = 0.5;
float lastX = 1024 / 2.0f;
//Record the position information of the last time in the Y direction of the mouse
float lastY = 768 / 2.0f;
//Determine whether the mouse position is the first load
bool firstMouse = true;
Camera camera(glm::vec3(-300.0f, -300.0f, 5.0f), glm::radians(0.0f), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//Mouse movement
void mouse_callback(GLFWwindow* window, double xPos, double yPos) {
	//Determine whether the mouse is loaded for the first time
	if (firstMouse == true) {
		//Mouse coordinates are camera coordinates
		lastX = xPos;
		lastY = yPos;
		//Loading the mouse is not the first time
		firstMouse = false;
	}
	//Offset of mouse movement
	
	//X-axis movement
	deltaX = xPos - lastX;
	//Move in Y direction
	deltaY = yPos - lastY;
	//The coordinates of the point on the mouse are the coordinates after the move
	lastX = xPos;
	lastY = yPos;
	//Change camera position by mouse movement
	camera.ProcessMouseMovement(deltaX, deltaY);
}

void mouse_Button_callback(GLFWwindow* window, int button, int action, int mos) {
	if (action == GLFW_PRESS) {
		switch (button) {
		case GLFW_MOUSE_BUTTON_LEFT:
			if (bootCount!=0)
			{
				firstBoold = true;
			}
			camera.ProcessMouseMovement(deltaX, deltaY-25);
			float ScreenX = 0;
			float ScreenY = 0;
			float zf = 1.0f;
			glm::vec4 posDNSF = glm::vec4(ScreenX, ScreenY, zf, 1.0);
			glm::vec4 ray_posF = glm::inverse(projMat) * posDNSF;
			glm::vec4 rayf = glm::inverse(viewMat) * ray_posF;

			if (rayf.w != 0.0){
				rayf.x /= rayf.w;
				rayf.y /= rayf.w;
				rayf.z /= rayf.w;
			}
			glm::vec3 ray_dir;
			ray_dir.x = rayf.x - camera.cameraPosition.x;
			ray_dir.y = rayf.y - camera.cameraPosition.y;
			ray_dir.z = rayf.z - camera.cameraPosition.z;
			ray_dir = glm::normalize(ray_dir);

			glm::vec4 maxs = glm::vec4(1.0f, 3.0f, 21.0f, 1.0f);
			glm::vec4 mins = glm::vec4(-1.0f, -6.0f, -4.0f, 1.0f);
			glm::vec3 ori = camera.cameraPosition;
			glm::mat4 posmat = glm::translate(modelMat, glm::vec3(rockX, 0.0f, rockZ));
			glm::vec3 max = posmat * maxs;
			glm::vec3 min = posmat * mins;
			float t;
			glm::vec3  ptOnPlane;
			if (ray_dir.x != 0) {
				if (ray_dir.x > 0) {
					t = (min.x - ori.x) / ray_dir.x;
				}else {
					t = (max.x - ori.x) / ray_dir.x;
				}if (t > 0.0f) {
					ptOnPlane = ori + ray_dir * t;
					//p>1.2&&p<-1.2&&p>-0.6&&p<0.29
					if (min.y < ptOnPlane.y && ptOnPlane.y < max.y && min.z < ptOnPlane.z && ptOnPlane.z < max.z)
					{
						bootCount++;
					}
				}
			}

			if (ray_dir.y != 0.f)
			{
				if (ray_dir.y > 0)
					t = (min.y - ori.y) / ray_dir.y;
				else
					t = (max.y - ori.y) / ray_dir.y;
				if (t > 0.f){
					ptOnPlane = ori + ray_dir * t;
					if (min.z < ptOnPlane.z && ptOnPlane.z < max.z && min.x < ptOnPlane.x && ptOnPlane.x < max.x)
					{
						bootCount++;
					}
				}
			}

			if (ray_dir.z != 0.f)
			{
				if (ray_dir.z > 0)
					t = (min.z - ori.z) / ray_dir.z;
				else
					t = (max.z - ori.z) / ray_dir.z;

				if (t > 0.f){
					ptOnPlane = ori + ray_dir * t;
					if (min.x < ptOnPlane.x && ptOnPlane.x < max.x && min.y < ptOnPlane.y && ptOnPlane.y < max.y)
					{
						bootCount++;
					}
				}
			}
			if (bootCount == 5) {
				boot = false;
			}
			break;
		}
	}
}

//Keyboard input
void processInput(GLFWwindow* window) {
	//Push out procedure when ESC is pressed
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		//Close program
		glfwSetWindowShouldClose(window, true);
	}
	//Camera advances when q is pressed
	else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		//Camera moves in the positive direction of Z axis
		camera.speedZ = 0.1f;
	}
	//Camera advances when e is pressed
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		//Camera moves in the negative Z direction
		camera.speedZ = -0.1f;
	}
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		camera.speedX = -0.1f;
	}
	//Camera advances when D is pressed
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		//Camera moves in the positive X-axis direction
		camera.speedX = 0.1f;
	}
	//When not moving
	else {
		//Camera x, y, Z moving distance is 0
		camera.speedZ = 0;
		camera.speedX = 0;
	}
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
		//Camera moves in the positive X-axis direction
		bootCount = 0;
		boot = true;
	}
}
int main() {
	//Initialize glfw
	glfwInit();
	//Confirm OpenGL version number Version:4.5
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	//Set OpenGL operation mode to core mode
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//Create a form with the size of 1024 * 768 and the name of "Module Loader(Zhuang Ma 10664074)"
	GLFWwindow* window = glfwCreateWindow(1024, 768, "CS GAME(Zhuang Ma 10664074)", NULL, NULL);
	//Determine whether the form is loaded successfully
	if (window == NULL){
		std::cout << "Window Load Failed!!" << std::endl;
		glfwTerminate();
		return -1;
	}

	//Confirm context
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//Call mouse move function
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetMouseButtonCallback(window, mouse_Button_callback);
	//Allow loading of extension entry points
	glewExperimental = true;
	//Judge whether the glue initialization is successful
	if (glewInit() != GLEW_OK) {
		printf("Init GLEW ERROR");
		glfwTerminate();
		return -1;
	}

	//Set view size
	glViewport(0, 0, 1024, 768);
	//Opening depth test
	glEnable(GL_DEPTH_TEST);
	//Enable back culling
	glEnable(GL_CULL_FACE);
	//Don't render model Bei
	glCullFace(GL_BACK);
	
	Shader* SkyBoxShader = new Shader("Shader\\VertSkybox.vert", "Shader\\FragSkybox.frag");
	SkyBox skyBox;
	Shader* myShader = new Shader("Shader\\VertexShader.vert", "Shader\\FragmentShader.frag");

	gun.Moduleload(".\\module\\MR96.obj", ".\\texture\\MR96.png");
	hand.Moduleload(".\\module\\arm.obj", ".\\texture\\arm.jpg");
	aim.Moduleload(".\\module\\aiming.obj", ".\\texture\\aiming.jpg");
	house.Moduleload(".\\module\\house1.obj", ".\\texture\\house1.png");
	ground.Moduleload(".\\module\\plane.obj", ".\\texture\\sand2.jpg");
	rock.Moduleload(".\\module\\wawa.obj", ".\\texture\\wawa.png");


	//Set the far and near surface, 0.1f in and out, 1000.0f in the distance
	projMat = glm::perspective(glm::radians(40.0f), 1024.0f / 768.0f, 0.1f, 100000.0f);

	HouseModelMat = glm::translate(HouseModelMat, glm::vec3(280.0f, 90.0f, -300.0f));
	HouseModelMat = glm::rotate(HouseModelMat, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	HouseModelMat = glm::scale(HouseModelMat, glm::vec3(0.2f, 0.2f, 0.2f));

	HouseModelMat2 = glm::translate(HouseModelMat2, glm::vec3(-260.0f, 90.0f, 280.0f));
	HouseModelMat2 = glm::scale(HouseModelMat2, glm::vec3(0.2f, 0.2f, 0.2f));

	HouseModelMat3 = glm::translate(HouseModelMat3, glm::vec3(-240.0f, 90.0f, -880.0f));
	HouseModelMat3 = glm::rotate(HouseModelMat3, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	HouseModelMat3 = glm::scale(HouseModelMat3, glm::vec3(0.2f, 0.2f, 0.2f));

	HouseModelMat4 = glm::translate(HouseModelMat4, glm::vec3(-880.0f, 90.0f, -300.0f));
	HouseModelMat4 = glm::rotate(HouseModelMat4, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	HouseModelMat4 = glm::scale(HouseModelMat4, glm::vec3(0.25f, 0.25f, 0.25f));

	AimModelMat = glm::translate(AimModelMat, glm::vec3(0.0f, 0.0f, -15.0f));
	AimModelMat = glm::rotate(AimModelMat, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	AimModelMat = glm::scale(AimModelMat, glm::vec3(0.01f, 0.01f, 0.01f));

	HandModelMat = glm::translate(HandModelMat, glm::vec3(3.0f, -3.0f, -6.0f));
	HandModelMat = glm::rotate(HandModelMat, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	HandModelMat = glm::scale(HandModelMat, glm::vec3(0.4f, 0.4f, 0.4f));
	
	GunModelMat = glm::translate(GunModelMat, glm::vec3(3.0f, -2.0f, -10.0f));
	GunModelMat = glm::rotate(GunModelMat, glm::radians(100.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	GunModelMat = glm::rotate(GunModelMat, glm::radians(5.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	GunModelMat = glm::scale(GunModelMat, glm::vec3(0.02f, 0.02f, 0.02f));

	while (!glfwWindowShouldClose(window)){
		processInput(window);
		//Form background color
		glClearColor(1.0f, 0.513f, 0.98f, 1.0f);
		//Clean screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// skybox cube
		//Check whether there are any events triggered (such as keyboard input, mouse movement, etc.)
		//Swap color buffer
		


		myShader->use();
		viewMat = camera.GetViewMatrix();
		if (boot == true) {
			srand((unsigned)time(NULL));
			if (firstBoold == true) {
				for (int i = 0; i < 100; i++)
				{
					x = -(rand() % (501 - 1));
					z = -(rand() % (501 - 1));
				}
			}else{
				x = -(rand() % (501 - 1));
				z += -0.5;
			}
			if (z < -570) {
				z = -50;
			}
			rockX = x;
			rockZ = z;
			glUniformMatrix4fv(glGetUniformLocation(myShader->ProgramID, "modelMat"), 1, GL_FALSE, glm::value_ptr(glm::translate(rockModelMat, glm::vec3(rockX, 0.0f, rockZ))));
			glUniformMatrix4fv(glGetUniformLocation(myShader->ProgramID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
			glUniformMatrix4fv(glGetUniformLocation(myShader->ProgramID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));
			rock.Draw_Module(myShader);
		}else{
			if (MessageBox(NULL, TEXT("YOU WIN!!!!! \n Continue or Exit"), "Congratulations!!!", MB_YESNO) == IDYES){
				x = -(rand() % 500) * rockSpeed;
				z = -400.0f;
				bootCount = 0;
				boot = true;
				firstBoold = false;
			}else{
				glfwSetWindowShouldClose(window, true);
			}
		}

		glUniformMatrix4fv(glGetUniformLocation(myShader->ProgramID, "modelMat"), 1, GL_FALSE, glm::value_ptr(glm::translate(modelMat, glm::vec3(0.0f, -1.0f, -30.0f))));
		glUniformMatrix4fv(glGetUniformLocation(myShader->ProgramID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
		glUniformMatrix4fv(glGetUniformLocation(myShader->ProgramID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));
		for (int i = 0; i < 60; i++)
		{
			for (int j = 0; j < 60; j++) {
				glUniformMatrix4fv(glGetUniformLocation(myShader->ProgramID, "modelMat"), 1, GL_FALSE, glm::value_ptr(glm::translate(modelMat, glm::vec3(-i * 10, -15.0f, -j * 10))));
				ground.Draw_Module(myShader);
			}
		}
		glUniformMatrix4fv(glGetUniformLocation(myShader->ProgramID, "modelMat"), 1, GL_FALSE, glm::value_ptr(HouseModelMat));
		glUniformMatrix4fv(glGetUniformLocation(myShader->ProgramID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
		glUniformMatrix4fv(glGetUniformLocation(myShader->ProgramID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));
		house.Draw_Module(myShader);

		glUniformMatrix4fv(glGetUniformLocation(myShader->ProgramID, "modelMat"), 1, GL_FALSE, glm::value_ptr(HouseModelMat2));
		house.Draw_Module(myShader);

		glUniformMatrix4fv(glGetUniformLocation(myShader->ProgramID, "modelMat"), 1, GL_FALSE, glm::value_ptr(HouseModelMat3));
		house.Draw_Module(myShader);

		glUniformMatrix4fv(glGetUniformLocation(myShader->ProgramID, "modelMat"), 1, GL_FALSE, glm::value_ptr(HouseModelMat4));
		house.Draw_Module(myShader);


		glUniformMatrix4fv(glGetUniformLocation(myShader->ProgramID, "modelMat"), 1, GL_FALSE, glm::value_ptr(GunModelMat));
		glUniformMatrix4fv(glGetUniformLocation(myShader->ProgramID, "viewMat"), 1, GL_FALSE, glm::value_ptr(GunViewMat));
		glUniformMatrix4fv(glGetUniformLocation(myShader->ProgramID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));
		gun.Draw_Module(myShader);


		glUniformMatrix4fv(glGetUniformLocation(myShader->ProgramID, "modelMat"), 1, GL_FALSE, glm::value_ptr(AimModelMat));
		glUniformMatrix4fv(glGetUniformLocation(myShader->ProgramID, "viewMat"), 1, GL_FALSE, glm::value_ptr(AimViewMat));
		glUniformMatrix4fv(glGetUniformLocation(myShader->ProgramID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));
		aim.Draw_Module(myShader);

		glUniformMatrix4fv(glGetUniformLocation(myShader->ProgramID, "modelMat"), 1, GL_FALSE, glm::value_ptr(HandModelMat));
		glUniformMatrix4fv(glGetUniformLocation(myShader->ProgramID, "viewMat"), 1, GL_FALSE, glm::value_ptr(HandViewMat));
		glUniformMatrix4fv(glGetUniformLocation(myShader->ProgramID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));
		hand.Draw_Module(myShader);

		SkyBoxShader->use();
		skyViewMat = glm::mat4(glm::mat3(camera.GetViewMatrix()));
		//skyViewMat = camera.GetViewMatrix();
		glUniformMatrix4fv(glGetUniformLocation(SkyBoxShader->ProgramID, "view"), 1, GL_FALSE, glm::value_ptr(skyViewMat));
		glUniformMatrix4fv(glGetUniformLocation(SkyBoxShader->ProgramID, "projection"), 1, GL_FALSE, glm::value_ptr(projMat));
		skyBox.Draw_SkyBox(SkyBoxShader);

		glfwSwapBuffers(window);
		glfwPollEvents();
		camera.UpdataCameraPos();
	}
	glfwTerminate();
	return 0;
}