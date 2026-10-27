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

Generador::~Generador()
{
	for (Particle* p : particles) {
		//lanza una excepcion por las particulas que ya se borraron antes de borrar el generador
		//hay que eliminar las particulas del vector cuando se borran
		delete p; // Libera cada partícula viva que quedara en el generador
	}
	particles.clear();
}

void 
Generador::updateFuente(double t) {
	//Todas las particulas aparecen en la misma posicion
	Vector3D posParticula(pose.p.x, pose.p.y, pose.p.z);
	Vector4 color(0.2f, 0.6f, 1.0f, 1.0f); // Color azul

	//Calculamos cuanto se va a esparzir la particula (cuanto se mueev en x y en z)
	std::uniform_real_distribution<float> distSpread(mini, maxi); // mini = -5, maxi = 5

	float vx = distSpread(generator);
	float vz = distSpread(generator);

	Vector3D velocidadFinal(vx, vel.y, vz);
	//Le aplicamos gravedad
	Vector3D aceleracion(0.0f, -10.0f, 0.0f);

	//Creamos la partícula
	particles.push_back(new Particle(posParticula, velocidadFinal, color, aceleracion));
}

void
Generador::updateNieve(double t) {
	//Calculamos la psoicion en la que aparecera la particula
	std::uniform_real_distribution<float> distPos(static_cast<float>(mini), static_cast<float>(maxi));
	float posX = pose.p.x + distPos(generator);
	float posZ = pose.p.z + distPos(generator);
	float posY = pose.p.y;
	Vector3D posParicle(posX, posY, posZ);
	Vector4 color(1.0f, 1.0f, 1.0f, 1.0f); //Color blanco

	//Creamos la particula
	particles.push_back(new Particle(posParicle, vel, color));
}

void
Generador::update(double t) {

	for (auto it = particles.begin(); it != particles.end(); ) {
		(*it)->integrate(t);

		// Si la partícula ha superado su tiempo de vida
		if ((*it)->isDead()) {
			delete* it;
			it = particles.erase(it);
		}
		else {
			++it;
		}
	}
}