#include <stdio.h>
#include <string.h>

#include "../include/vector.h"
#include "../input_error.h"

#define CORRECT_ARG_COUNT	3
#define MAX_STRING_SIZE		512
#define MAX_EDGE_COUNT		512

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

/*
	FUNCTION PROTOTYPES
*/


void	get_graph_information(char* filename, Edge*** edges, Vertex*** vertices, int* vertexCount, int* edgeCount);

int main(int argc, char* argv[])
{
	
	//	Remember to remove this hard-coded value and replace it with a
	//	reference to the first(second?) input argument
	char* input_filepath = "../data/input_test_1.grph";
	
	
	//	Pull the information from the graph input file
	Edge** edges;
	Vertex** vertices;
	int vertexCount = -1;
	int edgeCount = -1;
	
	get_graph_information(input_filepath, &edges, &vertices, &vertexCount, &edgeCount);	
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