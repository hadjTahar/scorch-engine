#include "cameracontroller.h"

#include <core/graphicscamera.h>


namespace Qx
{

CameraController::CameraController(prv::GraphicsItem *parentItem):
    CameraBaseInput{ parentItem },
    m_camera{ nullptr },
    m_rotationSensitivity{0.001},
    m_panSpeed{ 1 },
    m_zoomSpeed{ 1 },
    m_mouseWheel{},
    m_mouseEnabled{true},
    m_is2D{ parentItem->isGraphicsItem2D() }
{

    resetControllers();
    process = [this](Qx::x_real dlt)
    {
        if( !m_camera )
            return;

        if( m_is2D )
            manage2DCamera(dlt);
        else
            manage3DCamera(dlt);

    };
}

void CameraController::setCamera(prv::GraphicsCamera *newCamera)
{
    m_camera = newCamera;
}

void CameraController::setMovement(CamMoves mv, const x_string &input)
{
    addInput( mv,  input );
}

void CameraController::enableMouse(bool enbl)
{
    m_mouseEnabled = enbl;
}


void CameraController::update2DCamera(const x_vector3 &panDelta,
                                      const x_vector3 &mouseDelta,
                                      x_real dlt)
{
    const auto camProperties = m_camera->properties;
    auto nwPos = camProperties.position();
    nwPos += panDelta;
    nwPos += mouseDelta;
    m_camera->properties.setPosition(nwPos);
    m_camera->update();

}

void CameraController::update3DCamera(const x_vector3 &panDelta,
                                    const x_vector3 &mouseDelta,
                                    x_real dlt)
{

    const auto camProperties = m_camera->properties;

    auto pos = camProperties.position();
    auto ctr = camProperties.forward(); // Actually the look-at target.

    bool updt = false;

    auto clampVec3 = [](const x_vector3& v,
                        const x_vector3& mn,
                        const x_vector3& mx)
    {
        return x_vector3{
            x_vector::clamp(v.x, mn.x, mx.x),
            x_vector::clamp(v.y, mn.y, mx.y),
            x_vector::clamp(v.z, mn.z, mx.z)
        };
    };

    //----------------------------------------------------------------------
    // Pan
    //----------------------------------------------------------------------

    if (panDelta != x_vector3{0,0,0})
    {
        updt = true;

        const auto nPanDelta =
            m_panSpeed * dlt * x_vector::normalize(panDelta);

        pos += nPanDelta;
        ctr += nPanDelta;

        // pos = clampVec3(pos, m_minPosition, m_maxPosition);
        // ctr = clampVec3(ctr, m_minPosition, m_maxPosition);
    }

    //----------------------------------------------------------------------
    // Rotate (original implementation)
    //----------------------------------------------------------------------

    if (mouseDelta != x_vector3{0,0,0})
    {
        updt = true;

        const auto yaw   = -mouseDelta.x * m_rotationSensitivity;
        const auto pitch = -mouseDelta.y * m_rotationSensitivity;

        x_vector3 v = pos - ctr;

        // Rotate around world up.
        v = rotateAroundAxis(v, {0,1,0}, yaw);

        // Compute the new camera basis.
        const auto currentForward =
            x_vector::normalize(-v);

        const auto currentRight =
            x_vector::normalize(
                x_vector::cross(currentForward, {0,1,0}));

        // Rotate around camera right.
        v = rotateAroundAxis(v, currentRight, pitch);

        pos = ctr + v;

        const auto newForward =
            x_vector::normalize(ctr - pos);

        const auto newRight =
            x_vector::normalize(
                x_vector::cross(newForward, {0,1,0}));

        const auto newUp =
            x_vector::cross(newRight, newForward);

        m_camera->properties.setUp(newUp);

        // pos = clampVec3(pos, m_minPosition, m_maxPosition);
    }

    //----------------------------------------------------------------------
    // Zoom
    //----------------------------------------------------------------------

    if (m_mouseWheel != x_vector3{0,0,0})
    {
        updt = true;
        const auto mouseScrollDelta = m_mouseWheel.x;
        const auto v = ctr - pos;
        float dist = x_vector::length(v);
        dist = x_vector::clamp(
            dist - mouseScrollDelta * m_zoomSpeed,
            0.5f,
            500.0f);
        pos = ctr - x_vector::normalize(v) * dist;
        // pos = clampVec3(pos, m_minPosition, m_maxPosition);
    }

    if (!updt)
        return;

    m_camera->properties.setPosition(pos);
    m_camera->properties.setForward(ctr);

    m_camera->update();
}


glm::vec3 CameraController::rotateAroundAxis(const glm::vec3 &v,
                                             const glm::vec3 &axis,
                                             x_real angleRadians) {
    // Ensure the axis is normalized to avoid scaling artifacts
    glm::vec3 normAxis = glm::normalize(axis);

    // Create a quaternion representing the rotation
    glm::quat rotation = glm::angleAxis(angleRadians, normAxis);

    // Rotate the vector using the quaternion operator*
    return rotation * v;
}

x_vector3 CameraController::limitedPosition( const x_vector3 &pos ) const
{
    return pos;
    // Clamp camera position to stay within boundaries
    auto ret = pos;
    ret.x = x_vector::clamp(pos.x, m_minPosition.x, m_maxPosition.x);
    ret.y = x_vector::clamp(pos.y, m_minPosition.y, m_maxPosition.y);
    ret.z = x_vector::clamp(pos.z, m_minPosition.z, m_maxPosition.z);


    // ret.x = -100;
    dbg_print_st() << ret.x;
    return x_vector::clamp(pos,m_minPosition,m_maxPosition);
}

void CameraController::manage2DCamera(x_real dlt)
{
    x_vector3 panDelta{0,0,0};
    x_vector3 mouseMove{0,0,0};
    x_vector3 mouseDlt {0,0,0};


    // 1. Compute basis vectors
    const x_vector3 horizontal = {1,0,0};
    const x_vector3 vertical   = {0,1,0};

    if( checkAction( CamMoves::MouseWheel2D, m_mouseWheel ) ){
    }
    else
        m_mouseWheel = {};

    if( checkAction( CamMoves::MousePress, m_mousePress ) ){
    }

    if( checkAction( CamMoves::MousePan2D, mouseMove ) ){
        mouseDlt = m_mousePress-mouseMove;
        m_mousePress = mouseMove;
    }

    if( checkAction( CamMoves::PanLeft2D ) ){
        panDelta -= horizontal;
    }
    if( checkAction( CamMoves::PanRight2D ) ){
        panDelta += horizontal;
    }

    if( checkAction( CamMoves::PanDownward2D ) ){
        panDelta += vertical;
    }
    if( checkAction( CamMoves::PanUpward2D ) ){
        panDelta -= vertical;
    }
    if( panDelta == x_vector3{0} && mouseDlt == x_vector3{0} )
        return;
    update2DCamera( panDelta, mouseDlt, dlt );
}

void CameraController::manage3DCamera(x_real dlt)
{
    x_vector3 panDelta{0,0,0};
    x_vector3 mouseMove{0,0,0};
    x_vector3 mouseDlt {0,0,0};
    const auto camProperties = m_camera->properties;


    // 1. Compute basis vectors
    const x_vector3 forward = x_vector::normalize( camProperties.forward() - camProperties.position() );
    const x_vector3 right   = x_vector::normalize( x_vector::cross(forward, camProperties.up()));

    if( checkAction( CamMoves::MouseWheel3D, m_mouseWheel ) ){
    }
    else
        m_mouseWheel = {};

    if( checkAction( CamMoves::MousePress, m_mousePress ) ){
    }

    if( checkAction( CamMoves::MouseRotation3D, mouseMove ) ){
        mouseDlt = m_mousePress-mouseMove;
        m_mousePress = mouseMove;
    }

    if( checkAction( CamMoves::PanLeft3D ) ){
        panDelta -= right;
    }
    if( checkAction( CamMoves::PanRight3D ) ){
        panDelta += right;
    }

    if( checkAction( CamMoves::PanForward3D ) ){
        panDelta += forward;
    }
    if( checkAction( CamMoves::PanBackward3D ) ){
        panDelta -= forward;
    }
    if( panDelta == x_vector3{0} && mouseDlt == x_vector3{0} )
        return;
    update3DCamera( panDelta, mouseDlt, dlt );
}

x_real CameraController::zoomSpeed() const
{
    return m_zoomSpeed;
}

void CameraController::setZoomSpeed(x_real newZoomSpeed)
{
    m_zoomSpeed = newZoomSpeed;
}

void CameraController::resetControllers()
{
    reset();
    if( m_is2D )
        reset2DControllers();
    else
        reset3DControllers();

}

void CameraController::reset2DControllers()
{
    setMovement( CamMoves::PanLeft2D,     "Q" );
    setMovement( CamMoves::PanRight2D,    "D" );
    setMovement( CamMoves::PanUpward2D,   "Z" );
    setMovement( CamMoves::PanDownward2D, "S" );

    addInput( CamMoves::MousePan2D,
             Qx::MouseButton::Left,
             Qx::MouseEventType::MouseMove);

    addInput( CamMoves::MouseWheel2D,
             Qx::MouseButton::None,
             Qx::MouseEventType::MouseWheel);


}

void CameraController::reset3DControllers()
{
    setMovement( CamMoves::PanLeft3D,     "Q" );
    setMovement( CamMoves::PanRight3D,    "D" );
    setMovement( CamMoves::PanForward3D,  "Z" );
    setMovement( CamMoves::PanBackward3D, "S" );

    addInput( CamMoves::MousePress,
             Qx::MouseButton::Left,
             Qx::MouseEventType::MousePress);

    addInput( CamMoves::MouseRotation3D,
             Qx::MouseButton::Left,
             Qx::MouseEventType::MouseMove);

    addInput( CamMoves::MouseWheel3D,
             Qx::MouseButton::None,
             Qx::MouseEventType::MouseWheel);

}


x_real CameraController::rotationSensitivity() const
{
    return m_rotationSensitivity;
}

void CameraController::setRotationSensitivity(x_real newRotationSensitivity)
{
    m_rotationSensitivity = newRotationSensitivity;
}

x_real CameraController::panSpeed() const
{
    return m_panSpeed;
}

void CameraController::setPanSpeed(x_real newSpeed)
{
    m_panSpeed = newSpeed;
}



}
