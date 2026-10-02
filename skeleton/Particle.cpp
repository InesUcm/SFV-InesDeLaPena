#include "Particle.h"
#include <cmath>

//Constructor de particula convelocidad constante
Particle::Particle(Vector3D pos, Vector3D vel) : 
	vel(vel)
{
	pose = physx::PxTransform(pos);
	physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(0.8f));
	renderItem = new RenderItem(shape, &pose, Vector4(0.0f, 0.8f, 1.0f, 1.0f));
}
//Constructor de particula con aceleracion
Particle::Particle(Vector3D pos, Vector3D vel, Vector3D acc, float damping) : 
	vel(vel), acc(acc), damping(damping)
{
	pose = physx::PxTransform(pos);
	physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(0.8f));
	renderItem = new RenderItem(shape, &pose, Vector4(0.0f, 0.8f, 1.0f, 1.0f));
}
//Constructor de proyectil
Particle::Particle(Vector3D pos, Vector3D vel, float masaReal, float velReal, float velSim, float gReal, float damping) : 
	vel(vel), masaReal(masaReal), velReal(velReal), velSim(velSim), gReal(gReal), damping(damping)
{
	pose = physx::PxTransform(pos);
	physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(0.8f));
	renderItem = new RenderItem(shape, &pose, Vector4(0.0f, 0.8f, 1.0f, 1.0f));
}

Particle::~Particle()
{
	if (renderItem) {
		renderItem->release();
		renderItem = nullptr;
	}
}

void Particle::integrate(double dt)
{
	semiImplicitEuler(dt);
}

void Particle::euler(double dt) {
	float deltaTime = static_cast<float>(dt);

	//actualizamos la posicion
	pose.p = pose.p + vel * deltaTime;

	// actualizamos la velocidad
	vel = vel + acc * deltaTime;

	// aplicamos el damping
	vel = vel * std::pow(damping, deltaTime);
}

void Particle::semiImplicitEuler(double dt)
{
	float deltaTime = static_cast<float>(dt);

	// actualizamos la velocidad
	vel = vel + acc * deltaTime;

	// aplicamos el damping
	vel = vel * std::pow(damping, deltaTime);

	// actualizamos la posicion
	pose.p = pose.p + vel * deltaTime;
}

void Particle::updateProyectil()
{
	if (velSim <= 0.0f) return;

	//Calculamos la masa simulada
	masaSim = masaReal * (velReal * velReal) / velSim;

	//Calculamos la gravedad real
	gSim = gReal * ((velReal*velReal) / (velSim*velSim));

	// La aceleración será la gravedad simulada en el eje Y
	acc = Vector3D(0.0f, gSim, 0.0f);
}

void Particle::setNewMasaProyectil(float newMassReal)
{
	masaReal = newMassReal;
	updateProyectil();
}