#include "Proyectil.h"
//Constructor de proyectil
Proyectil::Proyectil(Vector3D pos, Vector3D velReal, Vector3D velSim, float masaReal, float gReal, float damping) :
	Particle(pos, velSim), velReal(velReal), velSim(velSim), gReal(gReal)
{
	updateProyectil();
}

Proyectil::~Proyectil()
{
	// Liberación del RenderItem para evitar fugas de memoria
	if (renderItem) {
		renderItem->release();
		renderItem = nullptr;
	}
}

void Proyectil::update(double t)
{
	semiImplicitEuler(t);
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
}