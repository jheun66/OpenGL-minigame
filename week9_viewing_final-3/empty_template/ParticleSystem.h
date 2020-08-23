#pragma once

#include <vector>
#include "DataStructure/Vector3D.h"

class Particle
{
public:
	Vector3D<float> pos_, vel_;

	//Particle(const Particle& p)
	//{
	//	pos_ = p.pos_;
	//	vel_ = p.vel_;
	//}
};

class Sphere
{
public:
	Vector3D<float> center_;
	float radius_;

	float getSignedDistance(const Vector3D<float>& pos)
	{
		return (pos - center_).getMagnitude() - radius_;
	}

	Vector3D<float> getNormal(const Vector3D<float>& pos)
	{
		return (pos - center_).getNormalized();
	}
};

class ParticleSystem
{
public:
	std::vector<Particle> particles_;

	Sphere object;

	ParticleSystem()
	{
		particles_.resize(100000);

		for (int p = 0; p < particles_.size(); ++p)
		{
			particles_[p].pos_.x_ = (float)rand() / (float)RAND_MAX * 200   -2.0f-100.0f;
			particles_[p].pos_.y_ = (float)rand() / (float)RAND_MAX*50 + 9.0f;
			particles_[p].pos_.z_ = (float)rand() / (float)RAND_MAX * 200 -4.0f - 100.0f;

			particles_[p].vel_ = Vector3D<float>(0.0f, -50.0f, 0.0f);
		}		

		object.center_ = Vector3D<float>(-2.0, 3.5, -4.0);
		object.radius_ = 3.0;
	}

	void advanceOneTimeStep(const float& dt)
	{
		const TV gravity = TV(0.0, -60.0, 0.0);

		// Euler integration
		for (int p = 0; p < particles_.size(); ++p)
		{
			particles_[p].vel_ += gravity * dt;
			particles_[p].pos_ += particles_[p].vel_ * dt;
		}

		// Collision detection

		for (int p = 0; p < particles_.size(); ++p)
		{
			if (particles_[p].pos_.y_ < 0.0f && particles_[p].vel_.y_ < 0.0f)
			{
				particles_[p].vel_.y_ *= -0.4; // perfect restitution
				particles_[p].pos_.x_ = (float)rand() / (float)RAND_MAX * 200 - 2.0f - 100.0f;
				particles_[p].pos_.y_ = (float)rand() / (float)RAND_MAX * 30 + 9.0f;
				particles_[p].pos_.z_ = (float)rand() / (float)RAND_MAX * 200 - 4.0f - 100.0f;
				particles_[p].vel_ = Vector3D<float>(0.0f, -30.0f, 0.0f);
			}

		}

	}

};
