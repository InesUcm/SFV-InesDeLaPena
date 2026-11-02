#pragma once

#include "Scene.h"
#include "RenderUtils.hpp"
#include "Vector3D.h"
#include "Generador.h"
#include "GravityForceGenerator.h"
#include "ForceRegistry.h"
#include "WindForceGenerator.h"

class P3S_Scene : public Scene {
public:
    explicit P3S_Scene(std::string name = "P3S_Scene") : Scene(std::move(name)) {}

    ~P3S_Scene() {
        cleanup();
    }

    void init() override {
        Vector3D pos(0.0f, 0.0f, 0.0f);
        Vector3D vel(0, 0, 0);
        generadorExplosion = new Generador(pos, vel, 0.0f, 0.0f);

        Vector3D pos1(-20.0f, 40.0f, 35.0f);
        Vector3D vel1(0, -15, 0);
        generadorNieve = new Generador(pos1, vel1, 0.0f, 5.0f);

        gravityGen = new GravityForceGenerator(Vector3D(0.0f, -10.0f, 0.0f));

        windGen = new WindForceGenerator(Vector3D(15.0f, 0.0f, 0.0f), 1.5f, 0.0f);
    }

    void update(double dt) override {
        // Generamos las nuevas partículas
        generadorExplosion->updateExplosion();
        generadorNieve->updateNieve();

        //Creamos un vector unificado con TODAS las partículas vivas de la escena
        std::vector<Particle*> todasLasParticulas;

        // Añadimos las de la explosión
        auto& expParts = generadorExplosion->getParticles();
        todasLasParticulas.insert(todasLasParticulas.end(), expParts.begin(), expParts.end());

        // Añadimos las de la nieve
        auto& nieveParts = generadorNieve->getParticles();
        todasLasParticulas.insert(todasLasParticulas.end(), nieveParts.begin(), nieveParts.end());

        //Vaciamos el registro de fuerzas para empezar limpios
        registry.clear();

        //Registramos TODAS las partículas del vector unificado a la gravedad y al viento de golpe
        for (Particle* p : todasLasParticulas) {
            registry.add(p, gravityGen);
            registry.add(p, windGen);
        }

        //Aplicamos las fuerzas a todo el sistema unificado
        registry.updateForces(dt);

        //Actualizamos los generadores
        generadorExplosion->update(dt);
        generadorNieve->update(dt);
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override {
    }

    void cleanup() override {
        if (generadorExplosion) {
            delete generadorExplosion;
            generadorExplosion = nullptr;
        }
        if (generadorNieve) {
            delete generadorNieve;
            generadorNieve = nullptr;
        }
        if (gravityGen) {
            delete gravityGen;
            gravityGen = nullptr;
        }
        if (windGen) {
            delete windGen;
            windGen = nullptr;
        }
    }

private:
    Generador* generadorExplosion{ nullptr };
    Generador* generadorNieve{ nullptr };
    ForceRegistry registry;
    GravityForceGenerator* gravityGen{ nullptr };
    WindForceGenerator* windGen{ nullptr };
};