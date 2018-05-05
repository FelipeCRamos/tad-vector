#include <iostream>
#include <random>
#include <chrono>
#include "vector.hpp"

/*!
 * 	\file	main.cpp
 * 	\author Felipe Ramos & Max William
 */

/* Client code functions {{{*/
namespace client
{
	/*!
	 * 	\brief 	Prints the desired sc::Vector object on the std::cout
	 * 	\param	sc::Vector<T> &V : The Vector object that will be printed
	 * 	\param 	char sep : desired separator char, ex: ' ' (whitespace)
	 */
	template <class T>
		void print_it( sc::Vector<T> &V, char sep ){
			for( auto it = V.begin(); it != V.end(); ++it ){
				std::cout << *it << sep;
			}
			std::cout << std::endl;
		}

	// Populate a given array with random values between [0, 1000)
	/*!
	 * 	\brief 	Populates a given sc::Vector object with random values between
	 * 			0 and 1000
	 * 	\param	sc::Vector<T> &V : sc::Vector object that will be populated
	 */
	template <class T>
		void populate( sc::Vector<T> &V ){
			for( auto it = V.begin(); it != V.end(); ++it ){
				auto seed = 
					std::chrono::system_clock::now().time_since_epoch().count();
				std::mt19937 rd (seed);
				*it = rd() % 1000;
			}
		}
}
/*}}}*/

/* Styles functions {{{*/
namespace h{
	/*!
	 *	\brief	Prints a separator string on std::cout
	 */
	void sep( void ){
		std::cout << "\e[2m";
		for( int i = 0; i < 80; i++ )
			std::cout << "-";
		std::cout << "\e[0m";
		std::cout << std::endl;
	}

	/*!
	 * 	\brief 	Prints a defined phrase with H1 pre-defined styling
	 * 	\param 	std::string phrase : Phrase to print with style
	 */
	void h1(std::string phrase){
		std::cout << "\e[36;4;1m";
		std::cout << "~ " << phrase;
		std::cout << "\e[0m" << std::endl;
	}
	
	/*!
	 * 	\brief 	Prints a defined phrase with H2 pre-defined styling
	 * 	\param 	std::string phrase : Phrase to print with style
	 */
	void h2(std::string phrase){
		std::cout << "\e[1m";
		std::cout << "\n> ";
		std::cout << phrase << std::endl;
		std::cout << "\e[0m";
	}
}
/*}}}*/

