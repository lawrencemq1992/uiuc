/**
 * Machine Problem: Shell
 * CS 241 - Spring 2016
 */

#include "format.h"
#include "log.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

Log* cmdLog;// globa Log to store all the commands
int exit_ = 0;
int storefile = 0;
int twofile = 0;
//helper for #n command
int checkn( const char* command2)
{
	char* command = strdup(command2);
	char num[15];
	int out = 0;
	if( strlen( command ) > 1 && command[0] == '#' )
	{
		if( command[1] == '-' )
			print_invalid_index();
		else
		{
			for( int i = 1; (size_t)i <strlen( command ); i++ )
			{
				if( command[i]<=47 || command[i]>=58)
				{	
					print_invalid_index();
					break;
				}
				else	
					num[i-1] = command[i];
			}
			int j = strlen(command) -2;
			int mul = 1;
			while( j>=0 )
			{
				out += (num[j] -'0' )*mul;
				j--;
				mul *=10;
			}
		}
	}
	free(command);
	return out;
}

int getspace ( char* x )
{
	
	//printf( "loop begin\n" );
	//printf( "%s\n", x );
	char* y = strdup(x);
	int sum = 0;
	int counter = 0;
	while(*y != 0)
	{
		if( *y == ' ')
			sum++;
		y++;
		counter ++;
	}
	y = y - counter;
	free(y);
	
	//printf( "loop done\n" );
	return sum+1;

}

//with & return 1; 
int checkback (char* command )
{
	char* command2 = strdup(command);
	int find = 0;
	int length = 0;
	while( *command2 != 0 )
	{
		if( *command2 == '&' )
		{
			find = 1;
			break;
		}
		command2++;
		length++;
	}
	free(command2 - length);
	return find;

}

void execmd ( const char* command2 )
{
	
	char* command = strdup( command2 );
	
	//cd command
	if( strlen( command ) >=2 && command[0] == 'c' && command[1] == 'd' )
	{
		// just cd
		if( strlen( command ) <= 3 || command[2] != ' ')
		{
			print_no_directory( "" );
			free( command );
			return;
		}
		int checkvalue;
		if( command[3] != '/' )
		{
			char* path = get_full_path( command+3 );
			//printf( "%s\n", path );
			checkvalue = chdir( path );
			free(path);
		}
		else
			checkvalue = chdir( command +3 );
		if( checkvalue == -1 )
			print_no_directory( "" );
		else
			Log_add_command( cmdLog, command );//add the command to the log	
	}
	//exit command
	else if( strlen( command ) == 4 && ( strcmp( command, "exit" ) == 0 ) )
	{
		Log_add_command( cmdLog, command);
		exit_ = 1;
	}
	//!history command
	else if( strlen(command) == 8 && ( strcmp( command, "!history" )==0  ) )
	{
		for( size_t i = 0; i < Log_size( cmdLog); i ++ )
		{
			const char* temp = Log_get_command( cmdLog, i);
			printf( "%d	%s\n", (int)i, temp );
		}
	}	 
	//#<n> command
	else if( ( strlen(command) == 2 && command[1] == '0' ) || checkn(command)  > 0 )
	{
		int x = checkn(command);
		if( x >= (int)Log_size( cmdLog ) )
		{
			print_invalid_index();
		}
		else
		{
			const char * command2 = Log_get_command( cmdLog, (size_t)x);
			printf( "%s\n", command2 );
			execmd( command2 );
		}
	} 
	//!prefix command
	else if( strlen(command) >=1 && command[0] == '!' )
	{
		int find = 0;
		for( size_t i = Log_size( cmdLog )-1; (int)i>=0; i--)
		{
			const char* command2 = 	Log_get_command( cmdLog, i);
			if( strncmp( command2, command+1, strlen(command) -1 ) == 0 || strlen(command)==1 )
			{
				printf( "%s\n", command2 );
				execmd( command2 );
				find = 1;
				break;
			}
		}
		if( find == 0 )
			print_no_history_match();
	}
	
	else
	{
		char* tpcommand = strdup( command );
		Log_add_command( cmdLog, tpcommand );
		free( tpcommand );
		int status;
		int num = getspace ( command );
		int back = 0;
		if( checkback(command ) == 1)
		{
			back = 1;
			if( command[ strlen(command)-2 ] == ' ' ) 
				num--;
			else
				command[ strlen(command)-1 ] = 0;
		} 
		char** command_array = strsplit( command, " ", (size_t *)&num);
		//printf( "hehe\n" );
		pid_t child = fork();
		if( child == -1)
		{
			print_fork_failed();
		}
		else if( child > 0 )
		{
			print_command_executed( child );
			if( back == 0 )
			{	
				pid_t check = waitpid( child, &status, 0);
				if( check == -1 )
					print_wait_failed();
			}
			free_args(command_array);
		}
		else
		{
			execvp( command_array[0], command_array );
			print_exec_failed( command );
			exit(2);
		}
	}
	
	free( command );

}



//signal handler
/*
void handle_sigint( int signal )
{
	return;	
} */

