#pragma once
#include "Projectile.h"

class IProjectileCallback{
public:
    IProjectileCallback();
    virtual ~IProjectileCallback();
    virtual void ProjectileCallback(Projectile&) = 0;
};