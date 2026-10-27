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
        Vector3D pos(0, 100, 0);
        Vector3D vel(0, -15, 0);
        generador = new Generador(pos, vel, 25, -25);
    }

    void update(double dt) override {
        generador->updateUniforme(dt);
        generador->update(dt);
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override {
    }

    void cleanup() override {
        if (generador) {
            delete generador;
            generador = nullptr;
        }
    }

private:
    Generador* generador{ nullptr };
};