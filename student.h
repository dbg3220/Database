//
// File: student.h
// Description: header file for automating the creation, editing, and deletion
// of student objects from memory
//

#include <stdbool.h>

#ifndef _STUDENT_

/// struct pointer to signify an object of student
typedef struct { } * Student;

#endif

/// Creates a student object
///
/// The length of name must be less than 50 characters
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
Student student_create( char* name, char* email, int age, double gpa );

/// Removes from memory all space allocated for this student
///
/// @param student The student to be destroyed
void student_destroy( Student student );

/// Retrieves the name of this student
///
/// @param student The student to be analyzed
/// @return A pointer to the name of this student
char* student_getName( Student student );

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

/// Sets the name of this student
///
/// @param student The student to be manipulated
/// @param name The new name of this student
/// @return true if the student's name was successfully updated, false
/// if the parameter was invalid
bool student_setName( Student student, char* name );

/// Sets the email of this student
///
/// @param student The student to be manipulated
/// @param email The new email of this student
/// @return true if the student's email was succesfully updated, false
/// if the parameter was invalid
bool student_setEmail( Student student, char* email );

/// Sets the age of this student
///
/// @param student The student to be manipulated
/// @param age The new age of this student
/// @return true if the student's age was successfully updated, false
/// if the parameter was invalid
bool student_setAge( Student student, int age );

/// Sets the gpa of this student
///
/// @param student The student to be manipulated
/// @param gpa The new gpa of this student
/// @return true if the student's age was successfully updated, false
/// if the parameter was invalid
bool student_setGPA( Student student, double gpa );

/// Equals method for comparing two students, assumes the two
/// pointers provided are valid Student objects
///
/// @param s1 The first student to compare
/// @param s2 The second student to compare
/// @return true if s1 and s2 hold the same valuee, false otherwise
bool student_equals( const void * a, const void * b );

/// toString method for displaying a student as a string
///
/// @param student The student to create a string of
/// @return A valid C string representing the student, when not in use
/// must be freed from memory by client
char* student_toString( const void * a );
