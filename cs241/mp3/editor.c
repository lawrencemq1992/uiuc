#include "editor.h"
#include "document.h"
#include "format.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char *get_filename(int argc, char *argv[]) {
  // TODO implement get_filename
  // take a look at editor_main.c to see what this is used for
  if( argc == 1 )
  	print_usage_error();
  return argv[1];
}

void handle_display_command(Document *document, const char *command) {
  // TODO implement handle_display_command
  
  	if( document == NULL )
  	{
		print_document_empty_error();
		return;
	}
	
	//print the whole document
	if( strlen( command ) == 1 )
	{
		size_t size = Document_size(document);
		for( size_t i = 0; i < size;  i ++ )
		{
			print_line( document, i);
		}
		return;
	}
		
	if( command[1] != ' ' )
	{
		invalid_command(command);
		return;
	}	
	
	
	else  //with line number
	{
		int idx = 2;
		int** page = malloc( sizeof(int*) * ( strlen(command) -2 ) );
		
		// check the command 
		while( command[idx] )
		{
			if( command[idx] == ' ' || command[idx]<=47 || command[idx]>=58 || command[2] == '0')
			{
				invalid_command(command);
				return;
			}
			idx++;
		}
		//get the page number
		idx = 2;
		int counter = 0;
		while( command[idx] )
		{
			page[idx-2] = malloc( sizeof(int) );
			*page[idx-2] = command[idx]-'0';
			idx++;
			counter++;
		}
		idx = 1;
		int pagenum = 0;	
		for( int i = counter-1; i >=0; i-- )
		{
			//printf( "page num: %d\n", *page[i] );
			pagenum += idx * (*page[i]);
			idx*= 10;
		}	
		// free page
		for( int j = 0; j < counter; j ++ )
		{
			free(page[j]);
		}
		free(page);
		
		// wrong page number
		if( pagenum < 1 || pagenum >(int)Document_size(document) )
		{
			invalid_line();
			return;
		}
		
		//printf( "page num: %d\n", pagenum );
		
		int start = pagenum - 5;
		if( start < 1 )
			start = 1;
		int end = pagenum + 5;
		if( end > (int)Document_size(document) )
			end = (int)Document_size(document);
		
		
		//printf( "start: %d\n", start );	
		while( start <= end )
		{
			print_line( document, (size_t)start -1 );	
			start++;
		}
	}
}

