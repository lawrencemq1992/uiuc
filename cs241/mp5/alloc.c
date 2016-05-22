/**
 * Machine Problem 4
 * CS 241 - Spring 2016
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

typedef struct Node_
{
	size_t size;
	struct Node_* prev;
	struct Node_* next;		
} Node;


//link list for the free node
Node* head = NULL;
Node* tail = NULL;
size_t largest_free_size = 0;

// implement calloc!
void *calloc(size_t num, size_t size) {
  size_t total_size = num*size;
  void* address = malloc( total_size );
  if( !address )	  
  	return NULL;
  memset( address, total_size, 0 );
  return address;
}


//the largest size in free nodes
size_t findlarge( Node* head2 )
{
	size_t large = 0;
	Node* temp = head2;
	while( temp != NULL )
	{
		if( temp->size > large  )
			large = temp->size;
		temp = temp->next;
	}
	return large;
}


size_t sizeofnode (Node* head2 )
{
	size_t size = 0;
	Node* head3 = head2;
	while( head3 )
	{ 
		//printf( "node size is %d;", head3->size );
		head3 = head3->next;
		
		size++;
	}
	//printf( "\n" );
	return size;
}

//malloc
void *malloc(size_t size) 
{

  //malloc 0
  if( !size )
  	return NULL;
  
  //align the size	
  size = (size/16 + 1 ) *16;
  	
  //no free space, or no free block has such large size
  if( head == NULL || largest_free_size < size )
  {		 	
  	Node* node = sbrk( sizeof( Node ) + size );
  	//fail to malloc
  	if( node == (void *)-1 )
  		return NULL;
  	//set the node
  	node->size = (int)size;
  	node->prev = NULL;
  	node->next = NULL;
  	return (void*)node + sizeof( Node );
  }
  
  //not first malloc
  else
  {	 	 	
  	//find the first-fit block
  	Node* temphead = head;
  	while( temphead != NULL )
  	{	
  		if( temphead -> size >= size )
  			break; 
  		temphead = temphead -> next;
  	}
  	
  	
  	
  	if( temphead == NULL )
  	{		 	
  		sizeofnode(head);
  		
  		Node* node = sbrk( sizeof( Node ) + size );
  		//fail to malloc
  		if( node == (void *)-1 )
  			return NULL;
  		//set the node
  		node->size = (int)size;
  		node->prev = NULL;
  		node->next = NULL;
  		return (void*)node + sizeof( Node );
  	}
  	
  	size_t oldsize = temphead->size;
  	//has more space for a node
  	if( oldsize - size > sizeof( Node ) )
  	{
  		temphead -> size = (int)size;
  		int newsize = oldsize -size -sizeof( Node );
  		
  		//new node for cut from the old free node	
  		Node* newnode = (void*)temphead + sizeof(Node) + sizeof(char)*size;
  		newnode->size = newsize;
  		
  		//temphead is the only node
  		if( temphead == head && temphead == tail )
  		{
  			newnode->prev = NULL;
  			newnode->next = NULL;
			head = newnode;  			
			tail = newnode;
  		}
  		
  		//temphead is the head, but not tail
  		else if( temphead == head )
  		{	
  			newnode -> prev = NULL;
  			newnode -> next = temphead -> next;
  			temphead->next->prev = newnode;
  			head = newnode;
  		}
  		
  		//temphead is tail, not head
  		else if ( temphead == tail )
  		{
  			newnode -> next = NULL;
  			newnode -> prev = temphead -> prev;
  			newnode -> prev -> next = newnode;
  			tail = newnode;
  		}
  		
  		//if in the middle
  		else
  		{
  			newnode->next = temphead-> next;
  			newnode->prev = temphead-> prev;
  			newnode->next->prev = newnode;
  			newnode->prev->next = newnode;
  		}
  		
  		temphead -> prev = NULL;
  		temphead -> next = NULL;
  		
  			
  	}
  	//use the entire free node
  	else 
  	{
  		//if its the only node
  		if( temphead == head && temphead == tail)
  		{
  			head = NULL;
  			tail = NULL;
  		}
  		//its head, not tail
  		else if ( temphead == head )
  		{
  			head = temphead ->next;
  			head -> prev = NULL;
  		}
  		//its tail, not head
  		else if( temphead == tail )
  		{	
  			tail = temphead ->prev;
  			tail -> next = NULL;
  		}
  		else
  		{
  			Node* prev = temphead -> prev;
  			Node* next = temphead -> next;
  			prev -> next = next;
  			next -> prev = prev;
		}
		
		temphead -> prev = NULL;
  		temphead -> next = NULL;	  		
  	}
  	
  	
  	if( oldsize == largest_free_size )
  		largest_free_size = findlarge( head );
  	
  	
  	return (void*)temphead + sizeof(Node); 	
  }
  
  return NULL;	 	
}

//free, the link_list was ordered by the memory location 
void free(void *ptr) 
{
  
  Node* current_node = (void*)ptr - sizeof( Node );
  
  //has no freed node in the link_list
  if( head == NULL)
  {
  	head = current_node;
  	tail = current_node;
  	current_node -> prev = NULL;
  	current_node -> next = NULL;
  	if( current_node->size > largest_free_size )
  		largest_free_size = current_node->size;
  	return;
  }
  
  
  //put the node in the link list
  Node* temphead = head;
  //the free node link list is ordered in the descresing order
  while( temphead != NULL && (void*)temphead < (void*)current_node )
  {
  	temphead = temphead -> next;
  }
  //temphead is the first node has higher address than current_node
  
  //the current_node has lower address than all the nodes
  if( temphead == head )
  {
  	current_node -> prev = NULL;
  	current_node -> next = head;
  	head -> prev = current_node;
  	head = current_node;
  }
    
  //all node has higher address
  else if( temphead == NULL ) 
  {
  	tail -> next = current_node;
  	current_node->prev = tail;
  	current_node->next = NULL;
  	tail = current_node;
  }
  
  //in the middle
  else 
  {
  	Node* prev = temphead -> prev;
  	prev -> next = current_node;
  	current_node -> prev = prev;
	current_node -> next = temphead;
	temphead -> prev = current_node; 
  
  }
  
  //check prev and after
  int pre_node_size = 0;
  int post_node_size = 0;
  int current_node_size = current_node -> size;
  Node* pre_node = NULL;
  Node* post_node = NULL;
  
  //pre node has smaller address
  if( current_node != head )
  { 
  	pre_node = current_node -> prev;
  	if( (void*)pre_node + sizeof(Node) + pre_node->size == (void*) current_node )
  		pre_node_size = pre_node -> size;
  }
  
  //post node has bigger address
  if( current_node !=  tail )
  {
  	post_node = current_node -> next;
  	if( (void*)current_node + sizeof(Node) + current_node->size == (void*) post_node )
  		post_node_size = post_node -> size;
  }   
  
  //both pre and post are free
  size_t size = 0;
  if( pre_node_size > 0 && post_node_size > 0)
  {
  	size = pre_node_size + post_node_size  + current_node_size + 2*sizeof( Node );
  	pre_node->size = size;
  	pre_node -> next = post_node -> next;
  	if( post_node->next != NULL )
  		post_node ->next -> prev = pre_node;
  	if( post_node == tail )
  		tail = pre_node;

   }
  // only pre
  else if(  pre_node_size >0 )
  {
  	size = pre_node_size + current_node_size + sizeof( Node );
  	pre_node -> size = size;
  	pre_node -> next = post_node;
  	if( post_node != NULL)
  		post_node ->prev = pre_node; 
  	if( tail == current_node  )
  		tail = pre_node;
  		 	
  }
  //only post
  else if( post_node_size > 0 )
  {
  	size = post_node_size + current_node_size + sizeof( Node );
  	current_node -> size =  size;
  	current_node -> next = post_node ->next;
  	if( post_node -> next != NULL )
  		post_node ->next ->prev = current_node; 
  	if( post_node == tail )
  		tail = current_node;
  		
  	post_node ->prev = NULL;
  	post_node -> next = NULL;	
  			
  }
  
  //only current
  else
  {
  	size = current_node ->size;
  }
  
  if( size > largest_free_size )
  		largest_free_size = size;
  
}



void *realloc(void *ptr, size_t size) 
{
  // implement realloc!
  if( !ptr )
  	return malloc(size);
  else if( !size )
  {
  	free(ptr);
  	return NULL;
  }
  else
  {
  	Node* temp = ( void* )ptr - sizeof( Node );
  	size_t oldsize = temp->size;
  	void* address = malloc( size );
  	if( address != NULL )
  		memcpy( address, ptr, size < oldsize? size:oldsize );
  	free( ptr );
  	return address;
  
  }
  
}
