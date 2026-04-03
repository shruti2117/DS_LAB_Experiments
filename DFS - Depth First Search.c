#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

// Graph represented using adjacency list
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

Node* adjList[MAX_VERTICES];
int visited[MAX_VERTICES];

// Function to create a new adjacency list node
Node* createNode(int vertex) {
    //write your code here...
    Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->vertex = vertex;
	newNode->next = NULL;
	return newNode;

}

// Function to add an edge to the graph
void addEdge(int u, int v) {
    //write your code here...
    
 Node* newNode = createNode(v);
	newNode->next = adjList[u];
	adjList[u] = newNode;

}

// Function to sort the adjacency list for each vertex
void sortAdjList(int V) {
    for (int i = 0; i < V; i++) {
		Node* head = adjList[i];
		if (!head) continue;

        // Convert linked list to array
		int arr[MAX_VERTICES], count = 0;
		Node* temp = head;
		while (temp) {
			arr[count++] = temp->vertex;
			temp = temp->next;
		}

        // Sort array
		for (int j = 0; j < count - 1; j++) {
			for (int k = j + 1; k < count; k++) {
				if (arr[j] > arr[k]) {
					int t = arr[j];
					arr[j] = arr[k];
					arr[k] = t;
				}
			}
		}

		// Rebuild linked list
		adjList[i] = NULL;
		for (int j = count - 1; j >= 0; j--) {
			addEdge(i, arr[j]);
		}

	}

}

// Depth-First Search (DFS) function
void DFS(int start) {
	visited[start] = 1;
	printf("%d ", start);

	Node* temp = adjList[start];
	while (temp) {
		int adj = temp->vertex;
		if (!visited[adj]) {
			DFS(adj);
		}
		temp = temp->next;
	}

}

int main() {
    int V, E;
    int u, v, start;

    // Read number of vertices and edges
    scanf("%d %d", &V, &E);

    // Initialize adjacency list
    for (int i = 0; i < V; i++) {
        adjList[i] = NULL;
        visited[i] = 0;
    }

    // Read the edges
    for (int i = 0; i < E; i++) {
        scanf("%d %d", &u, &v);
        addEdge(u, v);
    }

    // Sort the adjacency list for each vertex
    sortAdjList(V);

    // Read the starting node
    scanf("%d", &start);

    // Perform DFS starting from the given node
    DFS(start);

    return 0;
}
