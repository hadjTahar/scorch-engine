#ifndef ECSCOLLISIONCOMPONENT_H
#define ECSCOLLISIONCOMPONENT_H

#include <components/corecomponent.h>
#include <flecs.h>
#include <misc/collisionstree.h>



namespace Qx {


template <typename CollisionType, auto collisionCallback>
class ECSCollisionComponent : public prv::CoreComponent
{
public:

    ECSCollisionComponent( prv::GraphicsItem *gItem):
        prv::CoreComponent( gItem ),
        collisionsSource{ nullptr }
    {
        process = [this]( x_real dlt )
        {
            CollisionsTree<ECSCollisionComponent>::search( *this, dlt );
        };
    }


    constexpr static uint8_t DIM      = 3;
    constexpr static uint8_t MAX_LEAF = 10;


    flecs::world const*  collisionsSource;
    std::vector<CollisionType*> collisions;
    // std::vector<flecs::entity> entities; // Store entity handles directly!

    /// ## Fill collisions, Eg: from an ecs
    inline void collect()
    {
        collisions.clear();
        // entities.clear();
        if( !collisionsSource )
            return;
        collisionsSource->query<CollisionType>().each([this]
                                                  (flecs::entity e,CollisionType& col)
                                                  {
                                                      collisions.push_back( &col );
                                                      // entities.push_back( e );
                                                  });
    }

    inline CollisionType &collisionAt( size_t idx )
    {
        return *collisions[ idx ];
    }
    /// ## Must return the total number of data points
    inline size_t kdtree_get_point_count() const {
        return collisions.size();
    }
    /// ## Must return the dim-th coordinate of the idx-th Element
    inline x_real kdtree_get_pt(const size_t idx, const size_t dim) const {
        if (dim == 0) return collisions[idx]->center.x;
        if (dim == 1) return collisions[idx]->center.y;
        return collisions[idx]->center.z;
    }
    /// ## Handle the collision
    // static void collision( const CollisionType &cols0, const CollisionType &cols1 )
    // {
    //     collisionCallback( cols0, cols1 );
    //     // dbg_print_st() << &cols0 << " collided with: " << &cols1;

    //     // if (a.type == EntityType::Bullet && b.type == EntityType::Enemy) {
    //     //     a.collision.isActive = false;
    //     //     b.collision.isActive = false;
    //     // }
    // }
    void collision( size_t idx, size_t jdx, bool impact )
    {
        collisionCallback( collisions[idx], collisions[jdx], impact );
    }
    /// ## Optional: Return false to use the default bounding box computation
    template <class BBOX>inline bool kdtree_get_bbox(BBOX& /* bb */) const {return false;}
};

}
#endif // ECSCOLLISIONCOMPONENT_H
