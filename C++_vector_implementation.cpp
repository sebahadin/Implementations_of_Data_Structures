//============================================================================
// Name         : MyVector.cpp
// Author       : Sebahadin Aman Denur
// Version      : 1.0
// Date Created : 25/03/2024
// Date Modified: 
// Description  : Vector implmentation in C++
//============================================================================

#include<iostream>
#include<cstdlib>
#include<iomanip>
#include <stdexcept>
#include<sstream>

using namespace std;

template <typename T>
class MyVector
{
	private:
		T *data;						//pointer to int(array) to store elements
		int v_size;						//current size of vector (number of elements in vector)
		int v_capacity;					//capacity of vector
	public:
		MyVector(int cap=0);			//Constructor
		~MyVector();					//Destructor
		int size() const;				//Return current size of vector
		int capacity() const;			//Return capacity of vector
		bool empty() const; 			//Rturn true if the vector is empty, False otherwise
		const T& front();				//Returns reference of the first element in the vector
		const T& back();				//Returns reference of the Last element in the vector
		void push_back(T element);		//Add an element at the end of vector
		void insert(int index, T element); //Add an element at the index 
		void erase(int index);			//Removes an element from the index
		T& operator[](int index);			//Returns the reference of an element at given index
		T& at(int index); 				//return reference of the element at given index
		void shrink_to_fit();			//Reduce vector capacity to fit its size
		void display();
};

void listCommands()
{
	cout<<"List of available Commands:"<<endl
		<<"display                  : Display the Vector"<<endl
		<<"push_back <element>      : Add an element to the end of the vector"<<endl
		<<"insert <index element>   : Insert an element at location index"<<endl
		<<"erase <index>            : Remove the element from index"<<endl
		<<"[index]                  : Returns a reference to an element at a specified index"<<endl
		<<"at <index>               : Returns a reference to an element at a specified index"<<endl
		<<"front                    : Return the (reference of) front element"<<endl
		<<"back                     : Returns a reference to the last element of the vector"<<endl
		<<"size                     : Returns the number of elements in the vector"<<endl
		<<"capacity                 : Returns the capacity of vector"<<endl
		<<"empty                    : Tests if the vector container is empty"<<endl
		<<"shrink                   : Reduce vector capacity to fit its size (shrink_to_fit)"<<endl
		<<"exit/quit                : Exit the Program"<<endl;
}
//=======================================
//#include "unittests.h"
//=======================================
int main()
{

	MyVector<int> myVector;
	//unitTest();
	string user_input;
	string command;
	string parameter1;
	string parameter2;
	listCommands();

	do
	{
		cout<<">";
		getline(cin,user_input);

		// parse userinput into command and parameter(s)
		stringstream sstr(user_input);
		getline(sstr,command,' ');
		getline(sstr,parameter1,' ');
		getline(sstr,parameter2);

		try
		{
			if(command=="display" or command=="d") 							myVector.display();
			else if(command=="push_back" or command=="p" )					myVector.push_back(stoi(parameter1)),myVector.display();
			else if(command=="insert" or command=="i")		    			myVector.insert(stoi(parameter1),stoi(parameter2)),myVector.display();
			else if(command=="erase" or command=="e")		    			myVector.erase(stoi(parameter1)),myVector.display();
			else if(command=="at" or command=="a")			    			cout<<myVector.at(stoi(parameter1))<<endl;
			else if(command[0]=='[' and command[command.length()-1]==']') 	cout<<myVector[stoi(command.substr(1,command.length()-2)+"")]<<endl;
			else if(command=="front" or command=="f")			cout<<myVector.front()<<endl;
			else if(command=="back" or command=="b")			cout<<myVector.back()<<endl;
			else if(command=="size" or command=="s")            cout<<myVector.size()<<endl;
			else if(command=="capacity" or command=="c")        cout<<myVector.capacity()<<endl;
			else if(command=="empty" or command=="e")			cout<<boolalpha<<myVector.empty()<<endl;
			else if(command=="shrink")          				myVector.shrink_to_fit(),myVector.display();
			else if(command == "help" or command=="?")			listCommands();
			else if(command == "exit" or command=="quit")			break;
			else 								cout<<"Invalid Commad !!"<<endl;
		}
		catch(exception &e)
		{
			cout<<"Exception: "<<e.what()<<endl;
		}

	}while(command!="exit" and command!="quit");

	return EXIT_SUCCESS;
}
//======================================
#ifndef _WIN32
//======================================
template <typename T>
void MyVector<T>::display()
{
	cout<<"╔";
	
	for(int i=0; i<v_capacity; i++)
	{	
		cout<<"════";
		if(i!=v_capacity-1) cout<<"╦";
	}
	cout<<"╗ size = "<<v_size<<endl;
	
	for(int i=0; i<v_capacity; i++)
	{
		cout<<"║";
		if(i<v_size)
			cout<<setw(4)<<data[i];
		else
			cout<<setw(4)<<" ";		
	}
	if(v_capacity==0) cout<<"║";
	cout<<"║"<<endl<<"╚";
	for(int i=0; i<v_capacity; i++)
	{
		cout<<"════";
		if(i != v_capacity-1) cout<<"╩";
	}
	cout<<"╝ capacity = "<<v_capacity<<endl;	
}
//======================================
#else
template <typename T>
void MyVector<T>::display()
{
	cout<<"+";
	
	for(int i=0; i<v_capacity; i++)
	{	
		cout<<"----";
		if(i!=v_capacity-1) cout<<"+";
	}
	cout<<"+ size = "<<v_size<<endl;
	
	for(int i=0; i<v_capacity; i++)
	{
		cout<<"|";
		if(i<v_size)
			cout<<setw(4)<<data[i];
		else
			cout<<setw(4)<<" ";		
	}
	if(v_capacity==0) cout<<"|";
	cout<<"|"<<endl<<"+";
	for(int i=0; i<v_capacity; i++)
	{
		cout<<"----";
		if(i != v_capacity-1) cout<<"+";
	}
	cout<<"+ capacity = "<<v_capacity<<endl;	
}
#endif


