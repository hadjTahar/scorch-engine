#include "../test_utils/tree_tests.h"
#include <benchmark/benchmark.h>



static void BM_LAYER_1_ADD(benchmark::State& state) {
    std::size_t count = static_cast<std::size_t>(state.range(0));
    for (auto _ : state)
    {
        dbg_unused( _ );
        Qx::prv::tests::layer_1_add( {count,0});
        benchmark::ClobberMemory(); // prevent compiler optimizing it away
    }
}

static void BM_LAYER_1_ADD_REMOVE(benchmark::State& state) {
    std::size_t count = static_cast<std::size_t>(state.range(0));
    for (auto _ : state)
    {
        dbg_unused( _ );
        Qx::prv::tests::layer_1_add_remove( {count,0});
        benchmark::ClobberMemory(); // prevent compiler optimizing it away
    }
}

static void BM_LAYER_1_CLEAR(benchmark::State& state) {
    std::size_t count = static_cast<std::size_t>(state.range(0));
    for (auto _ : state)
    {
        dbg_unused( _ );
        Qx::prv::tests::layer_1_clear( {count,0});
        benchmark::ClobberMemory(); // prevent compiler optimizing it away
    }
}


BENCHMARK(BM_LAYER_1_ADD)->Unit(benchmark::kMillisecond)->Arg(1000)->Arg(10000)->Arg(100000);
// BENCHMARK(BM_LAYER_1_ADD_REMOVE)->Unit(benchmark::kMillisecond)->Arg(1000)->Arg(10000)->Arg(100000);
// BENCHMARK(BM_LAYER_1_CLEAR)->Unit(benchmark::kMillisecond)->Arg(1000)->Arg(10000)->Arg(100000);

BENCHMARK_MAIN();
