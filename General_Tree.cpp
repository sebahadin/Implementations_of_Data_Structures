
//============================================================================
// Author       :Sebahadin Aman Denur
// Version      :
// Date Created : 31/03/2024
// Date Modified: 01/04/2024
// Description  : General Tree implmentation in C++
//============================================================================
#include<iostream>
#include<sstream>
#include<stdlib.h>
#include<vector>
using namespace std;

class Node
{
    private:
        string name;                //name of the Node
        vector<Node*> children;        //Children of Node
        Node* parent;                 //link to the parent
    
    public:
        Node(string name) : name(name), parent(nullptr)
        { }
        string getName()
        {
            return this->name;
        }
        ~Node();
        friend class Tree;
};
//==========================================================
class Tree
{
    private:
        Node *root;                //root of the Tree
        Node *curr_Node;            //current Node
        
    public:
        Tree();
        ~Tree();
        Node* getRoot();
        Node* getCurrentNode();
        void cd(string name);
        void print();            //Print entire tree
    private:    //Helper methods
        void print_helper(string padding, string pointer,Node *node);
        bool isLastChild(Node *ptr);
    public:
        //Required Methods
        void insert(Node* node,string name);
        void remove(Node* node,string child_name);
        bool isExternal(Node* node);
        bool isInternal(Node* node);
        int size(Node* node);
        int depth(Node* node);
        int height(Node *node);
        int treeHeight();
        void preorder(Node *node);
        void postorder(Node *node);
};
//==================================================================
void help(void)
{
    cout<<"print/tree          : Print the Tee"<<endl
        <<"insert <child-name> : Insert a new node as a child of the current node"<<endl
        <<"remove <child-name> : Removes a specific child from the current node"<<endl
        <<"size                : Print the total number of nodes in the Tree"<<endl
        <<"Height              : Print the height of the current node"<<endl
        <<"depth               : Print the depth of the current node"<<endl
        <<"treeHeight          : Print the height(Max-depth) of the Tree"<<endl
        <<"isExternal          : Check if the current node is an external node or not"<<endl
        <<"isInternal          : Check if the current node is an internal node or not"<<endl
        <<"preorder            : Traverse/Print the Tree in pre-order"<<endl
        <<"postorder           : Traverse/Print the Tree in post-order"<<endl
        <<"help                : Display the list of available commands"<<endl
        <<"exit                : Exit the Program"<<endl;
}
//==================================================================
int main()
{
    Tree tree;
    help();
    while(true)
    {
        string user_input;
        string command;
        string parameter;
        cout<<">";
        getline(cin,user_input);

        // parse userinput into command and parameter(s)
        stringstream sstr(user_input);
        getline(sstr,command,' ');
        getline(sstr,parameter);

        try
        {
                 if(command=="insert" or command=="i")        tree.insert(tree.getCurrentNode(),parameter);
            else if(command=="remove" or command=="r")        tree.remove(tree.getCurrentNode(),parameter);
            else if(command=="cd")                            tree.cd(parameter);
            else if(command=="size")                        cout<<"Size of the Tree is :"<<tree.size(tree.getRoot())<<endl;
            else if(command=="depth")                        cout<<"The depth of the current node("<<tree.getCurrentNode()->getName()<<") is: "<<tree.depth(tree.getCurrentNode())<<endl;
            else if(command=="height")                        cout<<"The height of the current node("<<tree.getCurrentNode()->getName()<<") is: "<<tree.height(tree.getCurrentNode())<<endl;
            else if(command=="treeHeight")                    cout<<"The height(max-depth) of the Tree is: "<<tree.treeHeight()<<endl;
            else if(command=="print" or command=="tree")    tree.print();        //print the tree
            else if(command=="preorder")                    tree.preorder(tree.getRoot()),cout<<endl;
            else if(command=="postorder")                    tree.postorder(tree.getRoot()),cout<<endl;
            else if(command=="help")                        help();
            else if(command=="exit")                        break;
            else if(command=="isExternal")                    cout<<"Current node("<<tree.getCurrentNode()->getName()<<") is "<<((tree.isExternal(tree.getCurrentNode())==true) ? "":"not ")<<"an external node of the tree."<<endl;
            else if(command=="isInternal")                    cout<<"Current node("<<tree.getCurrentNode()->getName()<<") is "<<((tree.isInternal(tree.getCurrentNode())==true) ? "":"not ")<<"an internal node of the tree."<<endl;
            else                                             cout<<command<<": command not found"<<endl;
        }
        catch(exception &e)
        {
            cout<<"Exception: "<<e.what()<<endl;
        }

    }
}
//========================================================================
Tree::Tree()
{
    this->root = new Node("root");
    this->curr_Node = this->root;
}
Tree::~Tree()
{
    delete this->root;
}
//========================================================================
Node* Tree::getRoot()
{
    return root;
}
//========================================================================
Node* Tree::getCurrentNode()
{
    return curr_Node;
}
//========================================================================
void Tree::cd(string name)
{
    if(name=="..")
    {
        if(curr_Node!=root)    curr_Node = curr_Node->parent;
    }
    else
    {
        for(int i=0; i<curr_Node->children.size(); i++)
            if(name == curr_Node->children[i]->name)
            {
                curr_Node = curr_Node->children[i];                        //update current working directory
                return;
            }

        cout<<name<<": child not found"<<endl;
    }
}
//==========================================================================
void Tree::print()
{
    print_helper("","",root);
}
//==========================================================================
void Tree::print_helper(string padding, string pointer,Node *node)
{
    if (node != nullptr)
    {
        if(node == curr_Node)    //print current Node in blue color
            cout <<padding<<pointer<<"\x1B[33m"<<node->name<<"\x1B[0m"<<endl;
        else
            cout <<padding<<pointer<<node->name<<endl;

        if(node!=root)    padding+=(isLastChild(node)) ? "   " : "│  ";


        for(int i=0; i<node->children.size(); i++)    //remove the file/folder from original path
        {
            string marker = isLastChild(node->children[i]) ? "└──" : "├──";
            print_helper(padding,marker, node->children[i]);

        }
    }
}
//==========================================================================
bool Tree::isLastChild(Node *ptr)
{
    if(ptr!=root and ptr == ptr->parent->children[ptr->parent->children.size()-1])
        return true;
    return false;
}
//===========================================================================
//==========================================================================
// Checks if a node is external, meaning it has no children
bool Tree::isExternal(Node* node)
{
    return node->children.size() == 0; // Returns true if the children vector is empty
}
//==========================================================================
// Checks if a node is internal, meaning it has at least one child
bool Tree::isInternal(Node* node)
{
    return node->children.size() != 0; // Returns true if the children vector is not empty
}
//==========================================================================
// Calculates the size of the tree or subtree rooted at the given node
int Tree::size(Node *node)
{
    // Base case: if the node has no children, its size is 1
    if(node->children.size() == 0) return 1;
    
    int sum = 0; // Initializes sum of sizes
    
    // Recursively calculates the size of each subtree rooted at each child
    for(int i = 0 ; i < node->children.size(); i++)
    {
        sum += size(node->children[i]);
    }
    return sum + 1; // Includes the node itself in the total size
}
//========================================================================
// Inserts a new child with the given name under the specified node
void Tree::insert(Node* node, string child_name)
{
    Node* child = new Node(child_name); // Creates a new node for the child
    child->parent = node; // Sets the child's parent
    
    node->children.push_back(child); // Adds the child to the node's children vector
}
//========================================================================
// Removes a child with the given name from the specified node
void Tree::remove(Node* node, string child_name)
{
    // Searches for the node in the parent's children vector and removes it
    for(int i = 0; i < node->children.size(); i++)
    {
        if(node->children[i]->name == child_name)
        {
            delete node->children[i]; // Deletes the node
            node->children.erase(node->children.begin() + i); // Erases the child
            return;
        }
    }

    throw runtime_error("Child with name " + child_name + " not found!");
}
//==========================================================================
// Calculates the depth of a given node
int Tree::depth(Node* node)
{
    // Base case: the root has a depth of 0
    if (node == this-> root){
        return 0;
    }
    
    return depth(node->parent) + 1; // Recursive case: adds one to the depth of the parent node
}
//==========================================================================
// Calculates the height of a node
int Tree::height(Node* node)
{
    // Base case: if the node has no children, its height is 0
    if (node->children.empty()) {
        return 0;
    }
    
    int h = 0; // Initializes maximum height
    
    // Recursively finds the height of each child and keeps the maximum
    for(int i = 0; i < node->children.size(); i++)
    {
        int child_height = height(node->children[i]);
        if (child_height > h) { h = child_height; }
    }
    return h + 1; // Includes the node itself in the height calculation
}
//==========================================================================
// Calculates the height of the entire tree
int Tree::treeHeight()
{
    return height(this->root); // Delegates to the height function, starting at the root
}
//==========================================================================
// Performs a preorder traversal of the tree, starting at the given node
void Tree::preorder(Node *node)
{
    // Base case: if the node has no children, prints its name
    if (node->children.size() == 0) { cout<<node->name<< " "; return ; }
    
    cout<<node->name<< " "; // Prints the current node's name
    // Recursively visits each child in preorder
    for(int i = 0; i < node->children.size(); i++)
    {
        preorder(node->children[i]);
    }
}
//==========================================================================
// Performs a postorder traversal of the tree, starting at the given node
void Tree::postorder(Node *node)
{
    // Base case: if the node has no children, prints its name
    if (node->children.size() == 0) { cout<<node->name<< " "; return ; }
    
    // Recursively visits each child in postorder
    for(int i = 0; i < node->children.size(); i++)
    {
        postorder(node->children[i]); // This should call postorder instead of preorder for correct postorder behavior
    }
    cout<<node->name<< " "; // Prints the current node's name
}
//==========================================================================
// Destructor for the Node class, deallocates all children
Node::~Node()
{
    // Deletes all children of this node
    for(int i = 0; i < this->children.size(); i++)
    {
        delete this->children[i];
    }
}
