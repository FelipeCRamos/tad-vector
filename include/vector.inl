#include "vector.hpp"

/*!
 * \file 	vector.inl
 * \author 	Felipe Ramos & Max William
 */

namespace sc
{

	/* Special Member Block {{{*/

	/*!
	 * \brief	Constructs the list with count default-inserted instances of T 	
	 * \param 	size_type count : Number of elements that the vector will have
	 */
	template <class T>
	Vector<T>::Vector( size_type count ){
		m_capacity = 2;
		if( count >= 2 ){
			while( count >= m_capacity){
				m_capacity *= 2;
			}
		}
		// alocating [count] elements of type T
		this->elements = new T[m_capacity];
		for( int i = 0; i < count; i++ ){
			if(debug) elements[i] = i;			// debug inicializer
			else elements[i] = 0;				// normal inicializer
		}

		this->m_first = elements;
		this->m_last = elements + count;
		this->m_size = count;

		if(debug) std::cout << "> Vector allocated with sucess!" << std::endl;
	}

	/*!
	 * \brief	Default constructor that creates an empty list
	 */
	template <class T>
	Vector<T>::Vector( void ){
		int temp_capacity = 2;		

		this->elements = new T[temp_capacity];
		this->m_first = elements;
		this->m_last = elements;
		this->m_size = 0; 
		this->m_capacity = temp_capacity;

		if(debug) std::cout << "> Vector allocated with sucess!" << std::endl;
	}

	/*!
	 * \brief 	Copy constructor, makes a *deep copy* of another Vector object
	 * \param 	const Vector &other : Another Vector object
	 */
	template <class T>
	Vector<T>::Vector( const Vector &other ){
		int temp_capacity;
		if( other.size() > 2 ){
			temp_capacity = pow( 2, int(log2(other.size())) );

			if( other.size() > temp_capacity ){
				temp_capacity *= 2;
			}
		} else {
			temp_capacity = other.size();
		}
		this->elements = new T[temp_capacity];
		for( int i = 0; i < temp_capacity; i++ ){
			elements[i] = other.elements[i];	
		}
		this->m_first = elements;
		this->m_last = elements + other.size();
		this->m_size = other.size();
		this->m_capacity = temp_capacity;
	}

	/*!
	 * \brief 	Constructor that takes a std::initializer_list as arg.
	 * \param 	std::initializer_list ilist : Initializer list that will
	 * 			turn into a Vector
	 */
	template <class T>
	Vector<T>::Vector( std::initializer_list<T> ilist ){
	int temp_capacity;			
		if( ilist.size() > 2 ){
			temp_capacity = pow( 2, int(log2(ilist.size())) );					
			if( ilist.size() > temp_capacity ){
				temp_capacity *= 2;		
			}
		} else {
			temp_capacity = ilist.size();	
		}

		this->elements = new T[temp_capacity];
		int buf = 0;
		for( auto *i = ilist.begin(); i < ilist.end(); i++, buf++ ){
			elements[buf] = *i;
		}
		this->m_first = elements;
		this->m_last = elements + ilist.size();
		this->m_size = ilist.size();
		this->m_capacity = temp_capacity;
	}

	/*!
	 * \brief	Constructor that makes a copy from another simple array.
	 * \param 	InputIt *first : First element from the array
	 * \param 	InputIt *last : Last (stub) element from the array
	 */
	template <class InputIt>
	Vector<InputIt>::Vector( InputIt *first, InputIt *last ){
		int temp_capacity;		
		int size = std::distance(first, last);
		if( size > 2 ){
			temp_capacity = pow( 2, int(log2( size )) );
			if( size > temp_capacity ){
				temp_capacity *= 2;	
			}
		} else {
			temp_capacity = size;
		}
		this->elements = new InputIt[temp_capacity];
		int buf = 0;
		for( auto *i = first; i < last; i++, buf++ ){
			elements[buf] = *i;
		}
		this->m_first = elements;
		this->m_last = elements + size;
		this->m_size = size;
		this->m_capacity = temp_capacity;
	}
 
