/*
Authored by Prof. Jeong-Mo Hong, CSE Dongguk University
for Introduction to Computer Graphics, 2017 Spring
*/

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/GLU.h>
#include <GL/freeglut.h>
#include <cstring>
#include <stdlib.h>		  // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <iostream>
#include "math.h"
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <glm/gtc/quaternion.hpp> 
#include <glm/gtx/quaternion.hpp>
#include "Geometry/TriangularSurface/StaticTriangularSurface.h"
#include "GL2/GL2_Object.h"
#include "GL2/GL2_World.h"
#include "GL2/GL2_Light.h"
#include "GL2/GL2_Material.h"

#include "ParticleSystem.h"
#include "BMPImage.h"

int width_window = 640;
int height_window = 480;

GL2_World gl_world;

//기본 설정
glm::vec3 up(0.0f, 1.0f, 0.0f);	//realworld의 Up 벡터

glm::vec3 cameraPos(3.0f, 1.0f, 1.0f);			//카메라 위치
glm::vec3 cameraTarget(2.0f, 0.8f, 1.0f);		//카메라방향을 위한 타겟
glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);	 //카메라 방향
glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection)); //카메라의 오른쪽 방향
glm::vec3 cameraUp = glm::normalize(glm::cross(cameraDirection, cameraRight));//카메라의 위쪽 방향
glm::vec3 cameraFront = glm::normalize(glm::cross(cameraUp, cameraRight));	//카메라의 정면 방향
glm::vec3 dif_cameraFront = glm::vec3(0);	//카메라의 정면 방향

float lastX = 320, lastY = 240;		//640x480 크기 기준 원점

bool firstMouse = true;
bool start_move = false;

bool mouse_move = false;

float pitch = 90.0f;
float yaw = -90.0f;
float dif_yaw = 0.0f;


bool w = false;
bool s = false;
bool a = false;
bool d = false;
bool space = false;


bool up_ = false;
bool down_ = false;
bool left_ = false;
bool right_ = false;
bool front_ = false;
bool back_ = false;
bool up_r = false;
bool down_r = false;
bool left_r = false;
bool right_r = false;
bool front_r = false;
bool back_r = false;

bool clear = false;


	


glm::vec3 v;


void process_key(glm::vec3 &cameraPos, glm::vec3 v)
{
	if (w||a)
	{
		cameraPos += v * 0.08f;
	}
	else if (s || d)
	{
		cameraPos -= v * 0.08f;
	}
	else if (space)
	{
		cameraPos += v * 0.08f;
		if(cameraPos.y > 15.0f)
			cameraPos.y = 15.0f;
	}

	if (cameraPos.y > 1.0)
	{
		cameraPos.y -= 0.05f;
	}
	if (!clear) {
		if (cameraPos.x > 15.0)
		{
			cameraPos.x -= 0.5f;
		}
		if (cameraPos.x < -15.0)
		{
			cameraPos.x += 0.5f;
		}
		if (cameraPos.z > 15.0)
		{
			cameraPos.z -= 0.5f;
		}
		if (cameraPos.z < -15.0)
		{
			cameraPos.z+= 0.5f;
		}
	}
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		//forward
		v= cameraFront;	
		v.y = 0;
		w = true;
	}
	else if (key == GLFW_KEY_W && action == GLFW_RELEASE)
	{
		w = false;
	}

	 if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		//backward
		v= cameraFront;
		v.y =0;
		s = true;
	}
	 else if (key == GLFW_KEY_S && action == GLFW_RELEASE)
	 {
		 s = false;
	 }

	 if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{
		//left
		cameraRight= glm::normalize(glm::cross(up, cameraFront));	//update
		v=cameraRight;
		v.y =0;
		a = true;
	}
	 else if (key == GLFW_KEY_A && action == GLFW_RELEASE) {
		 a = false;
	 }
	 if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		//right
		cameraRight = glm::normalize(glm::cross(up, cameraFront));
		v = cameraRight;
		v.y = 0;
		d = true;
	}
	 else if (key == GLFW_KEY_D && action == GLFW_RELEASE)
	 {
		 d = false;
	 }

	 if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	 {
		 v = glm::normalize(cameraUp);
		 v.x = 0;
		 v.z = 0;
		 space = true;
	 }
	 else if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE) {
		 space = false;
	 }


	 if (key == GLFW_KEY_R && action == GLFW_PRESS)
	 {
		 //upside
		 up_ = true;
	 }
	 if (key == GLFW_KEY_F && action == GLFW_PRESS)
	 {
		 //upside reverse
		 up_r = true;
	 }
	 if (key == GLFW_KEY_T && action == GLFW_PRESS)
	 {
		 down_ = true;
	 }
	 if (key == GLFW_KEY_G && action == GLFW_PRESS)
	 {
		
		 down_r = true;
	 }
	 if (key == GLFW_KEY_Y && action == GLFW_PRESS)
	 {
		 left_ = true;
	 }
	 if (key == GLFW_KEY_H && action == GLFW_PRESS)
	 {
		
		 left_r = true;
	 }
	 if (key == GLFW_KEY_U && action == GLFW_PRESS)
	 {
		
		 right_ = true;

	 }
	 if (key == GLFW_KEY_J && action == GLFW_PRESS)
	 {
		 
		 right_r = true;
	 }
	 if (key == GLFW_KEY_I && action == GLFW_PRESS)
	 {
		 front_ = true;
	 }
	 if (key == GLFW_KEY_K && action == GLFW_PRESS)
	 {
		 front_r = true;
	 }
	 if (key == GLFW_KEY_O && action == GLFW_PRESS)
	 {
		 back_ = true;
	 }
	 if (key == GLFW_KEY_L && action == GLFW_PRESS)
	 {
		 back_r = true;
	 }

}


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	gl_world.camera_.UpdateDolly(yoffset);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		if (start_move == false)
			start_move = true;
		else
			start_move = false;
	}
}


