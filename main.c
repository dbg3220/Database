// Main module of this program, will interpret user input to modify the student database

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "database.h"

#define USAGE       		"Usage: ./main <database_file>"
#define ERROR_NOT_FOUND     "Command Not Found, type 'help' to see a list of relevant commands"
#define ERROR_USE_GET		"You must use get to bring up a list of students to update"
#define COMMANDS    		"->'quit': Ends the program and saves all changes\n"\
                    		"->'get': Retrieves students from the database. You can get all or search by name, email, age, or gpa\n"\
                    		"->'help: Shows a list of helpful commands"
#define PROMPT				"Enter Command: "

/// Displays a list of students with a parameter indicating what section
/// of the list to display
///
/// @precondition num < roundup[list_size( list )/10]
/// @param list The list to be displayed, assumed to have data payloads of type
/// student
/// @param num The num'th 10 students to be displayed
static void display( ListADT list, int num ){
	int size = list_size( list );
	if( size == 0 ){
		printf( "0 result found\n" );
		return;
	}
	for( int i = num * 10; i < num * 10 + 10 && i < size; i++ ){
		Student s = (Student) list_get( list, i );
		char* str = student_toString( s );
		printf( "%d. %s\n", i + 1, str );
		free( str );
	}
	if( !(size < (num * 10 + 10)) ){
		printf( "...(%d total results found)\n", size );
	}
}

/// @brief main function of this program
/// @return EXIT_SUCCESS upon successful completion of this program,
/// EXIT_FAILURE otherwise
int main( int argv, char* argc[] ){
    if( argv != 2 || strcmp( argc[1], "-h" ) == 0 ){
        printf( "%s\n", USAGE );
        return EXIT_FAILURE;
    } 

	printf( "Loading data from: %s\n", argc[1] );
    Database database = database_create( argc[1] );

    char input[50];
	ListADT list = NULL;
    while( true ){
        printf( PROMPT );
        scanf( "%49s", input );

        if( strcmp( input, "quit" ) == 0 ){//quit command ends the program
            break;
        } else if( strcmp( input, "get" ) == 0 ){//get command gives user students to view
			list = database_get( database );
			display( list, 0 );
        } else if( strcmp( input, "add" ) == 0 ){//add command lets user add a student
		} else if( strcmp( input, "update" ) == 0 ){//update command lets user update a student
			if( list != NULL ){
			} else {
				printf( ERROR_USE_GET );
			}
		} else if( strcmp( input, "delete" ) == 0 ){//delete command lets user delete a student
			if( list != NULL ){
			} else {
				printf( ERROR_USE_GET );
			}
		} else if ( strcmp( input, "help" ) == 0 ){//help command shows user useful commands
            printf( "%s\n", COMMANDS );
        } else {//default, if no command recognized shows user an error
            printf( "%s\n", ERROR_NOT_FOUND );
        }
    }

    printf( "Saving database to file\n" );
    database_exit( database );

    return EXIT_SUCCESS;
}