	/*!
	 * \brief 	Default destructor
	 */
	template <class T>
	Vector<T>::~Vector(){
		if(elements != NULL){
			delete[] elements;
			if(debug) std::cout << "> Vector deleted with sucess!" << std::endl;
		}
	}
	/*}}}*/

	/* Capacity Methods {{{*/
	/*!
	 * 	\brief	Tells if a sc::Vector is empty (0 elements)
	 * 	\return	bool result : True if the element is empty, false otherwise	
	 */
	template <class T>
	bool Vector<T>::empty(){
		return (m_size == 0 ? true : false);
	}

	/*!
	 * \brief	Discover how many elements the sc::Vector has
	 * \return	size_type size : Size of elements in the sc::Vector
	 */
	template <class T>
	size_type Vector<T>::size() const {
		return this->m_size;
	}

	/*! 
	 * \brief	Discover what is the total capacity of the sc::Vector	
	 * \return 	size_type capacity : maximum amount of elements for current
	 * 			allocated size
	 */
	template <class T>
	size_type Vector<T>::capacity() const{
		return this->m_capacity;
	}

	/*! 
	 * \brief Allocates memory if new_cap > capacity
	 * \param new_cap expected size of the array after function call
	 */
	template <class T>
	void Vector<T>::reserve(size_type new_cap){
		if( new_cap > m_capacity ){
			while(new_cap > m_capacity){
				m_capacity *= 2;	
			}
			T *temp_elements = new T[m_capacity];
			if(m_first != m_last) std::copy( elements, m_last, temp_elements );
			delete [] elements;
			elements = temp_elements;
			m_first = elements;
			m_last = elements+m_size;
		}
	}
	/*}}}*/

	/* Modifiers Methods {{{*/
	/*!
	 * \brief 	Insert an element in the end of the sc::Vector
	 * \param 	const T& value : Value to be inserted on the list
	 */
	template <class T>
	void Vector<T>::push_back( const T& value ){
		
		if( m_size < m_capacity ){
			*(m_last++) = value;
			m_size += 1;
		} 
		else {
			
			this->reserve( m_capacity * 2 );	
			m_size += 1;
			*(m_last++) = value;
		}
	}
	/*! Adds an element to the front of the array */
	/*!
	 * \brief	Insert an element in the first position in the sc::Vector
	 * \param	const T& value : Value to be inserted on the list
	 */
	template <typename T>
	void Vector<T>::push_front(const T & value){
	
		if(m_size <= 2){
			this->reserve(2);
			m_size += 1;
			if(m_size >= 1){
				 std::copy(m_first,m_last,m_first+1);
			}
			m_last++;
			*m_first = value;
		}
		
		else if( m_size < m_capacity ){
			std::copy(m_first,m_last,m_first+1);
			*m_first = value;
			m_size += 1;
			m_last++;
		} 
		else {
			
			this->reserve( m_capacity * 2 );	
			m_size += 1;
			std::copy(m_first,m_last,m_first+1);
			*m_first = value;
			m_last++;
		}
	}
	/*!
	 * \brief	Remove an element from the first position on the sc::Vector
	 */
	template <typename T>
	void Vector<T>::pop_front(){

		if(m_size != 0){
			std::copy(m_first+1,m_last,m_first);
			m_size--;
			m_last--;
		}
		else{
			throw std::runtime_error("Don't pop an empty vector");
		}
	}
	/*!
	 * \brief	Remove an element from the last position on the sc::Vector
	 */
	template <typename T>
	void Vector<T>::pop_back(){

		if(m_size != 0){
			m_size--;
			m_last--;
		}
		else{
			throw std::runtime_error("Don't pop an empty vector");
		}
	}