void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	mouse_move = true;
	//기존 값과 차이 마우스를 얼마 돌린지 알수있습니다.
	float xoffset = xpos - lastX;	
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;
	float sensitivity = 0.5f;	//민감도
	xoffset *= sensitivity;
	yoffset *= sensitivity;
		
	yaw += xoffset;
	pitch += yoffset;
	dif_yaw = xoffset;
	//올려다보고 내려다 볼수 있는 각도를 정해줍니다. 
	if (pitch > 59.0f)			
		pitch = 59.0f;
	if (pitch < -90.0f)
		pitch = -90.0f;

	glm::vec3 temp_cameraFront = cameraFront;
	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);		//front방향의 정규화
	dif_cameraFront = cameraFront - temp_cameraFront;

}

int main(void)
{
	GLFWwindow *window = nullptr;

	/* Initialize the library */
	if (!glfwInit()) return -1;

	glfwWindowHint(GLFW_SAMPLES, 32);

	// window resolution
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	width_window = mode->width * 0.8f;
	height_window = mode->height * 0.8f;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width_window, height_window, "Hello World", NULL, NULL);

	if (!window) {
		glfwTerminate();
		return -1;
	}

	// callbacks here
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);

	glfwSetKeyCallback(window, key_callback);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	glClearColor(0, 0, 0, 1); // while background

	printf("%s\n", glGetString(GL_VERSION));

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	const float aspect = (float)width / (float)height;
	glViewport(0, 0, width, height);
	glOrtho(-1.2*aspect, 1.2*aspect, -1.2, 1.2, -100.0, 100.0);
	gluLookAt(0.1, 0.1, 0.1, 0.0, 0.0, 0.0, 0, 1, 0);//camera takes care of it

	const float zNear = 0.001, zFar = 100.0, fov = 45.0;			// UI
	gl_world.camera_.Resize(width, height, fov, zNear, zFar);
	gl_world.initShaders();