int checkinput( int t1, char** t2 )
{
	if( t1 == 1 )
		return 1;
	else if ( t1 == 3 && ( strcmp( t2[1], "-h" ) == 0 || strcmp( t2[1], "-f") == 0 ) )
		return 1;
	else if( t1 == 5 && ( strcmp( t2[1], "-h" ) == 0 || strcmp( t2[1], "-f") == 0 ) && ( strcmp( t2[3], "-h" ) == 0 || strcmp( t2[3], "-f") == 0 ) )
		return 1;
	return 0;

}


int main(int argc, char *argv[]) {
// TODO: This is the entry point for your 
 
 //signal handler
 signal( SIGINT, SIG_IGN );
  
  //error check
  if( checkinput( argc, argv ) == 0 )
  {
  	print_usage();
  	exit(4);
  }
  
  //-f mode = 0; -h mode =1
  int mode = 0;
  if( argc == 3)
  { 
  	if( strcmp( argv[1], "-h" ) == 0 )
  	{
  		mode = 1;
  		storefile = 1;
  	}
  	else
  		mode = 0;
  }
  else if (argc == 1 )
  {
  	mode = 1;
  }
  else if( argc == 5 )
  {
  	mode = 2;
  } 
  // create the cmdLog to store all the commands
  cmdLog = Log_create();  
  
  //print the bash
  print_shell_owner( "lzhan101" );	
  	
  FILE* fd;	
  //-f mode
  if( mode == 0 )
  {
  	fd = fopen( argv[2], "r" );
  	if( fd == NULL )
  	{	
  		Log_destroy( cmdLog);
  		print_script_file_error();
  		exit(1);
  	} 	
  
 	// for read from file in -f mode
  	size_t len;
  	ssize_t read;
  	char* command = NULL;
  	while( (read = getline( &command, &len, fd )) != -1 )
  	{
  		//print bash
  		pid_t pid = getpid();// the pid of current process
  		char* pwd = getcwd( NULL, 200); // the full path to the current working directory
  		print_prompt( pwd, pid);
  		printf( "%s", command );
  		free( pwd );
  		
  		size_t size = strlen( command );
  		command[size -1 ] = 0; 
		char* command_copy = strdup( command);
  		execmd( command_copy );
  		free( command_copy );
  		if( exit_ == 1 )
  		{
  			break;
  		}
  	}
  	//if haven't run the exit, run it
  	if( exit_ == 0 )
  		execmd( "exit" );
	free( command );
  }
    
  // -h mode
  else if ( mode == 1 )
  {	
  	if( argc > 1 )
  		fd = fopen( argv[2], "w" );
  	size_t len;
  	ssize_t read;
  	char* command = NULL;	
  	while(1)
  	{
  		pid_t pid = getpid();// the pid of current process
  		char* pwd = getcwd( NULL, 200); // the full path to the current working directory
  		print_prompt( pwd, pid);
  		free( pwd );
  		
		read = getline( &command, &len, stdin );
		
		size_t size = strlen( command );
  		command[size -1] = 0; 
		
  		// exec the command
  		char* command_copy = strdup( command);
  		execmd( command_copy );
  		free( command_copy );

  		//if run the exit command, then exit the loop
  		if( exit_ == 1 )
  			break;
  	}
  	free( command );
  }
  // mode = 2
  else 
  {
  	FILE* fd2;//for read
	if( strcmp( argv[3], "-f") == 0 ) 
	{	  
  		fd2 = fopen( argv[4], "r" );
  		fd = fopen( argv[2], "w" );
  	}
  	else
  	{
  		fd2 = fopen( argv[2], "r" );
  		fd = fopen( argv[4], "w" );
  	}
  	if( fd2 == NULL )
  	{	
  		Log_destroy( cmdLog);
  		print_script_file_error();
  		exit(1);
  	} 	
  
 	// for read from file in -f mode
  	size_t len;
  	ssize_t read;
  	char* command = NULL;
  	while( (read = getline( &command, &len, fd2 )) != -1 )
  	{
  		//print bash
  		pid_t pid = getpid();// the pid of current process
  		char* pwd = getcwd( NULL, 200); // the full path to the current working directory
  		print_prompt( pwd, pid);
  		printf( "%s", command );
  		free( pwd );
  		
  		size_t size = strlen( command );
  		command[size -1 ] = 0; 
		char* command_copy = strdup( command);
  		execmd( command_copy );
  		free( command_copy );
  		if( exit_ == 1 )
  		{
  			break;
  		}
  	}
  	//if haven't run the exit, run it
  	if( exit_ == 0 )
  		execmd( "exit" );
	free( command );
	fclose( fd2 ); 		
  	storefile = 1;	
  }
  
  wait( NULL );
  		
  // if -h, save the history of shell
  if( storefile == 1 )
  {
  	Log_save( cmdLog, argv[2] );
  }
  if( argc > 1 )
  	fclose( fd );
  
  Log_destroy( cmdLog);
  return 0;	
  
}