	/*!
	 * \brief 	Insert an defined number of terms on the sc::Vector object
	 * \param 	iterator pos : Position to start inserting elements
	 * \param 	const T& value : Value to be inserted
	 */
	template <typename T>
	typename Vector<T>::iterator Vector<T>::insert
	(iterator pos, const T &value){
		int distance = pos - m_first;

		bool reserved = false;	
		if(++m_size >= m_capacity){
			this->reserve(m_capacity*2);
			reserved = true;
		}
		
		if(debug) std::cout << "Distance: " << distance << std::endl;

		if(distance == m_size)
		{
			*m_last = value;
			if(!reserved) m_last++;
			return elements+m_size;
		}
		else{
			T temp;
			std::copy(elements+distance,elements+m_size,elements+distance+1);
			*(elements+distance) = value;
			if(!reserved) m_last++;
		}
		return elements+distance;
	}

	/*!
	 * \brief 	Insert an defined number of terms on the sc::Vector object
	 * \param 	iterator pos : Position to start inserting elements
	 * \param 	iterator first : First iterator that will be inserted
	 * \param 	iterator last : Last iterator that will stop the insertion
	 */
	template <typename T>
	typename Vector<T>::iterator Vector<T>::insert
	(iterator pos,iterator first, iterator last ){
		int distance = last-first;
		int first_index = pos-m_first;

		T temp[distance];	
		int index = 0;
		for (auto i(first); i != last; ++i,++index) {
			temp[index] = *i;
		}
	
		if(debug){
			std::cout << "Before : ";
			std::copy(temp,temp+distance,
					std::ostream_iterator<int>(std::cout ," "));
			std::cout << "first_index : " << first_index << std::endl;
		}
		reserve(m_size+distance);

		std::copy(elements+first_index,
				elements+m_size,elements+first_index+distance);
	
		m_size += distance;
		
		if(debug) {
			std::cout << "After : ";
			std::copy(elements,elements+m_size,
				std::ostream_iterator<int>(std::cout ," "));
			std::cout << std::endl;
		}
		std::copy(temp,temp+distance,elements+first_index);
		
		m_last += distance;
		return elements+first_index; 
	}

	/*!
	 * \brief 	Insert an defined number of terms on the sc::Vector object
	 * \param 	iterator pos : Position to start inserting elements
	 * \param 	std::initializer_list<T> ilist : initializer_list object that
	 * 			will be inserted on the sc::Vector
	 */
	template <typename T>
	typename Vector<T>::iterator Vector<T>::insert
	(iterator pos,std::initializer_list<T> ilist){

		int first_index = pos-m_first;
		if(1){
			std::cout << "Before : ";
			std::cout << "Cap : " << capacity() << std::endl;
			std::cout << "size : " << size() << std::endl;
			std::copy(m_first,m_last,
					std::ostream_iterator<int>(std::cout ," "));
			std::cout << std::endl;
		}
		
		if(m_size+ilist.size() > m_capacity){
				reserve(m_size+ilist.size());
		}
		
		std::copy(elements+first_index,elements+m_size,
				elements+first_index+ilist.size());
		std::copy(ilist.begin(),ilist.end(),elements+first_index);
	
		m_size += ilist.size();
		m_last += ilist.size();
		if(1) {
			std::cout << "After : ";
			std::cout << "Cap : " << capacity() << std::endl;
			std::cout << "size : " << size() << std::endl;
			std::copy(elements,elements+m_size,
				std::ostream_iterator<int>(std::cout ," "));
			std::cout << std::endl;
		}
		return elements+first_index; 
	}

	/*!
	 * \brief 	Reset current sc::Vector object
	 */
	template <typename T>
	void Vector<T>::clear(void){
		m_size = 0;
		m_first = elements;
		m_last = elements;
	}

