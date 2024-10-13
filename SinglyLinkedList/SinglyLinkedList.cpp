//============================================================================
// Author       : Sebahadin Denur
// Version      : 1.0
// Date Created : 11\02\2024
// Date Modified: 
// Description  : Singly Linked-List implementation in C++
//============================================================================
#include<iostream>
#include<string>
#include<fstream>
#include<exception>
#include<sstream>
using namespace std;
//====================================
class Node
{
	private:
		int elem; //data element 
		Node* next; //Link (pointer) to the next Node
		
	public:
		Node(int elem) : elem(elem), next(NULL)
		{}
		friend class MyLinkedList ;
};


//=====================================
class MyLinkedList
{
	private:
		Node* head; // pointer to the head of list
	public:
		MyLinkedList (); // empty list constructor
		~MyLinkedList (); // destructor to clean up all nodes
		bool empty() const; // is list empty?
		void addFront(int elem); // add a new Node at the front of the list
		void removeFront(); // remove front Node from the list
		void remove(int elem);	 // remove the first occurrence of an element of the list, if the element exists.
		unsigned int countElem(int elem) const; //count frequency of an element in the list
		int getIndexOf(int elem) const; //returns first index of an element in the list, -1 if the element is not present
		void display() const;
		void readData(string); //read a file and load it into the linked list
		void writeData(string) const; //write the linked list to a file
};
//=====================================
void listCommands()
{
	cout<<"List of available Commands:"<<endl
		<<"display            : Display the Linked List"<<endl
		<<"addFront <element> : Add <element> to the front of the Linked List"<<endl
		<<"removeFront        : Remove the front node of the Linked List"<<endl
		<<"remove        	  : Remove the first occurrence of an element of the list (if exists)"<<endl
		<<"count <element>    : count frequency of an element in the list"<<endl
		<<"indexOf <element>  : return first index of an element in the list (-1 of not present)"<<endl
		<<"read <file_name>   : Load the data from <file> and add it into the Linked List"<<endl
		<<"write <file_name>   : Dump the contents of the Linked list to <file>"<<endl
		<<"help               : Display the list of available commands"<<endl
		<<"exit               : Exit the Program"<<endl;
}
//=======================================
// main function
int main()
{
	MyLinkedList myList;

	listCommands();
	string user_input;
	string command;
	string parameter;

	do
	{
		cout<<">";
		getline(cin,user_input);
		
		// parse user input into command and parameter(s)
		stringstream sstr(user_input);
		getline(sstr,command,' ');
		getline(sstr,parameter);
		
		if(command=="display") 				myList.display();
		else if(command=="addFront" or command=="af")				myList.addFront(stoi(parameter)),myList.display();
		else if(command=="removeFront" or command=="rf")			myList.removeFront(),myList.display();
		else if(command=="remove" or command=="r")         			myList.remove(stoi(parameter)),myList.display();
		else if(command=="count")			cout<<parameter<<" occurs "<<myList.countElem(stoi(parameter))<<" time(s) in the list"<<endl;
		else if(command=="indexOf")         cout<<"First index of "<<parameter<<" in the list is: "<<myList.getIndexOf(stoi(parameter))<<endl;
		else if(command=="read")			myList.readData(parameter),myList.display();
		else if(command == "write")			myList.writeData(parameter);
		else if(command == "help")			listCommands();
		else if(command == "exit")			break;
		else 								cout<<"Invalid Commad !!"<<endl;
	}while(command!="exit");

	return EXIT_SUCCESS;
}
//====================================
// constructorMyLinkedList::MyLinkedList ()
MyLinkedList::MyLinkedList ()
{
    // Constructor initializes the head pointer to NULL
    this->head = NULL;
}

//====================================
// Destructor to clean up all nodes
MyLinkedList::~MyLinkedList ()
{
    // Remove nodes until the list is empty
    while(!empty()){
        removeFront();
    }
}

//====================================
// Check if the list is empty or not
bool MyLinkedList::empty() const
{
    // Returns true if the head pointer is NULL, indicating an empty list
    if(head != NULL){
        return false;
    }
    return true;
}

