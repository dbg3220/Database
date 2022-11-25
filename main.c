// Main module of this program, will interpret user input to modify the student database

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "database.h"

#define USAGE       "Usage: ./main <database_file>"
#define ERROR       "Command Not Found, type 'help' to see a list of relevant commands"
#define COMMANDS    "->'quit': Ends the program and saves all changes\n"\
                    "->'get': Retrieves students from the database. You can get"\
                    "all or search by name, email, age, or gpa\n"\
                    "->'help: Shows a list of helpful commands"
#define PROMPT		"Enter Command: "

/// Displays a list of students with a parameter indicating what section
/// of the list to display
///
/// @param list The list to be displayed, assumed to have data payloads of type
/// student
/// @param num The num'th 10 students to be displayed
static void display( ListADT list, int num ){
	//TODO
	int length = list_size( list );
	for( int i = 0; i < 11 && i < length; i++ ){
		Student s = (Student) list_get( list, i );
		printf( "%d. %s\n", i, student_toString( s ) );
	}
	if( length > 10 ){
		printf( "...(%d total students found)\n", length );
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
	ListADT list;
    while( true ){
        printf( PROMPT );
        scanf( "%49s", input );

        if( strcmp( input, "quit" ) == 0 ){
            break;
        } else if( strcmp( input, "get" ) == 0 ){
			ListADT list = database_get( database );
			display( list, 0 );
        } else if( strcmp( input, "add" ) == 0 ){

		} else if ( strcmp( input, "help" ) == 0 ){
            printf( "%s\n", COMMANDS );
        } else {
            printf( "%s\n", ERROR );
        }
    }

    printf( "Saving database to file\n" );
    database_exit( database );

    return EXIT_SUCCESS;
}

