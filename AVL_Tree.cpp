
/*
* @author Sebahadin Aman Denur
* @description BST Tree implementation in C++
* @date
*/
#include<iostream>
#include<cstdlib>
#include<sstream>
#include<iomanip>
#include<math.h>
#include<queue>
#include<vector>
using namespace std;




class Node
{
  private:
      int key;
      string value;
      Node* left;
      Node* right;
      Node* parent;
  public:
      Node(int key,string value): key(key),value(value),left(nullptr),right(nullptr), parent(nullptr) {}
      int getKey() { return this->key;}
      string getValue() {return this->value;}
      friend class AVL;
};
//=============================================================================
class AVL
{
  private:
      Node *root;
  public:
      AVL();                                  //constructor
      ~AVL();                                 //destructor
      Node* getRoot();                        //returns the root of the Tree
      void insert(Node* ptr,int key,string value);            //Insert key into tree/subtree with root ptr
      int height(Node *ptr);                  //Find the height of a tree/subtree with root ptr
      Node* find(Node *ptr,int key);      //Find and returns the node with key
      Node* findMin(Node *ptr);               //Find and return the Node with minimum key value from a tree/subtree with root ptr
      Node* findMax(Node *ptr);               //Find and return the Node with Max key value from a tree/subtree with root ptr
      void remove(Node *ptr,int key);         //Remove a node with key from the tree/subtree with root
      void printInorder(Node* ptr);           //Traverse (inroder) and print the key of a tree/subtree with root ptr
      void printTree();                       //Print 2D Tree
      int  balanceFactor(Node* ptr);//Compute the balance factor of the node
    void rotateRight(Node* z);//Rotate the tree/subtree rooted at z to right
    void rotateLeft(Node* z);//Rotate the tree/subtree rooted at z to left
    void rebalance(Node* ptr);//Rebalance the tree/subtree rooted at ptr

};




