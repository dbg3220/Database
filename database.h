//
// File: database.h
// Description: header module to be read by client to read/write
// from/to a database
//

#include "ListADT.h"
#include "student.h"

#ifndef _DATABASE_

typedef struct { } * Database;

#endif

/// Creates a new database given an input file. This database uses
/// student objects to store values. All parameters for a student can be
/// repeated in the database except for a student's email, that acts as a
/// unique identifier.
///
/// @param A C string representing the input file
/// @return A new Database, NULL if unsuccessful
Database database_create( char* file );

/// Saves all changes to the database file, removes
/// all data from memory and closes unused resources
///
/// @param database - the database to be closed
void database_exit( Database database );

/// Retrieves the entire database as a ListADT of student
/// objects. The ListADT that is returned must NOT be destroyed
/// by the client.
///
/// @param database - the database to be analyzed
/// @return A list of students in the entire database, may be empty
ListADT database_get( Database database );

/// Retrieves the student in the database that matches this email.
/// 
/// @param database - the database to be analyzed
/// @return The matching student if it exists, otherwise NULL
Student database_getByEmail( Database database, char* email );

/// Retrieves a list of all students who match the given name
///
/// @param database - the database to be analyzed
/// @param name the name to search against
/// @return A list of matching students, may be empty
ListADT database_getByName( Database database, char* name );
