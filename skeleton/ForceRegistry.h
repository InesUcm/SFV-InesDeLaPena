#pragma once
#include <vector>
#include "Particle.h"
#include "ForceGenerator.h"

class ForceRegistry {
protected:
    struct ParticleForceRegistration {
        Particle* particle;
        ForceGenerator* fg;
    };

    std::vector<ParticleForceRegistration> registrations;

public:
    void add(Particle* particle, ForceGenerator* fg);
    void remove(Particle* particle, ForceGenerator* fg);
    void updateForces(double duration);
};