//====================================
// Add a node at the front of the list
void MyLinkedList::addFront(int elem)
{
    // If the list is empty, create a new node and set it as the head
    if (head == NULL){
        head = new Node(elem);
    }
    else{
        // Create a new node, set its next pointer to the current head, and update the head
        Node* ptr = new Node(elem);
        ptr->next = head;
        head = ptr;
    }
}

//====================================
// Remove the first node from the list
void MyLinkedList::removeFront()
{
    // Check if the list is empty before attempting to remove the front node
    if(empty()){
        cout<<"The list is empty, cannot remove front"<<endl;
    }
    else{
        // Save the next node, delete the current head, and update the head
        Node* temp = head->next;
        delete head;
        head = temp;
    }
}

//=====================================
// Remove the first occurrence of an element from the list, if the element exists
void MyLinkedList::remove(int elem)
{
    // Check if the list is empty
    if (empty())
    {
        cout << "Couldn't remove item. The list is empty" << endl;
    }
    else
    {
        // Find the index of the element
        int elem_index = getIndexOf(elem);
        bool itemfound = false;

        if (elem_index == 0 && head != NULL)
        {
            // If the element is at the front, remove the front node
            cout << "First occurrence of " << head->elem << " has been successfully deleted from the list" << endl;
            itemfound = true;
            removeFront();
        }
        else
        {
            // Traverse the list to find the element and remove it
            Node *ptr = head;
            int count = -1;

            while (ptr != NULL)
            {
                count++;
                if (count == elem_index - 1)
                {
                    // Save the next node, update pointers, and delete the target node
                    Node *temp = ptr->next;
                    ptr->next = temp->next;
                    cout << "First occurrence of " << temp->elem << " has been successfully deleted from the list" << endl;
                    itemfound = true;
                    delete temp;
                    break;
                }
                ptr = ptr->next;
            }
        }

        // Display a message if the element was not found in the list
        if (!itemfound)
        {
            cout << elem << " is not in the list" << endl;
        }
    }
}

//====================================
// Count the frequency of an element in the list
unsigned int MyLinkedList::countElem(int elem) const
{
    // Traverse the list and count occurrences of the given element
    Node* ptr = head;
    unsigned int count = 0;
    
    while(ptr != NULL){
        if(ptr->elem == elem){
            count++;
        }
        
        ptr = ptr->next;
    }
    
    return count;
}

//==============================================
// Get the first index of an element in the list.
// Returns -1 if the element is not present
int MyLinkedList::getIndexOf(int elem) const
{
    // Traverse the list and find the index of the first occurrence of the element
    Node* ptr = head;
    int index = -1;
    bool elem_exists = false;
    
    while(ptr != NULL){
        index++;
        if(ptr->elem == elem){
            elem_exists = true;
            break;
        }
        ptr = ptr->next;
    }
    
    // Return -1 if the element is not present, otherwise, return the index
    if(elem_exists)
        return index;
    else return -1;
}

//==============================================
// Display all nodes of the linked list
void MyLinkedList::display() const
{
    // Traverse the list and display each node's element
    Node* ptr;
    cout<<"head";
    for(ptr = head; ptr!=NULL;ptr = ptr->next){
        cout<<"->"<<ptr->elem;
    }
    cout<<"->NULL"<<endl;
}

//==============================================
// Load data from a file and add it to the Linked List
void MyLinkedList::readData(string path)
{
    int data=0;
    ifstream infile(path);
    
    // Check if the file exists
    if(infile.fail()){
        cout<<"File does not exist"<<endl;
    }
    else{
        // Read data from the file and add it to the front of the list
        while(!infile.eof()){
            infile>>data;
            addFront(data);
        }
    }
    infile.close();
}

//=============================================
// Dump/write the contents of the list to a file
void MyLinkedList::writeData(string path) const
{
    // Check if the list is empty
    if(empty())
    {
        cout<<"List is empty"<<endl;
    }
    else{
        // Write the elements of the list to the specified file
        ofstream out(path);
        if(out.fail()){
            cout<<"Couldn't write into the file"<<endl;
        }
        else{
            Node* ptr = head;
            int num(0);
            while(ptr != NULL){
                // Write the current element to the file
                out<<ptr->elem<<endl;
                num++;
                ptr = ptr->next;
            }
            cout<<num<<" records have been exported to "<<path<<endl;
        }
        
        out.close();
    }
}

//==================================================
