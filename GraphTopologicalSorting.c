//
// Algoritmos e Estruturas de Dados --- 2023/2024
//
// Topological Sorting
//

#include "GraphTopologicalSorting.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "IntegersQueue.h"
#include "instrumentation.h"

struct _GraphTopoSort {
  int* marked;                     // Aux array
  unsigned int* numIncomingEdges;  // Aux array
  unsigned int* vertexSequence;    // The result
  int validResult;                 // 0 or 1
  unsigned int numVertices;        // From the graph
  Graph* graph;
};

// Macros to simplify accessing instrumentation counters:
#define MEMREAD InstrCount[0]
#define MEMWRITE InstrCount[1]
#define ITERATIONS InstrCount[2]

// AUXILIARY FUNCTION
// Allocate memory for the struct
// And for its array fields
// Initialize all struct fields
//
static GraphTopoSort* _create(Graph* g) {
  assert(g != NULL);

  GraphTopoSort* p = NULL;

  // TO BE COMPLETED
  // ...
  p = (GraphTopoSort*)malloc(sizeof(struct _GraphTopoSort));
  if (p == NULL) {
    return NULL;
  }

  p->marked = (int*)calloc(GraphGetNumVertices(g) , GraphGetNumVertices(g) * sizeof(int));
  if (p->marked == NULL) {
    free(p);
    return NULL;
  }

  p->numIncomingEdges =
      (unsigned int*)malloc(GraphGetNumVertices(g) * sizeof(unsigned int));
  if (p->numIncomingEdges == NULL) {
    free(p->marked);
    free(p);
    return NULL;
  }

  p->vertexSequence =
      (unsigned int*)malloc(GraphGetNumVertices(g) * sizeof(unsigned int));
  if (p->vertexSequence == NULL) {
    free(p->marked);
    free(p->numIncomingEdges);
    free(p);
    return NULL;
  }

  p->validResult = 0;
  p->numVertices = GraphGetNumVertices(g);
  p->graph = g;
  MEMWRITE+=3;

  return p;
}

//
// Computing the topological sorting, if any, using the 1st algorithm:
// 1 - Create a copy of the graph
// 2 - Successively identify vertices without incoming edges and remove their
//     outgoing edges
// Check if a valid sorting was computed and set the isValid field
// For instance, by checking if the number of elements in the vertexSequence is
// the number of graph vertices
//
GraphTopoSort* GraphTopoSortComputeV1(Graph* g) {
  ITERATIONS++;
  assert(g != NULL && GraphIsDigraph(g) == 1);

  // Create and initialize the struct

  GraphTopoSort* topoSort = _create(g);

  // Build the topological sorting

  // TO BE COMPLETED
  //...
  unsigned int nVertices = topoSort->numVertices;
  MEMREAD++;
  unsigned int verticesInSequence = 0;
  unsigned int count = 0;

  Graph* gCopy = GraphCopy(g);

  while (nVertices != verticesInSequence) {
    count++;
    for (unsigned int i = 0; i < nVertices; i++) {
      ITERATIONS++;
      // Check if vertex has no incoming edges
      MEMREAD++;
      if (GraphGetVertexInDegree(gCopy, i) == 0 && topoSort->marked[i] == 0) {

        // Remove outgoing edges
        if (GraphGetVertexOutDegree(gCopy, i) != 0) {
          unsigned int* adj = GraphGetAdjacentsTo(gCopy, i);
          unsigned int numEdges = GraphGetVertexOutDegree(gCopy, i);

          for (unsigned int j = 1; j < numEdges + 1; j++) {
            ITERATIONS++;
            GraphRemoveEdge(gCopy, i, adj[j]);
          }
          free(adj);
        }
        topoSort->marked[i] = 1;
        topoSort->vertexSequence[verticesInSequence++] = i;
        MEMWRITE+=2;
        break;
      }
    }
    if (count == nVertices) {
      break;
    }
  }

  if (nVertices == verticesInSequence) {
    topoSort->validResult = 1;
    MEMWRITE++;
  }

  GraphDestroy(&gCopy);

  return topoSort;
}

//
// Computing the topological sorting, if any, using the 2nd algorithm
// Check if a valid sorting was computed and set the isValid field
// For instance, by checking if the number of elements in the vertexSequence is
// the number of graph vertices
//
GraphTopoSort* GraphTopoSortComputeV2(Graph* g) {
  assert(g != NULL && GraphIsDigraph(g) == 1);

  // Create and initialize the struct

  GraphTopoSort* topoSort = _create(g);
  unsigned int nVertices = topoSort->numVertices;
  MEMREAD++;
  // Build the topological sorting

  // TO BE COMPLETED

  ///////////////// ALGORITMO DO ARRAY AUXILIAR //////////////////////////////////

  // criar o array auxiliar numEdgesPerVertex, no caso numIncomingEdges para resgitar o inDegree de cada vertice
  // preencher o array auxiliar com o inDegree de cada vertice
  for (unsigned int i = 0; i < nVertices; i++) {
    ITERATIONS++;
    MEMWRITE++;
    topoSort->numIncomingEdges[i] = GraphGetVertexInDegree(g, i);
  }

  // enquanto for possível selecionar vértice v com numIncomingEdges[v] == 0 E não marcado
  // certificar que todos os vértices foram percorridos
  unsigned int verticesInSequence = 0;
  unsigned int count = 0;
  while (verticesInSequence != nVertices) {
    for (unsigned int v = 0; v < nVertices; v++) {
      ITERATIONS++;
      MEMREAD+=2;
      if (topoSort->numIncomingEdges[v] == 0 && topoSort->marked[v] == 0) {
        // marcar v
        topoSort->marked[v] = 1;
        MEMWRITE++;
        // inserir v no topoSort
        topoSort->vertexSequence[verticesInSequence++] = v;
        MEMWRITE++;
        // para cada vértice w adjacente a v numEdgesPerVertex[w]--
        unsigned int* adj = GraphGetAdjacentsTo(g, v);
        for (unsigned int w = 1; w < GraphGetVertexOutDegree(g, v) + 1  ; w++) {
          ITERATIONS++;
          topoSort->numIncomingEdges[adj[w]]--;
          MEMWRITE++;
        }
        free(adj);
        break;
      }
        
    }
    count ++;  
    if (count == nVertices)
        break;
  }

  // se o topoSort contiver todos os vértices do grafo
  if (verticesInSequence == nVertices) {
    // topoSort é válido
    topoSort->validResult = 1;
    MEMWRITE++;
  }

  return topoSort;
}

