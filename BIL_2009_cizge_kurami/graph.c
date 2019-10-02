// hafta 1
// TODO komsuluk ve bitisiklik donusturucu - bu iptal
// TODO maksimum ve minimum derece bulan kod

// hafta 2
// TODO odev bir cigenin duzenli olup olmadigini kotrol eden
// TODO cizge tumyelen c kodu


#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct {
	int size;
	int* matrix;
} Graph;

Graph* initGraph(int node_count) {
	Graph* g = (Graph*)malloc(sizeof(Graph));
	g->size = node_count;
	g->matrix = (int*)calloc(node_count * node_count, sizeof(int));

	return g;
}

void freeGraph(Graph* g) {
	free(g->matrix);
	free(g);
}

int getEdge(Graph* g, int source, int destination) {
	return g->matrix[source * g->size + destination];
}

void setEdge(Graph* g, int source, int destination, int value) {
	g->matrix[source * g-> size + destination] = value;
}

void drawGraph(Graph* g) {
	for (int i = 0; i < g->size; i++) {
		for (int j = 0; j < g->size; j++) {
			printf("%d ", getEdge(g, i, j));
		}
		printf("\n");
	}
	printf("\n");
}

void makeEdge(Graph* g, int source, int destination) {
	setEdge(g, source, destination, 1);
	setEdge(g, destination, source, 1);
	return;
}

void removeEdge(Graph* g, int source, int destination) {
	setEdge(g, source, destination, 0);
	setEdge(g, source, destination, 0);
	return;
}

// etkilenmis alt cizge
Graph* getInducedSubgraph(Graph* g, int* vertices, int count) {
	Graph* a = initGraph(count);

	for (int i = 0; i < count; i++) {
		for (int j = 0; j < count; j++) {
			setEdge(a, i, j, getEdge(g, vertices[i], vertices[j]));
		}
	}
	return a;
}

// tumyelen cizge
// tam graph olmasini saglamayan butun ayritlari iceren graph
Graph* getComplementGraph(Graph* g) {
	Graph* a = initGraph(g->size);
	for (int i = 0; i < g->size; i++) {
		for (int j = 0; j < g->size; j++) {
			setEdge(a, i, j, !getEdge(g, i, j));
		}
	}
	return a;
}

// Returns how many connections is a given vertex has
// Equalivent to deg(v)
int degree(Graph* g, int vertex) {
	int count = 0;
	for (int i = 0; i < g->size; i++) {
		if(getEdge(g, vertex, i) != 0) {
			count++;
		}
	}
	return count;
}

int maxDegree(Graph* g) {
	int max = 0;
	for (int i = 0; i < g->size; i++) {
		if(degree(g, i) > max) {
			max = degree(g, i);
		}
	}
	return max;
}

int minDegree(Graph* g) {
	int min = g->size;
	for (int i = 0; i < g->size; i++) {
		if(degree(g, i) < min) {
			min = degree(g, i);
		}
	}
	return min;
}

bool isIsolated(Graph* g, int vertex) {
	for (int i = 0; i < g->size; i++) {
		if (getEdge(g, vertex, i) != 0) {
			return false;
		}
	}
	return true;
}


int arraySum(int* arr, int count) {
	int sum = 0;
	for (int i = 0; i < count; i++) {
		sum += arr[i];
	}
	return sum;
}

// Largest to smallest for qsort()
int compare(const void * a, const void * b) {
	return ( *(int*)b - *(int*)a );
}

void printArray(int* arr, int count) {
	for (int i = 0; i < count; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

bool havelHakimi(int* arr, int count) {
	qsort(arr, count, sizeof(int), compare);
	printArray(arr, count);
	while(arraySum(arr, count) > 1) {
		for (int i = 1; i < arr[0] + 1; i++) {
			arr[i]--;
		}
		arr[0] = 0;
		qsort(arr, count, sizeof(int), compare);
		printArray(arr, count);
	}
	return !arraySum(arr, count);
}

// No node is connected to any other node
void setNullGraph(Graph* g) {
	for (int i = 0; i < g->size; i++) {
		for (int j = 0; j < g->size; j++) {
			removeEdge(g, i, j);
		}
	}
}

// Every node is connected to every other node
// Shown as Kn, n is node count
void setCompleteGraph(Graph* g) {
	for (int i = 0; i < g->size; i++) {
		for (int j = 0; j < g->size; j++) {
			makeEdge(g, i, j);
		}
	}
	return;
}

// Every node is connected in series in an open form
// Shown as Pn, n is node count
void setPathGraph(Graph* g) {
	for (int i = 0; i < g->size - 1; i++) {
		makeEdge(g, i, i+1);
	}
	return;
}

// Every node is connected in series in a cloed form
// Shown as Cn, n is node count
void setCyclicGraph(Graph* g) {
	for (int i = 0; i < g->size; i++) {
		makeEdge(g, i, (i+1) % g->size);
	}
	return;
}

// Every node is connected to a single node
// Shown as Sn, n is node count
void setStarGraph(Graph* g) {
	for (int i = 1; i < g->size; i++) {
		makeEdge(g, 0, i);
	}
	return;
}

// Combintaion of a cycle graph and a star graph
// Shown as Wn, n is node count
void setWheelGraph(Graph* g) {
	for (int i = 0; i < g->size; i++) {
		makeEdge(g, i, (i+1) % g->size);
	}
	for (int i = 1; i < g->size; i++) {
		makeEdge(g, 0, i);
	}
	return;
}

// Checks for 2^n * m naiive method
bool isBipartite(Graph* g) {
	for (int i = 0; i < 1 << g->size; i++) {
		for (int j = 0; j < g->size; j++) {
			printf("%d ", !!(i & (1 << j)));
		}
		printf("\n");
	}
	return false;
}

bool isRegularGraph(Graph* g) {
	int d = degree(g, 0);
	for (int i = 1; i < g->size; i++) {
		if (degree(g, i) != d) {
			return false;
		}
	}
	return true;
}

// herhangi bir ayrittan baska ayrita giden grup
// yuruyus
bool validWalk(Graph* g, int* vertices, int size) {
	// TODO
	return false;
}

// walk ama ayni noktadan gecmiyor
// yol
bool validPath(Graph* g, int* vertices, int size) {
	// TODO
	return false;
}

// walk ama basladigi yerde bitiyor
// cevre
bool validCycle(Graph*g, int* vertices, int size) {
	// TODO
	return false;
}

int main(int argc, char const *argv[]) {

	int a[] = {6, 5, 5, 4, 3, 3, 2, 2, 2};
	printf("%s\n", havelHakimi(a, sizeof(a)/sizeof(a[0])) ? "true" : "false");

	Graph* g = initGraph(4);
	drawGraph(g);

	isBipartite(g);

	printf("%d\n", degree(g, 0));

	drawGraph(g);
	freeGraph(g);
	return 0;
}
