#include "ForceRegistry.h"

void ForceRegistry::add(Particle* particle, ForceGenerator* fg) {
    registrations.push_back({ particle, fg });
}

void ForceRegistry::remove(Particle* particle, ForceGenerator* fg) {
    for (auto it = registrations.begin(); it != registrations.end(); ++it) {
        if (it->particle == particle && it->fg == fg) {
            registrations.erase(it);
            break;
        }
    }
}

void ForceRegistry::updateForces(double duration) {
    for (const auto& reg : registrations) {
        reg.fg->updateForce(reg.particle, duration);
    }
}