#include "Proyectil.h"
//Constructor de proyectil
Proyectil::Proyectil(Vector3D pos, Vector3D velReal, Vector3D velSim, float masaReal, TipoProyectil tipo, float gReal) :
	Particle(pos, velSim), velReal(velReal), velSim(velSim), masaReal(masaReal), gReal(gReal), tipo(tipo)
{
	if (tipo == CANON) {
		this->masaReal = 15.0f; // Pesado
	}
	else if (tipo == BALA) {
		this->masaReal = 0.5f;  // Ligero
	}

	updateProyectil();

	setMass(masaSim);
}

Proyectil::~Proyectil()
{
}

void Proyectil::update(double t)
{
	integrate(t);
}

void Proyectil::updateProyectil()
{
	//Calculamos la masa simulada
	masaSim = masaReal * (velReal.magnitude() * velReal.magnitude()) / (velSim.magnitude() * velSim.magnitude());

	//Calculamos la gravedad real
	gSim = gReal * ((velReal.magnitude() * velReal.magnitude()) / (velSim.magnitude() * velSim.magnitude()));

	// La aceleración será la gravedad simulada en el eje Y
	acc = Vector3D(0.0f, gSim, 0.0f);
}

void Proyectil::setNewMass(float newMassReal)
{
	masaReal = newMassReal;
	updateProyectil();
	setMass(masaSim);
}

void Proyectil::escalarVelocidad(float factor) {
	velReal = velReal * factor;
	velSim = velSim * factor;
	vel = velSim;
	updateProyectil();
}

void Proyectil::escalarEnergia(float factor) {
	float factorVel = std::sqrt(factor);
	escalarVelocidad(factorVel);
}

void Proyectil::escalarFuerzas(float factor) {
	forceAccum = forceAccum * factor;
}