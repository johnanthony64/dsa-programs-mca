#include <stdio.h>
#include <stdlib.h>

#define INFINITY 9999
#define MAX_VERTICES 100

int G[MAX_VERTICES][MAX_VERTICES];
int n;

// Function to create graph
void create_graph() {
  int i, j;
  
  printf("Enter number of vertices: ");
  scanf("%d", &n);
  
  for(i=0; i<n; i++) {
    for(j=0; j<n; j++) {
      G[i][j] = INFINITY;
    }
  }
  
  // read edges and weights
  int u, v, w;
  printf("Enter edges and weights:\n");
  for(i=0; i<n; i++) {
    scanf("%d%d%d", &u, &v, &w);
    G[u][v] = G[v][u] = w; 
  }
}

// Function to find minimum key vertex
int find_min(int weights[], int selected[]) {
  int min_vertex = -1;
  int min = INFINITY;
  int i;
  
  for(i=0; i<n; i++) {
    if(!selected[i] && weights[i] < min) {
      min = weights[i];
      min_vertex = i; 
    }
  }
  
  return min_vertex;
}

// Function to construct MST using Prim's algorithm  
void prims_mst() {
  int parent[MAX_VERTICES]; 
  int weights[MAX_VERTICES];
  int selected[MAX_VERTICES];
  
  for(int i=0; i<n; i++) {
    weights[i] = INFINITY;
    selected[i] = 0;
  }
  
  weights[0] = 0; 
  parent[0] = -1;
  
  int count;
  int u, v;

  // Add n-1 edges to MST
  for(count=0; count<n-1; count++) {
    u = find_min(weights, selected);

    selected[u] = 1;

    // Explore all adjacent for u  
    for(v=0; v<n; v++) {
      if(G[u][v] && !selected[v] && G[u][v] < weights[v]) {
        weights[v] = G[u][v];
        parent[v] = u;
      }
    }
  }

  // Print MST edges
  for(int i=1; i<n; i++) {
    printf("Edge %d - %d: %d\n", parent[i], i, G[parent[i]][i]); 
  }
}

// Function for finding vertex with minimum key
int find_min_key(int keys[], int selected[]) {
   int min = INFINITY, min_index;
  
   for (int i = 0; i < n; i++)
     if (selected[i] == 0 && keys[i] < min)
         min = keys[i], min_index = i;
  
   return min_index;
}

// Function to construct MST using Kruskal's algorithm
void kruskals_mst() {
  int parent[MAX_VERTICES];
  int keys[MAX_VERTICES];
  int selected[MAX_VERTICES];
  
  // Initialize keys and selected arrays
  for(int i=0; i<n; i++) {
    keys[i] = INFINITY;
    selected[i] = 0;
  }
  
  // Include minimum weight edges one by one
  int edge_count = 0; 
  while (edge_count < n-1) {
    int min = find_min_key(keys, selected);
    selected[min] = 1;

    // Update keys of adjacent vertices
    for (int i = 0; i < n; i++) {
      if(G[min][i] && selected[i] == 0 && G[min][i] < keys[i]) {
         parent[i] = min;
         keys[i] = G[min][i];    
      }
    }
    edge_count++;
  }

  // Print MST edges
  for (int i = 1; i < n; i++)
     printf("Edge %d - %d: %d \n", parent[i], i, G[i][parent[i]]);
}

int main() {
  create_graph();
  
  printf("\nMST using Prim's Algorithm:\n");
  prims_mst();

  printf("\nMST using Kruskal's Algorithm:\n"); 
  kruskals_mst();

  return 0;
}

