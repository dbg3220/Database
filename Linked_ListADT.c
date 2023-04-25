//
// File: Linked_ListADT.c
// Description: A library module that implements a linked list abstract data type
//  for portable use in client programs.
//
// Author: Damon Gonzalez
//

#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>

/// struct for representing an item in the list
struct list_item {
	void * data;
	struct list_item * next;
};

typedef struct list_item list_item;

/// Object representation of a list abstract data type which overrides the
/// datatype present in ListADT.h. The toString function provided must
/// return strings allocated on the heap or the print function will cause
/// an error;
typedef struct ListADT_H {
	list_item* head;
	bool (*equals)( const void * a, const void * b );
	char* (*toString)( const void * a );
    long int size;
} * ListADT;

#define _LIST_IMPL_
#include "ListADT.h"

ListADT list_create( bool (*equals)( const void * a, const void * b ),
					 char* (*toString)( const void * a ) ){
	ListADT list = (ListADT)malloc( sizeof( struct ListADT_H ) );
	list->head = NULL;
	list->equals = equals;
	list->toString = toString;
    list->size = 0;
	return list;
}

void list_destroy( ListADT list ){
	list_clear( list );
	free( list );
}

void list_clear( ListADT list ){
	list_item* elm = list->head;
	while( elm != NULL ){
		list_item* next = elm->next;
		free( elm );
		elm = next;
	}
	list->head = NULL;
    list->size = 0;
}

void * list_get( ListADT list, int index ){
	if( index > list->size - 1 || index < 0 ){
		return NULL;
	}
	list_item* elm = list->head;
	int i = 0;
	while( i != index ){
		elm = elm->next;
		i++;
	}
	return elm->data;
}

bool list_add( ListADT list, void * a, int index ){
	if( index > list->size || index < 0 ){
		return false;
	}

	list_item* new = (list_item*)malloc( sizeof( list_item ) );
    new->data = a;
    list_item** walk = &list->head;
    int i = 0;
    while( i != index ){
        walk = &(*walk)->next;
        i++;
    }
    new->next = *walk;
    *walk = new;
    list->size++;
    return true;
}

void list_append( ListADT list, void* a ){
	list_add( list, a, list->size );
}

bool list_set( ListADT list, void* a, int index ){
    if( index < 0 || index > list->size - 1 ){
        return false;
    }

    int i = 0;
    list_item* walk = list->head;
    while( i != index ){
        walk = walk->next;
        i++;
    }
    walk->data = a;
    return true;
}

void* list_delete( ListADT list, int index ){
	if( index > list->size - 1 || index < 0 ){
		return NULL;
	}

    void* val;
    list_item** walk = &list->head;
    int i = 0;
    while( i != index ){
        walk = &(*walk)->next;
        i++;
    }
    list_item* temp = *walk;
    *walk = (*walk)->next;
    val = temp->data;
    free( temp );
    list->size--;
    return val;
}

int list_size( ListADT list ){
	return list->size;
}

int list_indexOf( ListADT list, const void * a ){
	if( list->equals == NULL ){
		return -1;
	}
	list_item* elm = list->head;
	int i = 0;
	while( elm != NULL ){
		if( list->equals( elm->data, a ) ){
			return i;
		}
		elm = elm->next;
		i++;
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
	if( list->size == 0 ){
		printf( "{}\n" );
	} else if ( list->size == 1 ){
		char* str = list->toString( list->head->data );
		printf( "{ %s }\n", str );
        free( str );
	} else {
		printf( "{ " );
		list_item* elm = list->head;
		while( elm->next != NULL ){
			char* str = list->toString( elm->data );
			printf( "%s, ", str );
            free( str );
			elm = elm->next;
		}
		char* str = list->toString( elm->data );
		printf( "%s }\n", str );
        free( str );
	}
}

