#include <stdio.h>
#include <string.h>

#include "../include/vector.h"
#include "../input_error.h"

#define VERTEX_QUEUE_INIT_SIZE 	256
#define MAX_STRING_SIZE			512
#define MAX_EDGE_COUNT			512
#define SOURCE_VERTEX			1

typedef enum {false, true} bool;

/*
	STRUCTS
*/
typedef struct _edge {
	int start;
	int end;
} Edge;

typedef struct _vertex {
	int value;
	int distanceFromSource;
} Vertex;

typedef struct _adjacencyList {
	int vertexValue;
	int size;
	int* data;
} AdjacencyList;

typedef struct _vertexStack {
	Vertex**	data;
	int			size;
	int			capacity;
} VertexStack;

void	init_vertex_stack(VertexStack* vs);
bool	is_empty_vertex_stack(VertexStack* vs);
void	push_vertex_stack(VertexStack* vs, Vertex* v);
Vertex*	pop_vertex_stack(VertexStack* vs);
void	print_info_stack(VertexStack* vs);

/*
	FUNCTION PROTOTYPES
*/


void	get_graph_information(char* filename, Edge*** edges, Vertex*** vertices, int* vertexCount, int* edgeCount);
void	construct_adjacency_lists(int edgeCount, Edge** edges, int vertexCount, Vertex** vertices, AdjacencyList*** adjacencyLists);
void	bfs(int sourceVertex, int vertexCount, Vertex** vertices, AdjacencyList** adjacencyLists);


void print_vertex(Vertex* v);


int main(int argc, char* argv[])
{
	
	//	Remember to remove this hard-coded value and replace it with a
	//	reference to the first(second?) input argument
	char* input_filepath = "../data/input_test_1.grph";
	
	
	//	Pull the information from the graph input file
	Edge** 				edges;
	Vertex** 			vertices;
	AdjacencyList**		adjLists;
	
	int vertexCount = -1;
	int edgeCount = -1;
	
	get_graph_information(input_filepath, &edges, &vertices, &vertexCount, &edgeCount);	

	construct_adjacency_lists(edgeCount, edges, vertexCount, vertices, &adjLists);

	bfs( SOURCE_VERTEX, vertexCount, vertices, adjLists);
	
	
	
	
	
	
	
	
	
	
}



void get_graph_information(char* filename, Edge*** edges, Vertex*** vertices, int* vertexCount, int* edgeCount)
{
	//	Open the file
	
	FILE *graph_file = fopen(filename, "r");
	
	//	Check the file for errors
	if (graph_file == NULL)
	{
		//	FIX
		printf("\nThere was an error opening the graph file\n");
		exit(1);
	}
	
	//	Read in the first value as the vertex count
	int temp_vertex_count;
	
	int ret_val = fscanf(graph_file, "%d", &temp_vertex_count);
	
	if (ret_val == 1)
	{
		*vertexCount = temp_vertex_count;
	}
	else
	{
		printf("\nI couldn't read in a proper vertex count value...\n");
		//	FIX
		exit(1);
	}
	
	//	Construct the list of vertices
	*vertices = malloc( *vertexCount * sizeof(Vertex*));
	
	int vertex_index = 0;
	
	for(vertex_index = 0; vertex_index < *vertexCount; vertex_index++)
	{
		(*vertices)[vertex_index] = malloc( sizeof(Vertex) );
		(*vertices)[vertex_index]->value = vertex_index + 1;
		(*vertices)[vertex_index]->distanceFromSource = -1;	
	}
	
	
	//	Allocate space for all the edge pointers
	*edges = malloc( MAX_EDGE_COUNT * sizeof(Edge*));
	
	//	Begin reading the edges from the file
	int edge_index = 0;
	bool did_find_edge = false;
	
	while (!feof(graph_file))
	{
		int temp_edge_start;
		int temp_edge_end;
		
		int edge_ret_val = fscanf(graph_file, " (%d,%d)", &temp_edge_start, &temp_edge_end);
		
		if (edge_ret_val == 2)
		{
			(*edges)[edge_index] = malloc( sizeof(Edge));
			(*edges)[edge_index]->start = temp_edge_start;
			(*edges)[edge_index]->end = temp_edge_end;
			edge_index++;
			
			if (did_find_edge == false)
				did_find_edge = true;
			
		}
	}
	
	if (did_find_edge == true)
		*edgeCount = edge_index;	
}

