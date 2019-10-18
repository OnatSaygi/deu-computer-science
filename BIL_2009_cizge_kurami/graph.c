// TODO komsuluk ve bitisiklik donusturucu - bu iptal
// TODO maksimum ve minimum derece bulan kod
// TODO odev bir cigenin duzenli olup olmadigini kotrol eden
// TODO cizge tumyelen c kodu

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "graph.h"

int main(int argc, char const *argv[]) {

	int a[] = {6, 5, 5, 4, 3, 3, 2, 2, 2};
	printf("%s\n", havelHakimi(a, sizeof(a)/sizeof(a[0])) ? "true" : "false");

	Graph* g = initGraph(5);
	makeEdge(g, 0, 3);
	makeEdge(g, 0, 4);
	makeEdge(g, 1, 3);
	makeEdge(g, 1, 4);
	makeEdge(g, 2, 3);
	makeEdge(g, 2, 4);
	makeEdge(g, 1, 2);

	drawGraph(g);

	for (int i = 0; i < g->size; i++) {
		printf("Tepe %d: %d\n", i, degree(g, i));
	}
	printf("max: %d\n", maxDegree(g));
	printf("min: %d\n", minDegree(g));

	printf("%s\n", isBipartite(g) ? "true" : "false");
	printf("%s\n", isBipartiteNaiive(g) ? "true" : "false");

	return 0;
}