	/*!
	 * \brief 	Replaces the contents with count copies of pre-defined values
	 * \param 	size_type count : How many times the const T &value will appear
	 * \param 	const T &value : Value that will be inserted
	 */
	template <typename T>
	void Vector<T>::assign(size_type count,  const T & value){

	clear();
	reserve(count);
	for (int i = 0; i < count; ++i) {
		elements[i] = value;	
	}
	m_last += count;
	m_size += count;
	}

	/*!
	 * \brief 	Replaces the contents with count copies of pre-defined values
	 * \param 	iterator first : First iterator element
	 * \param 	iterator last : Last iterator element
	 */
	template <typename T>
	void Vector<T>::assign(iterator first, iterator last){
	
		int distance = last-first;
		clear();
		reserve(distance);
		for (auto i(first);  i != last;++i ) {
			*m_last++ = *i;	
			m_size++;
		}
	}

	/*!
	 * \brief 	Replaces the contents with count copies of pre-defined values
	 * \param 	std::initializer_list<T> ilist : initializer_list that will 
	 * 			populate the sc::Vector object
	 */
	template <typename T>
	void Vector<T>::assign(std::initializer_list<T> ilist){
	if(m_capacity < ilist.size()){

			while(m_capacity < ilist.size( )){
				m_capacity *= 2;	
			}
			reserve(m_capacity);
	}
	clear();	
	m_last+= ilist.size();
	m_size+= ilist.size();
	std::copy(ilist.begin(),ilist.end(),elements);	
	}

	/*!
	 * \brief 	Resizes if needed the total capacity of a sc::Vector object
	 */
	template <typename T>
	void Vector<T>::shrink_to_fit(void){

			m_capacity = pow(2,int(log2(m_size))+1);
			T *temp_elements = new T[m_capacity];
			std::copy(elements,elements+m_size,temp_elements);
			delete [] elements;
			elements = temp_elements;
			m_first = elements;
			m_last = elements+m_size;
	}

	/*!
	 * \brief 	Removes from the sc::Vector either a element or a range of
	 * 			elements (first, last)
	 * \param	iterator pos : The position of the element to be erased	
	 */
	template <typename T>
	typename Vector<T>::iterator Vector<T>::erase(iterator pos){
		int index = pos-m_first;
		if(pos == end()-1 or pos == end()){
			m_last--;
			m_size--;
			return end();
		}
		if(pos != begin()){
			std::copy(elements+index+1,elements+m_size,elements+index);
			m_size--;
			m_last--;
			std::cout << "debug " << index-1 << std::endl;
			return elements+index;
		}
		
		else{
			std::copy(elements+index+1,elements+m_size,elements+index);
			m_size--;
			m_last--;
			return elements;
		}
	} 


	/*!
	 * \brief 	Removes from the sc::Vector either a element or a range of
	 * 			elements (first, last)
	 * \param	iterator first : First position iterator
	 * \param	iterator last : Last position iterator
	 */
	template <typename T>
	typename Vector<T>::iterator Vector<T>::erase
	( iterator first, iterator last ){
		int index = first-m_first;
		int index_l = last-m_first;
		std::copy(elements+index_l,elements+m_size,elements+index);
		m_size -= last-first;
		m_last -= last-first;

		return elements+index;
	} 
	/*}}}*/

	/* Elements Access Methods {{{*/

	/*!
	 * \brief Access the first element of the vector.
	 * \return The value of the first element of the vector (vector[0]).
	 */
	template <class T>
	const T &Vector<T>::front() const{
		return *(this->m_first);
	}

	/*!
	 * \brief Access the last element of the vector.
	 * \return The value of the last element of the vector (vector[size-1]).
	 */
	template <class T>
	const T &Vector<T>::back() const{
		T *valid_l = this->m_last - 1;
		return *valid_l;
	}
	
	/*!
	 * \brief Access element from a specified position
	 * \param size_type pos : User defined position
	 * \return Element at defined position
	 */
	template <class T>
	T &Vector<T>::at( size_type pos ){
		return ( this->elements[pos] );
	}

