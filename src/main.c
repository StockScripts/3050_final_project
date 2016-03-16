#include <stdio.h>
#include <string.h>
#include <limits.h>

#include "../include/vector.h"
#include "../input_error.h"

#define VERTEX_QUEUE_INIT_SIZE 	256
#define MAX_STRING_SIZE			512
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

void 	print_vertex(Vertex* v);

typedef struct _adjacencyList {
	int vertexValue;
	int size;
	int* data;
} AdjacencyList;

void	free_adjacencyList(AdjacencyList* al);



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
void	final_print(int vertexCount, Vertex** vertices);
void	cleanup(int vertexCount, int edgeCount, Edge** edges, Vertex** vertices, AdjacencyList** adjacencyLists);




int main(int argc, char* argv[])
{		
	//	Declare the main variables to be used throughout the program
	Edge** 				edges;
	Vertex** 			vertices;
	AdjacencyList**		adjLists;
	
	int vertexCount	= -1;
	int edgeCount 	= -1;
	
	//	Pull the graph information out of the input file and use that data
	//	to populated the Edge and Vertex 'arrays'
	get_graph_information(argv[1], &edges, &vertices, &vertexCount, &edgeCount);	

	//	Use the Edge and Vertex 'arrays' to contruct adjacency lists for each
	//	vertex
	construct_adjacency_lists(edgeCount, edges, vertexCount, vertices, &adjLists);

	//	Run the Breadth First Search algorithm on the graph information obtained
	//	by the previous two functions
	bfs( SOURCE_VERTEX , vertexCount, vertices, adjLists);
	
	//	Print out the vertex information (vertex value & distance from source) to
	//	stdout in the manner described in the assignment document
	final_print(vertexCount, vertices);
		
		
	//	Free any memory allocated
	cleanup(vertexCount, edgeCount, edges, vertices, adjLists);
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
	
	//	Check if the return value from fscanf is 1 indicating that
	//	1 value was read in from the file. If so then copy the value
	//	that was read in into the variable 'vertexCount'
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
		//	For every vertex allocate memory for the struct
		//	
		//	Set the value of the vertex to the index value
		//		and set the 'distanceFromSource' value to -1
		//		indicating a distance of infinity from the source
		(*vertices)[vertex_index] = malloc( sizeof(Vertex) );
		(*vertices)[vertex_index]->value = vertex_index + 1;
		(*vertices)[vertex_index]->distanceFromSource = -1;	
	}
	
	
	//	Allocate space for all the edge pointers
	*edges = malloc( UINT_MAX * sizeof(Edge*));
	
	//	Begin reading the edges from the file
	int edge_index = 0;
	bool did_find_edge = false;
	
	while (!feof(graph_file))
	{
		int temp_edge_start;
		int temp_edge_end;
		
		int edge_ret_val = fscanf(graph_file, " (%d,%d)", &temp_edge_start, &temp_edge_end);
		
		
		//	If the number of values read in from the file is equal to two
		//	(the start and end values of a vertex) then you know you've 
		//	found a valid edge and can use these values to create a new
		//	edge struct
		if (edge_ret_val == 2)
		{
			//	For every edge allocate memory for the struct
			//
			//	Set the start and end values of the newly allocated
			//	struct to the start and end values that were pulled
			//	from the file
			(*edges)[edge_index] = malloc( sizeof(Edge));
			(*edges)[edge_index]->start = temp_edge_start;
			(*edges)[edge_index]->end = temp_edge_end;
			
			
			//	Increment the edge index to keep track of how many
			//	edges are being read in from the file
			edge_index++;
						
						
			//	Make sure to note if at least one edge was found
			if (did_find_edge == false)
				did_find_edge = true;
		}
	}
	
	
	if (did_find_edge == true)
		*edgeCount = edge_index;	
		
		
	//	Close the file
	if (fclose(graph_file) == 0)
	{
		//	FIX
		printf("\nThe file was close successfully!\n");
	}
	else
	{
		printf("\nThe file could not be closed...\n");
	}
	
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
	//	Set the initial distances
	
	int i;
	Vertex* source_vertex;
	
	for (i = 0; i < vertexCount; i++)
	{
		int vertex_value = i + 1;
		
		Vertex* current_vertex = vertices[i];
		
		if (current_vertex->value == sourceVertex)
		{
			current_vertex->distanceFromSource = 0;
			source_vertex = current_vertex;
		}
		else
		{
			current_vertex->distanceFromSource = -1;
		}
	}
	
	
	VertexStack bfs_stack;
	
	init_vertex_stack(&bfs_stack);
	
	push_vertex_stack(&bfs_stack, source_vertex);
	
	while(is_empty_vertex_stack(&bfs_stack) == false)
	{
		Vertex* current_vertex = pop_vertex_stack(&bfs_stack);
		
		int current_vertex_index = (current_vertex->value - 1);
		
		AdjacencyList* adj_list = adjacencyLists[current_vertex_index];
		
		//	Iterate through all the vertices in the adjacency list of the vertex
		
		int j = 0;
		
		for (j=0; j < adj_list->size; j++)
		{
			int adj_list_value = adj_list->data[j];
			int adj_list_index_value = adj_list_value - 1;
			
			Vertex* adj_list_current_vertex = vertices[adj_list_index_value];
			
			if(adj_list_current_vertex->distanceFromSource == -1)
			{
				adj_list_current_vertex->distanceFromSource = current_vertex->distanceFromSource + 1;
				push_vertex_stack(&bfs_stack, adj_list_current_vertex);
			}
				
		}
	}
}
void final_print(int vertexCount, Vertex** vertices)
{
	//	Iterate through all the vertices and print them out in the format
	//	specified in the instruction document
	int i;
	
	for (i = 0; i < vertexCount; i++)
	{
		Vertex* current_vertex = vertices[i];
		
		printf("%d %d\n", current_vertex->value, current_vertex->distanceFromSource);
	}
}
void cleanup(int vertexCount, int edgeCount, Edge** edges, Vertex** vertices, AdjacencyList** adjacencyLists)
{
	//	First free all the individual vertices
	int i;
	
	for (i = 0; i < vertexCount; i++)
	{
		free(vertices[i]);
	}
	
	//	Next free all the vertex pointers that were allocated
	free(vertices);
	
	//	Free all the individual adjacency lists
	
	for (i = 0; i < vertexCount; i++)
	{
		free_adjacencyList(adjacencyLists[i]);
	}
	
	//	Free all the AdjacencyList pointers that were allocated
	
	free(adjacencyLists);
	
	for (i = 0; i < edgeCount; i++)
	{
		free(edges[i]);
	}
	
	free(edges);
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
		printf("\nThere's really nothing to print because the stack you gave me was null...\n");
	}
	else
	{
		printf("\n\nIs Empty:\t%s\nSize:\t%d\nCapacity:\t%d\n\n", ((vs->size == 0) ? "Yes" : "No"), vs->size, vs->capacity);
	}
}

/*
	Adjacency List Functions
*/
void free_adjacencyList(AdjacencyList* al)
{
	if (al != NULL)
	{
		if (al->data != NULL)
			free(al->data);
	}
}

/*
	Vertex Functions
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