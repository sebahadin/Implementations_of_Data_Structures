/**
 * @file lab5.cpp
 * @author Sebahadin Denur
 * @description This program convert an Infix expression to PostFix and then evaluate it
 * @date 04/03/2024
 */
//starter_code_begins
#include<iostream>
#include<string>
#include<exception>
#include<math.h>
#include<ctype.h>

using namespace std;

template <typename T>

class Mystack{
private:
    int max;
    int top_index;
    T* arr;
public:
    
    Mystack(int size);
    ~Mystack();
    void push(T elem);
    T pop();
    const T& top();
    bool empty();
    int size();
    
};


bool isOperator(char); //Function that checks if the input char is an operator
bool isgeq(char, char); //Helper function that compare two operators  and return True if the presedence of first operator is greater than or equal to the second operator
int convertOpToInt (char); //Function that converts operators into int so their precdence can be compared
string infix2postfix(string);   //Function that converts an infix notaiton into a postfix notation (lab4)
float evaluate(string postfix);     //Function that will evaluate a PostfixExpression and return the result
bool isBalanced(string expression); // Funciton that will check for balanced parentheses
//==========================================
int main()
{

    while(true)
    {
        string infix;
        //Infix expression
        cout<<"Enter an Infix Expression: ";
        cin>>infix;
        try
        {
            if(infix=="exit")
                break;
            
            else if(!isBalanced(infix))
            {
                cout<<"Expression is not Balanced "<<endl;
                continue;
            }

            string postfix = infix2postfix(infix);    //Postfix Expression
            cout<<"The postfix form is: "<<postfix<<endl;
            float ans=evaluate(postfix);            //evaluate the postfix Expresion
            cout<<infix<<"="<<ans<<endl;        //print the final answer
        }
        catch(exception &e)
        {
            cout<<"Exception: "<<e.what()<<endl;
        }
    }

    return EXIT_SUCCESS;
}


bool isOperator(char ch)
{
    if( ch=='+' || ch=='-' || ch=='*' || ch=='/' || ch=='^')
        return true;
    else
        return false;
}
//Function that converts operators into int so their precdence can be compared
int convertOpToInt (char ch)
{
    if (ch=='+' || ch=='-') return 1;
    if (ch=='*' || ch=='/') return 2;
    if (ch=='^') return 3;
    return 0;
}
//Helper method that compare two operators and return True if first operator
//has greater or equal predence than the second operator
bool isgeq(char opA, char opB)
{
    return (convertOpToInt(opA)>=convertOpToInt(opB));
}
//starter_code_ends

//===============================================================================
//Define MyStack Class here
//===============================================================================


// Function that will check for balanced parentheses
bool isBalanced(string expression)
{
    int size = expression.size();   // Get the size of the input expression
    
    Mystack<char>  s1(size);    // Create a character stack using Mystack class
    
    int i = 0;
    while (i < size) {
        
        char ch = expression[i];   // Retrieve the current character in the expression
        if (ch == '(')
        {
            s1.push(ch);   // Push '(' onto the stack if encountered
        }
        else if(ch == ')')
        {
            if (s1.empty())
            {
                return false;   // If ')' is encountered and the stack is empty, the expression is unbalanced
            }
            else
            {
                s1.pop();   // Pop '(' from the stack for a matching ')'
            }
        }
        i++;
    }
    
    if (s1.empty()) return true;   // If the stack is empty at the end, the expression is balanced
    return false;
}



