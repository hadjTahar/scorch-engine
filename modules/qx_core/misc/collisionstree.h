#ifndef COLLISIONSTREE_H
#define COLLISIONSTREE_H

#include <misc/defs.h>
#include <nanoflann/nanoflann.hpp>


namespace Qx {


template <typename CollisionsContainer>
class CollisionsTree
{

    constexpr static uint8_t DIM      = CollisionsContainer::DIM;
    constexpr static uint8_t MAX_LEAF = CollisionsContainer::MAX_LEAF;

    // 3. Define the KD-Tree Type
    using my_kd_tree_t = nanoflann::KDTreeSingleIndexAdaptor<
        nanoflann::L2_Simple_Adaptor<x_real, CollisionsContainer>,
        CollisionsContainer,
        DIM
        >;

public:

    static void search( CollisionsContainer &cloud, x_real dlt)
    {

        // CollisionsContainer cloud;
        cloud.collect();

        my_kd_tree_t index(DIM,
                           cloud,
                           nanoflann::KDTreeSingleIndexAdaptorParams(MAX_LEAF));
        index.buildIndex();

        // Structure to hold deferred pairs
        // enum class CollisionType { Collision, Visibility };
        struct CollisionPair {
            bool   impact; /// ## Collision or Visibility
            size_t first_idx;
            size_t second_idx;
        };
        std::vector<nanoflann::ResultItem<unsigned int, x_real>> ret_matches;
        nanoflann::SearchParameters search_params;

        const auto cnt = cloud.collisions.size();
        std::vector<CollisionPair> pending_collisions;
        pending_collisions.reserve( 5 * cnt );

        for (size_t i = 0; i < cnt; ++i) {
            const auto &collision = cloud.collisionAt(i);

            if ( !collision.isActive )
                continue;

            const auto ctr = collision.center;

            x_real query_pt[3] = { ctr.x, ctr.y, ctr.z };
            x_real search_radius = collision.visibleRadius * collision.visibleRadius;
            // Perform radius search
            size_t nMatches = index.radiusSearch(query_pt, search_radius, ret_matches, search_params);

            for (size_t j = 0; j < nMatches; ++j) {
                const auto target_idx = ret_matches[j].first;

                // Avoid self-collision and duplicate pairs (e.g., process only if i < target_idx)
                if (target_idx <= i)
                    continue;

                x_real dist_sq = ret_matches[j].second;
                // dbg_print() << i << " - " << target_idx;

                /// ## --- NARROW PHASE ---
                /// ## Since nanoflann checked bounding points/centers, do precise check here if needed:
                const auto &otherColsn  = cloud.collisionAt(target_idx);

                if ( !otherColsn.isActive )
                    continue;

                const auto sameLayer = collision.layer | otherColsn.mask;
                if ( !sameLayer )
                    continue;

                /// ## X : No longer needed, since both parties need to
                /// ## be informed
                /// ## Swap indices, if necessary
                auto idx = i;
                auto jdx = target_idx;

                // if( collision.layer > otherColsn.layer ){
                //     idx = target_idx;
                //     jdx = static_cast<size_t>(i);
                // }


                /// ## Check for a collision
                const auto cr1 = collision.boundingRadius;
                const auto cr2 = otherColsn.boundingRadius;
                const auto combined_collision = (cr1 + cr2) * (cr1 + cr2);
                /// ## Collision detected!
                if (dist_sq <= combined_collision){
                    pending_collisions.push_back({true ,idx, jdx});
                    continue;
                }

                /// ## Check for a visibility
                const auto vr1 = collision.visibleRadius;
                const auto vr2 = otherColsn.boundingRadius;
                const auto combined_visibility = (vr1 + vr2) * (vr1 + vr2);

                /// ## Visibility detected!
                if (dist_sq <= combined_visibility)
                    pending_collisions.push_back({ false,idx, jdx});

            }
        } /// ## For-Loop End


        // dbg_print() << pending_collisions.size();
        for (const auto &pair : pending_collisions)
            cloud.collision( pair.first_idx, pair.second_idx, pair.impact );
    }
};

}

#endif // COLLISIONSTREE_H
