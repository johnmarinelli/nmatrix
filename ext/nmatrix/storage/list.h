/////////////////////////////////////////////////////////////////////
// = NMatrix
//
// A linear algebra library for scientific computation in Ruby.
// NMatrix is part of SciRuby.
//
// NMatrix was originally inspired by and derived from NArray, by
// Masahiro Tanaka: http://narray.rubyforge.org
//
// == Copyright Information
//
// SciRuby is Copyright (c) 2010 - 2012, Ruby Science Foundation
// NMatrix is Copyright (c) 2012, Ruby Science Foundation
//
// Please see LICENSE.txt for additional copyright notices.
//
// == Contributing
//
// By contributing source code to SciRuby, you agree to be bound by
// our Contributor Agreement:
//
// * https://github.com/SciRuby/sciruby/wiki/Contributor-Agreement
//
// == list.h
//
// List-of-lists n-dimensional matrix storage. Uses singly-linked
// lists.

#ifndef LIST_H
#define LIST_H

/*
 * Standard Includes
 */

#include <stdlib.h>

/*
 * Project Includes
 */

#include "nmatrix.h"
#include "util/sl_list.h"

/*
 * Macros
 */

/*
 * Types
 */

typedef struct {
	int8_t    dtype;
	size_t    rank;
	size_t*   shape;
	size_t*   offset;
	void*     default_val;
	LIST*     rows;
} LIST_STORAGE;

/*
 * Functions
 */

////////////////
// Lifecycle //
///////////////

LIST_STORAGE*	list_storage_create(int8_t dtype, size_t* shape, size_t rank, void* init_val);
void					list_storage_delete(LIST_STORAGE* s);
void					list_storage_mark(void* m);

///////////////
// Accessors //
///////////////

void* list_storage_get(LIST_STORAGE* s, SLICE* slice);
void* list_storage_insert(LIST_STORAGE* s, SLICE* slice, void* val);
void* list_storage_remove(LIST_STORAGE* s, SLICE* slice);

///////////
// Tests //
///////////

bool list_storage_eqeq(const LIST_STORAGE* left, const LIST_STORAGE* right);

/////////////
// Utility //
/////////////

/*
 * Count non-zero elements. See also count_list_storage_nd_elements.
 */
inline size_t list_storage_count_elements(const LIST_STORAGE* s) {
  return list_storage_count_elements_r(s->rows, s->rank - 1);
}

size_t list_storage_count_elements_r(const LIST* l, size_t recursions);
size_t list_storage_count_nd_elements(const LIST_STORAGE* s);

/////////////////////////
// Copying and Casting //
/////////////////////////

LIST_STORAGE* list_storage_copy(LIST_STORAGE* rhs);
LIST_STORAGE* list_storage_cast_copy(LIST_STORAGE* rhs, int8_t new_dtype);
LIST_STORAGE* list_storage_from_dense(const DENSE_STORAGE* rhs, int8_t l_dtype);
LIST_STORAGE* list_storage_from_yale(const YALE_STORAGE* rhs, int8_t l_dtype);

#endif