void handle_write_command(Document *document, const char *command) {
  // TODO implement handle_write_command
  if( document == NULL )
  {
	print_document_empty_error();
	return;
  }	
  
  if( command[1] != ' ' ) 
  {
  	invalid_command(command);
		return;
  }
  
  // check the page, see if it is vaild
  int idx = 2;
  int size = strlen( command );
  while(  idx < size )	
  {
  	if( command[idx] == ' ' )
  		break;
  	if( command[idx]<=47 || command[idx]>=58 || command[2] == '0')
	{
		invalid_command(command);
		return;
	}
	idx++;
  }
  
  if( idx == size )
  {
	invalid_command(command);
	return;
  }
  
  //get the page number
  int** page = malloc( sizeof(int*) * ( idx -2 ) );
		
  int idx2 = 2;
  int counter = 0;
  while( idx2 < idx )
  {
	page[idx2-2] = malloc( sizeof(int) );
	*page[idx2-2] = command[idx2]-'0';
	idx2++;
	counter++;
  }
  idx2 = 1;
  int pagenum = 0;	
  for( int i = counter-1; i >=0; i-- )
  {
	//printf( "page num: %d\n", *page[i] );
	pagenum += idx2 * (*page[i]);
	idx2*= 10;
  }	
  // free page
  for( int j = 0; j < counter; j ++ )
  {
	free(page[j]);
  }
  free(page);
  
  //check weather this page number is inside the document
  if( pagenum < 1 )
  {  
  	invalid_line();
	return;
  }
  
  //page > size
  if( pagenum > (int) Document_size(document) )
  {
  	for( size_t i = Document_size(document); i < (size_t)pagenum ; i ++)
  	{
  		Document_set_line( document, i, "");
	}
  }
  
  //command is ""
  idx += 1;
  if( idx == size )
  	return;
  
  int end = idx;
  const char* x = command + idx;
  
  //idx is the start of string
  //get the num of '$'
  int linecounter = 1;
  while( end != size )
  {
  	if( command[end] == '$' )
  		linecounter ++;
  	end++;
  }
  
  //simple case
  if( linecounter == 1 )
  {
  	char* s  = strdup( x );
  	Document_set_line( document, pagenum - 1 , s );
  	free( s );
  	return;
  }
  
  //multiple case
  end = idx;
  int lineread = 0;
  while( end < size )
  {
  	while( end != size && command[end] != '$' )
  		end++;
  			
  	int bytes = end - idx;
  	
  	char*s = malloc( bytes + 1 );
  	//just a $
  	if( bytes == 0 )
  	{	
  		strcpy( s, "" );
  		end++;
  		idx++;
  		x++; 
  	}
  	
  	else //not just '$'
  	{
  		strncpy( s, x, bytes);
  		//printf( "%d\n", bytes );
  		s[bytes] = '\0';
  		//printf( "%s\n", s );
  		x += bytes + 1;
  		end++;			
  		idx = end;	
  	}
  	char* hehe = strdup(s);
  	if( lineread == 0 )
  	{
  		lineread = 1;	
  		Document_set_line( document, pagenum - 1, hehe);
  	}
  	else
  		Document_insert_line( document, pagenum -1 , hehe );
  	pagenum++;
  	free(s);
  	free(hehe);
  	if( end == size && command[end-1] == '$' )
  		Document_insert_line( document, pagenum -1 , "" );		
	  
  }
}
void handle_append_command(Document *document, const char *command) {
  // TODO implement handle_append_command
  
  if( document == NULL )
  {
	print_document_empty_error();
	return;
  }	
  
  if( command[1] != ' ' ) 
  {
  	invalid_command(command);
		return;
  }
  
  // check the page, see if it is vaild
  int idx = 2;
  int size = strlen( command );
  while(  idx < size )	
  {
  	if( command[idx] == ' ' )
  		break;
  	if( command[idx]<=47 || command[idx]>=58 || command[2] == '0')
	{
		invalid_command(command);
		return;
	}
	idx++;
  }
  
  if( idx == size )
  {
	invalid_command(command);
	return;
  }
  
  //get the page number
  int** page = malloc( sizeof(int*) * ( idx -2 ) );
		
  int idx2 = 2;
  int counter = 0;
  while( idx2 < idx )
  {
	page[idx2-2] = malloc( sizeof(int) );
	*page[idx2-2] = command[idx2]-'0';
	idx2++;
	counter++;
  }
  idx2 = 1;
  int pagenum = 0;	
  for( int i = counter-1; i >=0; i-- )
  {
	//printf( "page num: %d\n", *page[i] );
	pagenum += idx2 * (*page[i]);
	idx2*= 10;
  }	
  // free page
  for( int j = 0; j < counter; j ++ )
  {
	free(page[j]);
  }
  free(page);
  
  //check weather this page number is inside the document
  if( pagenum < 1 )
  {  
  	invalid_line();
	return;
  }
  
  
  //command is ""
  idx += 1;
  int end = idx;
  const char* x = command + idx;
  
  //page > size  
  if( pagenum > (int) Document_size(document) )
  {
  	for( size_t i = Document_size(document); i < (size_t)pagenum ; i ++)
  	{
  		Document_set_line( document, i, "");
	}
  }
    	
  //get the num of '$'
  int linecounter = 1;
  while( end != size )
  {
  	if( command[end] == '$' )
  		linecounter ++;
  	end++;
  }
  
  //simple case
  if( linecounter == 1 )
  {
  	char* s = strdup( x );
  	const char* s2 = Document_get_line( document, pagenum - 1 );
  	char* s3;
  	if( s2 !=  NULL )
  		s3 = malloc( strlen(s) + strlen(s2) + 1 );
  	else 
  		s3 = malloc( strlen(s) + 1 );
  	if( s2 != NULL )
  		strcpy( s3, s2);
  	//printf( "%s\n", s3 );	
  		
  	strcat( s3, s );
  	//printf( "%s\n", s3 );
  	Document_set_line( document, pagenum - 1 , s3 );  //include the case line is empty
  	free(s);
  	free(s3);
  	return;
  }
  
  //multiple case
  end = idx;
  int lineread = 0;
  while( end < size )
  {
  	while( end != size && command[end] != '$' )
  		end++;
  			
  	int bytes = end - idx;
  	
  	char*s = malloc( bytes + 1 );
  	//just a $
  	if( bytes == 0 )
  	{	
  		strcpy( s, "" );
  		end++;
  		idx++;
  		x++; 
  	}
  	
  	else //not just '$'
  	{
  		strncpy( s, x, bytes);
  		//printf( "%d\n", bytes );
  		s[bytes] = '\0';
  		//printf( "%s\n", s );
  		x += bytes + 1;
  		end++;			
  		idx = end;	
  	}
  	char* hehe = strdup(s);
  	if( lineread == 0 )
  	{
  		lineread = 1;
  		char* s1 = strdup( hehe );
  		const char* s2 = Document_get_line( document, pagenum - 1 );
  		char* s3;
  		if( s2 !=  NULL )
  			s3 = malloc( strlen(s1) + strlen(s2) + 1 );
  		else 
  			s3 = malloc( strlen(s1) + 1 );
  		if( s2 != NULL )
  			strcpy( s3, s2);
  		strcat( s3, s1 );
  		Document_set_line( document, pagenum - 1 , s3 );  //include the case line is empty
  		free(s1);
  		free(s3);
  	}
  	else
  		Document_insert_line( document, pagenum -1 , hehe );
  	pagenum++;
  	free(s);
  	free(hehe);
  	if( end == size && command[end-1] == '$' )
  		Document_insert_line( document, pagenum -1 , "" );		
	  
  }
}
 
