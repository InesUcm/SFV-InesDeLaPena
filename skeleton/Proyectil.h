#pragma once
#include "Particle.h"

class Proyectil: public Particle
{
public:
	enum TipoProyectil {
		CANON,
		BALA
	};

	Proyectil(Vector3D pos, Vector3D velReal, Vector3D velSim, float masaReal, TipoProyectil tipo, float gReal = -9.8f); //Proyectil
	~Proyectil();

	void setNewMass(float newMassReal);
	void updateProyectil();
	void update(double t);

	void escalarVelocidad(float factor);
	void escalarEnergia(float factor);
	void escalarFuerzas(float factor);

	TipoProyectil getTipo() const { return tipo; }

private:
	TipoProyectil tipo;

	//Proyectiles
	// Ms = Mr * Vr^2 / Vs^2
	// Gs = Gr * (Vr^2 / Vs^2)

	float masaReal;   // Masa real (kg)
	Vector3D velReal;    // Magnitud de la velocidad real (m/s)
	float gReal;      // Gravedad real (m/s^2)

	float masaSim;    // Masa simulada
	Vector3D velSim;     // Magnitud de la velocidad simulada (m/s)
	float gSim;       // Gravedad simulada
};

