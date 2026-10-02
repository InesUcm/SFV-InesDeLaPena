#pragma once
#include "Vector3D.h"
#include "RenderUtils.hpp"
class Particle
{
public:
	Particle(Vector3D Pos, Vector3D Vel); //Particula constante
	Particle(Vector3D Pos, Vector3D Vel, Vector3D Acc = Vector3D(0.0f, 0.0f, 0.0f), float damping = 0.99f); //Particula con aceleracion
	Particle(Vector3D pos, Vector3D vel, float masaReal, float velReal, float velSim, float gReal = -9.8f, float damping = 0.99f); //Proyectil
	~Particle();

	void integrate(double t);
	void euler(double t);
	void semiImplicitEuler(double t);

	void setNewMasaProyectil(float newMassReal);
	void updateProyectil();

private:
	Vector3D vel;
	Vector3D acc;
	float damping;

	//Proyectiles
	// Ms = Mr * Vr^2 / Vs^2
	// Gs = Gr * (Vr^2 / Vs^2)

	float masaReal;   // Masa real (kg)
	float velReal;    // Magnitud de la velocidad real (m/s)
	float gReal;      // Gravedad real (m/s^2)

	float masaSim;    // Masa simulada
	float velSim;     // Magnitud de la velocidad simulada (m/s)
	float gSim;       // Gravedad simulada

	physx:: PxTransform pose;
	RenderItem* renderItem;
};

