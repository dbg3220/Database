// Main module of this program, will interpret user input to modify the student database

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "student.h"
#include "database.h"
#include "ListADT.h"

#define USAGE "Usage: ./main <database_file>\n"

/// @brief main function of this program
/// @return EXIT_SUCCESS upon successful completion of this program,
/// EXIT_FAILURE otherwise
int main( int argv, char* argc[] ){
    if( argv != 2 || strcmp( argc[1], "-h" ) == 0 ){
        printf(USAGE);
        return EXIT_FAILURE;
    } 

	printf( "Loading data from: %s\n", argc[1] );
    //load database with filename(argc[1])

	//continuous while loop for command input by user
    while( true ){
        //TODO implement this while loop as the UI of this program

        break;//break when user inputs an exiting command
    }

    //ONLY RETURN ON SUCCESSFUL COMPLETION OF THIS PROGRAM
    return EXIT_SUCCESS;
}
