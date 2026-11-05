#include "WindForceGenerator.h"
#include <cmath>

WindForceGenerator::WindForceGenerator(const Vector3D& windVelocity, float k1, float k2)
    : windVelocity(windVelocity), k1(k1), k2(k2) {
}

void WindForceGenerator::updateForce(Particle* particle, double duration) {
    if (particle->getMass() <= 0.0f) return;

    //Obtenemos la velocidad de la partícula
    Vector3D particleVel = particle->getVel();

    //Velocidad relativa del viento respecto a la partícula: (v_viento - v_particula)
    Vector3D relativeVel = windVelocity - particleVel;

    //Magnitud (longitud) de la velocidad relativa: ||v_viento - v_particula||
    float speed = relativeVel.magnitude();


    //Aplicamos la fórmula: F_v = k1 * relVel + k2 * ||relVel|| * relVel
    Vector3D force = relativeVel * k1;

    if (k2 != 0.0f) {
        force += relativeVel * (speed * k2);
    }

    //Acumulamos la fuerza en la partícula
    particle->addForce(force);
}