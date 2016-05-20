/**
 * Machine Problem 1
 * CS 241 - Spring 2016
 */

#include "vector.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Test your vector here
int main() { 
	Vector* temp = Vector_create(); //create a vector
	
	Vector_append( temp, "a");//1
	Vector_append( temp, "b");//2
	Vector_append( temp, "c");//3
	Vector_append( temp, "d");//4
	Vector_append( temp, NULL);//5
	Vector_append( temp, "f");//6
	Vector_append( temp, "g");//7
	Vector_append( temp, NULL);//8
	Vector_append( temp, "");//9
	Vector_append( temp, "h");//10
	Vector_append( temp, "i");//11
	Vector_append( temp, NULL);//12
	
	Vector_resize( temp, 20 );
	
	if( Vector_size(temp) != 20 || strcmp( Vector_get( temp, 10 ), "i" ) || Vector_get( temp, 15 ) != NULL )
		perror( "something wrong.\n");
	
	//done for append, resize, get, size
	
	Vector_set( temp, 19, "caibi" );
	Vector_insert( temp, 20, "niubi" );
	Vector_insert( temp, 30, "wori" );
	
	if( Vector_size(temp) != 31 || strcmp( Vector_get( temp, 19 ), "caibi" ) || strcmp( Vector_get( temp, 20 ), "niubi" ) ||  Vector_get( temp, 15 ) != NULL || strcmp( Vector_get( temp, 30 ), "wori" ) )
		perror( "something wrong.\n");
	
	Vector_delete( temp, 11 );
	Vector_delete( temp, 27 );
	Vector_delete( temp, 1 );
	Vector_delete( temp, 18 );
	
	if( Vector_size(temp) != 27 || strcmp( Vector_get( temp, 4 ), "f" ) || strcmp( Vector_get( temp, 26 ), "wori") || Vector_get( temp, 18 ) !=NULL || strcmp( Vector_get( temp, 17 ), "caibi") )
		perror( "something wrong.\n");
	
	
	Vector_destroy( temp );

	return 0; 
}
