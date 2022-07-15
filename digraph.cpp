#include "digraph.h"
#include <stack>
#include <queue>

// Constructs an empty graph
diGraph::diGraph() {}

// Constructs the graph from a given vector of edges(connections)
diGraph::diGraph(std::vector<std::vector<std::string>> &connections)
{
   for (auto connection : connections)
   {
      addConnection(connection);
   }
}

// Updates adjacency list for a given arch(conncention) of the graph
void diGraph::addConnection(std::vector<std::string> &connection)
{
   if (connection.size() != 2 || connection[0] == connection[1])
      throw std::invalid_argument("Incorrect arch detected");

   vertices.insert(connection[0]);
   vertices.insert(connection[1]);

   visited_map.insert({connection[0], false});
   visited_map.insert({connection[1], false});

   adjacency_list.insert({connection[0], std::set<std::string>()});
   adjacency_list.insert({connection[1], std::set<std::string>()});

   // Inserting the adjacent vertex, set data structutre takes carte of duplicates
   adjacency_list[connection[0]].insert(connection[1]);
}

// Prints the adjacency list of the graph
void diGraph::print()
{
   for (auto vertex : vertices)
   {
      std::cout << vertex << ": ";
      bool first = true;
      for (auto neighbor : adjacency_list.find(vertex)->second)
      {
         if (!first)
         {
            std::cout << ", ";
            first = false;
         }
         std::cout << neighbor;
      }
      std::cout << "\n";
   }
}

// Sets all the entries in the visited map to false
void diGraph::unvisit()
{
   for (auto vertex : vertices)
      visited_map.find(vertex)->second = false;
}

// Performs breadth first search from a vertex and prints out the vertices which it visits
void diGraph::depthFirstSearch(std::string start)
{
   unvisit();

   if (vertices.find(start) == vertices.end())
      throw std::invalid_argument("Vertex name is not the part of the graph");

   std::stack<std::string> s;
   s.push(start);
   visited_map.find(start)->second = true;
   std::cout << "Depth first search: ";
   while (!s.empty())
   {
      std::string current = s.top();
      s.pop();
      std::cout << current << " ";

      for (auto neighbor : adjacency_list.find(current)->second)
      {
         if (!(visited_map.find(neighbor)->second))
         {
            s.push(neighbor);
            visited_map.find(neighbor)->second = true;
         }
      }
   }
   std::cout << "\n";

   unvisit();
}

// Performs breadth first search from a vertex and prints out the vertices which it visits
void diGraph::breadthFirstSearch(std::string start)
{
   unvisit();

   if (vertices.find(start) == vertices.end())
      throw std::invalid_argument("Vertex name is not the part of the graph");

   std::queue<std::string> q;
   q.push(start);
   std::cout << "Breadth first search: " << start << " ";
   visited_map.find(start)->second = true;

   while (!q.empty())
   {
      std::string temp = q.front();
      q.pop();
      for (auto neighbor : adjacency_list.find(temp)->second)
      {
         if (!visited_map.find(neighbor)->second)
         {
            visited_map.find(neighbor)->second = true;
            q.push(neighbor);
            std::cout << neighbor << " ";
         }
      }
   }
   std::cout << "\n";

   unvisit();
}

// Returns true if a cycle is found via modified depth first search
bool diGraph::searchForCycle(int &unvisited, std::string vertex)
{
   std::stack<std::string> s;
   std::set<std::string> found;
   s.push(vertex);

   while (!s.empty())
   {
      --unvisited;
      found.insert(vertex);
      std::string current = s.top();
      s.pop();
      visited_map.find(current)->second = true;
      for (auto neighbor : adjacency_list.find(current)->second)
      {
         bool visited = visited_map.find(neighbor)->second;

         if (visited && (found.find(neighbor) != found.end()))
            return true;

         if (!visited)
         {
            s.push(neighbor);
         }
      }
   }
   return false;
}

// Returns true if the graph is cyclic
bool diGraph::isCyclic()
{
   unvisit();
   int unvisited = vertices.size();
   // set univisted to 0 for loops
   while (unvisited > 1)
   {
      for (auto vertex : vertices)
      {
         if (!visited_map.find(vertex)->second)
            if (searchForCycle(unvisited, vertex))
               return true;
      }
   }
   unvisit();
   return false;
}

// Checks wether or not a path exists between two given vertices via depth first search
bool diGraph::pathExists(std::string v1, std::string v2)
{
   unvisit();

   if (vertices.find(v1) == vertices.end() || vertices.find(v2) == vertices.end())
      throw std::invalid_argument("One or more vertices is not in the graph");
   if (v1 == v2)
      return true;

   std::stack<std::string> s;
   s.push(v1);
   while (!s.empty())
   {
      std::string current = s.top();
      if (current == v2)
         return true;
      s.pop();
      visited_map.find(current)->second = true;
      for (auto neighbor : adjacency_list.find(current)->second)
      {
         if (!visited_map.find(neighbor)->second)
         {
            s.push(neighbor);
         }
      }
   }

   unvisit();

   return false;
}

// Returns True if two vertices in a graph are connected
bool diGraph::areConnected(std::string &v1, std::string &v2)
{
   if (pathExists(v1, v2))
      return true;
   return pathExists(v2, v1);
}

// Returns true if the graph is strongly connected
bool diGraph::isStronglyConnected()
{
   for (auto u : vertices)
   {
      for (auto v : vertices)
      {
         if (u != v)
            if (!pathExists(u, v))
               return false;
      }
   }
   return true;
}

// Returns all vertices of a graph by appending them to a vector as an argument
void diGraph::getVertices(std::vector<std::string> &request)
{
   for (auto vertex : vertices)
      request.push_back(vertex);
}

// Overloaded operator which prints out the adjacency list of the graph
std::ostream &
operator<<(std::ostream &os, const diGraph &dg)
{
   for (auto vertex : dg.vertices)
   {
      os << vertex << ": ";
      bool first = true;
      for (auto neighbor : dg.adjacency_list.find(vertex)->second)
      {
         if (!first)
            os << ", ";
         first = false;

         os << neighbor;
      }
      os << "\n";
   }
   return os;
}