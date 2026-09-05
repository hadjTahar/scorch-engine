#ifndef STEERINGMOTION_H
#define STEERINGMOTION_H

#include <components/corecomponent.h>

#include <easing/beziereasing.h>
#include <easing/dampedeasing.h>
#include <easing/polynomialeasing.h>



namespace Qx::prv
{

class SteeringMotion : public prv::CoreComponent
{
public:
    SteeringMotion(prv::GraphicsItem *parentItem);

protected:
    // Returns a velocity vector toward a target
    static x_vector3 Seek(x_vector3 currentPos, x_vector3 targetPos, float speed);

    // Follow logic
    static x_vector3 Follow(x_vector3 currentPos, x_vector3 targetPos, float speed, float stopDistance);



protected:
    /// ## prevent from changing ::process
    x_processCallback &process;
    DampedEasing       m_speedEasing;
    bool               m_done;

};

}
#endif // STEERINGMOTION_H
