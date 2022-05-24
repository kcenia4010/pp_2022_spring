// Copyright 2022 Tyrina Anastasia
#include <gtest/gtest.h>
#include <omp.h>

#include "./dijkstra.h"

TEST(DIJKSTRA_STD, TEST_1) {
  int V = 3;
  Graph graph = getRandomGraph(V);
  Graph result_sequential = sequentialDijkstra(graph, V);
  Graph result_parallel = parallelDijkstra(graph, V);

  for (int i = 0; i < V; i++) {
    ASSERT_EQ(result_sequential[i], result_parallel[i]);
  }
}

TEST(DIJKSTRA_STD, TEST_2) {
  int V = 3;
  Graph graph = getRandomGraph(V);
  Graph result_sequential = sequentialDijkstra(graph, V);
  Graph result_parallel = parallelDijkstra(graph, V);

  for (int i = 0; i < V; i++) {
    ASSERT_EQ(result_sequential[i], result_parallel[i]);
  }
}

TEST(DIJKSTRA_STD, TEST_3) {
  int V = 3;
  Graph graph = getRandomGraph(V);
  Graph result_sequential = sequentialDijkstra(graph, V);
  Graph result_parallel = parallelDijkstra(graph, V);

  for (int i = 0; i < V; i++) {
    ASSERT_EQ(result_sequential[i], result_parallel[i]);
  }
}

TEST(DIJKSTRA_STD, TEST_4) {
  int V = 3;
  Graph graph = getRandomGraph(V);
  Graph result_sequential = sequentialDijkstra(graph, V);
  Graph result_parallel = parallelDijkstra(graph, V);

  for (int i = 0; i < V; i++) {
    ASSERT_EQ(result_sequential[i], result_parallel[i]);
  }
}

int V = 3;

TEST(DIJKSTRA_STD, TEST_TIME) {
  Graph graph = getRandomGraph(V);

  double start = omp_get_wtime();
  dijkstra_parallel(graph, 0, V);
  double end = omp_get_wtime();
  double ptime = end - start;
  std::cout << "\tparallel time: " << ptime << "\n";

  start = omp_get_wtime();
  dijkstra(graph, 0, V);
  end = omp_get_wtime();
  double stime = end - start;
  std::cout << "\tsequential time: " << stime << "\n";

  std::cout << "\tefficiency: " << stime / ptime << "\n";
}
