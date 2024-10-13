//============================================================================
// Author       : Sebahdin Aman Denur
// Version      : 1.0
// Date Created : 22/04/2024
// Date Modified:
// Description  : Hash Table implementation using C++
//============================================================================

#include<iostream>
#include<fstream>
#include<sstream>
#include<math.h>
#include<iomanip>
#include<list>

using namespace std;
class Entry
{
    private:
        string key;
        string value;
        bool deleted;     //Is the bucket available to be reused (after deletion)
    public:
        Entry(string key, string value)
        {
            this->key = key;
            this->value = value;
            this->deleted = false;
        }
        friend class HashTable;
};

class HashTable
{
    private:
        Entry **buckets;                            // Array of Pointers to Entries
        unsigned int capacity;                        // Total Capacity of Hash Table
        unsigned int size;                               // Current # of entries in the Hash Table
        unsigned int collisions;                     // Total Number of Collisions
    public:
        HashTable(int capacity);
        unsigned int getSize();
        unsigned int getCollisions();
        unsigned long hashCode(string key);
        void insert(string key, string value);
        void remove(string key);
        string search(string key);
        ~HashTable();
};
//======================================================
int main(void)
{
    ifstream fin;
    fin.open("zipcodes.csv");
    if(!fin){
        cout<<"Can not open the file <zipcodes.txt>...!"<<endl;
        exit(-1);
    }
    
    string line;
    HashTable myHashTable(28859);// Prime number 30% bigger than >25844 (19880*1.3);
    getline(fin,line);  //skip first line
    while(!fin.eof())
    {
        string key, value;
        getline(fin,key,',');
        getline(fin,value);
        //cout<<key<<":"<<value<<endl;
        std::cout.setstate(std::ios_base::failbit); //dont print any thing on terminal until the failbit is cleared again.
        myHashTable.insert(key,value);
        std::cout.clear();                            //clear the failbit
    }
    fin.close();
    cout<<"==================================================="<<endl;
    cout<<"Hash Table size = "<<myHashTable.getSize()<<endl;
    cout<<"Total Number of Collisions = "<<myHashTable.getCollisions()<<endl;
    cout<<"Avg. # collisions/entry = "<<setprecision(2)<<float(myHashTable.getCollisions())/myHashTable.getSize()<<endl;
    cout<<"==================================================="<<endl;

    string user_input, command, argument1, argument2;

    while(true)
    {
    
        cout<<">";
        getline(cin,user_input);

        stringstream sstr(user_input);
        getline(sstr,command,' ');
        getline(sstr,argument1,',');
        getline(sstr,argument2);

            if(command == "find")      cout<<"Zip code for "<<argument1<<" is: "<<myHashTable.search(argument1)<<endl;
        else if(command == "insert")   myHashTable.insert(argument1,argument2);
        else if(command == "remove")   myHashTable.remove(argument1);
        else if(command == "help")       cout<<"Available Commands:\ninsert <key,value>\nremove <key>\nfind <key>"<<endl;
        else if(command == "exit")       break;
        else cout<<"Invalid command !!!"<<endl;
    }
    return 0;
}
//===================================================
HashTable::HashTable(int capacity)
{
    buckets = new Entry*[capacity];        // Array of Pointers to Entries
    for(int i=0; i<capacity; i++)
        buckets[i] = nullptr;

    this->capacity = capacity;
    this->size = 0;
    this->collisions = 0;
}
//======================================================
//Please add your implementaiton below this line.
// Destructor for HashTable
HashTable::~HashTable()
{     
    for(int i=0; i<capacity; i++)
    {
        if (buckets[i] != nullptr)
        {
            delete buckets[i];  // Delete individual buckets that are not null
        }
    }

    delete [] buckets;  // Delete the array of buckets
}

// Function to return the size of the hash table
unsigned int HashTable::getSize()
{
    return this->size;
}

// Function to return the number of collisions encountered
unsigned int HashTable::getCollisions()
{
    return this->collisions;
}

// Hash function to compute the hash code of a given key
// unsigned long HashTable::hashCode(const string key) 
// {
//     unsigned long h = 0;  // Initialize hash value
//     for (int i = 0; i < key.length(); ++i)
//     {
//         char c = key[i];
//         h = (h << 5) | (h >> (27));  // Perform a 5-bit cyclic shift
//         h += static_cast<unsigned char>(c);  // Add the character value to the hash
//     }

//     return h;  // Return the computed hash
// }

unsigned long HashTable ::hashCode(string word) {
     unsigned long h = 0; // assumed to be 4 bytes = 32 bits
    for (int i = 0; i < word.length(); i++) {
        h = (h << 5) | (h >> 27); // 5-bit cyclic shift
        h += (unsigned long) word[i]; // add in next character
    }
    return  h; // return index in the range 0..capacity-1
}


// Insert function to add a key-value pair to the hash table
void HashTable::insert(string key, string value) 
{
    if (this->size == this->capacity) 
    {
        cout << "Could not add " << key << ", max capacity is reached!" << endl;  // Check for full hash table
        return;
    }
    unsigned int index = hashCode(key) % this->capacity;  // Compute the bucket index
    unsigned int start_index = index;  // Save the start index
    bool placed = false;  // Flag to check if insertion was successful
    while (buckets[index] != nullptr && !placed)  // Loop to find an empty or deletable bucket
    {
        if (buckets[index]->deleted || buckets[index]->key == key)  // Check if the bucket is deletable or already has the same key
        {
            if (buckets[index]->key == key && !buckets[index]->deleted)  // Existing non-deleted entry
            {
                cout << "Existing record has been updated." << endl;
            } else 
            {
                cout << "New record has been added successfully." << endl;
                this->size++;
            }
            buckets[index]->key = key;
            buckets[index]->value = value;
            buckets[index]->deleted = false;
            placed = true;
        } else 
        {
            this->collisions++;  // Increment collisions if we skip an occupied bucket
            index = (index + 1) % this->capacity;  // Move to the next bucket
            if (index == start_index) break; // Check to avoid infinite loop
        }
    }
    if (!placed) {
        buckets[index] = new Entry(key, value);  // Create a new entry if no suitable bucket was found
        cout << "New record has been added successfully." << endl;
        this->size++;
    }
}

// Remove function to logically delete an entry based on its key
void HashTable::remove(string key)
{
    int index = hashCode(key) % this->capacity;  // Compute the bucket index
    int i = -1;
    
    while(buckets[index] != nullptr)
    {
        i++;
        index = (index + i) % this->capacity ;  // Compute the index with linear probing
        
        if (buckets[index] == nullptr || buckets[index]->deleted == true)
        {
            cout<<key<< " does not exist"<<endl;
            return;
        }
        else if (buckets[index]->key == key)
        {
            buckets[index]->deleted = true;  // Mark the entry as deleted
            this->size--;  // Decrement the size
            cout<<buckets[index]->key <<" has been successfully removed"<<endl;
            break;
        }
    }
}

// Search function to find a value based on its key
string HashTable::search(string key) 
{
    int index = hashCode(key) % this->capacity;  // Compute the bucket index
    int i = 0;
    while (buckets[index] != nullptr)  // Loop to find the key
    {
        if (!buckets[index]->deleted && buckets[index]->key == key)  // Check for non-deleted entries
        {
            return buckets[index]->value + " (Comparisons = " + to_string(i + 1) + ")";  // Return the value and comparison count
        }
        index = (index + 1) % this->capacity;  // Move to the next bucket
        i++;
        if (i >= this->capacity)
        {
            break;
        }
    }
    return " Record not found...!";  // Return not found message if the key is not present
}





