#include "mainwindow.h"

#include <items/rectangle.h>
#include <core/graphicsitem2d.h>
#include <core/graphicsscene2d.h>
#include <misc/collisions.h>
#include <misc/collisionstree.h>



struct CollisionsContainer {

    constexpr static uint8_t DIM = 3;
    constexpr static uint8_t MAX_LEAF = 10;

    std::vector<Qx::Collision>  collisionsSource;
    std::vector<Qx::Collision*> collisions;

    /// ## Fill collisions, Eg: from an ecs
    inline void collect()
    {
        collisionsSource.clear();
        collisions.clear();

        collisionsSource = {
                      {{1.0, 2.0, 3.0}},
                      {{4.0, 5.0, 6.0}},
                      {{10.0, 11.0, 12.0}},
                      // Intentionally close to the first point
                      {{1.1, 2.1, 3.1}},
                      {{1.1, 2.1, 3.1}},
                      {{1.1, 2.1, 3.1}},
                      {{1.1, 2.1, 3.1}},
                      };

        for ( auto &col : collisionsSource)
            collisions.push_back( &col );
    }

    Qx::Collision &collisionAt( size_t idx )
    {
        return *collisions[ idx ];
    }

    /// ## Must return the total number of data points
    inline size_t kdtree_get_point_count() const {
        return collisions.size();
    }

    /// ## Must return the dim-th coordinate of the idx-th Element
    inline Qx::x_real kdtree_get_pt(const size_t idx, const size_t dim) const {
        if (dim == 0) return collisions[idx]->center.x;
        if (dim == 1) return collisions[idx]->center.y;
        return collisions[idx]->center.z;
    }

    static void collision( size_t idx, size_t jdx, bool impact )
    {
        if( impact )
            dbg_print() << idx << " collided with : " << jdx;
        else
            dbg_print() << idx << " can see       : " << jdx;
    }

    /// ## Optional: Return false to use the default bounding box computation
    template <class BBOX>
    bool kdtree_get_bbox(BBOX& /* bb */) const {
        return false;
    }
};



MainWindow::MainWindow(CoreItem *parent):
    Qx::prv::GraphicsWindow{ parent }
{
    auto scene = addItem<Qx::prv::GraphicsScene2D>();
    auto vw0 = scene->addView();
    auto cam0 = vw0->camera();
    auto itm = scene->addItem<Qx::Rectangle>();

    CollisionsContainer cloud;
    Qx::CollisionsTree<CollisionsContainer>::search( cloud, 1 );
}
