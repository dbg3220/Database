// Testing module for this project
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "ListADT.h"
#include "database.h"

static int testStudent(){
    Student student = student_create( "Damon", "Gonzalez", "dbg3220@rit.edu", 19, 3.74 );
    char* str = student_toString( student );
    printf( "%s\n", str );
    free( str );

    ListADT list = list_create( student_equals, student_toString );
    list_append( list, (void *) student );

    Student duplicate = student_create( "Damon", "Gonzalez", "dbg3220@rit.edu", 19, 3.74 );
    bool result = list_contains( list, (void *) duplicate );
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