void construct_adjacency_lists(int edgeCount, Edge** edges, int vertexCount, Vertex** vertices, AdjacencyList*** adjacencyLists)
{
	//	Allocate memory for all the adjacency lists
	
	*adjacencyLists = malloc(vertexCount * sizeof(AdjacencyList*));
	
	int i = 0;
	
	for (i = 0; i < vertexCount; i++)
	{
		(*adjacencyLists)[i] = malloc( sizeof(AdjacencyList) );
		(*adjacencyLists)[i]->vertexValue = i + 1;
	}
	
	
	//	Use the edge information to construct adjacency lists for each node
	
	for (i = 0; i < vertexCount; i++)
	{
		int vertex_value = vertices[i]->value;
		
		struct vector temp_vector;
		
		init_vector(&temp_vector);
		
		
		int j = 0;
		
		for (j = 0; j < edgeCount; j++)
		{
			if (vertex_value == edges[j]->start)
				insert_element_vector(&temp_vector, edges[j]->end);
				
			if (vertex_value == edges[j]->end)
				insert_element_vector(&temp_vector, edges[j]->start);
		}
		
		int vector_size = temp_vector.size;
		int* static_vector_array;
		
		convert_to_static_int_array(&temp_vector, &static_vector_array);
		
		(*adjacencyLists)[i]->vertexValue = vertex_value;
		(*adjacencyLists)[i]->size = vector_size;
		(*adjacencyLists)[i]->data = static_vector_array;
		
		free_vector(&temp_vector);
	}
}
void bfs(int sourceVertex, int vertexCount, Vertex** vertices, AdjacencyList** adjacencyLists)
{
	
}









/*
	VERTEX STACK FUNCTIONS
*/
void init_vertex_stack(VertexStack* vs)
{
	vs->data = malloc( VERTEX_QUEUE_INIT_SIZE * sizeof(Vertex*));
	vs->size = 0;
	vs->capacity = VERTEX_QUEUE_INIT_SIZE; 
}
bool is_empty_vertex_stack(VertexStack* vs)
{
	if (vs->size == 0)
		return true;
	
	return false;
}
void push_vertex_stack(VertexStack* vs, Vertex* v)
{
	if (vs->capacity == vs->size) {
		vs->data = realloc(vs->data, sizeof(Vertex*) * vs->capacity * 2);
		vs->capacity *= 2;
	}
	print_vertex(v);
	vs->data[vs->size] = v;
	vs->size += 1;
}
Vertex*	pop_vertex_stack(VertexStack* vs)
{
	if (vs->size == 0)
		return NULL;
		
	vs->size -= 1;
	
	return vs->data[vs->size];
}
void print_info_stack(VertexStack* vs)
{
	if ( vs == NULL )
	{
		printf("\nThere's really nothing to print because the stack you gave me was null...\n")
	}
	else
	{
		printf("\n\nIs Empty:\t%s\nSize:\t%d\nCapacity:\t%d\n\n", ((vs->size == 0) ? "Yes" : "No"), vs->size, vs->capacity);
	}
}

/*
	UTILITY FUNCTIONS
*/
void print_vertex(Vertex* v)
{
	if (v == NULL)
	{
		printf("\nThe vertex was NULL. Quitting now...\n");
		exit(1);
	}
	
	printf("\n{ Value : %d, Distance : %d }", v->value, v->distanceFromSource);
}