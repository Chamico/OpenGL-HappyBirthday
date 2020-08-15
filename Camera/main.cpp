#include <iostream>


#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>



#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <ctime>

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

#include <D:/MyProject/OpenGL/OpenGL Settings/OpenGL Settings/packages/irrKlang-64bit-1.6.0/include/irrKlang.h>
#pragma comment(lib, "D:/MyProject/OpenGL/OpenGL Settings/OpenGL Settings/packages/irrKlang-64bit-1.6.0/lib/Winx64-visualStudio/irrKlang.lib")
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")


#include "Camera.h"
#include "Shader.h"


using std::cin;
using std::cout;
using std::endl;
using namespace irrklang;
//相关自定义的方法
void ProcessInput(GLFWwindow *window);


unsigned int indices[] = {
	0, 1, 2,
	2, 3, 0
};


const float xRate = 4.0f;
const float yRate = 2.8f;
const float zRate = 2.0f;

// 自定义的 24 个顶点位置
glm::vec3 cubePositions[] = {
  glm::vec3(0.0f * xRate,  0.0f * yRate,  0.5f * zRate),	// 1

  glm::vec3(-0.5f * xRate,  0.5f * yRate,  0.15f * zRate),	// 2
  glm::vec3(0.5f * xRate,  0.5f * yRate,  0.15f * zRate),	// 3

  glm::vec3(-0.3f * xRate,  -0.7f * yRate,  0.25f * zRate),	// 4
  glm::vec3(0.0f * xRate,  -0.9f * yRate,  0.25f * zRate),	// 5
  glm::vec3(0.3f * xRate,  -0.7f * yRate,  0.25f * zRate),	// 6

  glm::vec3(0.0f * xRate,  1.0f * yRate,  -0.65f * zRate),	// 7
  glm::vec3(0.4f * xRate,  1.33f * yRate,  -0.75f * zRate),	// 8
  glm::vec3(0.8f * xRate,  1.66f * yRate,  -0.85f * zRate),	// 9
  glm::vec3(1.2f * xRate,  1.99f * yRate,  -1.0f * zRate),	// 10
  glm::vec3(1.6f * xRate,  1.33f * yRate,  -0.75f * zRate),	// 11
  glm::vec3(1.9f * xRate,  0.9f * yRate,  -0.5f * zRate),	// 12
  glm::vec3(1.5f * xRate,  0.1f * yRate,  -0.25f * zRate),	// 13
  glm::vec3(1.1f * xRate,  -0.6f * yRate,  0.4f * zRate),	// 14
  glm::vec3(0.5f * xRate,  -1.2f * yRate,  0.7f * zRate),	// 15
  glm::vec3(0.0f * xRate,  -1.5f * yRate,  1.0f * zRate),	// 16

  glm::vec3(-0.5f * xRate,  -1.2f * yRate,  0.7f * zRate),	// 17
  glm::vec3(-1.1f * xRate,  -0.6f * yRate,  0.4f * zRate),	// 18
  glm::vec3(-1.5f * xRate,  0.1f * yRate,  -0.25f * zRate),	// 19
  glm::vec3(-1.9f * xRate,  0.9f * yRate,  -0.5f * zRate),	// 20
  glm::vec3(-1.6f * xRate,  1.33f * yRate,  -0.75f * zRate),// 21
  glm::vec3(-1.2f * xRate,  1.99f * yRate,  -1.0f * zRate),	// 22
  glm::vec3(-0.8f * xRate,  1.66f * yRate,  -0.85f * zRate),// 23
  glm::vec3(-0.4f * xRate,  1.33f * yRate,  -0.75f * zRate) // 24

  
};


// EBO 需要的 索引位置 信息
// 应该是代表 6 个面的 组合方式
float vertices[] = {

	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};


void   Delay(int   time)//time*1000为秒数 
{
	clock_t   now = clock();
	while (clock() - now < time);
}


