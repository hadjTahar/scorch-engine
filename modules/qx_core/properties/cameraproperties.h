#ifndef CAMERAPROPERTIES_H
#define CAMERAPROPERTIES_H

#include "properties.h"

#include <misc/defs.h>
#include <misc/debugprint.h>

namespace Qx::prv
{




enum class CameraMode { PERSPECTIVE, ORTHOGRAPHIC };




struct CameraProperties : PropertySet
{
    explicit CameraProperties(MetaObject &owner):
        PropertySet{owner}
    {
    }

    void setPosition( const x_vector3 &pos ){if(m_position == pos)return;m_position = pos;m_owner.propertyChanged( PropertyStates::Camera );}
    void setForward( const x_vector3 &vec ){if(m_forward == vec)return;m_forward = vec;m_owner.propertyChanged( PropertyStates::Camera );}
    void setUp( const x_vector3 &vec ){if(m_up == vec)return;m_up = vec;m_owner.propertyChanged( PropertyStates::Camera );}

    void setMode       ( const CameraMode &md ){if(m_mode == md)          return;m_mode = md;m_owner.propertyChanged( PropertyStates::Camera );}
    void setFieldOfView( const x_real val)      {if(m_fieldOfView == val) return;m_fieldOfView = val;m_owner.propertyChanged( PropertyStates::Camera );}
    void setAspectRatio( const x_real val)      {if(m_aspectRatio == val) return;m_aspectRatio = val;m_owner.propertyChanged( PropertyStates::Camera );}
    void setNearPlane  ( const x_real val)      {if(m_nearPlane == val)   return;m_nearPlane = val;m_owner.propertyChanged( PropertyStates::Camera );}
    void setFarPlane   ( const x_real val)      {if(m_farPlane == val)    return;m_farPlane = val;m_owner.propertyChanged( PropertyStates::Camera );}
    void setOrthoSize  ( const x_real val)      {if(m_orthoSize == val)   return;m_orthoSize = val;m_owner.propertyChanged( PropertyStates::Camera );}


    void setOrthoBox( const x_aabb &val) {

        const auto same = m_orthoBox.min == val.min && m_orthoBox.max == val.max;
        if(same)
            return;
        m_orthoBox  = val;m_owner.propertyChanged( PropertyStates::Camera );
    }


    auto  position()    const {return m_position; }
    auto  forward()     const {return m_forward; }
    auto  up()          const {return m_up; }
    auto  mode()        const {return m_mode; }
    auto  fieldOfView() const {return m_fieldOfView; }
    auto  aspectRatio() const {return m_aspectRatio; }
    auto  nearPlane()   const {return m_nearPlane; }
    auto  farPlane()    const {return m_farPlane; }
    auto  orthoSize()   const {return m_orthoSize; }
    auto  orthoBox()    const {return m_orthoBox; }

private:

    // Camera State
    x_vector3 m_position;
    x_vector3 m_forward;
    x_vector3 m_up;

    // Projection Parameters
    CameraMode  m_mode;
    x_real      m_fieldOfView{45}; // Degrees
    x_real      m_aspectRatio{1920.f/1080.f};
    x_real      m_nearPlane{.1f};
    x_real      m_farPlane{10 * 10000};
    x_real      m_orthoSize;   // Vertical "zoom" for orthographic
    x_aabb      m_orthoBox;


};

}
#endif // CAMERAPROPERTIES_H
