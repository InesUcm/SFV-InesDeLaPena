#pragma once

#include "Scene.h"
#include "RenderUtils.hpp"
#include "Vector3D.h"
#include "Proyectil.h"

class P1S_Scene : public Scene {
public:
    explicit P1S_Scene(std::string name = "P1S_Scene") : Scene(std::move(name)) {}

    ~P1S_Scene() {
        cleanup();
    }

    void init() override {
    }

    void update(double dt) override {
        for (auto p : proyectiles) {
            p->update(dt);
        }

        for (auto it = proyectiles.begin(); it != proyectiles.end(); )
        {
            if ((*it)->isDead()) {
                delete* it;
                it = proyectiles.erase(it);
            }
            else {
                ++it;
            }
        }
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override {

        Vector3D cameraDir = GetCamera()->getDir();

        if (key == 'z') {
            // Dispara una cañon
            std::cout << "Disparando cañon" << std::endl;
            proyectiles.push_back(new Proyectil(GetCamera()->getEye(), cameraDir * 250, cameraDir * 120, 15.0f, Proyectil::CANON));
        }
        else if (key == 'x') {
            // Dispara una bala
            std::cout << "Disparando bala" << std::endl;
            proyectiles.push_back(new Proyectil(GetCamera()->getEye(), cameraDir * 350, cameraDir * 150, 0.5f, Proyectil::BALA));
        }
    }

    void cleanup() override {
        for (auto p : proyectiles) {
            delete p; // Borra los proyectiles que siguen vivos en pantalla
        }
        proyectiles.clear();
       
    }

private:
    std::vector<Proyectil*> proyectiles;
    Proyectil* proyectil{ nullptr };
};