//==========================================================
void listCommands()
{
        
  cout<<"________________________________________________________"<<endl;
  cout<<"display            :Display the BST Tree"<<endl
      <<"height             :Find the height of the Tree"<<endl
      <<"min                :Find the node with minimum key in BST"<<endl
      <<"max                :Find the node with maximum key in BST"<<endl
      <<"find <key>         :Find a node with a given key value in BST"<<endl
      <<"insert <key,value> :Insert a new node in BST"<<endl
      <<"remove <key>       :Remove the node from BST "<<endl
      <<"inorder            :Print the BST in Inorder"<<endl
      <<"help               :Display the available commands"<<endl
      <<"exit               :Exit the program"<<endl;
}
//==========================================================
void demo( AVL &myBST)
{
  myBST.insert(myBST.getRoot(),10,"v10");
  myBST.insert(myBST.getRoot(),5,"v5");
  myBST.insert(myBST.getRoot(),4,"v4");
  myBST.insert(myBST.getRoot(),7,"v7");
  myBST.insert(myBST.getRoot(),13,"v13");
  myBST.insert(myBST.getRoot(),15,"v15");
  myBST.insert(myBST.getRoot(),12,"v12");
  myBST.printTree();
}
//==========================================================
int main(void)
{
  AVL myBST;
  listCommands();

  while(true)
  {
      string user_input="";
      string command="";
      string key="";
      string value="";
      try
      {
          cout<<">";
          getline(cin,user_input);
          // parse user input into command and parameter(s)
          stringstream sstr(user_input);
          getline(sstr,command,' ');
          getline(sstr,key,',');
          getline(sstr,value);
        
          Node* root = myBST.getRoot();   //get the root of the tree
          if( user_input =="display") myBST.printTree();
          else if( command =="height")    cout<<"Height = "<<myBST.height(root)<<endl;
          else if( command =="min")
          {
              Node* min = myBST.findMin(root);
              cout<<"Min. key = "<<((min!=nullptr)? to_string(min->getKey()):" does not exist")<<endl;
          }
          else if( command =="max")
          {
              Node* max = myBST.findMax(root);
              cout<<"Max. key = "<<((max!=nullptr)? to_string(max->getKey()):" does not exist")<<endl;
          }
          else if( command =="find" or command =="f")
          {
              Node *node = myBST.find(root,stoi(key));
              if(node==nullptr)
                  cout<<key<<" not found"<<endl;
              else
                  cout<<"("<<key<<","<<node->getValue()<<")"<<endl;
          }
          else if( command =="insert" or command=="i")    { myBST.insert(root, stoi(key),value); myBST.printTree();}
          else if( command =="remove" or command=="r")    { myBST.remove(root,stoi(key)); myBST.printTree();}
          else if( command =="inorder")   {myBST.printInorder(root); cout<<endl;}
          else if( command == "demo") demo(myBST);
          else if( command == "help") listCommands();
          else if( command =="exit" or command =="quit" or command =="q") break;
          else cout<<"Invalid command !!!"<<endl;
      }
      catch(exception &ex)
      {
          cout<<ex.what()<<endl;
      }


  }
  return 0;
}
//===============================================================
//Print a 2D Tree
void AVL::printTree()
{
  cout<<"Tree:"<<endl;
  int levels = height(this->root);
  int max_nodes = pow(2,levels+1)-1;
  queue<Node*> myQueue;
  vector<Node*> myVector;
  myQueue.push(this->root);

  //Travers the tree in Breadth First Order and store each node into myVector
  for(int i=0; i<max_nodes; i++)
  {
      Node* cur = myQueue.front();
      myQueue.pop();
      myVector.push_back(cur);
      if(cur != nullptr)
      {
          myQueue.push(cur->left);
          myQueue.push(cur->right);
      }
      else //For Empty nodes push nullptr(placeholder) in Queue
      {
          myQueue.push(nullptr);
          myQueue.push(nullptr);
      }
  }

  if(max_nodes >0)            //if a non-empty tree
  {
      int *spaces = new int[levels+1];
      spaces[levels]=0;
      int level=0;

      for(int j=levels-1; j>=0; j--)
          spaces[j]=2*spaces[j+1]+1;
    
      for (int i=0; i<max_nodes; i++)
      {
          if(i == (pow(2,level)-1))   // if first node of a level
          {
              cout<<endl<<endl;       // go to next line
              for(int k=0; k<spaces[level]; k++)  //print sufficient spaces before printing the first node of a level
                 cout<<"   ";
            
              level++;
          }
          if(myVector[i]!=nullptr)     cout<<std::left<<setw(3)<<myVector[i]->getKey();
          else                         cout<<std::left<<setw(3)<<" ";
          if(level>1)
              for(int k=0; k<spaces[level-2]; k++)    // print spaces between two nodes on same level
                  cout<<"   ";
      }
      cout<<endl;
      for(int i=0; i<pow(levels,2.5); i++)    //Add last line with ----
          cout<<"___";
    
      cout<<endl;
      delete[] spaces;
  }
}
//=====================================================================
AVL::AVL()
{
  this->root=nullptr;
}
//=====================================================================

//destructor to delete the tree
AVL::~AVL()
{
  queue<Node*> myQueue;
  
  myQueue.push(this->root);//push the root of the tree

  while(!myQueue.empty())
  {
      Node* current = myQueue.front();
      myQueue.pop();//    Remove the front element from the queue

      if (current!=nullptr)
      {
          if (current->left != nullptr)
          {
              myQueue.push(current->left);//push the left child of the current node
          }
          if (current->right != nullptr)
          {
              myQueue.push(current->right);//push the right child of the current node
          }
          delete current;//delete the current node
      }
  }
}
//=====================================================================
// Return the root of the tree
Node* AVL::getRoot()
{
  return this->root;
}
//=====================================================================
//Insert recursively the key in the tree/subtree rooted at ptr
void AVL::insert(Node *ptr, int key, string value)
{
    if (ptr == nullptr) // Tree is empty
    {
        this->root = new Node(key, value); // Create new node at root
        rebalance(this->root);
    }
    else
    {
        if (key < ptr->key)//if the key is less than the key of the current node  insert on the left
        {
            if (ptr->left == nullptr)
            {
                ptr->left = new Node(key, value); // Create new node
                ptr->left->parent = ptr;
                rebalance(ptr->left);
            }
            else//if the left child is not null insert recursively on the left
            {
                insert(ptr->left, key, value); // Recursive insert on the left
            }
        }
        else if (key > ptr->key)//if the key is greater than the key of the current node  insert on the right
        {
            if (ptr->right == nullptr)
            {
                ptr->right = new Node(key, value); // Create new node
                ptr->right->parent = ptr;//set the parent of the right child to the current node
                rebalance(ptr->right);//rebalance the tree  after insertion
            }
            else//if the right child is not null insert recursively on the right
            {
                insert(ptr->right, key, value); // Recursive insert on the right
            }
        }
        else
        {
            ptr->value = value; // Update the value if key already exists
            cout << "Key already exists. It's value has been updated" << endl;
        }
    }
}

