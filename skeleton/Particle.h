#pragma once
#include "Vector3D.h"
#include "RenderUtils.hpp"
#include <random>
#include <chrono>

class Particle
{
public:
	Particle(Vector3D Pos, Vector3D Vel, Vector4 color = Vector4(1.0f, 1.0f, 1.0f, 1.0f), Vector3D Acc = Vector3D(0.0f, 0.0f, 0.0f), float damping = 0.99f); //Particula con aceleracion
	~Particle();

	void integrate(double t);
	bool isDead() {
		return dead;
	}
	void setLiveTime(float time) {
		liveTime = time;
	}

	float Particle::getMass() const {
		return mass;
	}

	void Particle::setMass(float m) {
		if (m <= 0.0f) {
			mass = 0.0f;
			inverseMass = 0.0f;
		}
		else {
			mass = m;
			inverseMass = 1.0f / m;
		}
	}

	void Particle::addForce(const Vector3D& force) {
		forceAccum += force;
	}

	void Particle::clearForce() {
		forceAccum = Vector3D(0.0f, 0.0f, 0.0f);
	}

	Vector3D Particle::getVel() { return vel; }

protected:
	Vector3D vel;
	Vector3D acc;
	float damping;
	float timeAlive = 0.0f;
	float liveTime;
	Vector4 color;
	bool dead = false;

	//Fuerzas
	float mass;
	float inverseMass;
	Vector3D forceAccum;

	physx:: PxTransform pose;
	RenderItem* renderItem;
	static std::mt19937 generator;

	void euler(double t);
	void semiImplicitEuler(double t);
};

