#ifndef GRAPHICSCAMERA_H
#define GRAPHICSCAMERA_H


#include <misc/screen.h>
#include <misc/vecs.h>
#include <properties/cameraproperties.h>
#include <core/metaobject.h>

namespace Qx::prv
{

class GraphicsScene;


class GraphicsCamera : public MetaObject
{
    QX_META_OBJECT( GraphicsCamera, MetaItemType::NA, MetaItemType::NA )

public:
    GraphicsCamera( GraphicsScene *scene );
    void update();
    void propertyChanged(PropertyStates newPropertyStates) override;
    x_matrix4x4 viewMatrix() const;
    x_matrix4x4 projectionMatrix() const;

    /// ## Helpers
    void resetUICamera( const Screen &scrn );
    void reset2DOrthoCamera( const Screen &scrn );
    void reset2DPerspectiveCamera( const Screen &scrn );

    void reset3DOrthoCamera( const Screen &scrn, const x_aabb &aabb );
    void reset3DOrthoCamera( const Screen &scrn );
    void reset3DPerspectiveCamera( const Screen &scrn );


public:
    CameraProperties properties;

private:
    GraphicsScene *m_scene;
};

}
#endif // GRAPHICSCAMERA_H
