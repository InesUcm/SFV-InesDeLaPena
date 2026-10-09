#pragma once
#include "Vector3D.h"
#include "RenderUtils.hpp"
class Particle
{
public:
	Particle(Vector3D Pos, Vector3D Vel, Vector3D Acc = Vector3D(0.0f, 0.0f, 0.0f), float damping = 0.99f); //Particula con aceleracion
	~Particle();

	void integrate(double t);
	void euler(double t);
	void semiImplicitEuler(double t);

protected:
	Vector3D vel;
	Vector3D acc;
	float damping;

	physx:: PxTransform pose;
	RenderItem* renderItem;
};