void handle_delete_command(Document *document, const char *command) {
  // TODO implement handle_delete_command
  if( document == NULL )
  {
	print_document_empty_error();
	return;
  }	
  
  if( command[1] != ' ' ) 
  {
  	invalid_command(command);
		return;
  }
  
  // check the page, see if it is vaild
  int idx = 2;
  int size = strlen( command );
  while(  idx < size )	
  {
  	if( command[idx] == ' ' )
  		break;
  	if( command[idx]<=47 || command[idx]>=58 || command[2] == '0')
	{
		invalid_command(command);
		return;
	}
	idx++;
  }
  
  if( idx != size )
  {
	invalid_command(command);
	return;
  }
  
  //get the page number
  int** page = malloc( sizeof(int*) * ( idx -2 ) );
		
  int idx2 = 2;
  int counter = 0;
  while( idx2 < idx )
  {
	page[idx2-2] = malloc( sizeof(int) );
	*page[idx2-2] = command[idx2]-'0';
	idx2++;
	counter++;
  }
  idx2 = 1;
  int pagenum = 0;	
  for( int i = counter-1; i >=0; i-- )
  {
	//printf( "page num: %d\n", *page[i] );
	pagenum += idx2 * (*page[i]);
	idx2*= 10;
  }	
  // free page
  for( int j = 0; j < counter; j ++ )
  {
	free(page[j]);
  }
  free(page);
  
  //check weather this page number is inside the document
  if( pagenum < 1 || pagenum >= (int)Document_size(document) )
  {  
  	invalid_line();
	return;
  }
  
  Document_delete_line( document, pagenum -1 );

}

void handle_search_command(Document *document, const char *command) {
  // TODO implement handle_search_command
  
  const char* word = command + 1 ;
  size_t size =  Document_size( document );
  for( size_t i = 0; i < size; i ++ )
  {
  	char* temp = strstr( Document_get_line( document, i), word );
  	if(  temp != NULL )
  	{	  
		print_search_line( (int)(i+1), Document_get_line( document, i), temp, word );
  	}
  }
  
}

void handle_save_command(Document *document, const char *filename) {
  // TODO implement handle_save_command
  FILE* fd = fopen( filename, "w+");
  size_t size =  Document_size( document );
  for( size_t i = 0; i < size; i ++ )
  {
  	const char* temp = Document_get_line( document, i);
  	fprintf( fd, "%s\n", temp );
  }
  fclose( fd );
  
  
}
