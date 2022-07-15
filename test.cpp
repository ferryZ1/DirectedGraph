/*
 * A short program which showcases the use of the diGraph class
 * The program reads edges from standard input
 * Input has to be of form(numbers at the begging represent beginning of a line, vertex can be any string):
 * 1 Number of edges
 * 2 edge0
 * 3 edge1
 * ...
 *
 * Example:
 * 1 5
 * 2 A B
 * 3 B A
 * 4 C D
 * 5 A G
 * 6 G B
 */

#include "digraph.h"
#include <iostream>

// A debug function which prints a given vector
template <typename T>
void printVector(std::vector<T> v)
{
   std::cout << "[";
   bool first = true;
   for (auto i : v)
   {
      if (!first)
         std::cout << ", ";
      first = false;
      std::cout << i;
   }
   std::cout << "]\n";
}

int main(void)
{
   std::vector<std::vector<std::string>> graph_input;
   std::vector<std::string> vertices;

   int arches;

   std::cin >> arches;

   for (int i = 0; i < arches; ++i)
   {
      std::vector<std::string> temp;
      temp.resize(2);
      std::cin >> temp[0];
      std::cin >> temp[1];
      graph_input.push_back(temp);
   }

   diGraph *graph;
   try
   {
      graph = new diGraph(graph_input);
      graph->getVertices(vertices);
      graph->depthFirstSearch("A");
      graph->breadthFirstSearch("A");
      std::cout << graph->isCyclic() << "\n";
      std::cout << graph->pathExists("A", "B") << "\n";
      std::cout << graph->isStronglyConnected() << "\n";
      printVector<std::string>(vertices);
   }
   catch (std::invalid_argument const &e)
   {
      std::cerr << e.what();
   }
   catch (...)
   {
      std::cerr << "Something wrong happened\n";
   }

   std::cout << *graph;

   delete graph;
   return 0;
}