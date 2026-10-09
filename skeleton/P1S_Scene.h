#pragma once

#include "Scene.h"
#include "RenderUtils.hpp"
#include "Vector3D.h"
#include "Proyectil.h"

class P1S_Scene : public Scene {
public:
    explicit P1S_Scene(std::string name = "P1S_Scene") : Scene(std::move(name)) {}


    void init() override {
    }

    void update(double dt) override {
        for (auto p : proyectiles) {
            p->update(dt);
        }
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override {

        Vector3D cameraDir;
        float masaReal = 15.0f;

        if (key == '+') {
            proyectil->setNewMass(masaReal + 1.0f);
        }
        else if (key == ' ') {
            cameraDir = GetCamera()->getDir();
            proyectiles.push_back(new Proyectil(GetCamera()->getEye(), cameraDir*200, cameraDir*120, masaReal));
        }
    }

    void cleanup() override {
        for (auto p : proyectiles) {
            delete p;
            p = nullptr;
        }
        proyectiles.clear();
    }

private:
    std::vector<Proyectil*> proyectiles;
    Proyectil* proyectil{ nullptr };
};