#ifndef	H_GRAPH_H
#define H_GRAPH_H

#include <stdlib.h>
#include <stdlib.h>
#include <string.h>

#define INIT_VECTOR_SIZE		256
#define INIT_EDGE_VECTOR_SIZE	32

enum vector_errors
{
	OUT_OF_BOUNDS = 499,
};

struct vector
{
	int*	data;
	int		size;
	int		capacity;
};

void 	init_vector(struct vector* v);
int		access_element_vector(struct vector* v, size_t index);
void	insert_element_vector(struct vector* v, int element_to_insert);
void	sort_elements_vector(struct vector* v);
void	print_elements_vector(struct vector* v);
void	free_vector(struct vector* v);
void	get_int_array_vector(struct vector* v, int** new_array);





typedef struct sEdge {
	int start;
	int end;	
} Edge;

void	init_edge(Edge* edge);
void	init_with_start_and_end(Edge* edge, int start, int end);
void	print_edge(Edge* e);




typedef struct sEdgeVector {
	Edge**	data;
	int		size;
	int		capacity;
} EdgeVector;

void 	init_edge_vector(EdgeVector* ev);
void 	insert_element_edge_vector(EdgeVector* ev, Edge* edge);
Edge* 	access_element_edge_vector(EdgeVector* ev, int index);
void	print_edges_edge_vector(EdgeVector* ev);

typedef struct sVertex {
	int	value;
	int	distanceFromSource;
} Vertex;

void	init_vertex(Vertex* v);
void 	init_with_value_vertex(Vertex* v, int value);
void	print_vertex(Vertex* v);







typedef struct sAdjacencyList {
	int		vertexValue;
	int*	adjacencyValues;
	int		adjacencyCount;
} AdjacencyList;

void 	init_adjacency_list(AdjacencyList* adj, int vertexValue, int adjCount, int* adjValues);
int 	get_value_for_index_adjacency_list(AdjacencyList* adj, int valueIndex);
void 	print_adjacency_list(AdjacencyList* adj);


typedef struct sGraph {
	Vertex**		vertices;
	int				vertexCount;
	AdjacencyList**	adjacencyLists;
} Graph;

void	init_with_file_graph(Graph* g, char* filename);
Vertex* access_vertex_with_index_graph(Graph* g, int vertex_index);
void	print_graph(Graph* g);

typedef struct sVertexQueue {
	Vertex**	vertices;
	int			vertexCount;
} VertexQueue;



#endif