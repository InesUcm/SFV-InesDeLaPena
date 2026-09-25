#pragma once

#include "Scene.h"
#include "RenderUtils.hpp"
#include "Vector3D.h"

class P0S_Scene : public Scene {
public:
    explicit P0S_Scene(std::string name = "P0S_Scene") : Scene(std::move(name)) {}

    void init() override {
        Vector3D u(3.0f, 1.0f, 0.0f);
        Vector3D v(0.0f, 4.0f, 0.0f);

        Vector3D w = u.cross(v);

        Vector3D axisX = u.normalize() * 5.0f; // Eje X local
        Vector3D axisY = v.normalize() * 5.0f; // Eje Y local
        Vector3D axisZ = w.normalize() * 5.0f; // Eje Z local
        Vector3D origin(0.0f, 0.0f, 0.0f);    // Origen

        physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(1.0f));

        // Centro
        m_transformOrigin = physx::PxTransform(origin);
        m_renderItemOrigin = new RenderItem(shape, &m_transformOrigin, Vector4(1.0f, 1.0f, 1.0f, 1.0f));

        // Bola Roja (Eje X)
        m_transformX = physx::PxTransform(axisX);
        m_renderItemX = new RenderItem(shape, &m_transformX, Vector4(1.0f, 0.0f, 0.0f, 1.0f));

        // Bola Verde (Eje Y)
        m_transformY = physx::PxTransform(axisY);
        m_renderItemY = new RenderItem(shape, &m_transformY, Vector4(0.0f, 1.0f, 0.0f, 1.0f));

        // Bola Azul (Eje Z)
        m_transformZ = physx::PxTransform(axisZ);
        m_renderItemZ = new RenderItem(shape, &m_transformZ, Vector4(0.0f, 0.0f, 1.0f, 1.0f));

        Vector3D D(0.0f, 0.0f, 1.0f);
        Vector3D P_1(2.0f, 0.0f, 3.0f);
        Vector3D P_2(-4.0f, 0.0f, 1.0f);
        Vector3D P_3(0.0f, 0.0f, -5.0f);
        Vector3D P_4(3.0f, 0.0f, 0.0f);

        Vector3D d = D.normalize() * 2.0f;

        float prod1 = D.dot(P_1);//+ Verde
        float prod2 = D.dot(P_2);//+ Verde
        float prod3 = D.dot(P_3);//- Rojo
        float prod4 = D.dot(P_4);//= Amarillo

        m_transformD = physx::PxTransform(d);
        m_renderItemD = new RenderItem(shape, &m_transformD, Vector4(0.0f, 0.0f, 0.0f, 1.0f));
        m_transformV1 = physx::PxTransform(P_1);
        m_renderItemV1 = new RenderItem(shape, &m_transformV1, Vector4(0.0f, 1.0f, 0.0f, 1.0f));
        m_transformV2 = physx::PxTransform(P_2);
        m_renderItemV2 = new RenderItem(shape, &m_transformV2, Vector4(0.0f, 1.0f, 0.0f, 1.0f));
        m_transformV3 = physx::PxTransform(P_3);
        m_renderItemV3 = new RenderItem(shape, &m_transformV3, Vector4(1.0f, 0.0f, 0.0f, 1.0f));
        m_transformV4 = physx::PxTransform(P_4);
        m_renderItemV4 = new RenderItem(shape, &m_transformV4, Vector4(1.0f, 1.0f, 0.0f, 1.0f));
    }

    void update(double dt) override {
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override {
        if (key == 'r' || key == 'R') {
            m_transformOrigin.p = physx::PxVec3(0.0f, 0.0f, 0.0f);
        }
    }

    void cleanup() override {
        // Liberación limpia invocado .release() sobre cada RenderItem exactamente como en la plantilla
        if (m_renderItemOrigin) {
            m_renderItemOrigin->release();
            m_renderItemOrigin = nullptr;
        }
        if (m_renderItemX) {
            m_renderItemX->release();
            m_renderItemX = nullptr;
        }
        if (m_renderItemY) {
            m_renderItemY->release();
            m_renderItemY = nullptr;
        }
        if (m_renderItemZ) {
            m_renderItemZ->release();
            m_renderItemZ = nullptr;
        }
        if (m_renderItemD) {
            m_renderItemD->release();
            m_renderItemD = nullptr;
        }
        if (m_renderItemV1) {
            m_renderItemV1->release();
            m_renderItemV1 = nullptr;
        }
        if (m_renderItemV2) {
            m_renderItemV2->release();
            m_renderItemV2 = nullptr;
        }
        if (m_renderItemV3) {
            m_renderItemV3->release();
            m_renderItemV3 = nullptr;
        }
        if (m_renderItemV4) {
            m_renderItemV4->release();
            m_renderItemV4 = nullptr;
        }
    }

private:
    // Transformadas
    physx::PxTransform m_transformOrigin;
    physx::PxTransform m_transformX;
    physx::PxTransform m_transformY;
    physx::PxTransform m_transformZ;
    physx::PxTransform m_transformD;
    physx::PxTransform m_transformV1;
    physx::PxTransform m_transformV2;
    physx::PxTransform m_transformV3;
    physx::PxTransform m_transformV4;

    // RenderItems individuales inicializados a nullptr
    RenderItem* m_renderItemOrigin{ nullptr };
    RenderItem* m_renderItemX{ nullptr };
    RenderItem* m_renderItemY{ nullptr };
    RenderItem* m_renderItemZ{ nullptr };
    RenderItem* m_renderItemD{ nullptr };
    RenderItem* m_renderItemV1{ nullptr };
    RenderItem* m_renderItemV2{ nullptr };
    RenderItem* m_renderItemV3{ nullptr };
    RenderItem* m_renderItemV4{ nullptr };
};