//
// Computing the topological sorting, if any, using the 3rd algorithm
// Check if a valid sorting was computed and set the isValid field
// For instance, by checking if the number of elements in the vertexSequence is
// the number of graph vertices
//
GraphTopoSort* GraphTopoSortComputeV3(Graph* g) {
  assert(g != NULL && GraphIsDigraph(g) == 1);

  // Create and initialize the struct

  GraphTopoSort* topoSort = _create(g);
  Queue *queue = QueueCreate(GraphGetNumVertices(g));
  unsigned int nVertices = topoSort->numVertices;

  // Build the topological sorting

  // TO BE COMPLETED

  ///////////////// ALGORITMO DO CONJUNTO DE CANDIDATOS //////////////////////////////////

  // Registar num array auxiliar numEdgesPerVertex o InDegree de cada vértice
  // É o array numIncomingEdges
  for (unsigned int i = 0; i < nVertices; i++) {
    ITERATIONS++;
    topoSort->numIncomingEdges[i] = GraphGetVertexInDegree(g, i);
    MEMWRITE++;
  }
  
  // criar fila com os vértices com numIncomingEdges[v] == 0
  for (unsigned int v = 0; v < nVertices; v++) {
    ITERATIONS++;
    MEMREAD++;
    if (topoSort->numIncomingEdges[v] == 0) {
      QueueEnqueue(queue, v);
    }
  }

  unsigned int verticesInSequence = 0;

  // enquanto a fila não for vazia
  while ( !QueueIsEmpty(queue) ) {
    // retirar próximo vértice da fila
    unsigned int v = QueueDequeue(queue);
    // inserir v no topoSort
    topoSort->vertexSequence[verticesInSequence++] = v;
    MEMWRITE++;
    // para cada vértice w adjacente a v
    unsigned int* adj = GraphGetAdjacentsTo(g, v);
    for (unsigned int w = 1; w < GraphGetVertexOutDegree(g, v) + 1 ; w++) {
      ITERATIONS++;
      // decrementar numEdgesPerVertex[w]
      topoSort->numIncomingEdges[adj[w]]--;
      MEMWRITE++;
      // se numEdgesPerVertex[w] == 0
      MEMREAD++;
      if (topoSort->numIncomingEdges[adj[w]] == 0) {
        // inserir w na fila
        QueueEnqueue(queue, adj[w]);
      }
    }
    free(adj);
  }

  // se o topoSort contiver todos os vértices do grafo
  if (verticesInSequence == nVertices) {
    // topoSort é válido
    topoSort->validResult = 1;
    MEMWRITE++;
  }

  QueueDestroy(&queue);

  return topoSort;
}

void GraphTopoSortDestroy(GraphTopoSort** p) {
  assert(*p != NULL);

  GraphTopoSort* aux = *p;

  free(aux->marked);
  free(aux->numIncomingEdges);
  free(aux->vertexSequence);

  free(*p);
  *p = NULL;
}

//
// A valid sorting was computed?
//
int GraphTopoSortIsValid(const GraphTopoSort* p) { return p->validResult; }

//
// Getting an array containing the topological sequence of vertex indices
// Or NULL, if no sequence could be computed
// MEMORY IS ALLOCATED FOR THE RESULTING ARRAY
//
unsigned int* GraphTopoSortGetSequence(const GraphTopoSort* p) {
  assert(p != NULL);
  // TO BE COMPLETED
  // ...
  return GraphTopoSortIsValid(p) ? p->vertexSequence : NULL;
}

// DISPLAYING on the console

//
// The toplogical sequence of vertex indices, if it could be computed
//
void GraphTopoSortDisplaySequence(const GraphTopoSort* p) {
  assert(p != NULL);

  MEMREAD++;
  if (p->validResult == 0) {
    printf(" *** The topological sorting could not be computed!! *** \n");
    return;
  }

  printf("Topological Sorting - Vertex indices:\n");
  for (unsigned int i = 0; i < GraphGetNumVertices(p->graph); i++) {
    ITERATIONS++;
    MEMREAD++;
    printf("%d ", p->vertexSequence[i]);
  }
  printf("\n");
}

//
// The toplogical sequence of vertex indices, if it could be computed
// Followed by the digraph displayed using the adjecency lists
// Adjacency lists are presented in topologic sorted order
//
void GraphTopoSortDisplay(const GraphTopoSort* p) {
  assert(p != NULL);

  // The topological order
  GraphTopoSortDisplaySequence(p);

  MEMREAD++;
  if (p->validResult == 0) {
    return;
  }

  // The Digraph
  for (unsigned int i = 0; i < GraphGetNumVertices(p->graph); i++) {
    ITERATIONS++;
    MEMREAD+=2;
    GraphListAdjacents(p->graph, p->vertexSequence[i]);
  }
  printf("\n");
}
