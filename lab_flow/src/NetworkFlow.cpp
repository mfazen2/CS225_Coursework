#include <vector>
#include <algorithm>
#include <set>

#include "cs225_graph/graph.h"
#include "cs225_graph/edge.h"

#include "NetworkFlow.h"

int min(int a, int b) {
  if (a<b)
    return a;
  else return b;
}

NetworkFlow::NetworkFlow(Graph & startingGraph, Vertex source, Vertex sink) :
  g_(startingGraph), residual_(Graph(true,true)), flow_(Graph(true,true)), source_(source), sink_(sink) {

  // YOUR CODE HERE
  maxFlow_ = 0; //initialize flow to a minimum state
  std::vector<Vertex> vertices = g_.getVertices();
  std::vector<Edge> edges = g_.getEdges();
  for (const auto& v : vertices) {
    flow_.insertVertex(v);
    residual_.insertVertex(v);
  for (const auto& e : edges){
    flow_.insertEdge(e.source,e.dest);
    flow_.setEdgeWeight(e.source,e.dest,0);
    
    residual_.insertEdge(e.source,e.dest);
    residual_.setEdgeWeight(e.source,e.dest,e.getWeight());
    
    residual_.insertEdge(e.dest,e.source);
    residual_.setEdgeWeight(e.dest,e.source,0);
  }
  }
}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the helper function.
   *
   * @param source  The starting (current) vertex
   * @param sink    The destination vertex
   * @param path    The vertices in the path
   * @param visited A set of vertices we have visited
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink, 
  std::vector<Vertex> &path, std::set<Vertex> &visited) {

  if (visited.count(source) != 0)
    return false;
  visited.insert(source);

  if (source == sink) {
    return true;
  }

  vector<Vertex> adjs = residual_.getAdjacent(source);
  for(auto it = adjs.begin(); it != adjs.end(); it++) {
    if (visited.count(*it) == 0 && residual_.getEdgeWeight(source,*it) > 0) {
      path.push_back(*it);
      if (findAugmentingPath(*it,sink,path,visited))
        return true;
      else {
        path.pop_back();
      }
    }
  }

  return false;
}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the main function.  It initializes a set to keep track of visited vertices.
   *
   * @param source The starting (current) vertex
   * @param sink   The destination vertex
   * @param path   The vertices in the path
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink, std::vector<Vertex> &path) {
   std::set<Vertex> visited;
   path.clear();
   path.push_back(source);
   return findAugmentingPath(source,sink,path,visited);
}

  /**
   * pathCapacity - Determine the capacity of a path in the residual graph.
   *
   * @param path   The vertices in the path
   */

int NetworkFlow::pathCapacity(const std::vector<Vertex> & path) const {
  // YOUR CODE HERE
  if (path.size() <= 1){return 0;}
  int min = INT_MAX;
  for (int i = 0; i < (int) path.size()-1;i++){
    int edgeWeight = residual_.getEdgeWeight(path[i],path[i+1]);
    if (edgeWeight < min){min = edgeWeight;}
  }
  return min;
}

  /**
   * calculuateFlow - Determine the capacity of a path in the residual graph.
   * Sets the member function `maxFlow_` to be the flow, and updates the
   * residual graph and flow graph according to the algorithm.
   *
   * @return The network flow graph.
   */

const Graph & NetworkFlow::calculateFlow() {
  // YOUR CODE HERE
  std::vector<Vertex> vertices = residual_.getVertices();
  while(findAugmentingPath(source_,sink_,vertices)){
    int cap = pathCapacity(vertices);
    maxFlow_+=cap;
    for (int i = 0; i < (int) vertices.size()-1;i++){
      residual_.setEdgeWeight(vertices[i], vertices[i + 1], residual_.getEdgeWeight(vertices[i], vertices[i + 1]) - cap);
      residual_.setEdgeWeight(vertices[i + 1], vertices[i], residual_.getEdgeWeight(vertices[i + 1], vertices[i]) + cap);
      if (flow_.edgeExists(vertices[i],vertices[i+1])){ flow_.setEdgeWeight(vertices[i], vertices[i + 1], flow_.getEdgeWeight(vertices[i], vertices[i + 1]) + cap);}
      else{flow_.setEdgeWeight(vertices[i + 1], vertices[i], flow_.getEdgeWeight(vertices[i + 1], vertices[i]) - cap);}
    }
  }
  return flow_;
}

int NetworkFlow::getMaxFlow() const {
  return maxFlow_;
}

const Graph & NetworkFlow::getGraph() const {
  return g_;
}

const Graph & NetworkFlow::getFlowGraph() const {
  return flow_;
}

const Graph & NetworkFlow::getResidualGraph() const {
  return residual_;
}

