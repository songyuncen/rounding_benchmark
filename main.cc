#include <cmath>
#include <immintrin.h>
#include "benchmark/benchmark.h"

double numbers[] = { 1.1, 1.6, -1.3, -1.6, 0.1, -0.1, 0.7, -0.7, 4.0, -4.0 };
constexpr int N = sizeof(numbers) / sizeof(double);

inline int IntrinRound(double d) {
  __m128d f = _mm_load_sd(&d);
  int i = _mm_cvtsd_i32(f);
  return i;
}

inline int IntrinCeil(double d) {
  constexpr unsigned int bit_mask = 0b10 << 13;

  unsigned int old_csr = _mm_getcsr();
  unsigned int new_csr = old_csr | bit_mask;
  _mm_setcsr(new_csr);

  __m128d f = _mm_load_sd(&d);
  int i = _mm_cvtsd_i32(f);
  _mm_setcsr(old_csr);
  return i;
}

inline int IntrinFloor(double d) {
  constexpr unsigned int bit_mask = 0b01 << 13;
  unsigned int old_csr = _mm_getcsr();
  unsigned int new_csr = old_csr | bit_mask;
  _mm_setcsr(new_csr);

  __m128d f = _mm_load_sd(&d);
  int i = _mm_cvtsd_i32(f);
  _mm_setcsr(old_csr);
  return i;
}

inline int CalcRound(double value) {
  return (int)(value + (value >= 0 ? 0.5 : -0.5));
}

inline int CalcFloor(double value) {
  int i = (int)value;
  return i - (i > value);
}

inline int CalcCeil(double value) {
  int i = (int)value;
  return i + (i < value);
}

//

static void BM_CMathRound(benchmark::State& state) {
  int res[N];
  for (auto _ : state) {
    for (int i = 0; i < N; ++i) {
      res [i] = std::round(numbers[i]);
    }
  }

  for (int i = 0; i < N; ++i) {
    res[i] = i + res[i];
  }
}

static void BM_CMathFloor(benchmark::State& state) {
  int res[N];
  for (auto _ : state) {
    for (int i = 0; i < N; ++i) {
      res [i] = std::floor(numbers[i]);
    }
  }

  for (int i = 0; i < N; ++i) {
    res[i] = i + res[i];
  }
}

static void BM_CMathCeil(benchmark::State& state) {
  int res[N];
  for (auto _ : state) {
    for (int i = 0; i < N; ++i) {
      res [i] = std::ceil(numbers[i]);
    }
  }

  for (int i = 0; i < N; ++i) {
    res[i] = i + res[i];
  }
}




static void BM_CalcRound(benchmark::State& state) {
  int res[N];
  for (auto _ : state) {
    for (int i = 0; i < N; ++i) {
      res[i] = CalcRound(numbers[i]);
    }
  }

  for (int i = 0; i < N; ++i) {
    res[i] = i + res[i];
  }
}

static void BM_CalcFloor(benchmark::State& state) {
  int res[N];
  for (auto _ : state) {
    for (int i = 0; i < N; ++i) {
      res[i] = CalcFloor(numbers[i]);
    }
  }

  for (int i = 0; i < N; ++i) {
    res[i] = i + res[i];
  }
}

static void BM_CalcCeil(benchmark::State& state) {
  int res[N];
  for (auto _ : state) {
    for (int i = 0; i < N; ++i) {
      res[i] = CalcCeil(numbers[i]);
    }
  }

  for (int i = 0; i < N; ++i) {
    res[i] = i + res[i];
  }
}

static void BM_IntrinRound(benchmark::State& state) {
  int res[N];
  for (auto _ : state) {
    for (int i = 0; i < N; ++i) {
      res[i] = IntrinRound(numbers[i]);
    }
  }

  for (int i = 0; i < N; ++i) {
    res[i] = i + res[i];
  }
}

static void BM_IntrinFloor(benchmark::State& state) {
  int res[N];
  for (auto _ : state) {
    for (int i = 0; i < N; ++i) {
      res[i] = IntrinFloor(numbers[i]);
    }
  }

  for (int i = 0; i < N; ++i) {
    res[i] = i + res[i];
  }
}

static void BM_IntrinCeil(benchmark::State& state) {
  int res[N];
  for (auto _ : state) {
    for (int i = 0; i < N; ++i) {
      res[i] = IntrinCeil(numbers[i]);
    }
  }

  for (int i = 0; i < N; ++i) {
    res[i] = i + res[i];
  }
}


BENCHMARK(BM_CalcRound)->Repetitions(10)->ReportAggregatesOnly(true);
BENCHMARK(BM_CMathRound)->Repetitions(10)->ReportAggregatesOnly(true);
BENCHMARK(BM_IntrinRound)->Repetitions(10)->ReportAggregatesOnly(true);

BENCHMARK(BM_CalcFloor)->Repetitions(10)->ReportAggregatesOnly(true);
BENCHMARK(BM_CMathFloor)->Repetitions(10)->ReportAggregatesOnly(true);
BENCHMARK(BM_IntrinFloor)->Repetitions(10)->ReportAggregatesOnly(true);

BENCHMARK(BM_CalcCeil)->Repetitions(10)->ReportAggregatesOnly(true);
BENCHMARK(BM_CMathCeil)->Repetitions(10)->ReportAggregatesOnly(true);
BENCHMARK(BM_IntrinCeil)->Repetitions(10)->ReportAggregatesOnly(true);

