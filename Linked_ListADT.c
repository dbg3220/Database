//
// File: ListADT.c
// Description: A library module that implements a linked list abstract data type
//  for portable use in client programs.
//
// Author: Damon Gonzalez
//

#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>

/// struct for representing an element in the queue, contains a pointer to the
/// next element and a generic pointer to the data payload
typedef struct Element_H {
	void * data;
	struct Element_H * next;
} * Element;

/// object representation of a list abstract data type, overrides data type
/// present in ListADT.h
typedef struct ListADT_H {
	Element head;
	bool (*equals)( const void * a, const void * b );
	char* (*toString)( const void * a );
} * ListADT;

#define _LIST_IMPL_
#include "ListADT.h"

ListADT list_create( bool (*equals)( const void * a, const void * b ),
					 char* (*toString)( const void * a ) ){
	ListADT list = (ListADT)malloc( sizeof( struct ListADT_H ) );
	list->head = NULL;
	list->equals = equals;
	list->toString = toString;
	return list;
}

void list_destroy( ListADT list ){
	list_clear( list );
	free( list );
}

void list_clear( ListADT list ){
	Element elm = list->head;
	while( elm != NULL ){
		Element next = elm->next;
		free( elm );
		elm = next;
	}
	list->head = NULL;//Sets the beginning of the list to NULL so that the list is empty
}

void * list_get( ListADT list, int i ){
	if( i > list_size( list ) - 1 || i < 0 ){
		return NULL;
	}
	Element elm = list->head;
	int index = 0;
	while( index != i ){
		elm = elm->next;
		index++;
	}
	return elm->data;
}

/// Accessible only internally by this module, used to create
/// a new element in the list with the specified payload and a
/// next value of NULL
///
/// @param the payload to insert
/// @return an Element object, a pointer to struct Element_H
Element create_element( void * a ){
	Element elm = (Element)malloc( sizeof( struct Element_H ) );
	elm->data = a;
	elm->next = NULL;
	return elm;
}

bool list_add( ListADT list, void * a, int i ){
	if( i > list_size( list ) || i < 0 ){
		return false;
	}

	Element newElm = create_element( a );

	Element prev = NULL;
	Element elm = list->head;
	int index = 0;
	while( index != i ){
		prev = elm;
		elm = elm->next;
		index++;
	}
	if( index == 0 ){
		Element temp = list->head;
		list->head = newElm;
		newElm->next = temp;
	} else {
		prev->next = newElm;
		newElm->next = elm;
	}
	return true;
}

void list_append( ListADT list, void * a ){
	list_add( list, a, list_size( list ) );
}

bool list_delete( ListADT list, int i ){
	if( i > list_size( list ) - 1 || i < 0 ){
		return false;
	}	
	Element prev = NULL;
	Element elm = list->head;
	int index = 0;
	while( index != i ){
		prev = elm;
		elm = elm->next;
		index++;
	}
	if( prev != NULL ){
		prev = elm->next;
		free( elm );	
	} else {
		list->head = elm->next;
		free( elm );
	}	
	return true;
}

int list_size( ListADT list ){
	Element elm = list->head;
	int size = 0;
	while( elm != NULL ){
		elm = elm->next;
		size++;
	}
	return size;
}

int list_indexOf( ListADT list, const void * a ){
	if( list->equals == NULL ){
		return -1;
	}
	Element elm = list->head;
	int index = 0;
	while( elm != NULL ){
		if( list->equals( elm->data, a ) ){
			return index;
		}
		elm = elm->next;
		index++;
	}
	return -1;
}

bool list_contains( ListADT list, const void * a ){
	return list_indexOf( list, a ) != -1;
}	

void list_print( ListADT list ){
	if( list->toString == NULL ){
		printf( "{}\n" );
		return;
	}
	int size = list_size( list );
	if( size == 0 ){
		printf( "{}\n" );
	} else if ( size == 1 ){
		char* str = list->toString( list->head->data );
		printf( "{ %s }\n", str );
	} else {
		printf( "{ " );
		Element elm = list->head;
		while( elm->next != NULL ){
			char* str = list->toString( elm->data );
			printf( "%s, ", str );
			elm = elm->next;
		}
		char* str = list->toString( elm->data );
		printf( "%s }\n", str );
	}
}

