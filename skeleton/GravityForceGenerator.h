#pragma once
#include "ForceGenerator.h"
#include "Vector3D.h"

class GravityForceGenerator : public ForceGenerator {
public:
    explicit GravityForceGenerator(const Vector3D& gravity);
    virtual void updateForce(Particle* particle, double duration) override;

private:
    Vector3D gravity;
};