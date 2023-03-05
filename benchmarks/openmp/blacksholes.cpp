#include "benchmarks.hpp"
#include "cpu-microbenchmark/math.hpp"
#include "cpu-microbenchmark/utils.hpp"

#include <iostream>
#include <memory>
#include <vector>

namespace cpubm = cpu_benchmark;

template <typename T> struct Data {
  T spotPrice;
  T strike;
  T rate;
  T dividendRate;
  T volatility;
  T timeToMaturity;
  int type;
  float dividendValue;
  T refValue;
};

template <typename T> static T CNDF(T input) {
  constexpr T inv_sqrt_2xPI = 0.39894228040143270286;

  bool sign = input < 0;

  T xInput = std::abs(input);

  T expValues = cpubm::exp(-0.5f * xInput * xInput);

  T xNPrimeOfX = expValues * inv_sqrt_2xPI;

  T xK2 = 1.0 / (0.2316419 * xInput + 1.0);
  T xK2_2 = xK2 * xK2;
  T xK2_3 = xK2_2 * xK2;
  T xK2_4 = xK2_3 * xK2;
  T xK2_5 = xK2_4 * xK2;

  T xLocal_1 = xK2 * 0.319381530;
  T xLocal_2 = xK2_2 * (-0.356563782);
  T xLocal_3 = xK2_3 * 1.781477937;
  xLocal_2 = xLocal_2 + xLocal_3;
  xLocal_3 = xK2_4 * (-1.821255978);
  xLocal_2 = xLocal_2 + xLocal_3;
  xLocal_3 = xK2_5 * 1.330274429;
  xLocal_2 = xLocal_2 + xLocal_3;

  xLocal_1 = xLocal_2 + xLocal_1;
  T xLocal = xLocal_1 * xNPrimeOfX;
  xLocal = 1.0 - xLocal;

  return sign ? 1.0 - xLocal : xLocal;
}

template <typename T>
static T BlackScholesEq(T spotPrice, T strike, T rate, T volatility, T time,
                        int otype) {
  T xTime = time;
  T xSqrtTime = cpubm::sqrt(xTime);

  T logValues = cpubm::log(spotPrice / strike);

  T xLogTerm = logValues;

  T xPowerTerm = volatility * volatility * 0.5;

  T xDen = volatility * xSqrtTime;

  T xD1 = (rate * xPowerTerm * time + xLogTerm) / xDen;
  T xD2 = xD1 - xDen;

  T nofXd1 = CNDF(xD1);
  T nofXd2 = CNDF(xD2);

  T futureValue = strike * (cpubm::exp(-(rate) * (time)));
  T optionPrice;
  if (otype == 0) {
    optionPrice = (spotPrice * nofXd1) - (futureValue * nofXd2);
  } else {
    T neg1 = 1.0 - nofXd1;
    T neg2 = 1.0 - nofXd2;
    optionPrice = (futureValue * neg2) - (spotPrice * neg1);
  }

  return optionPrice;
}

template <typename T> static void BlackScholes(Allocator &alloc, Timer &timer) {

  std::vector<Data<T>> data;
  data.reserve(10000);

#define PUSH_DATA(x1, x2, x3, x4, x5, x6, x7, x8, x9)                          \
  data.push_back(Data<T>{x1, x2, x3, x4, x5, x6, x7, x8, x9});

#include "blacksholes_data.hpp"

#undef PUSH_DATA

  const size_t numData = data.size();

  T *prices = alloc.allocate<T>(numData);

  timer.start();
#pragma omp parallel for simd
  for (size_t i = 0; i < numData; i++) {
    prices[i] = BlackScholesEq<T>(data[i].spotPrice, data[i].strike,
                                  data[i].rate, data[i].volatility,
                                  data[i].timeToMaturity, data[i].type);
  }
  timer.end();
  preserve(prices);

  int numErrors = 0;
  for (size_t i = 0; i < numData; i++) {
    if (std::abs(prices[i] - data[i].refValue) >= 1e-4) {
      numErrors++;
    }
  }

  // TODO export as a metric
  // std::clog << "Black-Scholes errors: " << numErrors << "\n";

  alloc.free(prices);
}

void createBS(std::vector<std::unique_ptr<Benchmark>> &container) {
  container.push_back(std::move(std::make_unique<OpenMPBenchmark>(
      "black_scholes_float", BlackScholes<float>)));
  container.push_back(std::move(std::make_unique<OpenMPBenchmark>(
      "black_scholes_double", BlackScholes<double>)));
}
