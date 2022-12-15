// Testing module for this project
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "ListADT.h"
#include "database.h"

#define PASS    "TEST PASSED\n"
#define FAIL    "TEST FAILED\n"

static int testStudent(){
    Student student, duplicate, duplicate2;
    char* firstname = "Damon";
    char* lastname = "Gonzalez";
    char* email = "dbg3220@rit.edu";
    int age = 19;
    double gpa = 3.74;
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

static int testDatabase(){
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
    return 1;
}

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