//=====================================================================

//Find the Height of the tree/subtree rooted at ptr
int AVL::height(Node* ptr)
{
  if(ptr==nullptr)
  {
      return -1;//if the tree is empty return -1
  }
  else
  {
      int left_height = height(ptr->left);//compute the height of the left subtree
      int right_height = height(ptr->right);//compute the height of the right subtree
      //the height of the tree is the maximum height of the left and right subtree + 1
      if (left_height > right_height)//if the left height is greater than the right height return the left height +1
      {
          return left_height+1;//return the left height +1
      }
      return right_height+1;//return the right height +1
  }
}


//=====================================================================
// Find recursively (or iteratively ) the key with minimum in the tree/subtree rooted at ptr
Node* AVL::findMin(Node *ptr)
{
  if (ptr->left==nullptr)
  {
      return ptr;//if reached to the left most node
  }
  {
      return findMin(ptr->left);//recursive call to find the minimum key in the left subtree
  }
}
//=====================================================================
// Find recursively (or iteratively ) the key with Maximum in the tree/subtree rooted at ptr
Node* AVL::findMax(Node *ptr)
{
  if (ptr->right==nullptr)
  {
      return ptr;//if reached to the right most node
  }
  {
      return findMax(ptr->right);//recursive call to find the maximum key in the right subtree
  }
}
//=====================================================================
// Find recursively the node with key value in the tree/subtree rooted at ptr
Node* AVL::find(Node *ptr,int key)
{
  if (ptr==nullptr)
  {
      return nullptr;//if the pointer is null key is not found
  }
  if (ptr->key==key)
  {
      return ptr;//if the key is found
  }
  if (key<ptr->key)//if the key is less than the key of the current node
  {
      return find(ptr->left,key);//recursive call to find the key in the left subtree
  }
  else
  {
      return find(ptr->right,key);//recursive call to find the key in the right subtree
  }
}
//=========================================================
//Remove recursively the node with key value from the tree/subtree rooted at ptr
void AVL::remove(Node *ptr,int key)
{
  if(ptr==nullptr)
  {
      cout<<"Key not found in the data"<<endl;
      return;//if the tree is empty
  }
  else
  {
      if (key < ptr->key)
      {
          remove(ptr->left,key);//recursive call to remove the key from the left subtree
      }
      else if (key > ptr->key)
      {
          remove(ptr->right,key);//recursive call to remove the key from the right subtree
      }
      else
      {// Node with the key found
       if (ptr->left == nullptr && ptr->right == nullptr)
       {
           // Node is a leaf (no children)
           if (ptr->parent == nullptr)
           {
               root = nullptr;  // Node is the root and has no children
           } else if (ptr == ptr->parent->left)
           {
               ptr->parent->left = nullptr;  // Node is a left child
           } else
           {
               ptr->parent->right = nullptr;  // Node is a right child
           }
           
           if (ptr->parent != nullptr)//if the parent of the node is not null rebalance the tree
           {
                rebalance(ptr->parent);  // Rebalance the tree
           }
           
           delete ptr;  // Delete the node
       } else if (ptr->left == nullptr || ptr->right == nullptr)
       {
           // Node has one child
           Node* temp = (ptr->left != nullptr) ? ptr->left : ptr->right;
           if (ptr->parent == nullptr)
           {
               root = temp;  // Node is the root
           } else if (ptr == ptr->parent->left)
           {
               ptr->parent->left = temp;  // Connect the child to the parent
           } else
           {
               ptr->parent->right = temp;// Connect the child to the parent
           }
           temp->parent = ptr->parent;
           
              if (ptr->parent != nullptr)
              {
                rebalance(ptr->parent);  // Rebalance the tree
              }
           delete ptr;  // Delete the node
       }
          else
          {
              Node* temp = findMin(ptr->right);//find the minimum key in the right subtree
              ptr->key = temp->key;//overwrite the key of the node to be removed
              ptr->value = temp->value;//overwrite the value of the node to be removed
              remove(ptr->right,temp->key);//if the node has both left and right child
          }
      }

  }
}
//===============================================================
//Print recursively the tree/subtree rooted at ptr Inorder fromat
void AVL::printInorder(Node *ptr)
{
  if (ptr==nullptr)
  {
      return;
  }
  printInorder(ptr->left);//recursive call to print the left subtree
  cout<<"("<<ptr->key<<","<<ptr->value<<")";//print the key
  printInorder(ptr->right);//recursive call to print the right subtree
}



