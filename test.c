// Testing module for this project
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "ListADT.h"
#include "database.h"

static int testStudent(){
    char* firstname = "Damon";
    char* lastname = "Gonzalez";
    char* email = "dbg3220@rit.edu";
    int age = 19;
    double gpa = 3.74;
    Student student = student_create( firstname, lastname, email, age, gpa );
    Student duplicate = student_create( firstname, lastname, email, age, gpa );
    bool result = student_equals( (void*) student, (void*) duplicate );
    printf( "Testing student equals function\n");
    if( result ){
        printf( "TEST PASSED\n");
		return EXIT_SUCCESS;
    } else {
        printf( "TEST FAILED\n");
        return EXIT_FAILURE;
    }
}

static int testDatabase(){
	char* file = "data.csv";
	printf( "Testing database functionality with file <%s>\n", file );
	Database database = database_create( file );
	if( database ){
		printf( "TEST PASSED\n" );
		return EXIT_SUCCESS;
	} else {
		printf( "TEST FAILED\n" );
		return EXIT_FAILURE;
	}
}

int main(){
	testStudent();
	testDatabase();	
}
