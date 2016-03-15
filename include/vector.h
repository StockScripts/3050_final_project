#ifndef H_VECTOR_H
#define H_VECTOR_H

#include <stdlib.h>
#include <stdlib.h>
#include <string.h>

#define INIT_VECTOR_SIZE 512

enum vector_errors
{
	OUT_OF_BOUNDS = 0,
};

struct vector
{
	char*	name;
	int*	data;
	int		size;
	int		capacity;
};

void 	init_vector(struct vector* v);
void	init_with_name_vector(struct vector* v, char* vector_name);
int		access_element_vector(struct vector* v, size_t index);
void	insert_element_vector(struct vector* v, int element_to_insert);
void	sort_elements_vector(struct vector* v);
void	print_elements_vector(struct vector* v);
void	free_vector(struct vector* v);

#endif