#pragma once

class IProjectileCallback{
public:
    IProjectileCallback();
    virtual ~IProjectileCallback();
    virtual void ProjectileCallback() = 0;
};