// Custom exception class for empty vector
class VectorEmpty : public exception
{
public:
    // Override what() method to return error message
    virtual const char * what() const throw()
    {
        return "Vector is empty"; // Return error message
    }
};



// Constructor for MyVector class
template <typename T>
MyVector <T>::MyVector(int cap)
{
    v_size = 0; // Initialize vector size to 0
    v_capacity = cap; // Set vector capacity
    data = new T [v_capacity]; // Allocate memory for data array
}

// Destructor for MyVector class
template <typename T>
MyVector <T> :: ~MyVector()
{
    delete [] data; // Deallocate memory for data array
}

// Method to return the current size of the vector
template <typename T>
int MyVector <T> :: size() const
{
    return v_size; // Return the size of the vector
}

// Method to return the capacity of the vector
template <typename T>
int MyVector <T>:: capacity() const
{
    return v_capacity; // Return the capacity of the vector
}

// Method to check if the vector is empty
template <typename T>
bool MyVector <T> :: empty() const
{
    return v_size == 0; // Return true if vector is empty, false otherwise
}

// Method to return a reference to the first element of the vector
template <typename T>
const T& MyVector <T> :: front()
{
    if (empty()) // Check if the vector is empty
    {
        throw VectorEmpty(); // Throw exception if vector is empty
    }
    else
    {
        return data[0]; // Return reference to the first element
    }
}

// Method to return a reference to the last element of the vector
template <typename T>
const T& MyVector <T> :: back()
{
    if (empty()) // Check if the vector is empty
    {
        throw VectorEmpty(); // Throw exception if vector is empty
    }
    else
    {
        return data[v_size-1]; // Return reference to the last element
    }
}

