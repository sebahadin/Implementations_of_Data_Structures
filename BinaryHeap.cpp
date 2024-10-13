/*
 * @author Sebahadin Denur
 * @description Binary Heap Implementation in C++
 * @date 15/04/2024
 */
#include<iostream>
#include<exception>
#include<math.h>
#include<ctime>
#include<vector>
#include<iomanip>
#include<sstream>
using namespace std;

class Heap
{
    private:
        vector<int> array;
    public:
        Heap();
        void insert(int key);
        int removeMin();
        int getMin();
        int parent(int k);
        int left(int k);
        int right(int k);
        void bubbleup(int k);
        void bubbledown(int k);
        void print();
        void sort();
};

void listCommands()
{
    cout<<"-----------------------------------------------------------------"<<endl;
    cout<<"display            :Display the Heap"<<endl
        <<"insert <key>       :Insert a new element in the Heap"<<endl
        <<"getMin             :Get the element with Min. Key in the Heap"<<endl
        <<"removeMin          :Remove the element with Min. Key from Heap"<<endl
        <<"sort               :Sort the Heap"<<endl
        <<"help               :Display the available commands"<<endl
        <<"exit/quit          :Exit the program"<<endl;
    cout<<"-----------------------------------------------------------------"<<endl;
}
//=============================================
void demo(Heap &myHeap)
{
    for (int i=1; i<=7; i++)
    {
        int n = rand()%25;
        myHeap.insert(n);
    }
    myHeap.print();
}
//=============================================
int main()
{

    Heap myHeap;
    string user_input;
    string command;
    string argument;

    listCommands();

    while(true)
    {
        try
        {
            cout<<">";
            getline(cin,user_input);
        
            // parse userinput into command and parameter(s)
            stringstream sstr(user_input);
            getline(sstr,command,' ');
            getline(sstr,argument);

                 if(command =="display" or command=="d")        myHeap.print();
            else if(command =="insert"  or command=="i")        { myHeap.insert(stoi(argument)); myHeap.print(); }
            else if(command =="getMin")                            {int min=myHeap.getMin();cout<<"Min Key = "<<min<<endl;}
            else if(command =="removeMin"  or command=="r")     { cout<<myHeap.removeMin()<<" has been removed..!"<<endl; myHeap.print(); }
            else if(command =="sort")                              { myHeap.sort(); myHeap.print(); }
            else if(command == "help")                             listCommands();
            else if(command == "demo")                             demo(myHeap);
            else if(command == "exit" or command == "quit")     break;
            else cout<<"Invalid command !!!"<<endl;
        }
        catch (exception &e)
        {
            cout<<"Exception: "<<e.what()<<endl;
        }
    }
    return EXIT_SUCCESS;
}
//==================================================================
//This method prints a Heap in 2D format.
void Heap::print()
{
    if(array.size()>1)
    {
        int levels = int(log2(array.size()));

        int *spaces = new int[levels+1];
        spaces[levels]=0;

        for(int j=levels-1; j>=0; j--)
        {
                spaces[j]=2*spaces[j+1]+1;
        }
        
        int level=0;
        for (int i=0; i<array.size()-1; i++)
        {
            if(i == (pow(2,level)-1))
            {
                cout<<endl<<endl;
            
                for(int k=0; k<spaces[level]; k++)
                cout<<"   ";
                level++;
            }
            cout<<std::left<<setw(3)<<array[i+1];
        
            if(level>1)
            {
                for(int k=0; k<spaces[level-2]; k++)
                    cout<<"   ";
            }
            
        }
        cout<<endl;
        for(int i=0; i<spaces[0]*log2(array.size()/2)+4; i++)
            cout<<"__";
        
        cout<<endl;
        delete[] spaces;
    }

}
// Constructor for the Heap class
Heap::Heap()
{
    array.push_back(0); // Push back 0 to simplify 1-based index
}
// Insert an element in Heap keeping the Heap property intact
void Heap::insert(int key)
{
    if (array.size() <= 1)
    {
        array.push_back(key); // If heap is empty, simply insert the key
    }
    else
    {
        array.push_back(key); // Insert the key at the end
        bubbleup(array.size()-1); // Fix the heap property by bubbling up
    }
}
// Remove the minimum value from Heap keeping the Heap property intact
int Heap::removeMin()
{
    if (array.size()<=1) {
        throw runtime_error("heap is empty!"); // Exception if heap is empty
    }
    else
    {
        int min = array[1]; // Store the minimum value
        array[1] = array.back(); // Replace the root with the last element
        array.pop_back(); // Remove the last element
        bubbledown(1); // Fix the heap property by bubbling down
        
        return min; // Return the minimum value
        
    }
}
// Return (but don't remove) the minimum value from the Heap
int Heap::getMin()
{
    if (array.size()<=1)
    {
        throw runtime_error("heap is empty!"); // Exception if heap is empty
    }
    else
    {
        return array[1]; // Return the root element
    }
}
// Returns the index of the parent of the node i
int Heap::parent(int k)
{
    return (k)/2; // Return the parent index
}
// Returns the index of the left child of the node i
int Heap::left(int k)
{
    return (2*k); // Return the left child index
}
// Returns the index of the right child of the node i
int Heap::right(int k)
{
    return (2 * k + 1); // Return the right child index
}

void Heap::bubbleup(int k)
{
    int p;
    
    while( k>1)
    {
        p = parent(k); // Get parent of k
        if (array[p] > array[k]) // If parent is greater than current
        {
            int temp = array[p]; // Swap parent and current
            array[p] = array[k];
            array[k] = temp;
            k = p; // Move to the parent
        }
        else
        {
            break; // If no swap needed, break
        }
    }
}

void Heap::bubbledown(int k)
{
    while(true)
    {
        int l = left(k); // Get left child
        int r = right(k); // Get right child
        int s = k; // Start with current node
        
        if (l < array.size() && array[l] < array[s]) s = l; // If left child is smaller, choose left
        if (r < array.size() && array[r] < array[s]) s = r; // If right child is smaller, choose right
        
        if (s == k) break; // If no child is smaller, break
    
        int temp = array[k]; // Swap current node with smaller child
        array[k] = array[s];
        array[s]  = temp;
        k = s; // Move to the smaller child
    }
}
// This method will sort the internal array/vector
//       Copy the values from auxiliary array to the internal array/vector of heap
void Heap::sort()
{
    vector<int> sorted_array; // Create a temporary vector to hold sorted elements
    sorted_array.push_back(0); // Push back 0 to simplify 1-based index
    while (!(array.size()<=1))
    {
        sorted_array.push_back(removeMin()); // Continuously remove min and add to sorted_array
    }
    array = sorted_array; // Assign sorted elements back to the main array

}
//=============================================

