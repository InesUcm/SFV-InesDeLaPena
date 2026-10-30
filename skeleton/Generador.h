#pragma once
#include "Vector3D.h"
#include "RenderUtils.hpp"
#include "Particle.h"
#include <random>
#include <chrono>


class Generador
{
public:
	Generador(Vector3D pos, Vector3D vel, float media, float desviacion);
	~Generador();

	void updateNieve();
	void updateFuente();
	void updateExplosion();
	void update(double t);

private:
	Vector3D vel;
	float maxi;
	float mini;
	float media;
	float desviacion;

	Vector3D gauss(float media, float desviacion);

	physx::PxTransform pose;
	std::vector<Particle*> particles;

	static std::mt19937 generator;
};

