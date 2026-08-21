#ifndef CIRCLES_H
#define CIRCLES_H

#include <core/graphicsitem3d.h>
#include <utils/Entity.h>
#include <filament/Box.h>



class Circles final: public Qx::prv::GraphicsItem3D
{


public:
    Circles(CoreItem *parent);
    ~Circles();

protected:
    void updateModel() override;

};

#endif // CIRCLES_H
