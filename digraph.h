/*
 * Definition of diGraph class which an implementation of a simple
 * directed graph(no loops or double edges).
 *
 * Author: Fran Ogrinšak
 */

#include <vector>
#include <set>
#include <string>
#include <map>
#include <exception>
#include <iostream>

class diGraph
{
private:
   std::set<std::string> vertices;
   std::map<std::string, bool> visited_map;
   std::map<std::string, std::set<std::string>> adjacency_list;

   void unvisit();

   bool searchForCycle(int &unvisited, std::string vertex);

public:
   diGraph();
   diGraph(std::vector<std::vector<std::string>> &connections);

   void addConnection(std::vector<std::string> &connection);

   void print();

   void depthFirstSearch(std::string start);

   void breadthFirstSearch(std::string start);

   bool isCyclic();

   bool pathExists(std::string v1, std::string v2);

   bool areConnected(std::string &v1, std::string &v2);

   bool isStronglyConnected();

   void getVertices(std::vector<std::string> &request);

   friend std::ostream &operator<<(std::ostream &os, const diGraph &dg);
};

std::ostream &operator<<(std::ostream &os, const diGraph &dg);