// Method to add an element to the end of the vector
template <typename T>
void MyVector <T> :: push_back(T element)
{
    if (v_size == v_capacity) // Check if vector is full
    {
        if (v_capacity == 0) // If capacity is 0
        {
            data = new T(element); // Create a new element
            v_size++; // Increment vector size
            v_capacity++; // Increment vector capacity
        }
        else // If capacity is not 0
        {
            T* temp = new T[v_capacity * 2]; // Create temporary array with doubled capacity
            
            for (int i = 0; i < v_size; i++) // Copy elements to temporary array
            {
                temp[i] = data[i];
            }
            
            delete [] data; // Deallocate memory for current array
            data = temp; // Update data pointer
            data[v_size] = element; // Add new element
            v_size++; // Increment vector size
            v_capacity = v_capacity * 2; // Double vector capacity
        }
    }
    else // If vector has space
    {
        data[v_size] = element; // Add element to vector
        v_size++; // Increment vector size
    }
}



// Method to insert an element at a specified index in the vector
template <typename T>
void MyVector <T> :: insert(int index, T element)
{
    if (index < 0 || index > v_size - 1) // Check if index is out of range
    {
        throw out_of_range("Vector index out of range"); // Throw exception if index is out of range
    }
    else
    {
        if (v_size == v_capacity) // Check if vector is full
        {
            T* temp = new T[v_capacity * 2]; // Create temporary array with doubled capacity
            
            for (int i = 0; i <= v_size; i++) // Copy elements to temporary array
            {
                if (index == i) // Insert element at specified index
                {
                    temp[i] = element;
                }
                else if (index > i) // Copy elements before index
                {
                    temp[i] = data[i];
                }
                else // Copy elements after index and shift right
                {
                    temp[i] = data[i - 1];
                }
            }
            
            delete [] data; // Deallocate memory for current array
            data = temp; // Update data pointer
            v_size++; // Increment vector size
            v_capacity = v_capacity * 2; // Double vector capacity
        }
        else // If vector has space
        {
            T temp = data[index]; // Store the element at the specified index
            data[index] = element; // Insert new element at specified index
            
            for(int i = index + 1 ; i <= v_size; i++) // Shift elements to the right
            {
                T temp2 = data[i];
                data[i] = temp;
                temp = temp2;
                
            }
            v_size++; // Increment vector size
        }
    }
}

// Method to erase an element at a specified index from the vector
template <typename T>
void MyVector <T> ::erase(int index)
{
    if (index < 0 || index > v_size - 1) // Check if index is out of range
    {
        throw out_of_range("Vector index out of range"); // Throw exception if index is out of range
    }
    else
    {
        for (int i = index ; i < v_size - 1; i++) // Shift elements to the left
        {
            data[i] = data[i+1];
        }
        v_size--; // Decrement vector size
    }
}

// Operator overloading to access elements using []
template <typename T>
T& MyVector <T> :: operator[](int index)
{
    return data[index]; // Return reference to element at index
}

// Method to access element at a specified index in the vector
template <typename T>
T& MyVector <T> :: at(int index)
{
    if (index < 0 || index > v_size - 1) // Check if index is out of range
    {
        throw out_of_range("Vector index out of range"); // Throw exception if index is out of range
    }
    else
    {
        return data[index]; // Return reference to element at index
    }
}

// Method to reduce vector capacity to fit its size
template <typename T>
void MyVector <T> :: shrink_to_fit()
{
    if (v_capacity > v_size) // Check if capacity is greater than size
    {
        T* temp = new T[v_size]; // Create temporary array with size equal to vector size
        
        for(int i = 0 ; i < v_size; i++) // Copy elements to temporary array
        {
            temp[i] = data[i];
        }
        
        delete [] data; // Deallocate memory for current array
        data = temp; // Update data pointer
        v_capacity = v_size; // Set capacity equal to size
    }
}

