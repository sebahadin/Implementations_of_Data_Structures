/**
 * @author Sebahadin Denur
 * @description Doubly LinkedList implementation in C++
 * @date 2024-02-19
 */
#include<iostream>
#include<string>
#include<sstream>
#include<iomanip>
using namespace std;


class Node
{
private:
        string elem; //data element (type string in this case)
        Node* next; //Link (pointer) to the next Node
        Node* prev; //Link (pointer) to the previous Node
        friend class DoublyLinkedList;
        
    public:
        Node(): next(NULL), prev(NULL)
        {}
        Node(string elem) : elem(elem),next(NULL), prev(NULL)
        {}
};
//==============================================================
class DoublyLinkedList
{
    private:
        Node* head;     // pointer to the head of List
        Node* tail;     // pointer to the tail of List
    public:
        DoublyLinkedList (); // constructor to create dummy head and tail nodes
        ~DoublyLinkedList (); // destructor to clean up all nodes
        bool isEmpty() const; // return true if the list is empty
        const string& front() const; // returns the const reference of the element from the first valid Node of list, throw an exception if the list is empty
        const string& back() const;  // returns the const reference of the element from last valid Node of the list, throw an exception if the list is empty
        void addFront(const string& elem); // add a new node to the front of list (after head)
        void addBack(const string & elem); //add a new node to the back of the list (before tail)
        void removeFront(); // remove front node from list, throw an exception if the list is empty
        void removeBack();  // remove last node from list, throw an exception if the list is empty
        void reverseList();    // reverse the list
        bool isPalindrome() const; //return true if the list is Palindrome, false otherwise
        void display() const;    // display all element of the list
};
//===================================
void listCommands()
{
    cout<<"List of available Commands:"<<endl
        <<"display            : Display the Doubly Linkled List"<<endl
        <<"front              : Display the first element of the List"<<endl
        <<"back               : Display the last element of the List"<<endl
        <<"addFront <elem>    : Add a new Node at the begining of the List"<<endl
        <<"addBack  <elem>    : Add a new Node at the end of the List"<<endl
        <<"removeFront        : Remove the first Node of the Linked List"<<endl
        <<"removeBack         : Remove the last  Node of the Linked List"<<endl
        <<"isEmpty            : Check if the List is empty?"<<endl
        <<"reverse            : Reverse the Linked List"<<endl
        <<"isPalindrome       : Check if the List is Palindrome or not?"<<endl
        <<"help               : Display the list of available commands"<<endl
        <<"exit               : Exit the Program"<<endl;
}
//===================================
int main()
{
    DoublyLinkedList myList;
    listCommands();
    string user_input;
    string command;
    string parameter;


    do
    {
        cout<<">";
        getline(cin,user_input);

        // parse userinput into command and parameter(s)
        stringstream sstr(user_input);
        getline(sstr,command,' ');
        getline(sstr,parameter);

        try
        {
            if(command=="display" or command=="d")                 myList.display();
            else if(command=="front" or command=="f")            cout<<"Front = "<<myList.front()<<endl;
            else if(command=="back" or command=="b")            cout<<"Back = "<<myList.back()<<endl;
            else if(command=="addFront" or command=="af")        myList.addFront(parameter),myList.display();
            else if(command=="addBack"    or command=="ab")        myList.addBack(parameter),myList.display();
            else if(command=="removeFront" or command=="rf")    myList.removeFront(),myList.display();
            else if(command=="removeBack" or command=="rb")        myList.removeBack(),myList.display();
            else if(command=="isEmpty"    or command=="ise")        cout<<"List is "<<(myList.isEmpty()? "Empty":"Not Empty")<<endl;
            else if(command=="reverse"    or command=="r")        myList.reverseList(),myList.display();
            else if(command=="isPalindrome" or command=="isp")    cout<<"List is "<<(myList.isPalindrome()? "Palindrome":"Not Palindrome")<<endl;
            else if(command == "help" or command=="h")            listCommands();
            else if(command == "exit" or command=="e")            break;
            else                                                 cout<<"Invalid Commad !!"<<endl;
        }
        catch(exception &e)
        {
            cout<<"Exception: "<<e.what()<<endl;
        }

    }while(command!="exit" and command!="quit");

    return EXIT_SUCCESS;
}
//============================================================
#ifdef _WIN32
void DoublyLinkedList::display() const
{
    Node *curr=head;
    while(curr!=NULL)
    {
        cout<<"+------";
        curr=curr->next;
    }
    cout<<"+"<<endl<<"|";
    curr=head;
    while(curr!=NULL)
    {
        if (curr == head)        cout<<" Head |";
        else if(curr == tail)    cout<<" Tail |";
        else                     cout<<setw(5)<<curr->elem<<" |";
    
        curr=curr->next;
    }
    curr=head;
    cout<<endl;
    while(curr!=NULL)
    {
        cout<<"+------";
        curr=curr->next;
    }
    cout<<"+"<<endl;
}
//====================================================================
#else
void DoublyLinkedList::display() const
{
    Node *curr=head;
    while(curr!=NULL)
    {
        cout<<"╔══════╗    ";
        curr=curr->next;
    }
    cout<<endl<<"║";
    curr=head;
    while(curr!=NULL)
    {
        if (curr == head)        cout<<" Head ║<══>║";
        else if(curr == tail)    cout<<" Tail ║";
        else                     cout<<setw(6)<<curr->elem<<"║<══>║";
    
        curr=curr->next;
    }
    curr=head;
    cout<<endl;
    while(curr!=NULL)
    {
        cout<<"╚══════╝    ";
        curr=curr->next;
    }
    cout<<endl;
}
#endif
//===========================================================
//Constructor to create Sentinel (dummy) nodes
DoublyLinkedList::DoublyLinkedList ()
{
    //create two dummy nodes for the head and tail
    head = new Node;
    tail = new Node;
    
    head->next = tail;
    tail->prev = head;

}
//============================================================
// Destructor to clean up all nodes in the DoublyLinkedList
DoublyLinkedList::~DoublyLinkedList()
{
    Node* temp = head; // Initialize a temporary pointer to the head of the list
    Node* temp2;       // Temporary pointer to store the next node

    // Iterate through each node in the list
    while (temp != NULL)
    {
        temp2 = temp->next; // Store the next node before deleting the current node
        delete temp;        // Delete the current node
        temp = temp2;       // Move to the next node in the list
    }
}

