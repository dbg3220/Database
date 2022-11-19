// Testing module for this project
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "student.h"
#include "ListADT.h"

int main(){
    Student student = student_create( "Damon", "dbg3220@rit.edu", 19, 3.74 );
    char* str = student_toString( student );
    printf( "%s\n", str );
    free( str );

    ListADT list = list_create( student_equals, student_toString );
    list_append( list, (void *) student );

    Student duplicate = student_create( "Damon", "dbg3220@rit.edu", 19, 3.74 );
    bool result = list_contains( list, (void *) duplicate );
    printf( "Testing student equals function\n");
    if( result ){
        printf( "TEST PASSED\n");
    } else {
        printf( "TEST FAILED\n");
        return EXIT_FAILURE;
    }
}