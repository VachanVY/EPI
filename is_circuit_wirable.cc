#include <cstddef>
#include <stdexcept>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/timed_executor.h"
using namespace std;

struct GraphVertex {
  /*
  -1 => unvisited
  1 => visited and colored 1
  0 => visited and colored 0
  */
  int d = -1;
  vector<GraphVertex*> edges;
};

// return false for odd length cycle else true
bool dfs(
  GraphVertex& curr,
  int curr_color,
  vector<GraphVertex>& graph
) {
  curr.d = curr_color;

  for (auto nei : curr.edges) {
    if (nei->d != -1) { // visited
      if (nei->d == curr_color) { // color doesn't match
        return false;
      }
    } else { // not visited
      if (!dfs(*nei, !curr_color, graph)) {
        return false;
      }
    }
  }
  return true;
}

bool IsAnyPlacementFeasible(vector<GraphVertex>& graph) {
  for (auto& vertex : graph) {
    if (vertex.d == -1 && !dfs(vertex, 0, graph))
      return false;
  }
  return true;
}
struct Edge {
  int from;
  int to;
};

namespace test_framework {
template <>
struct SerializationTrait<Edge> : UserSerTrait<Edge, int, int> {};
}  // namespace test_framework

bool IsAnyPlacementFeasibleWrapper(TimedExecutor& executor, int k,
                                   const vector<Edge>& edges) {
  vector<GraphVertex> graph;
  if (k <= 0) {
    throw std::runtime_error("Invalid k value");
  }
  graph.reserve(k);

  for (int i = 0; i < k; i++) {
    graph.push_back(GraphVertex{});
  }

  for (auto& e : edges) {
    if (e.from < 0 || e.from >= k || e.to < 0 || e.to >= k) {
      throw std::runtime_error("Invalid vertex index");
    }
    graph[e.from].edges.push_back(&graph[e.to]);
  }

  return executor.Run([&] { return IsAnyPlacementFeasible(graph); });
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "k", "edges"};
  return GenericTestMain(
      args, "is_circuit_wirable.cc", "is_circuit_wirable.tsv",
      &IsAnyPlacementFeasibleWrapper, DefaultComparator{}, param_names);
}
