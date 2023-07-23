#include <stdio.h>
#include <stdlib.h>

//edge -> source n destination
struct Edge{
	int src, dst;
};

struct Graph{
	//vCount -> jumlah vertex
	//eCount -> jumlah edge
	int vCount, eCount;
	Edge *edge;
};

Graph *createGraph(int vCount, int eCount){
	Graph *graph = (Graph*) malloc (sizeof(Graph));
	graph->vCount = vCount;
	graph->eCount = eCount;
	graph->edge = (Edge*) malloc(sizeof(Edge)*eCount); //edge[0],edge[1], dst

	return graph;
}

int findParent(int parent[], int vertex){
	if (parent[vertex] == vertex){
		//kalau parentya adalah diri dia sendiri (parent tertinggi)
		return vertex;
	}else{
		return parent[vertex] = findParent(parent, parent[vertex]);
	}
}

bool isCyclic(Graph *graph){
	int parent[graph->vCount];
	
	// makeSet
	for (int i = 0; i < graph->vCount; i++){
		parent[i] = i;
	}
	
	//cek edge apakah menyebabkan cyclic ato ngga
	for (int i = 0; i < graph->eCount; i++){
		int src = graph->edge[i].src;
		int dst = graph->edge[i].dst;
		
		//findParent
		int srcP = findParent(parent, src);
		int dstP = findParent(parent, dst);
		
		//kalo parent tertinggi sama, berarti cyclic
		if (srcP == dstP) return true;
		
		//kalo parent tertinggi ngga sama, berarti union
		parent[srcP] = dstP;
	}
	
	return false;
}

int main(){
	int vCount = 4;
	int eCount = 4;
	Graph *graph = createGraph (vCount, eCount);
	
	graph->edge[0].src = 0;
	graph->edge[0].dst = 1;
	
	graph->edge[1].src = 1;
	graph->edge[1].dst = 2;
	
	graph->edge[2].src = 2;
	graph->edge[2].dst = 3;
	
	graph->edge[3].src = 0;
	graph->edge[3].dst = 3;
	
	
	printf ("Your graph is %s\n", isCyclic(graph)? "cyclic":"not cyclic");
	
	return 0;
}

