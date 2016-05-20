/**
 * Machine Problem 1
 * CS 241 - Spring 2016
 */

#include "document.h"
#include "stdio.h"
// test your document here
int main() { 
	
	
	/*
	Document* t = Document_create_from_file( "doc.txt" );
	Document_write_to_file( t, "doc2.txt" );
	Document* t2 = Document_create_from_file( "doc2.txt" );
	Document_write_to_file( t2, "doc3.txt" );
	Document_destroy( t );
	Document_destroy( t2 );
	*/
	
	Document * t = Document_create_from_file( "doc.txt" );
	size_t len = Document_size( t );
	size_t i = 0;
	while( i < len)
	{
		printf( "%s\n", Document_get_line( t, i ) );
		i++;
	}
	Document_destroy( t );
	
	
	return 0; 
}
