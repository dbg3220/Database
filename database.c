//
// File: database.c
// Description: Module to implement function headers described in database.h
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ListADT.h"

typedef struct Database_H {
    ListADT students;
    char* file;
} * Database;

#define _DATABASE_
#define _SOURCE_
#include "database.h"

/// Loads the database from the file specified
///
/// @param database - the database to be loaded
/// @return 1 if the data file was successfully read, 0 if there was a conflict
static int load( Database database ){
	//TODO
	FILE * file = fopen( database->file, "r" );
	if( !file ){
		printf( "Error reading from <%s>\n", database->file );
		return 0;
	}
	char line[200];
	while ( fgets( line, 200, file ) != NULL ){
		if( line[ strlen( line ) - 1 ] == '\n' ){
			line[ strlen( line ) - 1 ] = '\0';//trims the final character if it is a newline character
		}
		char* name = strtok( line, "," );
		char* email = strtok( NULL, "," );
		int age = atoi( strtok( NULL, "," ) );
		double gpa = strtod( strtok( NULL, "," ), NULL );
		printf( "name: %s, email: %s, age: %d, gpa: %.2f\n", name, email, age, gpa );
		Student student = student_create( name, email, age, gpa );
		list_append( database->students, (void *) student );
	}
	fclose( file );
	return 1;
}

/// Saves the database to the file originally specified
///
/// @param database - the database to be saved
static void save( Database database ){
	//TODO
}

Database database_create( char* file ){
    Database database = (Database)malloc( sizeof( struct Database_H ) );
    database->file = file;
    database->students = list_create( student_equals, student_toString );
	int result = load( database );
	if( !result ){
		list_destroy( database->students );
		free( database );
		return NULL;
	}
    return database;
}

void database_exit( Database database ){
	//TODO
	save( database );
	while( list_size( database->students ) != 0 ){
		Student student = (Student) list_get( database->students, 0 );
		student_destroy( student );
	}
	list_destroy( database->students );
	free( database );
}

