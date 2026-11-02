#pragma once
#include "Particle.h"

class ForceGenerator {
public:
    virtual ~ForceGenerator() {}
    // Método que aplicará la fuerza a una partícula específica
    virtual void updateForce(Particle* particle, double duration) = 0;
};