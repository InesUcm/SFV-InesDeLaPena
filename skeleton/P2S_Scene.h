#pragma once

#include "Scene.h"
#include "RenderUtils.hpp"
#include "Vector3D.h"
#include "Generador.h"

class P2S_Scene : public Scene {
public:
    explicit P2S_Scene(std::string name = "P2S_Scene") : Scene(std::move(name)) {}

    ~P2S_Scene() {
        cleanup();
    }

    void init() override {
        Vector3D pos(-20.0f, 40.0f, 35.0f);
        Vector3D vel(0, -15, 0);
        generadorNieve = new Generador(pos, vel, 0.0f, 5.0f);

        Vector3D pos1(0, 0, 0);
        Vector3D vel1(0, 18, 0);
        generadorFuente = new Generador(pos1, vel1, 0.0f, 2.0f);

        Vector3D pos2(25.0f, 0.0f, -35.0f);
        Vector3D vel2(0, 0, 0);
        generadorExplosion = new Generador(pos2, vel2, 0.0f, 0.0f);
    }

    void update(double dt) override {
        generadorNieve->updateNieve();
        generadorNieve->update(dt);

        generadorFuente->updateFuente();
        generadorFuente->update(dt);

        generadorExplosion->updateExplosion();
        generadorExplosion->update(dt);
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override {
    }

    void cleanup() override {
        if (generadorNieve) {
            delete generadorNieve;
            generadorNieve = nullptr;
        }
        if (generadorFuente) {
            delete generadorFuente;
            generadorFuente = nullptr;
        }
        if (generadorExplosion) {
            delete generadorExplosion;
            generadorExplosion = nullptr;
        }
    }

private:
    Generador* generadorNieve{ nullptr };
    Generador* generadorFuente { nullptr };
    Generador* generadorExplosion { nullptr };

};