// Function that converts an Infix Notation to a Postfix notation
string infix2postfix(string infix)
{
    if (!isBalanced(infix))
    {
        throw runtime_error("Error!! the provided argument is not valid!!");
    }
    else
    {
        int size = infix.size();   // Get the size of the input infix expression
        Mystack<char> s1(size);    // Create a character stack using Mystack class
        string postfix = "";      // Initialize an empty string to store the postfix expression

        for (int i = 0; i < size; i++)
        {
            char ch = infix[i];   // Retrieve the current character in the infix expression

            if (ch == '(')
            {
                s1.push(ch);   // Push '(' onto the stack if encountered
            }
            else if (isOperator(ch))
            {
                if(s1.empty())
                {
                    s1.push(ch);   // If stack is empty, push the operator onto the stack
                }
                else
                {
                    while (!s1.empty() && isgeq(s1.top(), ch))
                    {
                        postfix += s1.pop();   // Pop operators from the stack and append to postfix until a lower precedence operator is encountered
                    }
                    s1.push(ch);   // Push the current operator onto the stack
                }
            }
            else if (ch == ')')
            {
                do
                {
                    ch = s1.pop();   // Pop operators from the stack and append to postfix until '(' is encountered
                    if(ch != '(')
                        postfix += ch;
                }while ((ch != '(') && !s1.empty());
            }
            else
            {
                postfix += ch;   // If the character is an operand, append it to the postfix expression
            }
        }
        while (!s1.empty())
        {
            postfix += s1.pop();   // Pop any remaining operators from the stack and append to postfix
        }
        
        return postfix;   // Return the final postfix expression
    }
}

// Function that will evaluate a PostfixExpression and return the result
float evaluate(string postfix)
{
    int size = postfix.size();   // Get the size of the postfix expression
    Mystack<float> s1(size);     // Create a float stack using Mystack class
    
    for(int i = 0; i < size; i++)
    {
        char ch = postfix[i];   // Retrieve the current character in the postfix expression
        
        if (!isOperator(ch)){
            s1.push(float(ch - '0'));  // Convert char to int and push operands onto the stack
        }
        else
        {
            float b = s1.pop();   // Pop the second operand
            float a = s1.pop();   // Pop the first operand
            float value = 0;
            
            switch (ch) {
                case '+':
                    value = a + b;   // Perform addition
                    break;
                case '-':
                    value = a - b;   // Perform subtraction
                    break;
                case '*':
                    value = a * b;   // Perform multiplication
                    break;
                case '/':
                    value = a / b;   // Perform division
                    break;
                case '^':
                    value = pow(a, b);   // Perform exponentiation
                    break;
            }
            
            s1.push(value);   // Push the result back onto the stack
        }
    }
    return s1.pop();   // Return the final result of the postfix expression
}


// Template class implementation for Mystack

// Constructor for Mystack class
template <typename T>
Mystack<T>::Mystack(int size)
{
    max = size;             // Set the maximum size of the stack
    top_index = -1;         // Initialize the top index to -1 (empty stack)
    arr = new T[max];       // Allocate memory for the stack array
}

// Destructor for Mystack class
template <typename T>
Mystack<T>::~Mystack()
{
    delete [] arr;          // Deallocate memory used for the stack array
}

// Function to push an element onto the stack
template <typename T>
void Mystack<T>::push(T elem)
{
    if(top_index == max-1)
    {
        throw runtime_error("Couldn't push the element, stack is full");   // Throw an error if the stack is full
    }
    else
    {
        top_index++;          // Increment the top index
        arr[top_index] = elem; // Push the element onto the stack
    }
}

// Function to check if the stack is empty
template <typename T>
bool Mystack<T>::empty()
{
    return top_index == -1;   // Return true if the top index is -1 (empty stack)
}

// Function to pop an element from the stack
template <typename T>
T Mystack<T>::pop()
{
    if(empty())
    {
        throw runtime_error("Error!! The stack is empty");   // Throw an error if the stack is empty
    }
    else
    {
        return arr[top_index--];   // Return the top element and decrement the top index
    }
}

// Function to get the top element of the stack without popping
template <typename T>
const T& Mystack<T>::top()
{
    if(empty())
    {
        throw runtime_error("Error!! The stack is empty");   // Throw an error if the stack is empty
    }
    else
    {
        return arr[top_index];   // Return the top element of the stack
    }
}

// Function to get the size of the stack
template <typename T>
int Mystack<T>::size()
{
    return top_index + 1;   // Return the size of the stack (number of elements)
}
