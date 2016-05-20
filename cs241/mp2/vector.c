/**
 * Machine Problem 1
 * CS 241 - Spring 2016
 */

/* An automatically-expanding array of strings. */
#include "vector.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

#define INITIAL_CAPACITY 10

Vector *Vector_create() {
  
  Vector* out = malloc( sizeof( Vector) );
  out->size = 0;
  out->capacity = 10;
  out->array = malloc( 10*sizeof(char*) );
  return out;
}

void Vector_destroy(Vector *vector) {
  assert(vector);
  for( size_t i = 0; i< vector->size; i ++ )
  {
  	if( vector->array[i] != NULL )
  		free( vector->array[i]);
  }
  free(vector->array);
  free(vector);
  
}

size_t Vector_size(Vector *vector) {
  assert(vector);
  return vector->size;
}

void Vector_resize(Vector *vector, size_t new_size) {
  assert(vector);
  size_t oldsize = Vector_size( vector );
  size_t capacity = vector->capacity;
  vector->size = new_size; //set before loop
  if( oldsize >= new_size )//shrink
  {
  	for(size_t i = new_size; i<oldsize; i++ )
  	{
  		if( vector->array[i]!=NULL )
  			free( vector->array[i] );
	}
  }
  else //size increase
  {
  	if( new_size > capacity) //need to increase the capacity
  	{
  		while( new_size > capacity )
  			capacity *= 2;
 		vector->array = realloc( vector->array, capacity * sizeof(char*) );
 		vector->capacity = capacity;
 	}	
 	for( size_t i = oldsize; i<new_size; i++ )
 		Vector_set( vector, i, NULL );
  	
  }
  	
}

void Vector_set(Vector *vector, size_t index, const char *str) {
  assert(vector);
  assert( index >=0 && index < vector->size);//must be in the range of [0, size)
  if( str == NULL )
  	vector->array[index] = NULL;
  else
  {
  	vector->array[index] = malloc( strlen(str) + 1 );
  	strcpy( vector->array[index], str );
  }  
  
}

const char *Vector_get(Vector *vector, size_t index) {
  assert(vector);
  assert( index>=0 && index<vector->size);
  if( vector->array[index] == NULL )
  	return NULL; 
  return vector->array[index];
}

void Vector_insert(Vector *vector, size_t index, const char *str) {
  assert(vector);
  if( index >= vector->size ) // the index is beyond the size of vector
  {
  	Vector_resize( vector, index +1 );
  	Vector_set( vector, index, str );
  }
  
  else //index is smaller than the size of vector
  {
  	if( vector->array[index] == NULL)//if it is NULL
  		Vector_set( vector, index, str );
  	else //not NULL
  	{
  		if( vector->size + 1 > vector->capacity ) // if the vector is already full	
  			vector->capacity *= 2;//double the capacity
  	
  		char** newarray = malloc( sizeof(char*) * vector->capacity );
  		//copy before index
  		for( size_t i = 0; i < index; i ++ )
  		{
  			if( vector->array[i] != NULL )
  			{
  				newarray[i] = malloc( strlen(vector->array[i]) + 1 );
  				strcpy( newarray[i], vector->array[i] );
  				free( vector->array[i] );
  			}
  			else 
  				newarray[i] = NULL;	   
  		}
  		//copy at index
  		if( str == NULL )
  			newarray[index] = NULL;
  		else
  		{
  			newarray[index] = malloc( strlen(str) + 1 );
  			strcpy( newarray[index], str );
  		}
  		//copy after index
  		for( size_t i = index; i < vector->size; i ++ )
  		{
  			if( vector->array[i] != NULL )
  			{
  				newarray[i+1] = malloc( strlen(vector->array[i]) + 1 );
  				strcpy( newarray[i+1], vector->array[i] );
  				free( vector->array[i] );
  			}
  			else 
  				newarray[i+1] = NULL;	   
  		}
  		//assign the vector with new array
  		free( vector->array );
  		vector->array = newarray;
  		vector->size+=1;//size++
  	}
  
  }
}

void Vector_delete(Vector *vector, size_t index) {
  assert(vector);
  assert( index < vector->size );
  char** newarray = malloc( sizeof(char*) * vector->capacity );
  //before the index
  for( size_t i = 0; i < index; i ++ )
  {
  	if( vector->array[i] != NULL )
  	{
  		newarray[i] = malloc( strlen(vector->array[i]) + 1 );
  		strcpy( newarray[i], vector->array[i] );
  		free( vector->array[i] );
  	}
  	else 
  		newarray[i] = NULL;	  
  }
  //at index
  if( vector->array[index] != NULL )
  	free( vector->array[index] );
  //after after index
  for( size_t i = index+1; i < vector->size; i ++ )
  {
  	if( vector->array[i] != NULL )
  	{
  		newarray[i-1] = malloc( strlen(vector->array[i]) + 1 );
  		strcpy( newarray[i-1], vector->array[i] );
  		free( vector->array[i] );
  	}
  	else 
  		newarray[i-1] = NULL;	   
  }
  //assign the vector with new array
  free( vector->array );
  vector->array = newarray;	
  vector->size --;
    
}

void Vector_append(Vector *vector, const char *str) {
  assert(vector);
  vector->size += 1;
  if( vector->size > vector -> capacity)
  {	
  	vector->capacity *= 2;
  	vector->array = realloc( vector->array, (vector->capacity) *sizeof(char*) );
  }	
  Vector_set( vector, vector->size-1, str );
  
}
