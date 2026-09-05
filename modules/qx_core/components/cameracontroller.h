#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

#include "inputeventcomponent.h"


namespace Qx
{


using CameraBaseInput = InputEventComponent<CamMoves>;


class CameraController : public CameraBaseInput
{
public:
    CameraController(prv::GraphicsItem *parentItem);
    void setCamera(prv::GraphicsCamera *newCamera);
    void setMovement(CamMoves mv, const x_string &input);
    void enableMouse(bool enbl);

    x_real panSpeed() const;
    void setPanSpeed(x_real newSpeed);

    x_real rotationSensitivity() const;
    void setRotationSensitivity(x_real newRotationSensitivity);

    x_real zoomSpeed() const;
    void setZoomSpeed(x_real newZoomSpeed);
    void resetControllers();

protected:
    void reset2DControllers();
    void reset3DControllers();

    // using addInput;
    using CameraBaseInput::addInput;
    void update2DCamera(const x_vector3 &panDelta,
                        const x_vector3 &mouseDelta,
                        x_real dlt );
    void update3DCamera(const x_vector3 &panDelta,
                        const x_vector3 &mouseDelta,
                        x_real dlt );

    // Rotates a vector 'v' around an arbitrary axis by 'angleRadians'
    glm::vec3 rotateAroundAxis(const glm::vec3& v,
                               const glm::vec3& axis,
                               x_real angleRadians);
    
    x_vector3 limitedPosition(const x_vector3 &pos) const;

    void manage2DCamera(Qx::x_real dlt);
    void manage3DCamera(Qx::x_real dlt);

protected:
    prv::GraphicsCamera *m_camera;
    x_real m_rotationSensitivity;
    x_real m_panSpeed;
    x_real m_zoomSpeed;
    x_vector3 m_mousePress;
    x_vector3 m_mouseWheel;

    x_vector3 m_minPosition{-1000.0f, -1000.0f,  -1000.0f};
    x_vector3 m_maxPosition{ 1000.0f,  1000.0f, 1000.0f};

    float m_yaw   = 0.0f;
    float m_pitch = 0.0f;

    constexpr static float PI = 3.14159265358979323846f;
    float m_minPitch = -89.0f*PI/180.f;
    float m_maxPitch = 89.0f*PI/180.f;

    float m_minYaw = -3.141592654f;
    float m_maxYaw =  3.141592654f;


    bool   m_mouseEnabled;
    bool   m_is2D;
};


}
#endif // CAMERACONTROLLER_H
