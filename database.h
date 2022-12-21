//
// Header module to be read by client to read/write from/to a database
//
// Note: Get methods in this file (aside from getByEmail) return a ListADT
// which the client must remember to destroy using list_destroy
//
// @author Damon Gonzalez
//

#include <stdbool.h>

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
/// @param file - A C string representing the input file
/// @return A new Database, NULL if unsuccessful
Database database_create( char* file );

/// Closes the database by removing all resources and saves the changes to the
/// original file specified by the client.
///
/// @param database - the database to be closed
void database_exit( Database database );

/// Closes the database by removing all resources but does not save changes.
///
/// @param database - the database to be closed
void database_force_exit( Database database );

/// Retrieves the entire database as a ListADT of student objects.
///
/// @param database - the database to be analyzed
/// @return A list of students in the entire database, may be empty
ListADT database_get( Database database );

/// Retrieves the student in the database that matches this email.
/// 
/// @param database - the database to be analyzed
/// @return The matching student if it exists, otherwise NULL
Student database_getByEmail( Database database, char* email );

/// Retrieves a list of all students who match the given firstname
///
/// @param database - the database to be analyzed
/// @param name - the name to search against
/// @return A list of matching students, may be empty
ListADT database_getByFirstName( Database database, char* firstName );

/// Retrieves a list of all students who match the given lastname
///
/// @param database - the database to be analyzed
/// @param name - the name to search against
/// @return A list of matching students, may be empty
ListADT database_getByLastName( Database database, char* lastName );

/// Retrieves a list of all students at the given age
///
/// @param database - the database to be analyzed
/// @param age - the age to be matched by
/// @return A list of all students with the matching age, may be empty
ListADT database_getByAge( Database database, int age );

/// Retrieves a list of all students within the specified gpa range
/// 
/// @param database - the database to be analyzed
/// @param low - the low of the gpa interval
/// @param high - the high end of the gpa interval
/// @return A ListADT of student objects
ListADT database_getByGPA( Database database, double low, double high );

/// Adds a student to the database
///
/// @param database - the database to be analyzed 
/// @param student - the student to be added to the database
/// @return true if the student was successfully added to the database, false
/// if a duplicate email was found
bool database_add( Database database, Student student );

/// Updates a student in the database using the email as a unique identifier
///
/// @param database - the database to be analyzed
/// @param student - the student to be updated
/// @return true if the student was successfully found and updated,
/// false otherwise
bool database_update( Database database, Student student );

/// Deletes a student in the database using the email as an identifier
///
/// @param database - the database to be analyzed
/// @param student - the email of the student to be deleted
/// @return true if the student was successfully deleted,
/// false if could not be found
bool database_delete( Database database, char* email );

