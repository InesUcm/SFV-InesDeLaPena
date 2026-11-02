#pragma once

#include "Scene.h"
#include "RenderUtils.hpp"
#include "Vector3D.h"
#include "Generador.h"

class P3S_Scene : public Scene {
public:
    explicit P3S_Scene(std::string name = "P3S_Scene") : Scene(std::move(name)) {}

    ~P3S_Scene() {
        cleanup();
    }

    void init() override {
        std::cout << "cargando escena 3" << std::endl;
        Vector3D pos(0.0f, 0.0f, 0.0f);
        Vector3D vel(0, 0, 0);
        generadorExplosion = new Generador(pos, vel, 0.0f, 0.0f);
    }

    void update(double dt) override {
        generadorExplosion->updateExplosion();
        generadorExplosion->update(dt);
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override {
    }

    void cleanup() override {
        if (generadorExplosion) {
            delete generadorExplosion;
            generadorExplosion = nullptr;
        }
    }

private:
    Generador* generadorExplosion{ nullptr };

};