//
// File: student.c
// Description: Source module for implementing functions described in student.h
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_NAME_LENGTH  50
#define MAX_EMAIL_LENGTH 100
#define MIN_AGE          1
#define MIN_GPA          0
#define MAX_GPA          4

typedef struct Student_H {
    double gpa;
    short age;
    char firstName[MAX_NAME_LENGTH + 1];
    char lastName[MAX_NAME_LENGTH + 1];
    char email[MAX_EMAIL_LENGTH + 1];
} * Student;

#define _STUDENT_
#define _SOURCE_
#include "student.h"

Student student_create( char* firstName, char* lastName, char* email, int age, double gpa ){
    if( strlen( firstName ) > MAX_NAME_LENGTH ||
        strlen( lastName ) > MAX_NAME_LENGTH ||
        strlen( email ) > MAX_EMAIL_LENGTH ||
        age < MIN_AGE || gpa < MIN_GPA || gpa > MAX_GPA ){
        return NULL;
    }
    Student student = (Student)malloc( sizeof( struct Student_H ) );
    strcpy( student->firstName, firstName );
    strcpy( student->lastName, lastName );
    strcpy( student->email, email );
    student->age = (short) age;
    student->gpa = gpa;
    return student;
}

void student_destroy( Student student ){
    free( student );
}

char* student_getFirstName( Student student ){
    return &(student->firstName[0]);
}

char* student_getLastName( Student student ){
    return &(student->lastName[0]);
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

bool student_equals( const void * a, const void * b ){
    Student s1 = (Student) a;
    Student s2 = (Student) b;
    char* firstName1 = s1->firstName;
    char* firstName2 = s2->firstName;
    char* lastName1 = s1->lastName;
    char* lastName2 = s2->lastName;
    char* email1 = s1->email;
    char* email2 = s2->email;
    return ( strcmp( firstName1, firstName2 ) == 0 ) &&
           ( strcmp( lastName1, lastName2 ) == 0 ) &&
           ( strcmp( email1, email2 ) == 0 ) &&
           ( s1->age == s2->age ) &&
           ( s1->gpa == s2->gpa );
}

char* student_toString( const void * a ){
    Student student = (Student) a;
    int length = strlen( student->firstName ) + strlen( student->lastName ) + 
        strlen( student->email ) + 40;
    char* str = (char*)malloc( sizeof( char ) * length );
    sprintf( str, "[name: %s %s, email: %s, age: %d, gpa: %.2f]", 
            student->firstName, student->lastName, student->email, 
            student->age, student->gpa );
    return str;
}

