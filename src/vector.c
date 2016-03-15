#include <stdio.h>

#include "../include/vector.h"

#define MAX_NAME_LENGTH 512

void merge_sort(int* data, int array_size);
void merge(int* merged_data, int* left_data, int left_count, int* right_data, int right_count);

void init_vector(struct vector* v)
{
	v->data = malloc(sizeof(int) * INIT_VECTOR_SIZE);
	v->size = 0;
	v->capacity = INIT_VECTOR_SIZE;
	
	v->name = malloc( sizeof(char) * MAX_NAME_LENGTH );
	strcpy(v->name, "Default Name");
}

void init_with_name_vector(struct vector* v, char* vector_name)
{
	init_vector(v);
	strcpy(v->name, vector_name);
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

void free_vector(struct vector* v)
{
	free(v->data);
	free(v->name);
	v->size 	= 0;
	v->capacity = 0;
}
void print_elements_vector(struct vector* v)
{
	if(v != NULL)
	{
		
		printf("\n\nVector Name: %s\tVector Size: %d\tVector Capacity: %d\tElements...", v->name , v->size , v->capacity);
		
		int i;
		
		for (i = 0; i < v->size; i++) {
			
			int data_element = v->data[i];
			int data_element_pos = i + 1;
			
			printf("\n%d)\t%d", data_element_pos, data_element);
		}	
		
		printf("\n\n");
	}
}
void convert_to_static_int_array(struct vector* v, int** static_array)
{
	*static_array = malloc( v->size * sizeof(int));
	
	int i = 0;
	
	for (i = 0; i < v->size; i++)
	{
		(*static_array)[i] = access_element_vector(v,i);
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