#include "Particle.h"
#include <cmath>

Particle::Particle(Vector3D pos, Vector3D vel, Vector3D acc, float damping) : vel(vel), acc(acc), damping(damping)
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