// Copyright 2022 Tyrina Anastasia
#include "../../../modules/task_4/tyrina_a_dijkstra/dijkstra.h"

#include <omp.h>

#include <climits>
#include <random>
#include <vector>

#include "../../../3rdparty/unapproved/unapproved.h"

Graph getRandomGraph(int V) {
  Graph graph(V, VectorInt(V));
  std::random_device dev;
  std::mt19937 gen(dev());

  for (int i = 0; i < V; ++i) {
    for (int j = i + 1; j < V; ++j) {
      graph[i][j] = gen() % 20;
      graph[j][i] = graph[i][j];
    }
    graph[i][i] = 0;
  }
  return graph;
}

int minDistance(const VectorInt& dist, const VectorBool& sptSet, int V) {
  int min = INT_MAX, min_index = 0;

  for (int v = 0; v < V; v++)
    if (sptSet[v] == false && dist[v] <= min) min = dist[v], min_index = v;

  return min_index;
}

VectorInt dijkstra(const Graph& graph, int src, int V) {
  VectorInt dist(V);
  VectorBool visited(V);

  for (int i = 0; i < V; i++) {
    dist[i] = INT_MAX;
    visited[i] = false;
  }

  dist[src] = 0;

  for (int count = 0; count < V - 1; count++) {
    int u = minDistance(dist, visited, V);

    visited[u] = true;

    for (int v = 0; v < V; v++) {
      if (!visited[v] && graph[u][v] && dist[u] != INT_MAX &&
          dist[u] + graph[u][v] < dist[v]) {
        dist[v] = dist[u] + graph[u][v];
      }
    }
  }

  return dist;
}

VectorInt dijkstra_parallel(const Graph& graph, int src, int V) {
  VectorInt dist(V, INT_MAX);
  VectorBool visited(V, false);

  dist[src] = 0;

  for (int count = 0; count < V - 1; count++) {
    int min = INT_MAX, u = 0;

      VectorInt local_min(V, INT8_MAX);
      VectorInt local_ind(V);

      int thread_num = 2;
      std::vector<std::thread> threads(thread_num);
      int delta = V / thread_num;

      auto thread_func = [&visited, &dist, &local_min, &local_ind](int begin, int end,
        int index) {
          for (int i = begin; i < end; ++i)
            if (!visited[i] && dist[i] <= local_min[index]) {
              local_min[index] = dist[i];
              local_ind[index] = i;
            }
      };

      for (int index = 0; index < thread_num - 1; ++index) {
        int begin = delta * index;
        int end = delta * (index + 1);
        threads[index] = std::thread(thread_func, begin, end, index);
      }
      threads[thread_num - 1] = std::thread(thread_func, delta * (thread_num - 1),
        V, thread_num - 1);

      for (auto&& i : threads) {
        i.join();
      }

      threads.clear();
      threads.resize(thread_num);

      for (int i = 0; i < thread_num; i++) {
        if (local_min[i] < min) {
          min = local_min[i];
          u = local_ind[i];
        }
      }

      visited[u] = true;

      auto thread_func1 = [&visited, &dist, &graph, u](int begin, int end,
        int index) {
          for (int v = begin; v < end; v++) {
            if (!visited[v] && graph[u][v] && dist[u] != INT_MAX &&
              dist[u] + graph[u][v] < dist[v]) {
              dist[v] = dist[u] + graph[u][v];
            }
          }
      };

      for (int index = 0; index < thread_num - 1; ++index) {
        int begin = delta * index;
        int end = delta * (index + 1);
        threads[index] = std::thread(thread_func1, begin, end, index);
      }
      threads[thread_num - 1] = std::thread(thread_func1, delta * (thread_num - 1),
        V, thread_num - 1);

      for (auto&& i : threads) {
        i.join();
      }
  }
  return dist;
}

Graph sequentialDijkstra(const Graph& graph, int V) {
  Graph result(V, VectorInt(V));

  for (int src = 0; src < V; ++src) {
    result[src] = dijkstra(graph, src, V);
  }

  return result;
}

Graph parallelDijkstra(const Graph& graph, int V) {
  Graph result(V, VectorInt(V));

  for (int src = 0; src < V; ++src) {
    result[src] = dijkstra_parallel(graph, src, V);
  }

  return result;
}
