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

char* student_getName( Student student ){
	return &(student->name[0]);
}

char* student_getEmail( Student student ){
	return &(student->email[0]);
}

int student_getAge( Student student ){
	return (int) student->age;
}

double student_getGPA( Student student ){
	return student->gpa;
}

bool student_setName( Student student, char* name ){
	if( strlen( name ) > MAX_NAME_LENGTH ){
		return false;
	}
	strcpy( student->name, name );
	return true;
}

bool student_setEmail( Student student, char* email ){
	if( strlen( email ) > MAX_EMAIL_LENGTH ){
		return false;
	}
	strcpy( student->email, email );
	return true;
}

bool student_setAge( Student student, int age ){
	if( age < MIN_AGE ){
		return false;
	}
	student->age = age;
	return true;
}

bool student_setGPA( Student student, double gpa ){
	if( gpa < MIN_GPA || gpa > MAX_GPA ){
		return false;
	}
	student->gpa = gpa;
	return true;
}

