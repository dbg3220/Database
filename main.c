// Main module of this program, will interpret user input to modify the student database

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "database.h"

#define USAGE               "Usage: ./main <database_file>"
#define MAX_ARGS            4
#define BUFFER_SIZE         50
#define ERROR_NOT_FOUND     "Command Not Found, type 'help' to see a list of relevant commands"
#define ERROR_USE_GET       "You must use get to bring up a list of students to modify"
#define COMMANDS            "'quit': Ends the program and saves all changes\n"\
                            "'fquit': Ends the program without saving changes\n"\
                            "'get': Retrieves students from the database. You can get all or search by firstname, lastname, age, or gpa\n"\
                            "'next': Displays the next 10 students\n"\
                            "'clear': Clears the current students from usage\n"\
                            "'add': Adds a new student to the database\n"\
                            "'update': Updates a selected student\n"\
                            "'delete': Deletes a selected student\n"\
                            "'help: Shows a list of helpful commands"
#define PROMPT              "-> "

/// Reads user input. Ignores all white space and terminates when a newline
/// is entered. If the number of characters entered by the user exceeds
/// length - 1 than the last character of the string is the character at
/// length - 1.
///
/// @param length - the size of the buffer to the input string
/// @param buffer - the buffer that the string is read into
static void input( int length, char buffer[length] ){
    int ch;
    for( int i = 0; i < length - 1 && (ch = getc( stdin )) != EOF; i++ ){
        if( ch == '\n' ){
            buffer[i] = '\0';
            break;
        }
        buffer[i] = ch;
    }
    buffer[length - 1] = '\0';
}

/// Takes a string and parses all text separated by spaces into an array
/// up to the MAX_ARGSth argument. If the original string has less arguments
/// than MAX_ARGS the value of following strings is not guaranteed.
///
/// @param buffer - the string to read from
/// @param args - the string array to parse into
/// @return The number of arguments processed, an int from 0 to 4
static int parse( char buffer[], char* args[] ){
    int arguments = 0;
    if( strcmp( buffer, "" ) == 0 ){
        return arguments;
    }
    
    args[0] = strtok( buffer, " " );
    arguments++;
    for( int i = 1; i < MAX_ARGS; i++ ){
        args[i] = strtok( NULL, " " );
        if( args[i] == NULL ){
            break;
        }
        arguments++;
    }
    return arguments;
}

/// Displays 10 students in the list starting with the student at index num. If
/// an invalid index is given(i.e. < 0 or > list_size) then the first 10
/// students are displayed. If there are not at least 10 students from index
/// num to the end of the list than only however many students are from num to
/// the end of the list are displayed.
///
/// @param list - the list to be analyzed
/// @param num - the index of the first student to be displayed
static void display( ListADT list, int num ){
    int size = list_size( list );
    if( num < 0 || !(num < size ) ){
        num = 0;
    }
    for( int i = num; i < num + 10 && i < size; i++ ){
        Student s = (Student) list_get( list, i );
        char* str = student_toString( s );
        printf( "%d. %s\n", i, str );
        free( str );
    }
}

