#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUMBER_OF_VERTEX 200

/*
  parent[]: armazena o índice do vértice pai do i-ésimo elemento
*/

int OPERATIONS = 0;

void incrementOperations(int delta) {
  OPERATIONS += delta;
}

int comparator(const void *p1, const void *p2)
{
  const int(*x)[3] = p1;
  const int(*y)[3] = p2;

  return (*x)[2] - (*y)[2];
}

void makeSet(int parent[], int n)
{
  for (int i = 0; i < n; i++)
  {
    parent[i] = i;
  }
}

int findParent(int parent[], int component)
{
  incrementOperations(1);
  if (parent[component] == component) {
    incrementOperations(1);
    return component;
  }
  
  incrementOperations(1);
  return findParent(parent, parent[component]);
}

void unionSet(int u, int v, int parent[])
{
  u = findParent(parent, u);
  v = findParent(parent, v);

  parent[u] = v;

  incrementOperations(3);
}

void kruskalAlgo(int nVertexes, int nEdges, int edge[nEdges][3])
{
  qsort(edge, nEdges, sizeof(edge[0]), comparator);

  int parent[nVertexes];

  makeSet(parent, nVertexes);

  int minCost = 0;

  for (int i = 0; i < nEdges; i++) {
    int v1 = findParent(parent, edge[i][0]);
    int v2 = findParent(parent, edge[i][1]);
    int wt = edge[i][2];

    if (v1 != v2)
    {
      unionSet(v1, v2, parent);
      minCost += wt;
      printf("%d -- %d == %d\n", edge[i][0],
             edge[i][1], wt);
    }
  }

  printf("Minimum Cost Spanning Tree: %d\n", minCost);
}

// Driver code
int main()
{
  int totalEdges = (NUMBER_OF_VERTEX * (NUMBER_OF_VERTEX - 1)) / 2;
  int edge[totalEdges][3];
  srand((unsigned int) NUMBER_OF_VERTEX);

  for (int i = 0; i < (totalEdges); i++) {
    edge[i][2] = 100000;
  }

  int edgesCounter = 0;
  for (int i = 0; i < NUMBER_OF_VERTEX; i++) {
    for (int j = i + 1; j < NUMBER_OF_VERTEX && j != i; j++) {
      edge[edgesCounter][0] = i;
      edge[edgesCounter][1] = j;
      edge[edgesCounter][2] = (int)(((float) rand() / (float)(RAND_MAX)) * (float) totalEdges);
      edgesCounter++;
    }
  } 
  
  kruskalAlgo(NUMBER_OF_VERTEX, totalEdges, edge); 

  printf("Total operations: %d\n", OPERATIONS);
  
  return 0; 
}