//	glEnable(GL_MULTISAMPLE);


	ParticleSystem ps;


	StaticTriangularSurface surface;		//player
	StaticTriangularSurface surface2;		//땅
	



	StaticTriangularSurface surface_box[27];		//상자

	surface.readObj("tesser.obj", true, true);
	surface2.readObj("Box.obj", true, true);
	



	for (int i = 0;i < 27;i++)
	{
		surface_box[i].readObj("Box.obj", true, true);
	}

	GL2_Object gl_obj;
	glm::vec3 pos = cameraPos;
	pos.y -= 0.3f;
	gl_obj.initPhongSurface(surface, pos,1);

	GL2_Object gl_obj2;
	glm::vec3 pos2 = glm::vec3(0, -50, 0);
	gl_obj2.initPhongSurface(surface2, pos2,100);



	GL2_Object gl_obj_box[27];
	glm::vec3 pos_box[27];
	for (int i = 0;i < 27;i++)
	{
		
		if (i < 3) {
			pos_box[i] = glm::vec3(-3 + i, 2.5, -3);
			gl_obj_box[i].pos = pos_box[i];
			gl_obj_box[i].initPhongSurface(surface_box[i], pos_box[i], 1);
		}
		if (i>=3&&i < 6) {
			pos_box[i] = glm::vec3(-3 + i-3, 2.5+1, -3);
			gl_obj_box[i].pos = pos_box[i];
			gl_obj_box[i].initPhongSurface(surface_box[i], pos_box[i], 1);
		}
		if (i>=6&&i < 9) {
			pos_box[i] = glm::vec3(-3 + i - 6, 2.5 + 2, -3);
			gl_obj_box[i].pos = pos_box[i];
			gl_obj_box[i].initPhongSurface(surface_box[i], pos_box[i], 1);
		}

		if (i>=9 && i <12) {
			pos_box[i] = glm::vec3(-3 + i - 9, 2.5, -4);
			gl_obj_box[i].pos = pos_box[i];
			gl_obj_box[i].initPhongSurface(surface_box[i], pos_box[i], 1);
		}
		if (i>=12 && i <15) {
			pos_box[i] = glm::vec3(-3 + i - 12, 2.5 +1, -4);
			gl_obj_box[i].pos = pos_box[i];
			gl_obj_box[i].initPhongSurface(surface_box[i], pos_box[i], 1);
		}
		if (i>=15 && i <18) {
			pos_box[i] = glm::vec3(-3 + i - 15, 2.5 +2, -4);
			gl_obj_box[i].pos = pos_box[i];
			gl_obj_box[i].initPhongSurface(surface_box[i], pos_box[i], 1);
		}

		if (i>=18 && i <21) {
			pos_box[i] = glm::vec3(-3 + i - 18, 2.5, -5);
			gl_obj_box[i].pos = pos_box[i];
			gl_obj_box[i].initPhongSurface(surface_box[i], pos_box[i], 1);
		}
		if (i>=21 && i <24) {
			pos_box[i] = glm::vec3(-3 + i - 21, 2.5 +1, -5);
			gl_obj_box[i].pos = pos_box[i];
			gl_obj_box[i].initPhongSurface(surface_box[i], pos_box[i], 1);
		}
		if (i>=24 && i <27) {
			pos_box[i] = glm::vec3(-3 + i - 24, 2.5 +2, -5);
			gl_obj_box[i].pos = pos_box[i];
			gl_obj_box[i].initPhongSurface(surface_box[i], pos_box[i], 1);
		}

	}


	for (int i = 0;i < 27;i++)
	{
		
		if ((i >= 18 && i <27)&&(i != 22)||(i==4)) {
			gl_obj_box[i].mat_.setRed();
		}
		else 
			gl_obj_box[i].mat_.setGold();
	}

	gl_obj.mat_.ambient_ = glm::vec4(0.05f, 0.05f, 0.0f, 1.0f);
	gl_obj.mat_.diffuse_ = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
	gl_obj.mat_.specular_ = glm::vec4(0.7f, 0.7f, 0.7f, 1.0f);
	gl_obj.mat_.emission_=glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	gl_obj.mat_.shininess_ = 1.0f;

	gl_obj2.mat_.ambient_ = glm::vec4(0.05f, 0.05f, 0.05f, 1.0f);
	gl_obj2.mat_.diffuse_ = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
	gl_obj2.mat_.specular_ = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	gl_obj2.mat_.emission_ = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	gl_obj2.mat_.shininess_ = 1.0f;

	
	// depth test
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
	glDisable(GL_COLOR_MATERIAL);

	glLoadIdentity();

	GL2_Light light;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		if (start_move) {//마우스 우클릭
			//카메라 따라다니기
			glm::vec3 temp = cameraPos;
			process_key(cameraPos, v);
			glm::vec3 dif = cameraPos - temp;
			for (int i = 0; i < surface.vertex_positions_.num_elements_; i++) {
				surface.vertex_positions_[i] = glm::mat4(1) 
					*glm::translate(glm::vec3(dif))
					*glm::vec4(surface.vertex_positions_[i].x_,
						surface.vertex_positions_[i].y_,
						surface.vertex_positions_[i].z_,
						1.0f);
			}
			//카메라 따라 회전
			for (int i = 0; i < surface.vertex_positions_.num_elements_; i++) {
				surface.vertex_positions_[i] = glm::mat4(1)
					*glm::translate(cameraPos)
					*glm::mat4(glm::vec4(cos(glm::radians(dif_yaw)),0,sin(glm::radians(dif_yaw)),0),
						glm::vec4(0, 1, 0, 0),
						glm::vec4(-sin(glm::radians(dif_yaw)), 0, cos(glm::radians(dif_yaw)), 0),
						glm::vec4(0, 0, 0, 1)
						)
					*glm::translate(-cameraPos)
					*glm::vec4(surface.vertex_positions_[i].x_, 
						surface.vertex_positions_[i].y_,
						surface.vertex_positions_[i].z_,
						1.0f);
			}
			dif_yaw = 0.0f;
		}

		ps.advanceOneTimeStep(0.001f);
		if (!clear)
		{
			gl_obj.updatePhongSurface(surface, 50);
		}
		gl_world.camera_.ContinueRotation();

		glm::mat4 vp = gl_world.camera_.projection_*glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);


		for (int i = 0;i < 27;i++) {
			if (up_)
			{
				if (gl_obj_box[i].check_pos(surface_box[i], 0))
				{
					gl_obj_box[i].updatePhongSurface(surface_box[i],0);
				}
			}
			if (up_r)
			{
				if (gl_obj_box[i].check_pos(surface_box[i], 0))
				{
					gl_obj_box[i].updatePhongSurface(surface_box[i], 1);
				}

			}
			if (down_)
			{
				if (gl_obj_box[i].check_pos(surface_box[i], 1))
				{
					gl_obj_box[i].updatePhongSurface(surface_box[i], 2);
				}

			}
			if (down_r)
			{
				if (gl_obj_box[i].check_pos(surface_box[i], 1))
				{
					gl_obj_box[i].updatePhongSurface(surface_box[i], 3);
				}
			}
			if (left_)
			{
				if (gl_obj_box[i].check_pos(surface_box[i], 2))
				{
					gl_obj_box[i].updatePhongSurface(surface_box[i], 4);
				}
			}
			if (left_r)
			{
				if (gl_obj_box[i].check_pos(surface_box[i], 2))
				{
					gl_obj_box[i].updatePhongSurface(surface_box[i], 5);
				}
			}
			if (right_)
			{
				if (gl_obj_box[i].check_pos(surface_box[i], 3))
				{
					gl_obj_box[i].updatePhongSurface(surface_box[i], 6);
				}
			}
			if (right_r)
			{
				if (gl_obj_box[i].check_pos(surface_box[i], 3))
				{
					gl_obj_box[i].updatePhongSurface(surface_box[i], 7);
				}
			}
			if (front_)
			{
				if (gl_obj_box[i].check_pos(surface_box[i], 4))
				{
					gl_obj_box[i].updatePhongSurface(surface_box[i], 8);
				}
			}
			if (front_r)
			{
				if (gl_obj_box[i].check_pos(surface_box[i], 4))
				{
					gl_obj_box[i].updatePhongSurface(surface_box[i], 9);
				}
			}
			if (back_)
			{
				if (gl_obj_box[i].check_pos(surface_box[i], 5))
				{
					gl_obj_box[i].updatePhongSurface(surface_box[i], 10);
				}
			}
			if (back_r)
			{
				if (gl_obj_box[i].check_pos(surface_box[i], 5))
				{
					gl_obj_box[i].updatePhongSurface(surface_box[i], 11);
				}
			}
		}

		up_ = false;
		up_r = false;
		down_ = false;
		down_r = false;
		left_ = false;
		left_r = false;
		right_ = false;
		right_r = false;
		front_ = false;
		front_r = false;
		back_ = false;
		back_r = false;

		//clear cheak
		int count = 0;
		for (int i = 18;i < 27;i++)
		{
			if (gl_obj_box[i].check_pos(surface_box[i], 2))
			{
				count++;
			}
		}
		if (count == 8)
			clear = true;
		//


		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(gl_world.shaders_.program_id_);

		gl_world.shaders_.sendUniform(vp, "mvp");

		//gl_obj.drawPhongSurface();
		gl_obj.applyLighting(light);
		gl_obj.drawWithShader(gl_world.shaders_);

		gl_obj2.applyLighting(light);
		gl_obj2.drawWithShader(gl_world.shaders_);


		for (int i = 0;i < 27;i++)
		{
			gl_obj_box[i].applyLighting(light);
			gl_obj_box[i].drawWithShader(gl_world.shaders_);
		}

		glUseProgram(0);

		// Old-style rendering

		glLoadMatrixf(&vp[0][0]);

		glLineWidth(2);
		gl_world.drawAxes();

		// draw particles
		glDisable(GL_LIGHTING);

		glPointSize(5.0f);
		glBegin(GL_POINTS);

		for (int p = 0; p < ps.particles_.size(); ++p)
		{
			const TV3 color1 = TV3(1.0f, 1.0f, 1.0f), color2 = TV3(0.0, 0.0, 1.0f);
			const float alpha = ps.particles_[p].vel_.getMagnitude() * 0.5f;
			const TV3 blenced_color = alpha * color1 + (1.0f - alpha) * color2;
			glColor3fv(blenced_color.values_);
			glVertex3fv(ps.particles_[p].pos_.values_);
		}

		glEnd();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		//std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	glfwTerminate();

	return 0;
}

