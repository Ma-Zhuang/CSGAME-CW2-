# CSGAME-CW2-
CW2 ZHUANGMA(106644074)
# 3D Shooting Games

## User Interaction

After the start of the game, the characters will be generated at the center of the map, and the enemies will randomly appear in the map. The user controls the characters by mouse and keyboard.

When the player hits five enemies, the game ends. The user can choose to quit or restart the game.

***Start***

![](https://github.com/SOFT356-Genshushu/Pic/blob/master/start.PNG?raw=true)

***End***

When the user clicks the Yes button, the game starts again. After clicking the no button, the game ends and exits the program

![](https://github.com/SOFT356-Genshushu/Pic/blob/master/end.PNG?raw=true)

**keyboard** 

The keyboard mainly controls the movement of characters and the function of game restart.

The user can move the characters forward and backward by using the "W","A","S","D" button.

1. Game character moves forward when user presses "W"

   ![](https://github.com/SOFT356-Genshushu/Pic/blob/master/qina.PNG?raw=true)

2. Game character moves backward when user presses "S"

   ![](https://github.com/SOFT356-Genshushu/Pic/blob/master/hou.PNG?raw=true)

3. Game character moves left when user presses "A"

   ![](https://github.com/SOFT356-Genshushu/Pic/blob/master/zuo.PNG?raw=true)

4. Game character moves right when user presses "D"

   ![](https://github.com/SOFT356-Genshushu/Pic/blob/master/you.PNG?raw=true)

**Mouse**

The mouse is mainly used to control the movement of people's perspective and the function of shooting.

After the user moves the mouse, the corresponding angle of view will also follow the direction of mouse movement. When the user presses the left mouse button, it will be regarded as shooting, and the corresponding item angle of view will also simulate the function of sitting force after shooting by moving up.

1. When the user presses the left mouse button

   The camera's angle of view will move up to simulate the recoil after shooting

2. When the mouse moves to the left

   Player camera angle left

   ![](https://github.com/SOFT356-Genshushu/Pic/blob/master/vzuo.PNG?raw=true)

3. When the mouse moves to the right

   Player camera angle right

   ![](https://github.com/SOFT356-Genshushu/Pic/blob/master/vyou.PNG?raw=true)

4. When the mouse moves to the up

   Player camera angle up

   ![](https://github.com/SOFT356-Genshushu/Pic/blob/master/shang.PNG?raw=true)

5. When the mouse moves to the down

   Player camera angle down

   ![](https://github.com/SOFT356-Genshushu/Pic/blob/master/xia.PNG?raw=true)

## System Configuration

### GLEW

1. Right click the project solution and click the Properties button

2. Click C/C++ --->> General --->> Additional Include Directories

   ![1](https://github.com/SOFT356-Genshushu/Pic/blob/master/1.png?raw=true)

3. Click Add to import the path of GLEW Include 

   ![2](https://github.com/SOFT356-Genshushu/Pic/blob/master/2.png?raw=true)

   ![3](https://github.com/SOFT356-Genshushu/Pic/blob/master/3.png?raw=true)

4. Linker --->> General --->> Additional Library Directories

   ![4](https://github.com/SOFT356-Genshushu/Pic/blob/master/4.png?raw=true)

5. Click Add to import the path of GLEW Iib 

   ![5](https://github.com/SOFT356-Genshushu/Pic/blob/master/5.png?raw=true)

6. Linker --->> Input --->> Additional Dependencies

   ![6](https://github.com/SOFT356-Genshushu/Pic/blob/master/6.png?raw=true)

7. Input glew32s.lib

8. Input opengl32.lib

### GLFW

1. Right click the project solution and click the Properties button

2. Click C/C++ --->> General --->> Additional Include Directories

   ![1](https://github.com/SOFT356-Genshushu/Pic/blob/master/1.png?raw=true)

3. Click Add to import the path of GLFW Include 

   ![2](https://github.com/SOFT356-Genshushu/Pic/blob/master/2.png?raw=true)

   ![8](https://github.com/SOFT356-Genshushu/Pic/blob/master/8.png?raw=true)

4. Linker --->> General --->> Additional Library Directories

   ![4](https://github.com/SOFT356-Genshushu/Pic/blob/master/4.png?raw=true)

5. Click Add to import the path of GLFW Iib 

   ![7](https://github.com/SOFT356-Genshushu/Pic/blob/master/7.png?raw=true)

6. Linker --->> Input --->> Additional Dependencies

   ![6](https://github.com/SOFT356-Genshushu/Pic/blob/master/6.png?raw=true)

7. Input glfw32.lib

### GLM

1. Right click the project solution and click the Properties button

2. Click C/C++ --->> General --->> Additional Include Directories

   ![1](https://github.com/SOFT356-Genshushu/Pic/blob/master/1.png?raw=true)

3. Click Add to import the path of GLM 

   ![2](https://github.com/SOFT356-Genshushu/Pic/blob/master/2.png?raw=true)

   ![9](https://github.com/SOFT356-Genshushu/Pic/blob/master/9.png?raw=true)

### stb_image

1. Download the stb_image. h file through GitHub and download it to the project directory (https://github.com/nothings/stb/blob/master/stb_image.h）

2. Right click the project solution and select an existing item. --->>Locate the location of the stb_image. h file and click ADD --->> Click the stb_image. h file.

   ![10](https://github.com/SOFT356-Genshushu/Pic/blob/master/10.png?raw=true)
   ![11](https://github.com/SOFT356-Genshushu/Pic/blob/master/11.png?raw=true)

## Code Work flow

1. The main.cpp file is loaded first after the program runs. Three model transformation matrices are created. It is used to display and move the model in the scene. Then load the camera class and set the camera's position, rotation angle and deflection angle.
2. Secondly, the program enters into the main function and creates a form through glfw to display the model. In the main function, there are two types of callback functions, one is mouse movement, the other is mouse button response
3. The next step is to compile the shader. There are two types of shaders in this system: one is used to load the model, the other is used to load the sky box. After all shaders are compiled successfully, the model is loaded and the model position is moved.
4. Show model in render loop and listen for keyboard events
5. When the user moves the mouse, the angle of the camera will be changed according to the XY coordinate of the mouse on the screen
6. When the user presses the left mouse button, the system will calculate the bounding box of the current position of the model in the world space, and record the world space coordinates of the camera when the current button is clicked. The ray is emitted from the camera position to the far plane of the projection matrix by the way of ray. Then judge whether the current position ray intersects with the model, if intersect, judge whether the user hits the target.

## Class Diagram 

1. **Camera**

   

   ![](https://github.com/SOFT356-Genshushu/Pic/blob/master/cscamera.PNG?raw=true)

2. **Mesh**

   ![](https://github.com/SOFT356-Genshushu/Pic/blob/master/csmesh.PNG?raw=true)

3. **Module**

   ![](https://github.com/SOFT356-Genshushu/Pic/blob/master/csmodule.PNG?raw=true)

4. **Shader**

   ![](https://github.com/SOFT356-Genshushu/Pic/blob/master/csshader.PNG?raw=true)

5. **Sky Box**

   ![](https://github.com/SOFT356-Genshushu/Pic/blob/master/skybox.PNG?raw=true)

6. **Texture**

   ![](https://github.com/SOFT356-Genshushu/Pic/blob/master/sctex.PNG?raw=true)

7. **Relationship**

   ![](https://github.com/SOFT356-Genshushu/Pic/blob/master/diaoyong.PNG?raw=true)

## Realization

1. **Load model**

   In this system, the model is rendered by loading the model several times at a time, so the system memory consumption reaches the maximum value (about 192mb) when it is just running, and it will drop to about 80mb on average after the model is loaded.

   The read model files are all in obj format. By reading the obj file into the computer memory in a line by line fashion. After analyzing the file, the model vertex, normal, texture coordinate and face data are stored in the container defined in the mesh class for subsequent rendering.

   Before storage in the container, the model vertices, normals and texture coordinates will be reordered according to the face information read in each model file and then stored in the container.

   When all the above work is completed, the program will call the setupmesh function in the module class to fill in all the data of the model to VAO and VBO.

   Finally, in the rendering loop of main.cpp, we call the Draw_Module function in the module class to draw the model, and the Draw_Module function calls the Draw_Mesh function in the mesh class to draw the triangle surface of the model by reading the array.

   Of course, before rendering the model, you need to use the shader to convert the model from 3D to 2D screen. Three transformation matrices are used to realize this function. Firstly, the coordinates of the model in the world space are obtained by multiplying the model matrix and the model vertex data. Secondly, the coordinates of the model in the observation space are obtained by multiplying the observation matrix. Finally, the coordinates of the projection space and the screen are obtained by multiplying the perspective projection matrix.

2. **Load skybox**

   In main.cpp, we compile the shader corresponding to the sky box, then instantiate the skybox class to fill the sky box vertex and texture, and finally call the Draw_SkyBox function. This function is defined in the skybox class.

   In the process of filling sky box vertices and textures, because vertex information is directly defined in the class, no other calculation is required, and texture files are imported from the outside. Before filling, the address of texture image needs to be stored in a container. Then we call the loadCubemap function defined in the skybox class to read the texture image. Finally, the sky box is drawn by array

3. **Role perspective and position movement**

   Two functions are defined in the main.cpp file, namely, the mouse_callback function and the processinput function. Their role is to change the camera position and rotation angle through the keyboard or mouse.

   The mouse call function is implemented by recording the current position coordinates of the mouse and the last position coordinates. When the user moves the mouse, the current position coordinate of the mouse is subtracted from the position coordinate of the last mouse in the function to calculate the offset of the mouse position. The obtained offset is then transferred to processmousemovement function defined in camera class to reset the camera angle.

   The processinput function controls the direction of movement by listening for keyboard key events. When the user presses the "W" key, the z-direction component of the camera will add 0.1 distance. If the user presses the "s" key, the z-direction component of the camera will subtract 0.1 distance. Similarly, when the "a" and "d" keys are pressed, the component in the X direction of the camera will be increased or decreased by 0.1

4. **Random generation of target**

   ```c++
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
   ```

   Before the player hits the target, the value of the x component of the target is randomly generated by the random function. The value of the Z component is set to a fixed value. Each rendering will reduce the fixed value on the Z component, so as to achieve regular and uniform motion. If the player hits the target once, both the x-direction component and the z-direction component will be set to a random value, so as to realize the function that the target appears randomly in the scene. Finally, it is transferred to the model matrix to transform the position in the world space to realize the movement of the enemy.

   Because the system realizes the generation of random numbers through system time, only one random number is generated in the rendering cycle, and the result is the increasing trend of the generated random number display, which makes the function of random generation of enemy position impossible. Because it takes 1 to 2 seconds for the system time to get the true random number, the rendering cycle of the system executes 60 times per second. Therefore, it is necessary to generate 10 random numbers each time in the rendering convolution, so that there will be no increasing trend of random number display. (Compared with generating one random number per rendering loop, the memory cost of generating 10 random numbers per rendering loop will only increase by 1.1-1.3 MB, which can be ignored )

5. **Scene generation**

   **Ground**

   The ground is to read the ground model whose model is square once, and then call 3600 times continuously. The interval of each time is different, so a large piece of ground is rendered.

   ```c++
   for (int i = 0; i < 60; i++)
   		{
   			for (int j = 0; j < 60; j++) {
   				glUniformMatrix4fv(glGetUniformLocation(myShader->ProgramID, "modelMat"), 1, GL_FALSE, glm::value_ptr(glm::translate(modelMat, glm::vec3(-i * 10, -15.0f, -j * 10))));
   				ground.Draw_Module(myShader);
   			}
   		}
   ```

   **House**

   Because the scene is relatively simple, only four times of the same square house model is rendered repeatedly, so a closed environment rendering is realized

   ```c++
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
   ```

6. **Game end and restart**

   When the player hits the target 5 times, a window will pop up to prompt the user to win, and let the user choose whether to continue the game or exit the system.

   When the player chooses to continue the game, all target settings will be reset to zero, and the target location will be randomly generated again. If the player chooses to quit the game, the program will end directly and all forms will be closed.

   ```c++
   if (MessageBox(NULL, TEXT("YOU WIN!!!!! \n Continue or Exit"), "Congratulations!!!", MB_YESNO) == IDYES){
   				x = -(rand() % 500) * rockSpeed;
   				z = -400.0f;
   				bootCount = 0;
   				boot = true;
   				firstBoold = false;
   			}else{
   				glfwSetWindowShouldClose(window, true);
   }
   ```

   

## System Characteristics

1. Collision detection and edge detection

   **Collision detection**

   In the implementation of user shooting function, the system uses the AABB bounding box as the collision surface of the game. Whether the user hits the target is determined by the way of emitting ray to judge whether there is intersection between ray and model bounding box. Since the system belongs to the shooting game, the screen midpoint is set as the end point of the ray. The coordinates of the screen center position in the projection matrix are calculated, and a ray is emitted from the camera position as the starting point of the ray to the screen center position. Thus, the current shooting direction of the user is determined.

   When we judge whether the user hit the target, we divide the ray into three directions, and judge whether the three directions intersect with the bounding box of the model. To determine if the user has hit the target

   **Edge detection**

   In the aspect of edge detection, this system does not use the collision detection method between bounding box and bounding box. Instead, the camera position is used to determine whether the game character is outside the edge of the map. The advantage of this is that it reduces the amount of computation and memory overhead. But the disadvantage is that it is impossible to accurately judge whether the model is beyond the boundary in the complex map environment. Because the map environment of this system is relatively simple, this edge detection method is used

2. Simulated real shooting

   When the user clicks the left mouse button to realize the shooting function, the system will automatically shift the camera angle upward, so as to achieve the recoil force to simulate the real shooting and enhance the sense of game experience.

3. Game palatability

   After the user hits the target for the first shot, the target will enter the crazy mode, and the target will change from regular movement to irregular random appearance. Greatly enhances the independence of the game, thus enhancing the user's experience

