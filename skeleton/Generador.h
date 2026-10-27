#pragma once
#include "Vector3D.h"
#include "RenderUtils.hpp"
#include "Particle.h"
#include <random>
#include <chrono>


class Generador
{
public:
	Generador(Vector3D pos, Vector3D vel, float max, float min);
	~Generador();

	void updateNieve(double t);
	void updateFuente(double t);
	void update(double t);

private:
	Vector3D vel;
	float maxi;
	float mini;

	physx::PxTransform pose;
	std::vector<Particle*> particles;

	static std::mt19937 generator;
};