// 程序中使用了两个 while 循环，为了表示两个不同的动态过程
// 因为整体逻辑结构比较简单，故没做封装
int main(int argc, char* argv[]) {
	

	// 播放《生日快乐》
	// 仅需要执行一次便可一直循环播放
	ISoundEngine* engine = createIrrKlangDevice();
	if (!engine) {
		cout << "false" << endl;
		return 0;
	}
	// engine->play2D("song.wav", true);

	bool flag = true;	

	glfwInit();		// 初始化 glfw 函数库
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);		// 使用版本号为 3.3 的 glfw 库
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);		// 配置 OpenGL 属性

	// 创建 GLFW 窗口对象
	// 窗口大小（宽、高）   标题
	// 窗口的图标不好设置，尝试了 N 种方法也失败了
	GLFWwindow* window = glfwCreateWindow(1200, 900, "Happy birthday to my dear Danni", NULL, NULL);
	if (window == NULL) {
		cout << "Open window failed." << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glewExperimental = true;		// 根据需要设定的，没有为什么，问就是 glew 规定的

	if (glewInit() != GLEW_OK) {
		cout << "glew init failed" << endl;
		glfwTerminate();
		return -1;
	}

	//左下角起始坐标（0，0）
	//宽高的像素单位长度（1200，900）
	glViewport(0,0, 1200, 900);


	// 一些小技巧
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_FRONT);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	Shader* myShaer = new Shader("vertexSource.txt", "fragmentSource.txt");
	
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);		//产生一个 VAO
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);	//产生一个 VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//将数据传输至 VBO 缓冲区
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(6);

	glVertexAttribPointer(8, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(8);

	unsigned int TexBufferA;
	glGenTextures(1, &TexBufferA);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TexBufferA);

	

	int width, height, nrChannel;
	stbi_set_flip_vertically_on_load(true);

	unsigned int TexBufferB;
	glGenTextures(1, &TexBufferB);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, TexBufferB);

	// 打开一张图像
	unsigned char* data2 = stbi_load("picture1.png", &width, &height, &nrChannel, 0);
	if (data2) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		cout << "load image2 failed" << endl;
	}
	stbi_image_free(data2);

	Camera camera(glm::vec3(0.0f, 0.0f, 15.0f), glm::radians(0.0f), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 modelMat = glm::mat4(1.0f);
	modelMat = glm::rotate(modelMat, glm::radians(-45.0f), glm::vec3(0, 0, 1.0f));
	glm::mat4 viewMat = glm::mat4(1.0f);
	viewMat = glm::translate(viewMat, glm::vec3(0, 0, -3.0f));
	viewMat = camera.GetViewMatrix();
	glm::mat4 projMat = glm::mat4(1.0f);
	projMat = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

	// 都是一些位置和角度参数，通过调整此参数，产生移动和旋转等效果
	float objectAngle = 0.0f;
	float projectAngle = 0.005f;
	float viewStep = -60.0f;

	int count = 0;

	float cameraPositon = 100;
	float r = 242.0f;
	float g = 156.0f;
	float b = 177.0f;
	while (!glfwWindowShouldClose(window) && flag){

		ProcessInput(window);

		
		glClearColor((r) / 255.0f, (g) / 255.0f, (b) / 255.0f, 1.0f);
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, TexBufferB);
		glBindVertexArray(VAO);

		

		viewMat = camera.GetViewMatrix();

		camera.SetCameraPosition(glm::vec3(0.0f, 0.0f, cameraPositon));

		viewStep += 0.04;
		cameraPositon -= 0.005;
		//r -= 0.0003;
		g -= 0.01;
		b += 0.0023;
		if (cameraPositon <= 15) {
			cameraPositon = 15;
			flag = false;
		}

		for (int i = 0; i < 24; ++i) {

			

			if (viewStep >= 0) {
				viewStep = 0;
				
			}

			glm::mat4 modelMat2 = glm::mat4(1.0f);
			modelMat2 = glm::translate(modelMat2, cubePositions[i]);


			viewMat = glm::rotate(viewMat, glm::radians(viewStep), glm::vec3(0, 0, 1.0f));
			
			myShaer->Use();

			glUniform1i(glGetUniformLocation(myShaer->ID, "ourFace"), 3);
			glUniformMatrix4fv(glGetUniformLocation(myShaer->ID, "modelMat2"), 1, GL_FALSE, glm::value_ptr(modelMat2));
			glUniformMatrix4fv(glGetUniformLocation(myShaer->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
			glUniformMatrix4fv(glGetUniformLocation(myShaer->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();

	}


	bool rFlag = true;
	bool gFlag = true;
	bool bFlag = true;



	r = 224.0;
	g = 102.0f;
	b = 188.0f;


	while (!glfwWindowShouldClose(window)) {

		ProcessInput(window);

		if (r < 234 && rFlag) {
			r += 0.02;
		}
		else {
			r -= 0.02;
			rFlag = false;
			if (r <= 214) {
				rFlag = true;
			}
		}

		if (g <= 122 && gFlag) {
			g += 0.04;
		}
		else {
			g -= 0.04;
			gFlag = false;
			if (g <= 82) {
				gFlag = true;
			}
		}

		if (b <= 208 && bFlag) {
			b += 0.04;
		}
		else {
			b -= 0.04;
			bFlag = false;
			if (b <= 168) {
				bFlag = true;
			}
		}


		glClearColor(r/ 255.0f, g / 255.0f, b / 255.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, TexBufferB);
		glBindVertexArray(VAO);

		

		cameraPositon -= 0.001;
		count++;
		objectAngle += 0.05f;
		viewStep += 0.02;

		for (int i = 0; i < 24; ++i) {

			if (cameraPositon <= 3.4) {
				cameraPositon = 3.4;
			}

			if (objectAngle >= 360.0f) {
				objectAngle = 0;
			}

			if (projectAngle >= 360.0f) {
				projectAngle = 0.0f;
			}

			if (viewStep >= 0) {
				viewStep = 0;
			}

			glm::mat4 modelMat2 = glm::mat4(1.0f);
			modelMat2 = glm::translate(modelMat2, cubePositions[i]);

			modelMat2 = glm::rotate(modelMat2, glm::radians(objectAngle), glm::vec3(2, 10.0f, 5.0f));

			viewMat = glm::translate(viewMat, glm::vec3(0, 0, 0.0f));
			viewMat = camera.GetViewMatrix();
			camera.SetCameraPosition(glm::vec3(0.0f, 0.0f, cameraPositon));

			
			myShaer->Use();


			glUniform1i(glGetUniformLocation(myShaer->ID, "ourTexture"), 0);
			glUniform1i(glGetUniformLocation(myShaer->ID, "ourFace"), 3);
			glUniformMatrix4fv(glGetUniformLocation(myShaer->ID, "modelMat2"), 1, GL_FALSE, glm::value_ptr(modelMat2));
			glUniformMatrix4fv(glGetUniformLocation(myShaer->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
			glUniformMatrix4fv(glGetUniformLocation(myShaer->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));


			glDrawArrays(GL_TRIANGLES, 0, 36);
		}




		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	glfwTerminate();

	return 0;
}


//接受键盘的输入操作
//按下Esc 关闭 GLFW 窗口
void ProcessInput(GLFWwindow* window) {

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

}