#ifndef COLLISIONS_H
#define COLLISIONS_H

#include "vecs.h"
#include <type_traits>

namespace Qx {

/// ## Check ecsFlann for an example
struct Collision {
    x_vector3   center{};
    x_real      visibleRadius{1};  /// ## For visibility
    x_real      boundingRadius{1}; /// ## bounding box radius, for a hit
    x_layers    layer{1};          /// ## What category am I? (e.g., Layer_Bullet)
    /// ## Layer is also used for precedence to reorder
    /// ## ::collisionCallback, indices,
    /// ## Eg; ::collision( idx, jdx ) or ::collision( jdx, idx )
    /// ## ie, who hits who
    x_layers    mask{1};           /// What can I hit? (e.g., Layer_Enemy | Layer_Environment)
    uint8_t     precedence;
    bool        isActive{true};
};


// template<
//     typename EntityType,
//     typename = std::enable_if_t<std::is_enum_v<EntityType>>
//     >
// struct Entity {
//     size_t      id{0};
//     EntityType  type;
//     x_vector3   center{};
//     Collision   collision;
// };


struct BoidCollision : public Collision
{
    x_real protectedRadius;

    x_vector3 close{0};
    /// ## Acumulated averages
    x_vector3 vel_acum{0};
    x_vector3 pos_acum{0};
    x_vector3 velocity{1,1,1};
    x_real vel_neighboring_boids = 0;
    x_real pos_neighboring_boids = 0;

    x_real minspeed = 10.1;
    x_real maxspeed = 20.5;

    static inline x_real matchingfactor{.125};
    static inline x_real avoidfactor{3.75};
    static inline x_real centeringfactor{0.005};
    static inline x_real turnfactor{0.2};

    static inline x_vector3 worldMin{-30,-30,-10};
    static inline x_vector3 worldMax{30,30,10};


    void flock( BoidCollision *oth)
    {
        if( oth == this )
            return;

        const auto &ctr    = center;
        const auto &othCtr = oth->center;
        const auto  dltCtr = othCtr-ctr;


        /// ## All of this just to avoid sqrt..
        /// ## Squared radius
        const auto rd = dltCtr.x * dltCtr.x +
                        dltCtr.y * dltCtr.y +
                        dltCtr.z * dltCtr.z;

        /// ## Protected radius
        const auto pr1 = boundingRadius;
        const auto pr2 = oth->boundingRadius;
        const auto combined_pr = (pr1 + pr2) * (pr1 + pr2);

        /// ## Visibile radius
        const auto vr1 = visibleRadius;
        const auto vr2 = oth->visibleRadius;
        const auto combined_vr = (vr1 + vr2) * (vr1 + vr2);
        /// ## ------------------------------------

        /// ## Separation
        if ( rd < combined_pr)
            close += ctr - othCtr;
        if (rd < combined_vr ) {
            /// ## Alignment
            vel_acum += oth->velocity;
            vel_neighboring_boids += 1;
            /// ## Cohesion
            pos_acum += oth->center;
            pos_neighboring_boids += 1;
        }
    }


    void updateSeparation()
    {
        velocity += avoidfactor * close;
    }

    void updateAlignment()
    {
        if( vel_neighboring_boids <= 0 )
            return;
        const auto vel_avg = vel_acum / vel_neighboring_boids;
        velocity += matchingfactor * (vel_avg - velocity);

    }

    void updateCohesion()
    {
        if( pos_neighboring_boids <= 0 )
            return;
        const auto pos_avg = pos_acum/pos_neighboring_boids;
        velocity += centeringfactor * (pos_avg - center);
    }

    void updateEdges()
    {
        /// ## Screen edges
        if (center.x < worldMin.x)
            velocity.x = velocity.x + turnfactor;
        else if (center.x > worldMax.x)
            velocity.x = velocity.x - turnfactor;

        if (center.y < worldMin.y)
            velocity.y = velocity.y + turnfactor;
        else if (center.y > worldMax.x)
            velocity.y = velocity.y - turnfactor;

        if( center.z < worldMax.z )
            velocity.z = velocity.z + turnfactor;
        else if (center.z > worldMax.z)
            velocity.z = velocity.z - turnfactor;
    }

    void updateSpeedLimits()
    {

        const auto vx = velocity.x;
        const auto vy = velocity.y;
        const auto vz = velocity.z;

        const auto speed = sqrt(vx*vx + vy*vy + vz*vz);
        // dbg_print_st() << speed;



        if (speed < minspeed && speed > 0 )
            velocity = (velocity/speed) * minspeed;
        else if (speed > maxspeed)
            velocity = (velocity/speed) * maxspeed;

    }


    void updateCenter( x_real dlt )
    {

        updateSeparation();
        updateAlignment();
        updateCohesion();
        updateEdges();
        updateSpeedLimits();

        const auto seconds = dlt/1000.f;
        center = center + velocity * seconds;

        /// ## Reset averages
        close    = {0, 0, 0};
        vel_acum = {0, 0, 0};
        pos_acum = {0, 0, 0};
        vel_neighboring_boids = 0;
        pos_neighboring_boids = 0;

    }
};



}

#endif // COLLISIONS_H
