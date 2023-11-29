#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/*
  parent[]: armazena o índice do vértice pai do i-ésimo elemento
  rank[]: armazena a altura até o nó i
*/

int OPERATIONS = 0;

void incrementOperations(int delta)
{
  OPERATIONS += delta;
}

int comparator(const void *p1, const void *p2)
{
  const int(*x)[3] = p1;
  const int(*y)[3] = p2;

  return (*x)[2] - (*y)[2];
}

void makeSet(int parent[], int rank[], int n)
{
  for (int i = 0; i < n; i++)
  {
    parent[i] = i;
    rank[i] = 0;
  }
}

int findParentOptimized(int parent[], int component)
{
  incrementOperations(1);
  if (parent[component] == component)
  {
    incrementOperations(1);
    return parent[component];
  }

  incrementOperations(1);
  return parent[component] = findParentOptimized(parent, parent[component]);
}

int findParentUnoptimized(int parent[], int component)
{
  incrementOperations(1);
  if (parent[component] == component)
  {
    incrementOperations(1);
    return component;
  }

  incrementOperations(1);
  return findParentUnoptimized(parent, parent[component]);
}

int findParent(int parent[], int component, char *strategy)
{
  if (!strcmp(strategy, "optimized"))
  {
    return findParentOptimized(parent, component);
  }

  if (!strcmp(strategy, "unoptimized"))
  {
    return findParentUnoptimized(parent, component);
  }
}

void unionSetOptimized(int u, int v, int parent[], int rank[])
{
  int uParent = findParentOptimized(parent, u);
  int vParent = findParentOptimized(parent, v);

  incrementOperations(2);

  if (vParent != uParent)
  {
    incrementOperations(1);
    if (rank[uParent] < rank[vParent])
    {
      incrementOperations(2);
      parent[uParent] = vParent;
    }
    else if (rank[uParent] > rank[vParent])
    {
      incrementOperations(3);
      parent[vParent] = uParent;
    }
    else
    {
      incrementOperations(4);
      parent[vParent] = uParent;
      rank[uParent] += 1;
    }
  }
}

void unionSetUnoptimized(int u, int v, int parent[], int rank[])
{
  u = findParentUnoptimized(parent, u);
  v = findParentUnoptimized(parent, v);

  parent[u] = v;

  incrementOperations(3);
}

void unionSet(int u, int v, int parent[], int rank[], char *strategy)
{
  if (!strcmp(strategy, "optimized"))
  {
    return unionSetOptimized(u, v, parent, rank);
  }

  if (!strcmp(strategy, "unoptimized"))
  {
    return unionSetUnoptimized(u, v, parent, rank);
  }
}

void kruskalAlgo(int nVertexes, int nEdges, int edge[nEdges][3], char *strategy)
{
  qsort(edge, nEdges, sizeof(edge[0]), comparator);

  int parent[nVertexes];
  int rank[nVertexes];

  makeSet(parent, rank, nVertexes);

  int minCost = 0;

  for (int i = 0; i < nEdges; i++)
  {
    int v1 = findParent(parent, edge[i][0], strategy);
    int v2 = findParent(parent, edge[i][1], strategy);
    int wt = edge[i][2];

    if (v1 != v2)
    {
      unionSet(v1, v2, parent, rank, strategy);
      minCost += wt;
    }
  }
}

// Driver code
int main(int argc, char *argv[])
{
  unsigned int NUMBER_OF_VERTEX;
  unsigned int results[10];
  char *strategy;

  NUMBER_OF_VERTEX = strtoul(argv[1], 0L, 10);
  strategy = argv[2];

  int totalEdges = (NUMBER_OF_VERTEX * (NUMBER_OF_VERTEX - 1)) / 2;
  int edge[totalEdges][3];

  for (int i = 0; i < (totalEdges); i++)
  {
    edge[i][2] = 1000000;
  }

  int edgesCounter = 0;

  fprintf(stdout, "%s: ", strategy);

  for (int k = 0; k < 10; k++) {
    srand((unsigned int) k);
    for (int i = 0; i < NUMBER_OF_VERTEX; i++)
    {
      for (int j = i + 1; j < NUMBER_OF_VERTEX && j != i; j++)
      {
        edge[edgesCounter][0] = i;
        edge[edgesCounter][1] = j;
        edge[edgesCounter][2] = (int)(((float)rand() / (float)(RAND_MAX)) * (float)totalEdges);
        edgesCounter++;
      }
    }

    kruskalAlgo(NUMBER_OF_VERTEX, totalEdges, edge, strategy);

    fprintf(stdout, "%d, ", OPERATIONS);

    OPERATIONS = 0;
  }

  fprintf(stdout, "\n");

  return 0;
}
