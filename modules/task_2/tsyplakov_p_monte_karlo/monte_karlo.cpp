// Copyright 2022 Tsyplakov Pavel
#include "../../../modules/task_2/tsyplakov_p_monte_karlo/monte_karlo.h"
#include <omp.h>
#include <exception>
#include <functional>
#include <random>
#include <vector>

using std::exception;
using std::function;
using std::vector;

double getSequentialMonteKarlo(
    function<double(vector<double>)> const& integrableFunction,
    const vector<double>& upperLimit,
    const vector<double>& lowerLimit,
    const vector<double>::size_type amountOfPoint) {
  if (upperLimit.size() == 0 || lowerLimit.size() == 0 ||
      upperLimit.size() != lowerLimit.size()) {
    throw exception("Wrong limit!");
  }

  double result = 0.0;
  auto integrableDimensions = upperLimit.size();

  vector<std::uniform_real_distribution<double>> distributions(
      integrableDimensions);
  for (auto counter = 0; counter < integrableDimensions; ++counter) {
    distributions[counter] = std::uniform_real_distribution<double>(
        lowerLimit[counter], upperLimit[counter]);
  }

  std::random_device rd;
  std::mt19937 gen(rd());

  vector<double> randomPoints(integrableDimensions);
  for (auto counter = 0; counter < amountOfPoint; ++counter) {
    for (auto i = 0; i < integrableDimensions; ++i) {
      randomPoints[i] = distributions[i](gen);
    }

    result += integrableFunction(randomPoints);
  }

  double partialResult = 1.0;
  for (auto counter = 0; counter < integrableDimensions; ++counter) {
    partialResult *= upperLimit[counter] - lowerLimit[counter];
  }

  result *= (partialResult / amountOfPoint);
  return result;
}

double getParallelMonteKarlo(
    std::function<double(std::vector<double>)> const& integrableFunction,
    const std::vector<double>& upperLimit,
    const std::vector<double>& lowerLimit,
    const std::vector<double>::size_type amountOfPoint) {
  if (upperLimit.size() == 0 || lowerLimit.size() == 0 ||
      upperLimit.size() != lowerLimit.size()) {
    throw exception("Wrong limit!");
  }

  double reductionResult = 0.0;
  auto integrableDimensions = upperLimit.size();

  vector<std::uniform_real_distribution<double>> distributions(
      integrableDimensions);
  for (auto counter = 0; counter < integrableDimensions; ++counter) {
    distributions[counter] = std::uniform_real_distribution<double>(
        lowerLimit[counter], upperLimit[counter]);
  }

  std::random_device rd;
  std::mt19937 gen(rd());

  vector<double> randomPoints(integrableDimensions);
  int numberOfThread = omp_get_num_procs();
#pragma omp parallel for firstprivate(randomPoints) reduction(+ : reductionResult)
  for (auto counter = 0; counter < amountOfPoint; ++counter) {
    for (auto i = 0; i < integrableDimensions; ++i) {
      randomPoints[i] = distributions[i](gen);
    }

    reductionResult += integrableFunction(randomPoints);
  }

  double partialResult = 1.0;
  for (auto counter = 0; counter < integrableDimensions; ++counter) {
    partialResult *= upperLimit[counter] - lowerLimit[counter];
  }

  reductionResult *= (partialResult / amountOfPoint);
  return reductionResult;
}