	/*}}}*/

	/* Operators Overloading {{{*/

	/*!
	 * \brief 	sc::Vector operator `[]` overload function
	 * \param 	size_type pos : The desired position to access in elements[pos].
	 * \return 	The element at elements[pos].
	 */
	template <class T>
	T& Vector<T>::operator[]( size_type pos ){
		return this->elements[pos]; 
	}

	/*!
	 * \brief	sc::Vector operator `=` overload function
	 * \param	const Vector<T> &rhs : Right hand side object
	 * \return	The right hand side object
	 */
	template <class T>
	Vector<T> &Vector<T>::operator=( const Vector<T> &rhs ){
		if( this->m_size < rhs.m_size ){
			this->reserve( rhs.m_size );
		}

		this->m_capacity = rhs.m_capacity;
		this->m_size = rhs.m_size;
		this->m_first = this->elements; 
		this->m_last = this->elements + m_size;

		for( int i = 0; i < rhs.m_size; i++ ){
			this->elements[i] = rhs.elements[i];
		}
		return *this;
	}

	/*!
	 * \brief	sc::Vector operator '=' overload function that constructs the 
	 * 			object following a std::initializer_list object.
	 * \param 	std::initializer_list ilist : Initializer list object
	 */
	template <class T>
	Vector<T> &Vector<T>::operator=( std::initializer_list<T> ilist ){
		int temp_capacity;
		if( ilist.size() > 2 ){
			temp_capacity = pow( 2, int( log2( ilist.size() ) ) );
			if( ilist.size() > temp_capacity ){
				temp_capacity *= 2;
			}
		} else {
			temp_capacity = ilist.size();
		}

		this->elements = new T[temp_capacity];

		int buf = 0;
		for( auto i = std::begin(ilist); i != std::end(ilist); i++, buf++ ){
			elements[buf] = *i;
		}

		this->m_first = elements;
		this->m_last = elements + ilist.size();
		this->m_size = ilist.size();
		this->m_capacity = temp_capacity;
		if(debug) std::cout << ">> Saiu da função!" << std::endl;
	}

	/*!
	 * \brief	sc::Vector operator `==` overload function
	 * \param	const Vector<T> &rhs : Right hand side object
	 * \return	bool value if the two objects are equal.
	 * 			(true = 1, false = 0)
	 */
	template <class T>
	bool Vector<T>::operator==( const Vector &rhs ){
		if( rhs.m_size != this->m_size ){
			return false;
		} else {
			for( int i = 0; i < rhs.m_size ; i++ ){
				if( *(this->m_first+i) != *(rhs.m_first + i) ){
					return false;
				}
			}
		}
		// if he ever gets to this point, they're equal
		return true;
	}

	/*!
	 * \brief	sc::Vector operator `!=` overload function
	 * \param	const Vector<T> &rhs : Right hand side object
	 * \return	bool value if the two objects are unequal.
	 * 			(true = 1, false = 0)
	 */
	template <class T>
	bool Vector<T>::operator!=( const Vector &rhs ){
		if( *this == rhs ){
			return false;
		} else {
			return true;
		}
	}
	/*}}}*/

	/* Vector Iterators {{{*/

	/*!
	 * \brief Begin iterator
	 * \return Iterator to the first element of the vector.
	 */
	template <class T>
	typename Vector<T>::iterator Vector<T>::begin(){
		return Vector<T>::iterator(this->m_first);
		// return Vector<T>::iterator(this->m_first);
	}

	/*!
	 * \brief End iterator
	 * \return Iterator to the last element of the vector.
	 */
	template <class T>
	typename Vector<T>::iterator Vector<T>::end(){
		return Vector<T>::iterator(this->m_last);
		// return Vector<T>::iterator(this->m_last);
	}

