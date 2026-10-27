#include "Particle.h"
#include <cmath>
#include <iostream>

std::mt19937 Particle::generator(static_cast<unsigned int>(
	std::chrono::high_resolution_clock::now().time_since_epoch().count()
	));

//Constructor de particula con aceleracion
Particle::Particle(Vector3D pos, Vector3D vel, Vector4 color, Vector3D acc, float damping) :
	vel(vel), color(color), acc(acc), damping(damping)
{
	pose = physx::PxTransform(pos);
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(0.8f)), &pose, color);
	liveTime = std::uniform_real_distribution<float>(2.0f, 3.5f)(generator);
}


Particle::~Particle()
{
	if (renderItem) {
		std::cout << "borrando particula" << std::endl;
		renderItem->release();
		renderItem = nullptr;
	}
}

void Particle::integrate(double dt)
{
	timeAlive += dt;
	if (timeAlive > liveTime) {
		dead = true;
	}
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