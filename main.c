// Main module of this program, will interpret user input to modify the student database

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "database.h"
#include "ListADT.h"

#define USAGE       "Usage: ./main <database_file>"
#define ERROR       "Command Not Found, type 'help' to see a list of relevant commands"
#define COMMANDS    "->'quit': Ends the program and saves all changes\n"\
                    "->'get': Retrieves students from the database. You can get"\
                    "all or search by name, email, age, or gpa\n"\
                    "->'help: Shows a list of helpful commands"\

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

    char input[100];
    while( true ){
        printf( "Enter Command: ");
        scanf( "%s", input );

        if( strcmp( input, "quit" ) == 0 ){
            break;
        } else if( strcmp( input, "get") == 0 ){
            printf( "You chose to get all students(TO BE IMPLEMENTED)\n");
        } else if ( strcmp( input, "help" ) == 0 ){
            printf( "%s\n", COMMANDS );
        } else {
            printf( "%s\n", ERROR );
        }
    }

    printf( "Saving database to file\n");
    database_exit( database );

    return EXIT_SUCCESS;
}
