#ifndef WORLDITEM_H
#define WORLDITEM_H

#include <core/graphicsitem3d.h>

namespace Qx {


class WorldItem final: public Qx::prv::GraphicsItem3D
{
public:
    WorldItem(CoreItem *parent);


    x_vector3 worldMin() const;
    void setWorldMin(const x_vector3 &newWorldMin);

    x_vector3 worldMax() const;
    void setWorldMax(const x_vector3 &newWorldMax);

protected:
    void updateModel( GraphicsMeshModel *graphicsMeshModel ) override;

    x_vector3 m_worldMin;
    x_vector3 m_worldMax;
};

}
#endif // WORLDITEM_H
