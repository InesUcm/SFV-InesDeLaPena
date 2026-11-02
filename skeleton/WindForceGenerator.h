#pragma once
#include "ForceGenerator.h"
#include "Vector3D.h"

class WindForceGenerator : public ForceGenerator {
public:
    WindForceGenerator(const Vector3D& windVelocity, float k1, float k2);
    virtual void updateForce(Particle* particle, double duration) override;

    // Opcional: Para cambiar el viento dinámicamente si lo deseas
    void setWindVelocity(const Vector3D& w) { windVelocity = w; }

private:
    Vector3D windVelocity; // Velocidad del viento
    float k1;              // Coeficiente lineal
    float k2;              // Coeficiente cuadrático (turbulento)
};