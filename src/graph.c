#include <stdio.h>

#include "../include/graph.h"

/*
	VECTOR
*/
void merge_sort(int* data, int array_size);
void merge(int* merged_data, int* left_data, int left_count, int* right_data, int right_count);

void init_vector(struct vector* v)
{
	v->data = malloc(sizeof(int) * INIT_VECTOR_SIZE);
	v->size = 0;
	v->capacity = INIT_VECTOR_SIZE;
}

int access_element_vector(struct vector* v, size_t index)
{
	if( index >= v->size )
		exit(OUT_OF_BOUNDS);
		
	return v->data[index];
}

void insert_element_vector(struct vector* v, int element_to_insert)
{
	if( v->capacity == v->size ) {
		
		v->data = realloc(v->data, sizeof(int) * v->capacity * 2 );
		v->capacity *= 2;
	}
	
	v->data[v->size] = element_to_insert;
	v->size += 1;
}

int* vector_get_ptr(struct vector* v)
{
	return v->data;
}
void	get_int_array_vector(struct vector* v, int** new_array)
{
	*new_array = malloc( v->size * sizeof(int) );	
	
	int i = 0;
	
	for (i = 0; i < v->size; i++) {
		int new_element = access_element_vector(v, i);
		
		*new_array[i] = new_element;
	}
}
void free_vector(struct vector* v)
{
	free(v->data);
	v->size 	= 0;
	v->capacity = 0;
}
void print_elements_vector(struct vector* v)
{
	if(v != NULL)
	{
		
		printf("\n\nVector Name: DONT KNOW\tVector Size: %d\tVector Capacity: %d\tElements...", v->size , v->capacity);
		
		int i;
		
		for (i = 0; i < v->size; i++) {
			
			int data_element = v->data[i];
			int data_element_pos = i + 1;
			
			printf("\n%d)\t%d", data_element_pos, data_element);
		}	
		
		printf("\n\n");
	}
}

void sort_elements_vector(struct vector* v)
{
	merge_sort(v->data, v->size);
}

//	Merge sort operations

void merge_sort(int* data, int array_size)
{
	int mid_index, index, *left_data, *right_data;
	
	if ( array_size < 2 )
		return;
		
		
	mid_index = array_size / 2;
	
	left_data = (int*)malloc( sizeof(int) * mid_index );
	right_data = (int*)malloc( sizeof(int) * ( array_size - mid_index ) );
	
	for ( index = 0; index < mid_index; index++ )
	{
		left_data[index] = data[index];
	}
	
	for ( index = mid_index; index < array_size; index++ )
	{
		right_data[index - mid_index] = data[index]; 
	}
	
	merge_sort(left_data, mid_index);
	merge_sort(right_data, array_size - mid_index);
	merge(data, left_data, mid_index, right_data, array_size - mid_index);
	free(left_data);
	free(right_data);
}

void merge(int* merged_data, int* left_data, int left_count, int* right_data, int right_count)
{
	int index_left, index_right, index_merged;
	
	index_left 		= 0;
	index_right 	= 0;
	index_merged 	= 0;
	
	
	while( index_left < left_count && index_right < right_count )
	{
		if (left_data[index_left] < right_data[index_right])
		{
			merged_data[index_merged++] = left_data[index_left++];
		}	
		else
		{
			merged_data[index_merged++] = right_data[index_right++];
		}
	}
	
	while ( index_left < left_count )
	{
		merged_data[index_merged++] = left_data[index_left++];
	}
	
	while ( index_right < right_count )
	{
		merged_data[index_merged++] = right_data[index_right++];
	}
	
}




/*
	EDGE
*/
void	init_edge(Edge* edge) {
	edge->start = -1;
	edge->end = -1;
}
void	init_with_start_and_end(Edge* edge, int start, int end) {
	edge->start = start;
	edge->end = end;
}
void print_edge(Edge* e)
{
	printf("( %d , %d )", e->start, e->end);
}


/*
	EDGE VECTOR
*/
void init_edge_vector(EdgeVector* ev)
{
	ev->data = malloc( INIT_EDGE_VECTOR_SIZE * sizeof(Edge*));
	ev->capacity = INIT_EDGE_VECTOR_SIZE;
	ev->size = 0;
}

Edge* access_element_edge_vector(EdgeVector* ev, int index)
{
	if (index >= ev->size)
		exit(OUT_OF_BOUNDS);
		
	return (Edge*)ev->data[index];	
}

void insert_element_edge_vector(EdgeVector* ev, Edge* edge) {
	
	if( ev->capacity == ev->size ) {
		
		ev->data = realloc(ev->data, sizeof(Edge*) * ev->capacity * 2 );
		ev->capacity *= 2;
	}
	
	ev->data[ev->size] = edge;
	ev->size += 1;
}
void	print_edges_edge_vector(EdgeVector* ev)
{
	int i = 0;
	
	printf("\n");
	
	for (i = 0; i < ev->size; i++)
	{
		Edge* current_edge = access_element_edge_vector(ev, i);
		
		print_edge(current_edge);
	}
	
	printf("\n");
}
/*
	VERTEX
*/
void	init_vertex(Vertex* v)
{
	v->value = 0;
	v->distanceFromSource = -1;
}

void 	init_with_value_vertex(Vertex* v, int value)
{
	init_vertex(v);
	
	v->value = value;		
	

}

void	print_vertex(Vertex* v)
{
	printf("\n{Value : %d, Distance : %d}", v->value, v->distanceFromSource);
}