	/*!
	 * \brief Constant begin iterator
	 * \return A constant iterator to the first element of the vector.
	 */
	template <class T>
	typename Vector<T>::const_iterator Vector<T>::cbegin() const{
		return Vector<T>::const_iterator(this->m_first);
	}

	/*!
	 * \brief Constant end iterator
	 * \return A constant iterator to the last element of the vector.
	 */
	template <class T>
	typename Vector<T>::const_iterator Vector<T>::cend() const{
		return Vector<T>::const_iterator(this->m_last);
	}
	/*}}}*/

	/* Iterator Implementation {{{*/

	/*!
	 * \brief 	default iterator class constructor
	 * \param 	T *ptr : A pointer from any type that will be stored inside the
	 * 			iterator.
	 */
	template <class T>
	Vector<T>::iterator::iterator( T *ptr ){
		this->m_ptr = ptr;
	}

	/*!
	 * \brief Alternative constructor, that recieves another iterator.
	 * \param const Vector<U>::iterator &itr : Another iterator from Vector<U>.
	 */
	template <class U>
	Vector<U>::iterator::iterator( const Vector<U>::iterator &itr ){
		this->m_ptr = itr.m_ptr;
	}

	/*!
	 * \brief	Default iterator destructor
	 */
	template <class U>
	Vector<U>::iterator::~iterator() = default;

	/*!
	 * \brief Operator `=` overload function
	 * \param const Vector::iterator &rhs : Right hand side of the `=` sign.
	 */
	template <class T>
	typename Vector<T>::iterator &Vector<T>::iterator::operator=(
			const Vector::iterator &rhs )
	{
		this->m_ptr = rhs.m_ptr;
	}

	/*!
	 * \brief Operator `==` overload function
	 * \param const Vector::iterator &rhs : Right hand side of the `==` sign.
	 */
	template <class T>
	bool Vector<T>::iterator::operator==( const Vector::iterator &rhs ) const{
		return this->m_ptr == rhs.m_ptr;
	}

	/*!
	 * \brief Operator `!=` overload function
	 * \param const Vector::iterator &rhs : Right hand side of the `!=` sign.
	 */
	template <class T>
	bool Vector<T>::iterator::operator!=( const Vector::iterator &rhs ) const{
		return this->m_ptr != rhs.m_ptr;
	}

	/*!
	 * \brief Operator `*` overload function
	 */
	template <class T>
	T &Vector<T>::iterator::operator*( void ) const{
		return *this->m_ptr;
	}

	/*!
	 * \brief Operator `++` overload function
	 */
	template <class T>
	typename Vector<T>::iterator Vector<T>::iterator::operator++( void ){
		// ++it
		return ++this->m_ptr;
	}
	/*!
	 * \brief Operator `-` overload function
	 */
	template <class T>
	typename Vector<T>::iterator Vector<T>::iterator::operator-(int a ){
		// ++it
		return this->m_ptr-a;
	}

	/*!
	 * \brief Operator `-` overload function for ptr_diff
	 */
	template <class T>
	int Vector<T>::iterator::operator-(iterator rhs ){
		return this->m_ptr-rhs.m_ptr;
	}

	/*!
	 * \brief Operator `+` overload function
	 */
	template <class T>
	typename Vector<T>::iterator Vector<T>::iterator::operator+(int a ){
		// ++it
		return this->m_ptr+a;
	}
	/*!
	 * \brief Operator `++` overload function
	 * \param int : The object itself
	 */
	template <class T>
	typename Vector<T>::iterator Vector<T>::iterator::operator++( int ){
		// it++
		return this->m_ptr++;
	}

	/*!
	 * \brief Operator `--` overload function
	 */
	template <class T>
	typename Vector<T>::iterator Vector<T>::iterator::operator--( void ){
		// --it
		return --this->m_ptr;
	}

	/*!
	 * \brief Operator `--` overload function
	 * \param int : The object itself
	 */
	template <class T>
	typename Vector<T>::iterator Vector<T>::iterator::operator--( int ){
		// it--
		return this->m_ptr--;
	}

