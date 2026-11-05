#pragma once
#include "Particle.h"

class ForceGenerator {
protected:
    bool active = true;

public:
    virtual ~ForceGenerator() {}
    // Método que aplicará la fuerza a una partícula específica
    virtual void updateForce(Particle* particle, double duration) = 0;

    void setActive(bool state) { active = state; }
    bool isActive() const { return active; }
};