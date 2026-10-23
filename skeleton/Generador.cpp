#include "Generador.h"
#include "Particle.h"
#include <iostream>
std::mt19937 Generador::generator(static_cast<unsigned int>(
	std::chrono::high_resolution_clock::now().time_since_epoch().count()
	));

Generador::Generador(Vector3D pos, Vector3D vel, float maxi, float mini):
	vel(vel), maxi(maxi), mini(mini) {
	pose = physx::PxTransform(pos);
}

void
Generador::updateUniforme(double t) {
	std::uniform_real_distribution<float> distPos(static_cast<float>(mini), static_cast<float>(maxi));
	float posX = distPos(generator);
	float posZ = distPos(generator);
	std::cout << "Particula: " << posX << ", " << posZ << std::endl;
	Vector3D posParicle(posX, pose.q.y, posZ);
	Vector4 color(1.0f, 1.0f, 1.0f, 1.0f);

	particles.push_back(new Particle(posParicle, vel, color));
}

void
Generador::update(double t) {
	for (auto p : particles) {
		p->integrate(t);
	}
}