//
// File: database.c
// Description: Module to implement function headers described in database.h
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ListADT.h"
#include "student.h"

typedef struct Database_H {
    ListADT students;
    char* file;
} * Database;

#define _DATABASE_
#include "database.h"

Database database_create( char* file ){
    Database database = (Database)malloc( sizeof( struct Database_H ) );
    database->file = (char*)malloc( strlen( file ) * sizeof( char ) );
    database->students = list_create( NULL, NULL );//implement equals and tostring methods in student
    //TODO write code to read the file into students(ListADT)
    return database;
}