/*
	ADJACENCY LIST
*/
void init_adjacency_list(AdjacencyList* adj, int vertexValue, int adjCount, int* adjValues)
{
	adj->vertexValue = vertexValue;
	adj->adjacencyCount = adjCount;
	adj->adjacencyValues = adjValues;
}

int get_value_for_index_adjacency_list(AdjacencyList* adj, int valueIndex) {
	
	if (valueIndex >= adj->adjacencyCount) {
		return -1;
	}
	
	return adj->adjacencyValues[valueIndex];
}
void 	print_adjacency_list(AdjacencyList* adj)
{
	
	printf("\n\n");
	printf("Vertex Value:\t%d", adj->vertexValue);
	printf("\nAdjacency Count:\t%d", adj->adjacencyCount);
	printf("\nAdjacency Values:\t{ ");
	
	int i = 0;
	
	for (i = 0; i < adj->adjacencyCount;i++)
	{
		int current_value = adj->adjacencyValues[i];
		
		if (i == (adj->adjacencyCount - 1))
		{
			printf(", %d }", current_value);
		}
		else if (i == 0)
		{
			printf("%d, ", current_value);
		}
		else
		{
			printf(", %d", current_value);
		}
	}	
	
}

/*
	GRAPH
*/
void add_vertex_graph(Graph* g, int vertex_index, int vertex_value)
{
	Vertex* newVertex = malloc( sizeof(Vertex));
	
	init_with_value_vertex(newVertex, vertex_value);
	
	g->vertices[vertex_index] = newVertex;
	
}

void init_graph(Graph* g, int vertex_count)
{
	g->vertexCount = vertex_count;
	g->vertices = malloc( vertex_count * sizeof(Vertex*));
	g->adjacencyLists = malloc( vertex_count * sizeof(AdjacencyList*));
	
	int i = 0;
	
	for (i = 0; i < vertex_count; i++) {
		
		int vertex_index = i;
		int vertex_value = i + 1;
		
		add_vertex_graph(g, vertex_index, vertex_value);
	}
	
}


Vertex* access_vertex_with_index_graph(Graph* g, int vertex_index)
{
	if (vertex_index >= g->vertexCount)
		return NULL;
		
	return g->vertices[vertex_index];
}


void	init_with_file_graph(Graph* g, char* filename)
{
	//	Open the graph file for reading
	FILE	*graph_file = fopen(filename, "r");
	
	if	(graph_file == NULL)
		printf("\nThis is an unhandled error\n");
		
	int vertexCount;
	
	fscanf(graph_file, "%d", &vertexCount);
	
	printf("\n\nThe vertex count is %d\n", vertexCount);
	
	init_graph(g, vertexCount);
	
	EdgeVector edges;
	
	init_edge_vector(&edges);
	
	printf("\nThis is wowzers");
	print_vertex(access_vertex_with_index_graph( g,2));
	printf("\n");
	
	//	Now iterate throught the remaining lines in the input file
	//	to read in the edges
	
	while(!feof(graph_file))
	{
		int edgeStart;
		int edgeEnd;
		char some_read_value[1024];
		
		int ret_value = fscanf(graph_file, " (%d,%d)", &edgeStart, &edgeEnd);
		//int ret_value = fscanf(graph_file, "%s", some_read_value);
		
		//printf("\n%s\n", some_read_value);
		

		
		if (ret_value == 2)
		{
			Edge newEdge = malloc(sizeof(Edge));
		
			init_with_start_and_end(&newEdge, edgeStart, edgeEnd);
		
			insert_element_edge_vector(&edges, &newEdge);	
			
					printf("\nThe edge start is %d and the end is %d and the ret_value is %d\n", edgeStart, edgeEnd, ret_value);
		}
		
		
	}
	
	
	//	Iterate through the list of vertices to construct an adjacency list for each
	//	one
	
	int totalVertexCount = g->vertexCount;
	int i;
	
	for (i = 0; i < totalVertexCount; i++)
	{
		Vertex* current_vertex = access_vertex_with_index_graph(g, i);
		
		printf("\nCurrent something something %d\n", current_vertex->distanceFromSource);
		
		struct vector adjacency_vector;
		
		init_vector(&adjacency_vector);
		
		int totalEdgeCount = edges.size;
		int j = 0;
		
		for (j = 0; j < totalEdgeCount; j++)
		{
			Edge* current_edge = access_element_edge_vector(&edges, j);
			
			if (current_edge->start == current_vertex->value )
				insert_element_vector(&adjacency_vector, current_edge->end);
				
			if (current_edge->end == current_vertex->value)
				insert_element_vector(&adjacency_vector, current_edge->start);
		}
		
		int* static_adj_array;
		
		get_int_array_vector(&adjacency_vector, &static_adj_array);
		
		AdjacencyList adj_list;
		
		init_adjacency_list(&adj_list, current_vertex->value, adjacency_vector.size, static_adj_array);
		
		printf("\nSomething something %d\n", adj_list.vertexValue);
		
		g->adjacencyLists[i] = &adj_list;
		
		free_vector(&adjacency_vector);
	}
	
	fclose(graph_file);
	
}

void	print_graph(Graph* g)
{
	//	Print all the adjacency lists
	
	int i = 0;
	
	for (i = 0; i < g->vertexCount;i++)
	{
		AdjacencyList* current_list = g->adjacencyLists[i];
		
		print_adjacency_list(current_list);
		
	}
}