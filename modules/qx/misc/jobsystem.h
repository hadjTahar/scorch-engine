// #ifndef JOBSYSTEM_H
// #define JOBSYSTEM_H


// /// ## Not tested GPT

// #include <vector>
// #include <thread>
// #include <queue>
// #include <functional>
// #include <mutex>
// #include <condition_variable>
// #include <atomic>


// namespace Qx::prv {

// class JobSystem
// {
// public:
//     using Job = std::function<void()>;

//     JobSystem(x_count workerCount = std::thread::hardware_concurrency() - 1)
//         : m_stop(false), m_activeJobs(0)
//     {
//         if (workerCount == 0)
//             workerCount = 1;

//         for (x_count i = 0; i < workerCount; ++i)
//         {
//             m_workers.emplace_back([this] { workerLoop(); });
//         }
//     }

//     ~JobSystem()
//     {
//         {
//             std::lock_guard lock(m_queueMutex);
//             m_stop = true;
//         }

//         m_jobAvailable.notify_all();

//         for (auto& t : m_workers)
//             t.join();
//     }

//     // Submit a job (thread-safe)
//     void submit(Job job)
//     {
//         {
//             std::lock_guard lock(m_queueMutex);
//             m_jobs.push(std::move(job));
//             ++m_activeJobs;
//         }
//         m_jobAvailable.notify_one();
//     }

//     // Wait until all submitted jobs are finished
//     void wait()
//     {
//         std::unique_lock lock(m_waitMutex);
//         m_finished.wait(lock, [this] {
//             return m_activeJobs.load() == 0;
//         });
//     }

// private:
//     void workerLoop()
//     {
//         while (true)
//         {
//             Job job;

//             {
//                 std::unique_lock lock(m_queueMutex);
//                 m_jobAvailable.wait(lock, [this] {
//                     return m_stop || !m_jobs.empty();
//                 });

//                 if (m_stop && m_jobs.empty())
//                     return;

//                 job = std::move(m_jobs.front());
//                 m_jobs.pop();
//             }

//             // Execute job
//             job();

//             // Signal completion
//             if (--m_activeJobs == 0)
//             {
//                 std::lock_guard lock(m_waitMutex);
//                 m_finished.notify_all();
//             }
//         }
//     }

// private:
//     std::vector<std::thread>     m_workers;
//     std::queue<Job>              m_jobs;

//     std::mutex                   m_queueMutex;
//     std::condition_variable      m_jobAvailable;

//     std::mutex                   m_waitMutex;
//     std::condition_variable      m_finished;

//     std::atomic<x_count>          m_activeJobs;
//     bool                         m_stop;
// };

// }


// #endif // JOBSYSTEM_H
