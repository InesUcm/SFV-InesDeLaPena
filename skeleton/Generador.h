#pragma once
#include "Vector3D.h"
#include "RenderUtils.hpp"
#include "Particle.h"
#include <random>
#include <chrono>


class Generador
{
protected:
	bool active = true;

public:
	Generador(Vector3D pos, Vector3D vel, float media, float desviacion);
	~Generador();

	//Tres generadores de particulas distintos: de nieve, de fuente y de explosion
	void updateNieve();
	void updateFuente();
	void updateExplosion();

	void update(double t);

	void setActive(bool state) { active = state; }
	bool isActive() const { return active; }

	std::vector<Particle*>& getParticles() { return particles; }

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

