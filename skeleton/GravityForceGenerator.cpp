#include "GravityForceGenerator.h"

GravityForceGenerator::GravityForceGenerator(const Vector3D& gravity)
    : gravity(gravity) {
}

void GravityForceGenerator::updateForce(Particle* particle, double duration) {
    // Evitamos aplicar fuerza si la partícula tiene masa infinita o cero (por seguridad)
    if (particle->getMass() <= 0.0f) return;

    // Fórmula de la fuerza gravitatoria: F = m * g
    // Nota: Necesitarás que tu clase Particle tenga un método getMass() y un acumulador de fuerzas.
    Vector3D force = gravity * particle->getMass();
    particle->addForce(force);
}