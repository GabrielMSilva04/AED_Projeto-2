//
// Algoritmos e Estruturas de Dados --- 2023/2024
//
// Joaquim Madeira, Joao Manuel Rodrigues - June 2021, Nov 2023
//
// Graph EXAMPLE : Creating and displaying graphs
//

#include "Graph.h"

int main(void) {
  // What kind of graph is g01?
  Graph* g01 = GraphCreate(6, 0, 0);
  GraphAddEdge(g01, 1, 2);
  GraphAddEdge(g01, 1, 4);
  GraphAddEdge(g01, 3, 4);
  printf("The first graph:\n");
  GraphDisplay(g01);
  for (int i = 0; i < 6; i++) {
    GraphListAdjacents(g01, i);
  }
  printf("Remove edge (1,2)\n");
  GraphRemoveEdge(g01, 1, 2);
  GraphDisplay(g01);
  for (int i = 0; i < 6; i++) {
    GraphListAdjacents(g01, i);
  }

  Graph* dig01 = GraphCreate(6, 1, 0);
  GraphAddEdge(dig01, 1, 2);
  GraphAddEdge(dig01, 1, 4);
  GraphAddEdge(dig01, 3, 4);
  printf("The second graph:\n");
  GraphDisplay(dig01);
  for (int i = 0; i < 6; i++) {
    GraphListAdjacents(dig01, i);
  }
  printf("Remove edge (1,2)\n");
  GraphRemoveEdge(dig01, 1, 2);
  GraphDisplay(dig01);
  for (int i = 0; i < 6; i++) {
    GraphListAdjacents(dig01, i);
  }

  Graph* g03 = GraphCreate(6, 0, 1);
  GraphAddWeightedEdge(g03, 1, 2, 3);
  GraphAddWeightedEdge(g03, 1, 4, 5);
  GraphAddWeightedEdge(g03, 3, 4, 10);
  printf("The third graph:\n");
  GraphDisplay(g03);
  for (int i = 0; i < 6; i++) {
    GraphListAdjacents(g03, i);
  }
  printf("Remove edge (1,2)\n");
  GraphRemoveEdge(g03, 1, 2);
  GraphDisplay(g03);
  for (int i = 0; i < 6; i++) {
    GraphListAdjacents(g03, i);
  }

  GraphDestroy(&g01);
  GraphDestroy(&dig01);
  GraphDestroy(&g03);

  return 0;
}
