// File: ListADT.h
//
// Description: Interface to a list abstract data type module
//
// Author: Damon Gonzalez
//

#ifndef _LISTADT_H_
#define _LISTADT_H_

#include <stdbool.h>

// Define _LIST_IMPL_ in the module implementation file just before
// including this header file so that the struct type is opaque to
// the client of this file. If you are client simply include this header
// file.

#ifndef _LIST_IMPL_

/// ListADT is a pointer to an abstract list data structure whose
/// payload is generic. It is implied that the type remains constant for
/// all elements in this list.

typedef struct { } * ListADT;

#endif

/// Create a ListADT that used the supplied function as a comparison
/// routine.
///
/// @param equals the address of the equals function
/// @param toString the address of the toString function, converts
/// the data payload that a client has entered into a valid C string(memory
/// must be freed by client)
/// @return a ListADT instance, or NULL if the allocation fails

ListADT list_create( bool (*equals)( const void * a, const void * b ),
					 char* (*toString)( const void * a ) );

/// Destroy and deallocate the supplied ListADT
///
/// @param list - the ListADT to be manipulated

void list_destroy( ListADT list );

/// Remove all contents from the supplied ListADT, effectively creates
/// an empty list
///
/// @param list - the ListADT to be manipulated

void list_clear( ListADT list );

/// Retrieves the pointer to the ith element from the ListADT,
/// returns NULL if the client has entered an invalid index
/// (i.e.  (length of list - 1) < i || i < 0)
///
/// @param list - the ListADT to be manipulated
/// @param i - the index of the element to retrieve
/// @return the value at index i

void * list_get( ListADT list, int i );

/// Adds an element to this list at the specified index, pushes all elements
/// beyond this index by one
///
/// @param list - the ListADT to be manipulated
/// @param a the pointer to be inserted into the list
/// @param i the index to insert at
/// @return true if the element was successfully added, false otherwise

bool list_add( ListADT list, void * a, int i );

/// Appends an element to this list
///
/// @param list - the ListADT to be manipulated
/// @param a the pointer to be appended

void list_append( ListADT list, void * a );

/// Deletes an element from this list at the specified index
///
/// @param list - the ListADT to be manipulated
/// @param i the index to delete
/// @return true if the element was successfully deleted, false otherwise

bool list_delete( ListADT list, int i );

/// Gives the size of the list
///
/// @param list - the ListADT to be tested
/// @return the size of the list

int list_size( ListADT list );

/// Returns the index of the given element. If the supplied equals function
/// is NULL, always returns -1
///
/// @param list - the ListADT to be tested
/// @return the index of the given element, -1 if not found
int list_indexOf( ListADT list, const void * a );

/// Indicates whether a certain data entry is contained
/// within this ListADT. If the supplied equals function is NULL, always
/// returns -1
///
/// @param list - the ListADT to be tested
/// @return true if the element is in the list, false otherwise

bool list_contains( ListADT list, const void * a );

/// Prints to stdin on a single line the entire list using the print
/// function specified by the client, ending with a newline character. If
/// the supplied toString function is NULL prints an empty array.
///
/// @param list - the ListADT to be displayed

void list_print( ListADT list );

#endif
