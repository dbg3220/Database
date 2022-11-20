// Main module of this program, will interpret user input to modify the student database

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "database.h"
#include "ListADT.h"

#define USAGE "Usage: ./main <database_file>\n"

/// @brief main function of this program
/// @return EXIT_SUCCESS upon successful completion of this program,
/// EXIT_FAILURE otherwise
int main( int argv, char* argc[] ){
    if( argv != 2 || strcmp( argc[1], "-h" ) == 0 ){
        printf( USAGE );
        return EXIT_FAILURE;
    } 

	printf( "Loading data from: %s\n", argc[1] );
    Database database = database_create( argc[1] );
    printf( "\r                                  ");

    char input[50];
    while( true ){
        scanf( " ->%s", input );

        if( strcmp( input, "quit" ) == 0 ){
            break;
        }
    }

    return EXIT_SUCCESS;
}
