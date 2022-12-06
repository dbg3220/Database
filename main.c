// Main module of this program, will interpret user input to modify the student database

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "database.h"

#define USAGE               "Usage: ./main <database_file>"
#define ERROR_NOT_FOUND     "Command Not Found, type 'help' to see a list of relevant commands"
#define ERROR_USE_GET       "You must use get to bring up a list of students to modify"
#define COMMANDS            "'quit': Ends the program and saves all changes\n"\
                            "'fquit': Ends the program without saving changes\n"\
                            "'get': Retrieves students from the database. You can get all or search by name, email, age, or gpa\n"\
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
    for( int i = 0; i < length - 1 && (ch = getc(stdin)) != EOF; i++ ){
        if( ch == '\n' ){
            buffer[i] = '\0';
            break;
        }
        buffer[i] = ch;
    }
    buffer[length - 1] = '\0';
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

    int buffer_size = 50;
    char buffer[buffer_size];
    ListADT list = NULL;
    int num = 0;
    while( true ){
        printf( PROMPT );
        input( buffer_size, buffer );
        char* command = strtok( buffer, " " );
        if( command == NULL ){
            command = "";
        }

        if( strcmp( command, "quit" ) == 0 ){//quit command ends the program
            printf( "Saving database to file\n" );
            database_exit( database );
            break;
        } else if( strcmp( command, "fquit" ) == 0 ){//fquit ends program without saving
            printf( "Closing database without saving changes\n" );
            database_force_exit( database );
            break;
        } else if( strcmp( command, "get" ) == 0 ){//get command gives user students to view
            if( list != NULL ){
                list_destroy( list );
                list = NULL;
            }
            num = 0;
            command = strtok( NULL, " " );
            if( command == NULL ){
                printf( "get requires at least 1 additional argument\n" );
            } else if( strcmp( command, "all" ) == 0 ){
                list = database_get( database );
                display( list, num );
                printf( "...(%d total students found)\n", list_size( list ) );
            } else if( strcmp( command, "age" ) == 0 ) {
                command = strtok( NULL, " " );
                if( command == NULL ){
                    printf( "get age requires an age parameter, i.e. 'get age 19'\n" );
                } else {
                    int age = strtol( command, NULL, 10 );
                    list = database_getByAge( database, age );
                    display( list, num );
                    printf( "...(%d total students found)\n", list_size( list ) );
                }
            } else if( strcmp( command, "gpa" ) == 0 ){
                double lower, upper;
                char* args[2];
                args[0] = strtok( NULL, " " );
                args[1] = strtok( NULL, " " );
                if( args[0] == NULL || args[1] == NULL ){
                    printf( "get gpa requires two parameters, a lower bound and upper bound\n" );
                } else {
                    lower = strtod( args[0], NULL );
                    upper = strtod( args[1], NULL );
                    list = database_getByGPA( database, lower, upper );
                    display( list, num );
                    printf( "...(%d total students found)\n", list_size( list ) );
                }
            } else if( strcmp( command, "firstname" ) == 0 ){
                command = strtok( NULL, " " );
                if( command == NULL ){
                    printf( "get firstname requires a parameters, i.e. 'get firstname Damon'\n" );
                } else {
                    list = database_getByFirstName( database, command );
                    display( list, num );
                    printf( "...(%d total students found)\n", list_size( list ) );
                }
            } else if( strcmp( command, "lastname" ) == 0 ){
                command = strtok( NULL, " " );
                if( command == NULL ){
                    printf( "get lastname requires a parameter, i.e. 'get lastname Gonzalez'\n" );
                } else {
                    list = database_getByLastName( database, command );
                    display( list, num );
                    printf( "...(%d total students found)\n", list_size( list ) );
                }
            } else{
                printf( "'%s' not recognized, you can use all, lastname, age, gpa\n", command );
            }
        } else if( strcmp( command, "next" ) == 0 ){//next command shows more students
            if( list != NULL ){
                num += 10;
                if( num >= list_size( list ) ){
                    num = 0;
                }
                display( list, num );
                if( num + 9 < list_size( list ) - 1 ){
                    printf( "...(%d total students)\n", list_size( list ) - 1 );
                }
            } else {
                printf( "%s\n", ERROR_USE_GET );
            }
        } else if( strcmp( command, "clear" ) == 0 ){//clear command removes the current students from view
            list_destroy( list );
            list = NULL;
            num = 0;
        } else if( strcmp( command, "add" ) == 0 ){//add command lets user add a student
            char firstname[buffer_size];
            char lastname[buffer_size];
            char email[buffer_size];
            int age;
            double gpa;
            printf( "%s firstname-> ", PROMPT );
            input( buffer_size, firstname );
            printf( "%s lastname-> ", PROMPT );
            input( buffer_size, lastname );
            printf( "%s email-> ", PROMPT );
            input( buffer_size, email );
            printf( "%s age-> ", PROMPT );
            input( buffer_size, buffer );
            age = (int) strtol( buffer, NULL, 10 );
            printf( "%s gpa-> ", PROMPT );
            input( buffer_size, buffer );
            gpa = strtod( buffer, NULL );
            Student student = student_create( firstname, lastname, email, age, gpa );
            char* str = student_toString( student );
            if( database_add( database, student ) ){
                printf( "%s was successfully added\n", str );
            } else {
                printf( "This student's email already exists in the database, enter a unique email.\n" );
                free( student );
            }   
        } else if( strcmp( command, "update" ) == 0 ){//update command lets user update a student
            if( list != NULL ){
            } else {
                printf( "%s\n", ERROR_USE_GET );
            }
        } else if( strcmp( command, "delete" ) == 0 ){//delete command lets user delete a student
            if( list != NULL ){
                command = strtok( NULL, " " );
                if( command == NULL ){
                    printf( "delete requires 1 more parameter, i.e. delete 0\n" );
                } else {
                    int student_num = (int) strtol( command, NULL, 10 );
                    if( student_num >= 0 && student_num < list_size( list ) ){
                        Student s = (Student) list_get( list, student_num );
                        char* email = student_getEmail( s );
                        database_delete( database, email );
                    } else {
                        printf( "%d is not a valid index\n", student_num );
                    }
                }

            } else {
                printf( "%s\n", ERROR_USE_GET );
            }
        } else if ( strcmp( command, "help" ) == 0 ){//help command shows user useful commands
            printf( "%s\n", COMMANDS );
        } else {//default, if no command recognized shows user an error
            printf( "%s\n", ERROR_NOT_FOUND );
        }
    }

    return EXIT_SUCCESS;
}

