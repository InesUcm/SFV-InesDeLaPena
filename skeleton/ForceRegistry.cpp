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

void ForceRegistry::cleanDeletedParticles() {
    for (auto it = registrations.begin(); it != registrations.end(); ) {

        // Una forma muy segura y sencilla es limpiar el registro por completo al inicio del frame 
        // y que el generador las vuelva a registrar si siguen vivas, O comprobar si la partícula está muerta:
        if (it->particle->isDead()) {
            it = registrations.erase(it);
        }
        else {
            ++it;
        }
    }
}
void ForceRegistry::clear() {
    registrations.clear();
}