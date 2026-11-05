#include "GravityForceGenerator.h"

GravityForceGenerator::GravityForceGenerator(const Vector3D& gravity)
    : gravity(gravity) {
}

void GravityForceGenerator::updateForce(Particle* particle, double duration) {
    if (particle->getMass() <= 0.0f) return;

    // Fórmula de la fuerza gravitatoria: F = m * g
    Vector3D force = gravity * particle->getMass();
    particle->addForce(force);
}