	/*}}}*/

	/* Const_Iterator Implementation {{{*/

	/*!
	 * \brief default const_iterator class constructor
	 * \param T *ptr : A pointer from any type that will be stored inside the
	 * iterator.
	 */
	template <class T>
	Vector<T>::const_iterator::const_iterator( T *ptr ){
		this->m_ptr = ptr;
	}

	/*!
	 * \brief Alternative constructor, that recieves another const_iterator.
	 * \param const Vector<U>::const_iterator &itr : Another const_iterator from Vector<U>.
	 */
	template <class U>
	Vector<U>::const_iterator::const_iterator( const Vector<U>::const_iterator &itr ){
		this->m_ptr = itr.m_ptr;
		std::cout << "Vector<U>::const_iterator::const_iterator( itr ) created.\n";
	}

	/*!
	 * \brief Default const_iterator destructor
	 */
	template <class U>
	Vector<U>::const_iterator::~const_iterator() = default;

	/*!
	 * \brief Operator `=` overload function
	 * \param const Vector::const_iterator &rhs : Right hand side of the `=` sign.
	 */
	template <class T>
	typename Vector<T>::const_iterator &Vector<T>::const_iterator::operator=(
			const Vector::const_iterator &rhs )
	{
		this->m_ptr = rhs.m_ptr;
	}

	/*!
	 * \brief Operator `==` overload function
	 * \param const Vector::const_iterator &rhs : Right hand side of the `==` sign.
	 */
	template <class T>
	bool Vector<T>::const_iterator::operator==( const Vector::const_iterator &rhs ) const{
		return this->m_ptr == rhs.m_ptr;
	}

	/*!
	 * \brief Operator `!=` overload function
	 * \param const Vector::const_iterator &rhs : Right hand side of the `!=` sign.
	 */
	template <class T>
	bool Vector<T>::const_iterator::operator!=( const Vector::const_iterator &rhs ) const{
		return this->m_ptr != rhs.m_ptr;
	}

	/*!
	 * \brief Operator `*` overload function
	 */
	template <class T>
	const T &Vector<T>::const_iterator::operator*( void ) const{
		return *this->m_ptr;
	}

	/*!
	 * \brief Operator `++` overload function
	 */
	template <class T>
	typename Vector<T>::const_iterator Vector<T>::const_iterator::operator++( void ){
		// ++it
		return ++this->m_ptr;
	}
	/*!
	 * \brief Operator `-` overload function
	 */
	template <class T>
	typename Vector<T>::const_iterator Vector<T>::const_iterator::operator-(int a ){
		// ++it
		return this->m_ptr-a;
	}

	/*!
	 * \brief Operator `-` overload function for ptr_diff
	 */
	template <class T>
	int Vector<T>::const_iterator::operator-(const_iterator rhs ){
		return this->m_ptr-rhs.m_ptr;
	}

	/*!
	 * \brief Operator `+` overload function
	 */
	template <class T>
	typename Vector<T>::const_iterator Vector<T>::const_iterator::operator+(int a ){
		// ++it
		return this->m_ptr+a;
	}
	/*!
	 * \brief Operator `++` overload function
	 * \param int : The object itself
	 */
	template <class T>
	typename Vector<T>::const_iterator Vector<T>::const_iterator::operator++( int ){
		// it++
		return this->m_ptr++;
	}

	/*!
	 * \brief Operator `--` overload function
	 */
	template <class T>
	typename Vector<T>::const_iterator Vector<T>::const_iterator::operator--( void ){
		// --it
		return --this->m_ptr;
	}

	/*!
	 * \brief Operator `--` overload function
	 * \param int : The object itself
	 */
	template <class T>
	typename Vector<T>::const_iterator Vector<T>::const_iterator::operator--( int ){
		// it--
		return this->m_ptr--;
	}

	/*}}}*/

}
