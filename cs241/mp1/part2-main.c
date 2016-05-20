/**
 * Machine Problem 0
 * CS 241 - Spring 2016
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "part2-functions.h"

/**
 * (Edit this function to print out the "Illinois" lines in
 * part2-functions.c in order.)
 */
int main() {
  // your code here
  first_step(81);
  
  int * value = malloc(sizeof(int));
  *value = 132;
  second_step(value);
  free(value);  
  
  int** value2;
  value2 = malloc(sizeof(int*));
  *value2 = malloc( sizeof( int ) );
  **value2 = 8942;
  double_step(value2);
  free(value2[0]);
  free(value2);
  
  int* value3;
  int s = 15;
  value3 = (void*)( &s ) - 5*sizeof(void);
  //printf( "%p; %p ", &s, value3 );
  strange_step( value3);
  
  char* value4 = malloc( sizeof(char) * 4 );
  value4[3] = 0;
  empty_step( (void*)value4 );
  free( value4 );
  
  char* value5 = malloc( sizeof(char) * 4 );
  value5[3] = 'u';
  two_step( (void*) value5, value5 );
  free( value5 );
  
  char* value6 = malloc( 6 );
  three_step( value6, value6 + 2, value6 + 4);
  free( value6 );
  
  char* t1 = malloc( 16 * sizeof(char) );
  char* t2 = malloc( 16 * sizeof(char));
  char* t3 = malloc( 16 * sizeof(char));
  t1[1] = 1;
  t2[2] = 9;
  t3[3] = 17;
  step_step_step( t1, t2, t3 );
  free( t1 );
  free( t2 );
  free( t3 );
  
  
  char* a = malloc( 1 );
  int b = 10;
  *a = 10;
  it_may_be_odd( a, b );
  free( a );
  
  char jiba[13] = "niubi,CS241";
  tok_step( jiba );
  
  char* blue = malloc(4);
  blue[0] = 1;
  blue[1] = 2;
  blue[2] = 3;
  blue[3] = 0;
  the_end( (void*) blue, (void*) blue );
  free( blue );
  
  
  
  
   
  
  //printf( "%lu, %lu\n", sizeof( void), sizeof(void* ) );
  
  return 0;
}
