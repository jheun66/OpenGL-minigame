/*
Authored by Prof. Jeong-Mo Hong, CSE Dongguk University
for Introduction to Computer Graphics, 2017 Spring
*/

#pragma once

#include <GL/glew.h> // include glew first
#include "../Geometry/TriangularSurface/StaticTriangularSurface.h"
#include <glm\glm.hpp>
#include "GL2_ShaderProgram.h"
#include "GL2_Light.h"
#include "GL2_Material.h"
#include <glm/gtx/component_wise.hpp>

class GL2_Object
{
public:
	Array1D<GLuint> vbo_;
	int num_elements_ = 0;

	glm::vec3 pos; 

	glm::vec4 light_position_ = glm::vec4(0.0f, 0.3f, 0.0f, 1.0f);
	glm::vec4 light_product_ambient_ = glm::vec4(0.1f, 0.01f, 0.01f, 1.0f);
	glm::vec4 light_product_diffuse_ = glm::vec4(1.0f, 0.1f, 0.1f, 1.0f);
	glm::vec4 light_product_specular_ = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
	float mat_shininess_ = 5.0;

	GL2_Material mat_;

	GL2_Object()
	{
	}

	~GL2_Object()
	{
		glDeleteBuffersARB(vbo_.num_elements_, vbo_.values_);
	}
	
	bool check_pos(const StaticTriangularSurface& surface, int position_number)
	{
	
		pos.x =0;
		pos.y = 0;
		pos.z = 0;
		TV sum = glm::vec3(0, 0, 0);
		for (int i = 0; i < surface.vertex_positions_.num_elements_; i++)
		{
			 sum += surface.vertex_positions_.values_[i];
		}
		
		pos.x = sum.x_ / surface.vertex_positions_.num_elements_;
		pos.y = sum.y_ / surface.vertex_positions_.num_elements_;
		pos.z = sum.z_ / surface.vertex_positions_.num_elements_;
	
		if (position_number == 0)	//up
			if (pos.y < 4.7&&pos.y > 4.3)
				return true;
			else 
				return false;
		if (position_number == 1)	//down
			if (pos.y < 2.7&&pos.y > 2.3)
				return true;
			else
				return false;
		if (position_number == 2)	//left
			if (pos.z > -3.2&&pos.z < -2.7)
				return true;
			else
				return false;
		if (position_number == 3)	//right
			if (pos.z > -5.2&&pos.z < -4.7)
				return true;
			else
				return false;
		if (position_number == 4)	//front
			if (pos.x > -1.2&&pos.x < -0.7)
				return true;
			else
				return false;
		if (position_number == 5)	//back
			if (pos.x > -3.2&&pos.x < -2.7)
				return true;
			else
				return false;
	}


	void initPhongSurface(const StaticTriangularSurface& surface, glm::vec3 position, float size)		//Y축회전, 자기 기준과 X=0,Z=0기준인가??
	{
		vbo_.init(3); // vertex, normal, connectivity
		glGenBuffers(vbo_.num_elements_, vbo_.values_);
		for (int i = 0; i < surface.vertex_positions_.num_elements_; i++)
		{
			surface.vertex_positions_.values_[i] *= size;
			surface.vertex_positions_.values_[i] += position;
		}
	
		updatePhongSurface(surface, 50);
	}



