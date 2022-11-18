//
// File: database.h
// Description: a header file for providing interactions between
// a client
//

#include "ListADT.h"

#ifndef _DATABASE_

typedef struct { } * Database;

#endif

/// Creates a new database given an input file
///
/// @param A C string representing the input file
/// @return A new Database, NULL if unsuccessful
Database database_create( char* file );

/// Saves all changes to the database file, removes
/// all data from memory and closes unused resources
///
/// @param database The database to be closed
void database_exit( Database database );

/// Retrieves the entire database as a ListADT of student
/// objects
///
/// @param database The database to be analyzed
/// @return The whole database
ListADT database_get( Database database );
