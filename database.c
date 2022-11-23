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
	FILE * output = fopen( database->file, "w" );
	int length = list_size( database->students );
	for( int i = 0; i < length; i++ ){
		Student s = (Student) list_get( database->students, i );
		char* name = student_getName( s );
		char* email = student_getEmail( s );
		int age = student_getAge( s );
		double gpa = student_getGPA( s );
		fprintf( output, "%s,%s,%d,%.2f\n", name, email, age, gpa );
	}
	fclose( output );
}

/// Checks if a certain email is contained within the database
/// 
/// @param database - the database to be saved
/// @param email The email to match against
/// @return true if the email exists in the database, false otherwise
static bool contains( Database database, char* email ){
	int length = list_size( database->students );
	for( int i = 0; i < length; i++ ){
		Student s = (Student) list_get( database->students, i );
		if( strcmp( email, student_getEmail( s ) ) == 0 ){
			return true;
		}
	}
	return false;
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
	save( database );
	while( list_size( database->students ) != 0 ){
		Student student = (Student) list_get( database->students, 0 );
		list_delete( database->students, 0 );
		student_destroy( student );
	}
	list_destroy( database->students );
	free( database );
}

ListADT database_get( Database database ){
	ListADT list = list_create( student_equals, student_toString );
	int length = list_size( database->students );
	for( int i = 0; i < length; i++ ){
		list_append( list, list_get( database->students, i ) );
	}
	return list;
}

Student database_getByEmail( Database database, char* email ){
	int length = list_size( database->students );
	for( int i = 0; i < length; i++ ){
		Student s = (Student) list_get( database->students, i );
		if( strcmp( student_getEmail( s ), email ) == 0 ){
			return s;
		}
	}
	return NULL;
}

ListADT database_getByName( Database database, char* name ){
	ListADT list = list_create( student_equals, student_toString );
	int length = list_size( database->students );
	for( int i = 0; i < length; i++ ){
		Student s = (Student) list_get( database->students, i );
		if( strcmp( student_getName( s ), name ) == 0 ){
			list_append( list, (void *) s );
		}
	}
	return list;
}

ListADT database_getByAge( Database database, int age ){
	ListADT list = list_create( student_equals, student_toString );
	int length = list_size( database->students );
	for( int i = 0; i < length; i++ ){
		Student s = (Student) list_get( database->students, i );
		if( student_getAge( s ) == age ){
			list_append( list, (void *) s );
		}
	}
	return list;
}

ListADT database_getByGPA( Database database, double low, double high ){
	ListADT list = list_create( student_equals, student_toString );
	int length = list_size( database->students );
	for( int i = 0; i < length; i++ ){
		Student s = (Student) list_get( database->students, i );
		double gpa = student_getGPA( s );
		if( !(gpa < low) && !(gpa > high) ){
			list_append( list, (void *) s );
		}
	}
	return list;
}

bool database_add( Database database, Student student ){
	//TODO
	char* email = student_getEmail( student );
	if( contains( database, email ) ){
		return false;
	}
	list_append( database->students, student );	
	return true;
}

bool database_update( Database database, Student student ){
	//TODO
	return false;
}

bool database_delete( Database database, char* email ){
	//TODO
	return false;
}