// Compute the balance factor of the node
int AVL::balanceFactor(Node* ptr) 
{
    if (ptr == nullptr) {
        return 0; // If the tree is empty return 0
    }
    int left_height = height(ptr->left);//compute the height of the left subtree
    int right_height = height(ptr->right);//compute the height of the left and right subtree
    return right_height - left_height; // Right height minus left height
}

// Rotate the tree/subtree rooted at z to right
void AVL::rotateRight(Node* z) 
{
    Node* y = z->left;
    z->left = y->right;//move the right child of y to the left child of z
    if (y->right != nullptr)//if the right child of y is not null
    {
        y->right->parent = z;//set the parent of the right child of y to z
    }
    y->parent = z->parent;
    if (z->parent == nullptr)//if the parent of z is null
    {
        root = y;
    } else if (z == z->parent->left)
    {
        z->parent->left = y;
    } else
    {
        z->parent->right = y;//set the right child of the parent of z to y
    }
    y->right = z;
    z->parent = y;
}

// Rotate the tree/subtree rooted at z to left
void AVL::rotateLeft(Node* z) 
{
    Node* y = z->right;//set y to the right child of z
    z->right = y->left;//   move the left child of y to the right child of z
    if (y->left != nullptr)//if the left child of y is not null
    {
        y->left->parent = z;//set the parent of the left child of y to z
    }
    y->parent = z->parent;//set the parent of y to the parent of z
    if (z->parent == nullptr)//if the parent of z is null
    {
        root = y;//set the root to y
    } else if (z == z->parent->left)//if the parent of z is null
    {
        z->parent->left = y;//set the left child of the parent of z to y
    } else//if the parent of z is not null
    {
        z->parent->right = y;//set the right child of the parent of z to y
    }
    y->left = z;
    z->parent = y;
}

// Rebalance the tree/subtree rooted at ptr
void AVL::rebalance(Node* ptr) 
{
    while (ptr != nullptr) {
        int bf = balanceFactor(ptr);//compute the balance factor of the node
        if (bf > 1) {//if the balance factor is greater than 1
            if (balanceFactor(ptr->right) < 0) // If the balance factor of the right child is less than 0
            {
                rotateRight(ptr->right); // Right-Left case
            }
            rotateLeft(ptr); // Right-Right case
        } else if (bf < -1) {
            if (balanceFactor(ptr->left) > 0) 
            {
                rotateLeft(ptr->left); // Left-Right case
            }
            rotateRight(ptr); // Left-Left case
        }
        ptr = ptr->parent; // Move up to the parent
    }
}