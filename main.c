// Main module of this program, will interpret user input to modify the student database

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define USAGE "Usage: ./main <database_file>\n"

/// @brief reads the student entries from the database into memory
/// @param data the input stream representing the database
void load( FILE * data ){}

/// @brief main function of this program
/// @return EXIT_FAILURE if user failed to initiate program with correct commands, EXIT_SUCCESS otherwise
int main( int argv, char* argc[] ){
    if(argv != 2){
        printf(USAGE);
        return EXIT_FAILURE;
    } 

    FILE * database = fopen( argc[1], "rw" );

    load( database );

    fclose( database );

    while( true ){
        //TODO implement this while loop as the UI of this program
        break;
    }

    //ONLY RETURN ON SUCCESSFUL COMPLETION OF THIS PROGRAM
    return EXIT_SUCCESS;
}
