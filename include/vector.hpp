#ifndef VECTOR_HPP_
#define VECTOR_HPP_
#define debug false
#include <iostream>
#include <cmath>
#include <algorithm>

/*!
 * \file vector.hpp
 * \author Felipe Ramos & Max William
 */

using size_type = size_t; 

/*!
 * \brief A class that stores all vector functions
 */

namespace sc
{
	template <class T>
	class Vector{
	private:

		T *m_first;					// an 'first' pointer
		T *m_last;					// an 'last' pointer
		T *elements;				// where the array will be stored
		size_type m_size = 0;		// default empty array 
		size_type m_capacity;		// maximum capacity of the array

	public:

		/* Special functions {{{*/
		Vector( int );				// Default constructor
		~Vector();					// Default destructor
		/*}}}*/

		/* Capacity functions {{{*/
		bool empty();

		// Returns amount of the vector's initialized elements
		size_type size() const;

		// Returns amount of memory allocated for the vector
		size_type capacity() const;

		// If new_cap > capacity allocates (new_cap - capacity) bytes
		void reserve( size_type ); 
		/*}}}*/

		/* Modifiers functions {{{*/
		void clear();
		void push_front( const T & );
		void push_back( const T & );	// insert an element on last position
		void pop_front();
		void pop_back();
		void insert( T & );
		void shrink_to_fit();
		void assign( const T & );
		void erase();
		/* }}} */

		/* Element access functions {{{*/
		const T &front() const;		// Acess front member (first member)
		const T &back() const;		// Acess back member (last member)
		T &at( size_type pos );		// Acess [pos] element at the datatype
		/*}}} */

		/* Operator functions {{{*/
		// Copy content from another object
		Vector &operator=( const Vector & );

		// Checks if Vector1 == Vector2
		bool operator==( const Vector & );

		// Checks if Vector1 != Vector2
		bool operator!=( const Vector & );  

		// Access [pos] element by doing object[pos]
		T &operator[]( size_type );	 		
		/*}}}*/

		/* Class Iterator {{{*/
		class iterator{
			public:
				/* Public Code {{{*/
				typedef std::ptrdiff_t difference_type;
				typedef std::bidirectional_iterator_tag iterator_category;

				// constructors
				iterator( T* ptr=nullptr );
				iterator( const iterator & );

				// destructors
				~iterator( void );
				
				// operators 
				iterator &operator=( const iterator & );
				T &operator*( void ) const;

				iterator operator++( void );	// ++it
				iterator operator++( int );		// it++
				iterator operator--( void );	// --it
				iterator operator--( int );		// it--
//
				bool operator==( const iterator & ) const;
				bool operator!=( const iterator & ) const;
				
				/*}}}*/
			private:
				/* Private Code {{{*/
				T *m_ptr;
				/*}}}*/
		};
		/*}}}*/

		/* Iterator methods {{{*/
		typename Vector<T>::iterator begin();
		typename Vector<T>::iterator end();
		typename Vector<T>::iterator cbegin() const;
		typename Vector<T>::iterator cend() const;
		/*}}}*/

	};

}

// Source code 
#include "vector.inl"

#endif
