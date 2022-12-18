//
// Testing module for functions implemented in student.h and datbase.h
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "ListADT.h"
#include "database.h"

#define PASS    "TEST PASSED\n"
#define FAIL    "TEST FAILED\n"

/// Runs tests for student.h
static int testStudent(){
    Student student, duplicate, duplicate2;
    char* firstname = "Damon";
    char* lastname = "Gonzalez";
    char* email = "dbg3220@rit.edu";
    int age = 19;
    double gpa = 3.74;

    //student getters
    printf( "Testing student getters\n" );
    student = student_create( firstname, lastname, email, age, gpa );
    char* value = student_getFirstName( student );
    if( strcmp( value, firstname ) == 0 ){
        printf( PASS );
    } else {
        printf( FAIL );
        return 0;
    }
    value = student_getLastName( student );
    if( strcmp( value, lastname ) == 0 ){
        printf( PASS );
    } else {
        printf( FAIL );
        return 0;
    }
    value = student_getEmail( student );
    if( strcmp( value, email ) == 0 ){
        printf( PASS );
    } else {
        printf( FAIL );
        return 0;
    }
    int gotAge = student_getAge( student );
    if( gotAge == age ){
        printf( PASS );
    } else {
        printf( FAIL );
        return 0;
    }
    double gotGpa = student_getGPA( student );
    if( gotGpa == gpa ){
        printf( PASS );
    } else {
        printf( FAIL );
        return 0;
    }

    //student_equals
    printf( "Testing student_equals()\n");
    student = student_create( firstname, lastname, email, age, gpa );
    duplicate = student_create( firstname, lastname, email, age, gpa );
    bool result = student_equals( (void*) student, (void*) duplicate );
    if( result ){
        printf( PASS );
    } else {
        printf( FAIL );
        return 0;
    }
    duplicate2 = student_create( firstname, lastname, email, age, 0 );
    result = student_equals( (void*) student, (void*) duplicate2 );
    if( !result ){
        printf( PASS );
    } else {
        printf( FAIL );
        return 0;
    }

    //student_create
    printf( "Testing student_create()\n" );
    student = student_create( firstname, lastname, email, -20, 3.5 );
    if( !student ){
        printf( PASS );
    } else {
        printf( FAIL );
        return 0;
    }
    student = student_create( firstname, lastname, email, age, 5 );
    if( !student ){
        printf( PASS );
    } else {
        printf( FAIL );
        return 0;
    }
    student = student_create( firstname, "damondamondamondamondamondamondamondamondamondamondamondamondamondamondamondamondamon", email, age, gpa );
     if( !student ){
        printf( PASS );
    } else {
        printf( FAIL );
        return 0;
    }
    return 1;
}

/// Runs tests for database.h
static int testDatabase(){
    //database_create
    char* nofile = "file.csv";
    printf( "Testing database_create with non-existent file <%s>\n", nofile );
    Database test = database_create( nofile );
    if( !test ){
        printf( PASS );
    } else {
        printf( FAIL );
    }
	char* file = "data.csv";
	printf( "Testing database_create with file <%s>\n", file );
	Database database = database_create( file );
	if( database ){
		printf( PASS );
	} else {
		printf( FAIL );
		return 0;
	}

    //database_add
    printf( "Testing database_add\n" );
    char* firstname = "Joe";
    char* lastname = "Durso";
    char* email = "jd@hbd.com";
    int age = 50;
    double gpa = 4.0;
    Student student = student_create( firstname, lastname, email, age, gpa );
    database_add( database, student );
    Student result = database_getByEmail( database, email );
    if( student_equals( student, result ) ){
        printf( PASS );
    } else {
        printf( FAIL );
        return 0;
    }

    //database_update
    printf( "Testing database_update\n" );
    Student new_student = student_create( firstname, lastname, email, age, 2.3 );
    if( database_update( database, new_student ) ){
        printf( PASS );
    } else {
        printf( FAIL );
        return 0;
    }
    new_student = student_create( firstname, lastname, "random", age, 2.3 );
    if( !database_update( database, new_student ) ){
        printf( PASS );
    } else {
        printf( FAIL );
        return 0;
    }

    //database_delete
    printf( "Testing database_delete\n" );
    if( database_delete( database, email ) ){
        printf( PASS );
    } else {
        printf( FAIL );
        return 0;
    }
    if( !database_delete( database, "random" ) ){
        printf( PASS );
    } else {
        printf( FAIL );
        return 0;
    }

    //database_getByFirstName
    printf( "Testing database_getByFirstName\n" );
    ListADT list = database_getByFirstName( database, "random" );
    if( list_size( list ) == 0 ){
        printf( PASS );
    } else {
        printf( FAIL );
        return 0;
    }

    //database_getByLastName
    printf( "Testing database_getByLastName\n" );
    list = database_getByLastName( database, "random" );
    if( list_size( list ) == 0 ){
        printf( PASS );
    } else {
        printf( FAIL );
        return 0;
    }

    //database_getByAge
    printf( "Testing database_getByAge\n" );
    list = database_getByAge( database, -1 );
    if( list_size( list ) == 0 ){
        printf( PASS );
    } else {
        printf( FAIL );
        return 0;
    }

    //database_getByGPA
    printf( "Testing database_getByGPA\n" );
    list = database_getByGPA( database, 0, 0 );
    if( list_size( list ) == 0 ){
        printf( PASS );
    } else {
        printf( FAIL );
        return 0;
    }

    return 1;
}

/// main testing functions that runs tests for eahc relevant module
int main(){
	if( testStudent() ){
        printf( "!!!All student tests pass!!!\n\n" );
    } else {
        printf( "!!!Some student tests failed!!!\n\n" );
    }
	if( testDatabase() ){
        printf( "!!!All database tests pass!!!\n\n" );
    } else {
        printf( "!!!Some database tests failed!!!\n\n" );
    }
    return EXIT_SUCCESS;
}