	void updatePhongSurface(const StaticTriangularSurface& surface, int num)
	{
		
		if (num==0)		//위 회전
		{
			glm::vec3 position = glm::vec3(-2, 4.5, -4);
			for (int i = 0; i < surface.vertex_positions_.num_elements_; i++) {
				surface.vertex_positions_.values_[i] -= position;
				float radius = 90.0f;
				float tsin = sin(glm::radians(radius));
				float tcos = cos(glm::radians(radius));
				float temp = surface.vertex_positions_.values_[i].x_;

				surface.vertex_positions_.values_[i].x_ = surface.vertex_positions_.values_[i].x_*tcos - surface.vertex_positions_.values_[i].z_*tsin;
				surface.vertex_positions_.values_[i].z_ = temp*tsin + surface.vertex_positions_.values_[i].z_*tcos;
				surface.vertex_positions_.values_[i] += position;
			}
		}
		if (num == 1)		//회전
		{
			glm::vec3 position = glm::vec3(-2, 4.5, -4);
			for (int i = 0; i < surface.vertex_positions_.num_elements_; i++) {
				surface.vertex_positions_.values_[i] -= position;
				float radius = -90.0f;
				float tsin = sin(glm::radians(radius));
				float tcos = cos(glm::radians(radius));
				float temp = surface.vertex_positions_.values_[i].x_;

				surface.vertex_positions_.values_[i].x_ = surface.vertex_positions_.values_[i].x_*tcos - surface.vertex_positions_.values_[i].z_*tsin;
				surface.vertex_positions_.values_[i].z_ = temp*tsin + surface.vertex_positions_.values_[i].z_*tcos;
				surface.vertex_positions_.values_[i] += position;
			}

		}
		if (num == 2)		//회전
		{
			glm::vec3 position = glm::vec3(-2, 2.5, -4);
			for (int i = 0; i < surface.vertex_positions_.num_elements_; i++) {
				surface.vertex_positions_.values_[i] -= position;
				float radius = 90.0f;
				float tsin = sin(glm::radians(radius));
				float tcos = cos(glm::radians(radius));
				float temp = surface.vertex_positions_.values_[i].x_;

				surface.vertex_positions_.values_[i].x_ = surface.vertex_positions_.values_[i].x_*tcos - surface.vertex_positions_.values_[i].z_*tsin;
				surface.vertex_positions_.values_[i].z_ = temp*tsin + surface.vertex_positions_.values_[i].z_*tcos;
				surface.vertex_positions_.values_[i] += position;
			}

		}
		if (num == 3)		//회전
		{
			glm::vec3 position = glm::vec3(-2, 2.5, -4);
			for (int i = 0; i < surface.vertex_positions_.num_elements_; i++) {
				surface.vertex_positions_.values_[i] -= position;
				float radius = -90.0f;
				float tsin = sin(glm::radians(radius));
				float tcos = cos(glm::radians(radius));
				float temp = surface.vertex_positions_.values_[i].x_;

				surface.vertex_positions_.values_[i].x_ = surface.vertex_positions_.values_[i].x_*tcos - surface.vertex_positions_.values_[i].z_*tsin;
				surface.vertex_positions_.values_[i].z_ = temp*tsin + surface.vertex_positions_.values_[i].z_*tcos;
				surface.vertex_positions_.values_[i] += position;
			}

		}
		if (num == 4)		//회전
		{
			glm::vec3 position = glm::vec3(-2, 3.5, -3);
			for (int i = 0; i < surface.vertex_positions_.num_elements_; i++) {
				surface.vertex_positions_.values_[i] -= position;
				float radius = 90.0f;
				float tsin = sin(glm::radians(radius));
				float tcos = cos(glm::radians(radius));
				float temp = surface.vertex_positions_.values_[i].x_;

				surface.vertex_positions_.values_[i].x_ = surface.vertex_positions_.values_[i].x_*tcos + surface.vertex_positions_.values_[i].y_*tsin;
				surface.vertex_positions_.values_[i].y_ = -temp*tsin + surface.vertex_positions_.values_[i].y_*tcos;
				surface.vertex_positions_.values_[i] += position;
			}

		}
		if (num == 5)		//회전
		{
			glm::vec3 position = glm::vec3(-2, 3.5, -3);
			for (int i = 0; i < surface.vertex_positions_.num_elements_; i++) {
				surface.vertex_positions_.values_[i] -= position;
				float radius = -90.0f;
				float tsin = sin(glm::radians(radius));
				float tcos = cos(glm::radians(radius));
				float temp = surface.vertex_positions_.values_[i].x_;

				surface.vertex_positions_.values_[i].x_ = surface.vertex_positions_.values_[i].x_*tcos + surface.vertex_positions_.values_[i].y_*tsin;
				surface.vertex_positions_.values_[i].y_ = -temp*tsin + surface.vertex_positions_.values_[i].y_*tcos;
				surface.vertex_positions_.values_[i] += position;
			}

		}
		if (num == 6)		//회전
		{
			glm::vec3 position = glm::vec3(-2, 3.5, -5);
			for (int i = 0; i < surface.vertex_positions_.num_elements_; i++) {
				surface.vertex_positions_.values_[i] -= position;
				float radius = 90.0f;
				float tsin = sin(glm::radians(radius));
				float tcos = cos(glm::radians(radius));
				float temp = surface.vertex_positions_.values_[i].x_;

				surface.vertex_positions_.values_[i].x_ = surface.vertex_positions_.values_[i].x_*tcos + surface.vertex_positions_.values_[i].y_*tsin;
				surface.vertex_positions_.values_[i].y_ = -temp*tsin + surface.vertex_positions_.values_[i].y_*tcos;
				surface.vertex_positions_.values_[i] += position;
			}

		}
		if (num == 7)		//회전
		{
			glm::vec3 position = glm::vec3(-2, 3.5, -5);
			for (int i = 0; i < surface.vertex_positions_.num_elements_; i++) {
				surface.vertex_positions_.values_[i] -= position;
				float radius = -90.0f;
				float tsin = sin(glm::radians(radius));
				float tcos = cos(glm::radians(radius));
				float temp = surface.vertex_positions_.values_[i].x_;

				surface.vertex_positions_.values_[i].x_ = surface.vertex_positions_.values_[i].x_*tcos + surface.vertex_positions_.values_[i].y_*tsin;
				surface.vertex_positions_.values_[i].y_ = -temp*tsin + surface.vertex_positions_.values_[i].y_*tcos;
				surface.vertex_positions_.values_[i] += position;
			}

		}
		if (num == 8)		//회전
		{
			glm::vec3 position = glm::vec3(-1, 3.5, -4);
			for (int i = 0; i < surface.vertex_positions_.num_elements_; i++) {
				surface.vertex_positions_.values_[i] -= position;
				float radius = 90.0f;
				float tsin = sin(glm::radians(radius));
				float tcos = cos(glm::radians(radius));
				float temp = surface.vertex_positions_.values_[i].y_;

				surface.vertex_positions_.values_[i].y_ = surface.vertex_positions_.values_[i].y_*tcos + surface.vertex_positions_.values_[i].z_*tsin;
				surface.vertex_positions_.values_[i].z_ = -temp*tsin + surface.vertex_positions_.values_[i].z_*tcos;
				surface.vertex_positions_.values_[i] += position;
			}

		}
		if (num == 9)		//회전
		{
			glm::vec3 position = glm::vec3(-1, 3.5, -4);
			for (int i = 0; i < surface.vertex_positions_.num_elements_; i++) {
				surface.vertex_positions_.values_[i] -= position;
				float radius = -90.0f;
				float tsin = sin(glm::radians(radius));
				float tcos = cos(glm::radians(radius));
				float temp = surface.vertex_positions_.values_[i].y_;

				surface.vertex_positions_.values_[i].y_ = surface.vertex_positions_.values_[i].y_*tcos + surface.vertex_positions_.values_[i].z_*tsin;
				surface.vertex_positions_.values_[i].z_ = -temp*tsin + surface.vertex_positions_.values_[i].z_*tcos;
				surface.vertex_positions_.values_[i] += position;
			}

		}
		if (num == 10)		//회전
		{
			glm::vec3 position = glm::vec3(-3, 3.5, -4);
			for (int i = 0; i < surface.vertex_positions_.num_elements_; i++) {
				surface.vertex_positions_.values_[i] -= position;
				float radius = 90.0f;
				float tsin = sin(glm::radians(radius));
				float tcos = cos(glm::radians(radius));
				float temp = surface.vertex_positions_.values_[i].y_;

				surface.vertex_positions_.values_[i].y_ = surface.vertex_positions_.values_[i].y_*tcos + surface.vertex_positions_.values_[i].z_*tsin;
				surface.vertex_positions_.values_[i].z_ = -temp*tsin + surface.vertex_positions_.values_[i].z_*tcos;
				surface.vertex_positions_.values_[i] += position;
			}
		}
		if (num == 11)		//회전
		{
			glm::vec3 position = glm::vec3(-3, 3.5, -4);
			for (int i = 0; i < surface.vertex_positions_.num_elements_; i++) {
				surface.vertex_positions_.values_[i] -= position;
				float radius = -90.0f;
				float tsin = sin(glm::radians(radius));
				float tcos = cos(glm::radians(radius));
				float temp = surface.vertex_positions_.values_[i].y_;

				surface.vertex_positions_.values_[i].y_ = surface.vertex_positions_.values_[i].y_*tcos + surface.vertex_positions_.values_[i].z_*tsin;
				surface.vertex_positions_.values_[i].z_ = -temp*tsin + surface.vertex_positions_.values_[i].z_*tcos;
				surface.vertex_positions_.values_[i] += position;
			}
		}


		num_elements_ = surface.triangles_.num_elements_ * 3;

		glBindBuffer(GL_ARRAY_BUFFER, vbo_[0]);
		glBufferData(GL_ARRAY_BUFFER, surface.vertex_positions_.num_elements_ * sizeof(float) * 3,
			surface.vertex_positions_.values_, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, vbo_[1]);
		glBufferData(GL_ARRAY_BUFFER, surface.vertex_normals_.num_elements_ * sizeof(float) * 3,
			surface.vertex_normals_.values_, GL_STATIC_DRAW);

		Array1D<Vector3D<unsigned int> > tri_ix;
		surface.getUnsignedIntTriangles(tri_ix);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_[2]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, tri_ix.num_elements_ * sizeof(unsigned int) * 3,
			surface.triangles_.values_, GL_STATIC_DRAW);
	}

	void drawWithShader(const GL2_ShaderProgram& program)
	{
		//glUseProgram(shader_programme);	// activate your shader!

		//TODO: use one 'lightproduct' uniform for amb, dif, and spe.
		program.sendUniform(light_position_, "light_position");
		program.sendUniform(light_product_ambient_, "light_product_ambient");
		program.sendUniform(light_product_diffuse_, "light_product_diffuse");
		program.sendUniform(light_product_specular_, "light_product_specular");
		program.sendUniform(mat_shininess_, "mat_shininess");

		// draw here
		glBindBuffer(GL_ARRAY_BUFFER, vbo_[0]);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer
		(
			0,                  // attribute 0
			3,                  // size (r, g, b)
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		glBindBuffer(GL_ARRAY_BUFFER, vbo_[1]);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer
		(
			1,                  // attribute 0
			3,                  // size (r, g, b)
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_[2]);
		glLineWidth(1);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawElements(GL_TRIANGLES, num_elements_, GL_UNSIGNED_INT, 0);
	}

	void drawPhongSurface()
	{
		glUseProgram(0);

		glEnable(GL_LIGHTING);

		glBindBuffer(GL_ARRAY_BUFFER, vbo_[0]);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo_[1]);
		glEnableClientState(GL_NORMAL_ARRAY);
		glNormalPointer(GL_FLOAT, 0, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_[2]);
		glPolygonMode(GL_FRONT, GL_LINE);
		glDrawElements(GL_TRIANGLES, num_elements_, GL_UNSIGNED_INT, 0);	

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
	}

	void applyLighting(const GL2_Light& light)
	{
		light_product_ambient_ = light.ambient_ * mat_.ambient_ + mat_.emission_;
		light_product_diffuse_ = light.diffuse_ * mat_.diffuse_;
		light_product_specular_ = light.specular_ * mat_.specular_;

		light_position_ = light.position_;
		mat_shininess_ = mat_.shininess_;
	}
};