int main( void ){

	/* Special members tests {{{*/
	{
		h::h1("Special members tests");

		{
			h::h2("Empty constructor");
			
			// Declaration
			sc::Vector<int> EmptyVector; 
			std::cout << "EmptyVector object created!\n";

			// Populating
			std::cout << "Populating EmptyVector with push_back()...\n";
			for( int i = 0; i < 10; i++ )
				EmptyVector.push_back(i);

			// Simple print the object
			std::cout << "EmptyVector elements: ";
			client::print_it(EmptyVector, ' ');
		}

		{
			h::h2("Constructor with pre-defined size");

			// Declaration
			sc::Vector<int> SizeVector(10);

			// Populating
			std::cout << "Populating SizeVector with positive values...\n";
			for( int i = 0; i < 10; i++ )
				SizeVector[i] = i;

			// Simple print the object
			std::cout << "SizeVector elements: ";
			client::print_it( SizeVector, ' ' );
		}

		{
			h::h2("Copy constructor from a simple array");

			// Declaration
			int Vet[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
			sc::Vector<int> cVector( Vet, Vet+10 );

			// Simple print
			std::cout << "Copy vector elements: ";
			client::print_it( cVector, ' ' );
		}
		
		{
			h::h2("Copy constructor from another sc::Vector");

			// Declaration
			sc::Vector<int> origVec(10);
			client::populate( origVec );
			sc::Vector<int> copyVec( origVec );

			// Simple print
			std::cout << "Copied vector elements: ";
			client::print_it( copyVec, ' ' );
		}

		{
			h::h2("Object construtor by std::initializer");
			
			// Declaration
			sc::Vector<int> initVec = { 1, 4, 3, 2, 5, 9, 10 };

			// Simple print
			std::cout << "Initializer Vector elements: ";
			client::print_it(initVec, ' ');
		}

		{
			h::h2("Vector destructor");
			// Declaration
			sc::Vector<int> *V = new sc::Vector<int>;
			std::cout << "Vector allocated on " << V << std::endl;
			
			std::cout << "Trying to delete " << V << "..." << std::endl;
			delete V;
			std::cout << "Vector deleted with sucess!\n";
		}
		h::sep();
	}
	/*}}}*/
	
	/* Capacity functions tests {{{*/
	{
		h::h1("Capacity functions tests");
		{
			h::h2("Empty method test");
			// Declaration
			sc::Vector<int> V(10);
			client::populate(V);
			std::cout << "created Vector V with 10 elements\n";
			sc::Vector<int> V_emp;	
			std::cout << "created Vector V_emp with 0 elements\n";

			// tests
			std::cout << "Is V empty? ";
			std::cout << ( V.empty() ? "Yes\n" : "No\n" );
			std::cout << "Is V_emp empty? ";
			std::cout << ( V_emp.empty() ? "Yes\n" : "No\n" );
		}

		{
			h::h2("Size method test");
			// declaration
			sc::Vector<int> V(10);
			std::cout << "Vector V created\n";
			client::populate(V);
			std::cout << "Vector V has " << V.size() << " elements\n";

			sc::Vector<int> V2(40);
			std::cout << "Vector V2 created\n";
			client::populate(V2);
			std::cout << "Vector V2 has " << V2.size() << " elements\n";
		}
		
		{
			h::h2("Capacity method test");
			// declaration
			sc::Vector<int> V(20);	// this should give a capacity of 2^5
			std::cout << "Vector V created with 20 elements\n";
			std::cout << "It should have a capacity of 2^(ceil(log2(20)))\n";
			std::cout << "Capacity: " << V.capacity() << std::endl;
		}

		{
			h::h2("Reserve method test");
			// declaration
			sc::Vector<int> V(20);
			std::cout << "Vector V created with 20 elements at ";
			std::cout << &V << std::endl;
			std::cout << "It has the initial capacity of 2^(ceil(log2(20)))\n";
			std::cout << "V.capacity() = " << V.capacity() << std::endl;
			std::cout << "calling reserve(40)...\n";
			V.reserve(40);	
			std::cout << "V.capacity() = " << V.capacity() << std::endl;
		}
		h::sep();
	}
	/*}}}*/

	/* Modifiers functions tests {{{*/
	{
		h::h1("Modifiers functions tests");

		{
			h::h2("Clear method test");
			// Declaration
			sc::Vector<int> cVec(10);
			client::populate(cVec);
			std::cout << "Vector cVec created and populated ~" << &cVec;	
			std::cout << std::endl << "cVec elements: ";
			client::print_it(cVec, ' ');

			std::cout << "Running clear() on cVec\n";
			cVec.clear();
			std::cout << "cVec.size() = " << cVec.size() << std::endl;
		}

		{
			h::h2("Push_front & push_back method test");
			sc::Vector<int> pVec = {2, 3, 4};
			std::cout << "Vector pVec elements: ";
			client::print_it(pVec, ' ');

			pVec.push_back(99);
			pVec.push_front(-20);

			std::cout << "After push_back & push_front: ";
			client::print_it(pVec, ' ');

		}

		{
			h::h2("Pop_front & pop_backmethod test");
			// Declaration
			sc::Vector<int> pVec = { 2, 2, 2 };
			std::cout << "Vector pVec elements: ";
			client::print_it(pVec, ' ');

			pVec.pop_back();
			pVec.pop_front();

			std::cout << "after pop_front & pop_back: ";
			client::print_it(pVec, ' ');
		}

		{
			h::h2("Insert methods test");

			// Declaration
			sc::Vector<int> iVec(10);
			client::populate(iVec);

			auto it = iVec.begin();
			int Vet[] = { 10, 3, 4, 2, 10, 11 };

			iVec.insert( iVec.begin(), 10 );
			client::print_it( iVec, ' ' );
			iVec.insert( iVec.begin(), std::begin(Vet), std::end(Vet) );
			client::print_it( iVec, ' ' );

			 iVec.insert( iVec.begin(), { 10, 20, 30, 40, 50, 60 } );
			 client::print_it( iVec, ' ' ); 
		}

		{
			h::h2("Shrink_to_fit method test");
			// Declaration
			sc::Vector<int> iVec(10);
			client::populate(iVec);

			iVec.reserve(40);
			std::cout << "iVec capacity: " << iVec.capacity() << std::endl;
			iVec.shrink_to_fit();
			std::cout << "iVec capacity: " << iVec.capacity() << std::endl;
		}

		{
			h::h2("Assign method test");

			sc::Vector<int> iVec(10);
			client::populate(iVec);
			std::cout << "iVec elements: ";
			client::print_it(iVec, ' ');

			sc::Vector<int> aVec(20);
			client::populate(aVec);
			std::cout << "aVec elements: ";
			client::print_it(aVec, ' ');

			 std::cout << "iVec.assign(aVec.begin(), aVec.end()) = ";
			 iVec.assign(aVec.begin(), aVec.end());
			 client::print_it(iVec, ' ');

			std::cout << "iVec.assign(5, 10) = ";
			iVec.assign(5, 10);
			client::print_it(iVec, ' ');

			std::cout << "iVec.assign({ 3, 4, 5, 6, 7, 8 }) = ";
			iVec.assign({ 3, 4, 5, 6, 7, 8 });
			client::print_it(iVec, ' ');
		}

		{
			h::h2("Erase method with iterator");
			sc::Vector<int> iVec(10);
			client::populate(iVec);
			std::cout << "before elements: ";
			client::print_it(iVec, ' ');
			sc::Vector<int>::iterator it = iVec.begin();
			iVec.erase(it);
			iVec.erase( iVec.begin(), iVec.end() - 3);
			std::cout << "after elements: ";
			client::print_it(iVec, ' ');
		}
		h::sep();
	}
	/*}}}*/

	/* Element access functions tests {{{*/
	{
		h::h1("Element access functions tests");
		
		{
			h::h2("Front, back and at method test");
			sc::Vector<int> Vec(10);
			client::populate(Vec);
			std::cout << "Vec elements: ";
			client::print_it(Vec, ' ');
			std::cout << "Vec.front() = " << Vec.front() << std::endl;
			std::cout << "Vec.back() = " << Vec.back() << std::endl;
			std::cout << "Vec.at(2) = " << Vec.at(2) << std::endl;
		}

		h::sep();
	}
	/*}}}*/

	/* Operators tests {{{*/
	{
		h::h1("Operators tests");

		{	
			sc::Vector<int> V = { 1, 3, 2, 5, 4 };
			sc::Vector<int> V2= { 1, 2, 3, 4, 5 };
			sc::Vector<int> V3= { 3, 4, 2 };
			std::cout << "V = ";
			client::print_it(V, ' ');
			std::cout << "V2 = ";
			client::print_it(V2, ' ');

			std::cout << "V == V2? ";
			if( V == V2 ){
				std::cout << "True\n";
			} else {
				std::cout << "False\n";
			}
			std::cout << "V != V2? ";
			if( V != V2 ){
				std::cout << "True\n";
			} else {
				std::cout << "False\n";
			}
		
			std::cout << "Acessing V[3]: " << V[3] << std::endl;
		}
		h::sep();
	}
	/*}}}*/

	/* Iterators tests {{{*/
	{
		h::h1("Iterators tests");
		
		{
			h::h2("Begin & End methods");
			sc::Vector<int> V(10);
			client::populate(V);
			std::cout << "for loop to print elements in the Vector\n";
			std::cout << "\e[2m(in various forms, check the code to see)\e[0m\n";
			for( auto &it : V ){
				std::cout << it << ' ';
			}
			std::cout << std::endl;
			for( auto it = V.begin(); it != V.end(); it++ ){
				std::cout << *it << ' ';
			}
			std::cout << std::endl;
			for( sc::Vector<int>::iterator it = V.begin(); it != V.end(); ++it ){
				std::cout << *it << ' ';
			}

			std::cout << std::endl;
			std::cout << "\nConst print: (if we try to change a value, it get's ";
			std::cout << "a compilation error)\n";
			for( sc::Vector<int>::const_iterator it = V.cbegin(); it != V.cend(); ++it ){
				std::cout << *it << ' ';
			}
			std::cout << std::endl;
		}

		h::sep();
	}
	/*}}}*/

	std::cout << "\nEnd of the driver code." << std::endl;
	std::cout << "Authors: Felipe Ramos and Max William\n" << std::endl;
	return 1;
}

