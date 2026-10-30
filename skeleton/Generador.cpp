#include "Generador.h"
#include "Particle.h"
#include <iostream>
std::mt19937 Generador::generator(static_cast<unsigned int>(
	std::chrono::high_resolution_clock::now().time_since_epoch().count()
	));

Generador::Generador(Vector3D pos, Vector3D vel, float media, float desviacion):
	vel(vel), media(media), desviacion(desviacion) {
	pose = physx::PxTransform(pos.x, pos.y, pos.z);
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

Vector3D 
Generador::gauss(float media, float desviacion) {
	//Usamos la distribucion normal
	std::normal_distribution<float> dist(media, desviacion);

	// Generamos un valor aleatorio para cada componente
	float x = dist(generator);
	float y = dist(generator);
	float z = dist(generator);

	return Vector3D(x, y, z);
}

void 
Generador::updateFuente() {
	//Posición fija
	Vector3D posParticula(pose.p.x, pose.p.y, pose.p.z);

	// Velocidad usando la distribución gaussian
	Vector3D variacionVel = gauss(0.0f, desviacion);
	Vector3D velocidadFinal(vel.x + variacionVel.x, vel.y + std::abs(variacionVel.y), vel.z + variacionVel.z);

	Vector4 color(0.1f, 0.5f, 1.0f, 1.0f);
	Vector3D gravedad(0.0f, -10.0f, 0.0f);

	// Creamos y añadimos la partícula al vector
	particles.push_back(new Particle(posParticula, velocidadFinal, color, gravedad));
}

void
Generador::updateNieve() {
	//Calculamos la dispersión gaussiana (offset respecto al centro)
	Vector3D offset = gauss(media, desviacion);

	//Sumamos la posición real del generador
	float posX = pose.p.x + offset.x;
	float posY = pose.p.y + offset.y;
	float posZ = pose.p.z + offset.z;

	Vector3D pos(posX, posY, posZ);
	Vector4 color(1.0f, 1.0f, 1.0f, 1.0f); //Color blanco

	//Creamos la particula
	particles.push_back(new Particle(pos, vel, color));
}

void Generador::updateExplosion() {
	// 1. Posición fija: Nace exactamente en el punto de impacto/origen
	Vector3D posParticula(pose.p.x, pose.p.y, pose.p.z);

	// 2. Color de chispa de fuego (Naranja / Amarillo brillante)
	Vector4 color(1.0f, 0.5f, 0.1f, 1.0f);

	// 3. Velocidad en TODAS las direcciones usando Gauss
	// Media 0.0f y desviación alta (ej: 8.0f) para que se dispersen en esfera
	Vector3D velocidadFinal = gauss(0.0f, 8.0f);

	// 4. Creamos la partícula y la metemos al vector
	Particle* nuevaParticula = new Particle(posParticula, velocidadFinal, color);

	// 2. ⏱️ AQUÍ REDUCIMOS SU VIDA (ej: que duren solo 1.0 segundo o 0.8 segundos)
	nuevaParticula->setLiveTime(1.0f);

	// 3. La metemos al vector
	particles.push_back(nuevaParticula);
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