/**
 * Machine Problem 1
 * CS 241 - Spring 2016
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "document.h"
#include "vector.h"
#include "string.h"

Document *Document_create() {
  Document *document = (Document *)malloc(sizeof(Document));
  document->vector = Vector_create();
  assert(document);
  return document;
}

/**
 * Writes the content of 'document' to a file named 'filename'.
 * For each line in 'document' write it to 'filename'.
 * If line exist then format it as so ("%s\n", line),
 * where line is a null terminated string.
 * If line does not exist, then simply write a new line in its place.
 *
 * Note that "" and NULL are considered equivalent by the vector.
 */
void Document_write_to_file(Document *document, const char *filename) {
  assert(document);
  assert(filename);
  // see the comment in the header file for a description of how to do this!
  // your code here!
  FILE* fd = fopen( filename, "w+" );
  assert( fd != NULL );
  size_t  lines = Vector_size( document->vector ); //total number of lines
  for( size_t i = 0; i < lines; i ++ )
  {
  	const char* str = Vector_get( document->vector, i );
  	if( str == NULL )
  	{
  		fprintf( fd, "\n" );
  	}
  	else
  	{
  		fprintf( fd, "%s\n", str);
  	}
  }
  fclose( fd );   
  
}

/**
 * Creates a document and loads with the information from
 * the file named 'filename'.
 * Note if for any reason you can not open the file
 * then you should treat it as if it is an empty file
 * and move on.
 *
 * Note that "" and NULL are considered equivalent by the vector.
 */
Document *Document_create_from_file(char *filename) {
  assert(filename);
  // this function will read a file which is created by Document_write_to_file
  // your code here!
  FILE* fd = fopen( filename, "r+" );
  Document* Doc = Document_create();// the document to return
  assert( fd!= NULL );  
  char* line = NULL;
  size_t len = 0;
  while( getline( &line, &len, fd ) != -1 )
  {
  	size_t len = strlen( line );
  	line[ len-1 ] = 0;
  	Vector_append( Doc->vector, line );
  	
  }
  free(line);
  fclose( fd );
  
  return Doc;
}

/**
 * Frees all memory used to represent 'document'
*/
void Document_destroy(Document *document) {
  assert(document);
  Vector_destroy(document->vector);
  free(document);
}

/**
 * Returns the number of lines in use in 'document'.
 */
size_t Document_size(Document *document) {
  assert(document);
  return Vector_size(document->vector);
}

/**
 * Sets the 'index'-th line in 'document' to a copy of 'str'.
 * Note: lines in Document are 0 indexed.
*/
void Document_set_line(Document *document, size_t index, const char *str) {
  assert(document);
  Vector_set(document->vector, index, str);
}

/**
 * Returns the string stored in the 'index'-th line of 'document'.
*/
const char *Document_get_line(Document *document, size_t index) {
  assert(document);
  return Vector_get(document->vector, index);
}

/**
 * Inserts a copy of 'str' into the 'index'-th line of 'document'.
 * Note: Inserting into the middle of the document
 * shifts all subsequent lines down and inserting past the end fills
 * the gap with NULL pointers.
*/
void Document_insert_line(Document *document, size_t index, const char *str) {
  assert(document);
  Vector_insert(document->vector, index, str);
}



/**
 * Deletes the 'index'th line line in 'document'.
 * Note: Deleting a line in the middle of the document
 * shifts all subsequent lines up.
*/
void Document_delete_line(Document *document, size_t index) {
  assert(document);
  Vector_delete(document->vector, index);
}
