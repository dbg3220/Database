//
// File: student.h
// Description: header file for automating the creation, editing, and deletion
// of student objects from memory
//
// @author Damon Gonzalez
//

#include <stdbool.h>

#ifndef _STUDENT_

/// struct pointer to signify an object of student
typedef struct { } * Student;

#endif

/// Creates a student object
///
/// The length of first and last name must be less than 50 characters
/// The length of email must be less than 100 characters
/// age must be greater than 0
/// gpa must be within the bounds [0, 4]
///
/// --This function returns NULL if the parameters are invalid--
///
/// @param name A pointer to the name of the student, creates deep copy
/// @param email A pointer to the email of the student, creates deep copy
/// @param age The age of the student
/// @param gpa The gpa of the student
/// @return A newly created student allocated on the heap, NULL if unsuccessful
Student student_create( char* firstName, char* lastName, char* email, int age, double gpa );

/// Removes from memory all space allocated for this student
///
/// @param student The student to be destroyed
void student_destroy( Student student );

/// Retrieves the first name of this student
///
/// @param student The student to be analyzed
/// @return A pointer to the name of this student
char* student_getFirstName( Student student );

/// Retrieves the last name of this student
///
/// @param student The student to be analyzed
/// @return A pointer to the name of this student
char* student_getLastName( Student student );

/// Retrieves the email of this student
///
/// @param student The student to be analyzed
/// @return A pointer to the email of this student
char* student_getEmail( Student student );

/// Retrieves the age of the student
///
/// @param student The student to be analyzed
/// @return This student's age as an int
int student_getAge( Student student );

/// Retrieves the gpa of this student
///
/// @param student The student to be analyzed
/// @return This student's gpa as a double
double student_getGPA( Student student );

/// Equals method for comparing two students, assumes the two
/// pointers provided are valid Student objects
///
/// @param s1 The first student to compare
/// @param s2 The second student to compare
/// @return true if s1 and s2 hold the same valuee, false otherwise
bool student_equals( const void * a, const void * b );

/// toString method for converting the state information of a student into
/// a string. The pointer returned is allocated on the heap and must be freed
/// by the client.
///
/// @param student The student to create a string of
/// @return A valid C string representing the student
char* student_toString( const void * a );