//============================================================
// Check if the list is empty
bool DoublyLinkedList::isEmpty() const
{
    // If head's next points to tail, the list is empty
    if (head->next == tail)
        return true;
    
    // If head's next does not point to tail, the list is not empty
    return false;
}

    
//============================================================
// Return a const reference to the front element of the list
const string& DoublyLinkedList::front() const
{
    // Check if the list is empty
    if (isEmpty()) {
        // If empty, throw an exception indicating that the list is empty
        throw runtime_error("The list is empty");
    } else {
        // If not empty, retrieve and return the element of the first valid node
        Node* ptr = head->next;
        return ptr->elem;
    }
}

// Return a const reference to the back element of the list
const string& DoublyLinkedList::back() const
{
    // Check if the list is empty
    if (isEmpty()) {
        // If empty, throw an exception indicating that the list is empty
        throw runtime_error("List is empty");
    } else {
        // If not empty, retrieve and return the element of the last valid node
        Node* ptr = tail->prev;
        return ptr->elem;
    }
}

// Add a new node with the specified element to the front of the list
void DoublyLinkedList::addFront(const string& elem)
{
    // Create a new node with the specified element
    Node* new_node = new Node(elem);
    // Get the current first node in the list
    Node* temp = head->next;

    // Update pointers to insert the new node at the front
    new_node->next = temp;
    new_node->prev = head;
    
    temp->prev = new_node;
    
    head->next = new_node; // Update the head's next pointer to the new node
}

// Add a new node with the specified element to the back of the list
void DoublyLinkedList::addBack(const string& elem)
{
    // Create a new node with the specified element
    Node* new_node = new Node(elem);
    // Get the current last node in the list
    Node* temp = tail->prev;

    // Update pointers to insert the new node at the back
    new_node->prev = temp;
    new_node->next = tail;
    
    temp->next = new_node;

    tail->prev = new_node; // Update the tail's prev pointer to the new node
}

//============================================================
// Remove the front node from the list
void DoublyLinkedList::removeFront()
{
    // Check if the list is not empty
    if (!isEmpty())
    {
        Node* temp1, * temp2;

        // Get the first and second nodes in the list
        temp1 = head->next;
        temp2 = temp1->next;

        // Update pointers to remove the first node
        head->next = temp2;
        temp2->prev = head;

        // Delete the first node
        delete temp1;
    }
    else
    {
        // If the list is empty, throw an exception
        throw runtime_error("List is empty");
    }
}

// Remove the last node from the list
void DoublyLinkedList::removeBack()
{
    // Check if the list is not empty
    if (!isEmpty())
    {
        Node* temp1, * temp2;

        // Get the last and second-to-last nodes in the list
        temp1 = tail->prev;
        temp2 = temp1->prev;

        // Update pointers to remove the last node
        tail->prev = temp2;
        temp2->next = tail;

        // Delete the last node
        delete temp1;
    }
    else
    {
        // If the list is empty, throw an exception
        throw runtime_error("List is empty");
    }
}

// Reverse the list
void DoublyLinkedList::reverseList()
{
    // Check if the list is not empty
    if (!isEmpty())
    {
        Node* current = head->next;
        Node* temp;

        // Swap next and prev pointers for all nodes in the list
        while (current != tail)
        {
            temp = current->next;
            current->next = current->prev;
            current->prev = temp;

            current = temp;
        }

        // Swap head and tail pointers
        temp = head->next;
        head->next = tail->prev;
        tail->prev = temp;

        // Adjust next and prev pointers of the head and tail
        head->next->prev = head;
        tail->prev->next = tail;
    }
    else
    {
        // If the list is empty, throw an exception
        throw runtime_error("List is empty");
    }
}

// Check if the list is a palindrome
bool DoublyLinkedList::isPalindrome() const
{
    // Check if the list is not empty
    if (isEmpty())
    {
        // If the list is empty, throw an exception
        throw runtime_error("List is empty");
    }
    else
    {
        Node* temp1 = head->next;
        Node* temp2 = tail->prev;

        // Iterate through the list to check for palindrome property
        while (true)
        {
            if (temp1->elem != temp2->elem)
            {
                return false;
            }

            if (temp1 == temp2 || temp2->prev == temp1)
            {
                break;
            }

            temp1 = temp1->next;
            temp2 = temp2->prev;
        }

        // If the loop completes, the list is a palindrome
        return true;
    }
}
