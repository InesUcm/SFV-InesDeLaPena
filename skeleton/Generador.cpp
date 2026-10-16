#include "Generador.h"
#include "Particle.h"
Generador::Generador(Vector3D pos, Vector3D vel, float maxi, float mini):
	vel(vel), maxi(maxi), mini(mini) {
	pose = physx::PxTransform(pos);
}

void
Generador::updateUniforme(double t) {
	float posX = std::uniform_int_distribution<int>(mini, maxi)(generator);
	float posZ = std::uniform_int_distribution<int>(mini, maxi)(generator);
	Vector3D posParicle(posX, pose.q.y, posZ);

	particles.push_back(new Particle(posParicle, vel));
}

void
Generador::update(double t) {
	for (auto p : particles) {
		p->integrate(t);
	}
}