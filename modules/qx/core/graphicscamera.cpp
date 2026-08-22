#include "graphicscamera.h"

#include "graphicsscene.h"

namespace Qx::prv
{

GraphicsCamera::GraphicsCamera(GraphicsScene *scene):
    m_scene{ scene },
    properties{ *this }
{

    // auto dynPrprty = dampedProperty( itm );

}

void GraphicsCamera::update()
{
    propertyChanged( PropertyStates::Camera );
}

void GraphicsCamera::propertyChanged(PropertyStates newPropertyStates)
{
    auto win = m_scene->parentItem();
    win->propertyChanged( PropertyStates::Camera );
    m_scene->propertyChanged( PropertyStates::Camera );
}



x_matrix4x4 GraphicsCamera::viewMatrix() const
{
    MetaObject::check_is_alive( this );
    const x_vector3 position = properties.position();
    const x_vector3 forward  = properties.forward();
    const x_vector3 up       = properties.up();

    return glm::lookAt(position, position + forward, up);
}

x_matrix4x4 GraphicsCamera::projectionMatrix() const
{

    MetaObject::check_is_alive( this );
    const x_real near   =  properties.nearPlane();
    const x_real far    =  properties.farPlane();

    /// ## GPT
    if ( static_cast<CameraMode>(properties.mode()) == CameraMode::PERSPECTIVE)
    {
        const x_real tmpFov = properties.fieldOfView();
        const x_real tmpRat = properties.aspectRatio();

        return glm::perspective(glm::radians(tmpFov),
                                tmpRat,
                                near,
                                far);
    }
    else
    {
        const x_real left   = -properties.orthoSize() * properties.aspectRatio();
        const x_real right  =  properties.orthoSize() * properties.aspectRatio();
        const x_real bottom = -properties.orthoSize();
        const x_real top    =  properties.orthoSize();

        return glm::ortho(left, right, bottom, top, near, far);
    }
}

void GraphicsCamera::resetUICamera( const Screen &scrn )
{
    reset2DOrthoCamera( scrn );
}

void GraphicsCamera::reset2DOrthoCamera( const Screen &scrn )
{
    properties.setPosition( {} );
    properties.setForward( {0.0f, 0.0f, -1.0f} );
    properties.setUp( {0.0f, -1.0f, 0.0f} );

    properties.setMode( CameraMode::ORTHOGRAPHIC );
    properties.setFieldOfView( 45.0f );
    properties.setAspectRatio( 1 );
    properties.setNearPlane( 0.f );
    properties.setFarPlane( 10.0f );
    properties.setOrthoSize( 1.0f );
}

void GraphicsCamera::reset2DPerspectiveCamera( const Screen &scrn )
{
    properties.setPosition( {} );
    properties.setForward( {0.0f, 0.0f, -1.0f} );
    properties.setUp( {0.0f, -1.0f, 0.0f} );


    properties.setMode( CameraMode::PERSPECTIVE );
    properties.setFieldOfView( 90.0f );
    properties.setAspectRatio( 1 );
    properties.setNearPlane( 0.f );
    properties.setFarPlane( 1.f );
    properties.setOrthoSize( 1.0f );
}

void GraphicsCamera::reset3DOrthoCamera(const Screen &scrn,
                                        const x_aabb &aabb)
{
    properties.setPosition( {0.0f, 0.0f, 2.f} );
    properties.setForward( {0.0f, 0.0f, 1.0f} );
    properties.setUp( {0.0f, 1.0f, 0.0f} );


    properties.setMode( CameraMode::ORTHOGRAPHIC );
    properties.setOrthoBox( aabb );
}

void GraphicsCamera::reset3DOrthoCamera( const Screen &scrn )
{
    // // const auto sz = scrn.size();
    // const auto ratio = scrn.sizeRatio();

    // properties.setPosition( {} );
    // properties.setForward( {0.0f, 0.0f, -1.0f} );
    // properties.setUp( {0.0f, 1.0f, 0.0f} );


    // properties.setMode( CameraMode::ORTHOGRAPHIC );
    // properties.setFieldOfView( 45.0f );
    // properties.setAspectRatio( ratio );
    // properties.setNearPlane( 0.f );
    // properties.setFarPlane( 2.0f );
    // properties.setOrthoSize( 1.0f );
}

void GraphicsCamera::reset3DPerspectiveCamera( const Screen &scrn )
{
    // const auto sz = scrn.size();
    const auto ratio = scrn.sizeRatio();

    properties.setPosition( {0.0f, 0.0f, 2.f} );
    properties.setForward( {0.0f, 0.0f, 1.0f} );
    properties.setUp( {0.0f, 1.0f, 0.0f} );


    properties.setMode( CameraMode::PERSPECTIVE );
    properties.setFieldOfView( 45.0f );
    properties.setAspectRatio( ratio );
    properties.setNearPlane( 0.1f );
    properties.setFarPlane( 3000.f );
}



}
