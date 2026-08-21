/// ## Threads are added using gemini, NOT TESTED

// #ifndef NANOFLANN_THREADED_H
// #define NANOFLANN_THREADED_H



// #include <misc/defs.h>
// #include <nanoflann/nanoflann.hpp>
// #include <thread>
// #include <vector>
// #include <mutex>
// #include <algorithm>

// namespace Qx {

// template <typename CollisionsContainer>
// class NanoFlann
// {
//     constexpr static uint8_t DIM      = CollisionsContainer::DIM;
//     constexpr static uint8_t MAX_LEAF = CollisionsContainer::MAX_LEAF;

//     // Define the KD-Tree Type
//     using my_kd_tree_t = nanoflann::KDTreeSingleIndexAdaptor<
//         nanoflann::L2_Simple_Adaptor<x_real, CollisionsContainer>,
//         CollisionsContainer,
//         DIM
//         >;

// public:

//     static void search(CollisionsContainer &cloud, x_real dlt)
//     {
//         cloud.collect();

//         my_kd_tree_t index(DIM,
//                            cloud,
//                            nanoflann::KDTreeSingleIndexAdaptorParams(MAX_LEAF));
//         index.buildIndex();

//         // Structure to hold deferred pairs
//         struct CollisionPair {
//             bool   impact; /// Collision or Visibility
//             size_t first_idx;
//             size_t second_idx;
//         };

//         std::vector<CollisionPair> pending_collisions;
//         std::mutex pending_mutex;

//         const auto cnt = cloud.collisions.size();
//         if (cnt == 0)
//             return;

//         // Determine number of threads to use safely based on hardware
//         unsigned int num_threads = std::thread::hardware_concurrency();
//         if (num_threads == 0)
//             num_threads = 2;

//         // Don't spawn more threads than items
//         if (static_cast<size_t>(num_threads) > cnt) {
//             num_threads = static_cast<unsigned int>(cnt);
//         }

//         auto worker = [&](size_t start_idx, size_t end_idx) {
//             // Thread-local buffers for nanoflann and local results
//             nanoflann::SearchParameters local_search_params;
//             std::vector<nanoflann::ResultItem<unsigned int, x_real>> local_ret_matches;
//             std::vector<CollisionPair> local_pending_collisions;

//             for (size_t i = start_idx; i < end_idx; ++i) {
//                 const auto &collision = cloud.collisionAt(i);

//                 if (!collision.isActive)
//                     continue;

//                 const auto ctr = collision.center;

//                 x_real query_pt[3] = { ctr.x, ctr.y, ctr.z };
//                 x_real search_radius = collision.visibleRadius * collision.visibleRadius;

//                 // Perform radius search using thread-local match vector
//                 size_t nMatches = index.radiusSearch(query_pt, search_radius, local_ret_matches, local_search_params);

//                 for (size_t j = 0; j < nMatches; ++j) {
//                     const auto target_idx = local_ret_matches[j].first;

//                     // Avoid self-collision and duplicate pairs (process only if i < target_idx)
//                     if (target_idx <= i)
//                         continue;

//                     x_real dist_sq = local_ret_matches[j].second;

//                     /// --- NARROW PHASE ---
//                     const auto &otherColsn = cloud.collisionAt(target_idx);

//                     if (!otherColsn.isActive)
//                         continue;

//                     const auto sameLayer = collision.layer | otherColsn.mask;
//                     if (!sameLayer)
//                         continue;

//                     auto idx = i;
//                     auto jdx = target_idx;

//                     /// Check for a collision
//                     const auto cr1 = collision.boundingRadius;
//                     const auto cr2 = otherColsn.boundingRadius;
//                     const auto combined_collision = (cr1 + cr2) * (cr1 + cr2);

//                     if (dist_sq <= combined_collision) {
//                         local_pending_collisions.push_back({true, idx, jdx});
//                         continue;
//                     }

//                     /// Check for a visibility
//                     const auto vr1 = collision.visibleRadius;
//                     const auto vr2 = otherColsn.boundingRadius;
//                     const auto combined_visibility = (vr1 + vr2) * (vr1 + vr2);

//                     if (dist_sq <= combined_visibility)
//                         local_pending_collisions.push_back({false, idx, jdx});
//                 }
//             }

//             // Safely merge thread-local findings into the global container
//             std::lock_guard<std::mutex> lock(pending_mutex);
//             pending_collisions.insert(
//                 pending_collisions.end(),
//                 local_pending_collisions.begin(),
//                 local_pending_collisions.end()
//                 );
//         };

//         // Launch worker threads
//         std::vector<std::thread> threads;
//         threads.reserve(num_threads);

//         size_t chunk_size = cnt / num_threads;
//         for (unsigned int t = 0; t < num_threads; ++t) {
//             size_t start_idx = t * chunk_size;
//             size_t end_idx = (t == num_threads - 1) ? cnt : (start_idx + chunk_size);

//             threads.emplace_back(worker, start_idx, end_idx);
//         }

//         // Wait for all threads to complete
//         for (auto &th : threads) {
//             th.join();
//         }

//         // --- SEQUENTIAL EXECUTION PHASE ---
//         // Safe modification of cloud since threads have finished execution
//         dbg_print() << pending_collisions.size();
//         for (const auto &pair : pending_collisions)
//             cloud.collision(pair.first_idx, pair.second_idx, pair.impact);
//     }
// };

// }

// #endif // NANOFLANN_THREADED_H
