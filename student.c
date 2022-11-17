//
// File: student.c
// Description: Source module for implementing functions described in student.h
//

#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH  50
#define MAX_EMAIL_LENGTH 100
#define MIN_AGE          1
#define MIN_GPA          0
#define MAX_GPA          4

typedef struct Student_H {
	char name[MAX_NAME_LENGTH + 1];
	char email[MAX_EMAIL_LENGTH + 1];
	short age;
	double gpa;
} * Student;

#define _STUDENT_
#include "student.h"

Student student_create( char* name, char* email, int age, double gpa ){
	if( strlen( name ) > MAX_NAME_LENGTH ||
		strlen( email ) > MAX_EMAIL_LENGTH ||
		age < MIN_AGE || gpa < MIN_GPA || gpa > MAX_GPA ){
		return NULL;
	}
	Student student = (Student)malloc( sizeof( struct Student_H ) );
	strcpy( student->name, name );
	strcpy( student->email, email );
	student->age = (short) age;
	student->gpa = gpa;
	return student;
}

void student_destroy( Student student ){
	free( student );
}