/// Handles the get command input by the user with additional arguments. If
/// the command is successful the ListADT that is passed in is destroyed if
/// it is not NULL. If the command is improperly formatted than the ListADT
/// remains unchanged and NULL is returned.
///
/// @param database - the database to get from
/// @param list - the current list brought up by the user, may be NULL
/// @param args - the arguments written by the user
/// @param arguments - the amount of arguments given by the user
/// @return The new list if the command is successful, NULL otherwise
static ListADT get( Database database, ListADT list, char* args[], 
            int arguments ){
    if( arguments < 2 ){
        printf( "get requires at least 1 additional parameter\n" );
        return NULL;
    }

    if( strcmp( args[1], "all" ) == 0 ){
        if( list != NULL ) list_destroy( list );
        return database_get( database );
    } else if( strcmp( args[1], "firstname" ) == 0 ){
        if( arguments >= 3 ){
            if( list != NULL ) list_destroy( list );
            return database_getByFirstName( database, args[2] );
        } else {
            printf( "get firstname requires an additional parameter\n" );
            return NULL;
        }
    } else if( strcmp( args[1], "lastname" ) == 0 ){
        if( arguments >= 3 ){
            if( list != NULL ) list_destroy( list );
            return database_getByLastName( database, args[2] );
        } else {
            printf( "get lastname requires an additional parameter\n" );
            return NULL;
        }
    } else if( strcmp( args[1], "age" ) == 0 ){
        if( arguments >= 3 ){
           int age;
           if( sscanf( args[2], "%d", &age ) != 1 ){
               printf( "%s is not a valid number\n", args[2] );
               return NULL;
           }
           if( list != NULL ) list_destroy( list );
           return database_getByAge( database, age );
        } else {
            printf( "get age requires an additional parameter\n" );
            return NULL;
        }
    } else if( strcmp( args[1], "gpa" ) == 0 ){
        if( arguments >= 4 ){
            double low, high;
            if( sscanf( args[2], "%lf", &low ) != 1 ||
                sscanf( args[3], "%lf", &high ) != 1 ){
                printf( "%s and/or %s are not valid decimal numbers\n", args[2], args[3] );
                return NULL;
            }
            if( list != NULL ) list_destroy( list );
            return database_getByGPA( database, low, high );
        } else {
            printf( "get gpa requires 2 additional parameters\n" );
            return NULL;
        }
    } else {
        printf( "'%s' is not a subcommand of get\n", args[1] );
        return NULL;
    }
}

static ListADT add( Database database, ListADT list ){    
    //TODO
    return NULL;
}

static ListADT update( Database database, ListADT list ){
    //TODO
    return NULL;
}

static ListADT delete( Database database, ListADT list ){
    //TODO
    return NULL;
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
    if( database == NULL ){
        printf( "Error reading from <%s>, could not open database\n", argc[1] );
        return EXIT_FAILURE;
	}

    char buffer[BUFFER_SIZE];
    ListADT list = NULL;
    int num = 0;
    while( true ){
        printf( PROMPT );
        input( BUFFER_SIZE, buffer );
        char* args[MAX_ARGS];
        int arguments = parse( buffer, args );

        if( strcmp( args[0], "quit" ) == 0 ){//'quit'
            printf( "Saving database to file\n" );
            database_exit( database );
            break;
        } else if( strcmp( args[0], "fquit" ) == 0 ){//'fquit'
            printf( "Closing database without saving changes\n" );
            database_force_exit( database );
            break;
        } else if( strcmp( args[0], "get" ) == 0 ){//'get'
            ListADT temp = get( database, list, args, arguments );
            if( temp != NULL ) list = temp;
            num = 0;
            if( temp != NULL ){
                display( list, num );
            }
        } else if( strcmp( args[0], "next" ) == 0 ){//'next'
            if( list != NULL ){
                num += 10;
                if( num >= list_size( list ) ){
                    num = 0;
                }
                display( list, num );
            } else {
                printf( "You must have a list brought up to use 'next'\n" );
            }
        } else if( strcmp( args[0], "clear" ) == 0 ){//'clear'
            if( list != NULL ){
                list_destroy( list );
                list = NULL;
            }
        } else if( strcmp( args[0], "add" ) == 0 ){//'add'
            //TODO
        } else if( strcmp( args[0], "update" ) == 0 ){//'update'
            //TODO
        } else if( strcmp( args[0], "delete" ) == 0 ){//'delete'
            //TODO
        } else if( strcmp( args[0], "help" ) == 0 ){//'help'
            printf( "%s\n", COMMANDS );
        } else {//'default'
            printf( "%s\n", ERROR_NOT_FOUND );
        }
    }

    if( list != NULL ){//if list wasn't cleared before quit/fquit
        list_destroy( list );
    }

    return EXIT_SUCCESS;
}

