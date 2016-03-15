#include <stdio.h>
#include <string.h>

#include "../include/graph.h"
#include "../input_error.h"

#define CORRECT_ARG_COUNT 3
#define MAX_STRING_SIZE 512


int main(int argc, char* argv[])
{
	
	//	Remember to remove this hard-coded value and replace it with a
	//	reference to the first(second?) input argument
	char* input_filepath = "../data/input_test_1.grph";
	
	Graph main_graph;
	
	init_with_file_graph(&main_graph, input_filepath);
	
	print_graph(&main_graph);
}