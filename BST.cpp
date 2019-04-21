#include <iostream>
#include <string>
#include "BST.hpp"
using namespace std;

//********************* CREATE NODE & GETROOT FUNCTIOINS ***********************


/*
Method Name: createNode
Purpose: Create a node with mispelling as 'data'
return: pointer to the new node
*/
Node* BST::createNode(string data1, string data2){
  Node *newNode = new Node;
  newNode->mispelling = data1;
  newNode->correct = data2;
  newNode->left = nullptr;
  newNode->right = nullptr;
  return newNode;
}

//fucntion to return the root of the tree
Node* BST::getRoot(){
  return root;
}


 //************************ DESTROY NODE FUNCTION ******************************


 /**
 This function will destroy the subtree rooted at currNode.
 Think about in what order should you destroy. POSTORDER. or right-left-root
 **/

void BST::destroyNode(Node *currNode){
     if(currNode!=NULL){
         destroyNode(currNode->left);
         destroyNode(currNode->right);
         delete currNode;
         //currNode = NULL;
     }
 }


 //*************************** ADD NODE FUNCTION *******************************


/*
Method Name: addNodeHelper
Purpose: This function will add a node with mispelling as 'data' in the tree rooted at 'currNode'.
Call this function from addNode().
return: currNode
*/
Node* BST::addNodeHelper(Node* currNode, string data1, string data2){
  if(root == nullptr){ //if tree is empty
    root = createNode(data1, data2);
    return root;
  }
  if(currNode == nullptr){ //check if you've reached insert spot
    return createNode(data1, data2);
  }
  //else keep going down tree until you reach null
  if(currNode->mispelling < data1){
    currNode->right = addNodeHelper(currNode->right, data1, data2);
  }
  else if(currNode->mispelling > data1){
    currNode->left = addNodeHelper(currNode->left, data1, data2);
  }
  return currNode;
}


// function to insert a node in the tree. This function calls the addNodeHelper()
void BST::addNode(string data1, string data2){
  Node* addedNode = addNodeHelper(root, data1, data2);
  //cout << data1 << " has been added" << endl;
}


//************************ DELETE NODE FUNCTION ********************************


/*
Method Name: deleteNodeHelper
Purpose: This function deletes the node with 'value' as it's mispelling from the tree rooted at 'currNode'.
Call this function from deleteNode()
return: currNode
*/
Node* BST::deleteNodeHelper(Node *currNode, string value){
  if(currNode == NULL)
  {
    return NULL;
  }
  else if(value < currNode->mispelling)
  {
    currNode->left = deleteNodeHelper(currNode->left, value);
  }
  else if(value > currNode->mispelling)
  {
    currNode->right = deleteNodeHelper(currNode->right, value);
  }
  // We found the node with the value
  else
  {
    //Case 1: No child
    if(currNode->left == NULL && currNode->right == NULL)
    {
      delete currNode;
      return nullptr;
    }
    //Case 2: Only right child
    else if(currNode->left == NULL)
    {
      Node *tmp = currNode->right;
      delete currNode;
      return tmp;
    }
    //Case 2.5: Only left child
    else if(currNode->right == NULL)
    {
      Node *tmp = currNode->left;
      delete currNode;
      return tmp;
    }
    //Case 3: Two children
    else
    {
      Node *nextNode = currNode->right, *parent = currNode;
      ///Replace with Minimum from right subtree
      bool a = false;
      while(a == false){
        if(nextNode->left != nullptr){
          parent = nextNode;
          nextNode = nextNode->left;
        }
        else{
          if(parent==currNode){
            parent->right=nextNode->right;
            currNode->mispelling = nextNode->mispelling;
          }
          else{
            parent->left = nextNode->right;
            currNode->mispelling = nextNode->mispelling;

          }
          delete nextNode;
          return currNode;
        }
      }
    }
  }
  return currNode;
}


// function to delete a node in the tree. This function calls the deleteNodeHelper()
void BST::deleteNode(string data){
  Node* deletedNode = deleteNodeHelper(root, data);
  cout << data << " has been deleted" << endl;
}


//************************ IN/PRE/POST ORDER TRAVERSAL *************************
/**


void preOrder(Node *node){
  if(node == nullptr){
    return;
  }
  cout << node->mispelling  << " " << endl;
  preOrder(node->left);
  preOrder(node->right);
}

void inOrder(Node *node){
  if(node == nullptr){
    return;
  }
  inOrder(node->left);
  cout << node->mispelling << " " << endl;
  inOrder(node->right);
}

void postOrder(Node *node){
  if(node == nullptr){
    return;
  }
  postOrder(node->left);
  postOrder(node->right);
  cout << node->mispelling << " " << endl;
}


**/


//************************** SEARCH FUNCTION ***********************************


/*
Method Name: searchmispellingHelper
Purpose: This function will search for a node with "data" as it's mispelling in a tree rooted at 'currNode'.
Call this function from searchmispelling()
return: Node with "data" as it's mispelling if \found, otherwise NULL
*/
Node* BST::searchHelper(Node* currNode, string data1){
  if(currNode == nullptr || currNode->mispelling == data1){
    return currNode;
  }
  if(currNode->mispelling > data1){
    return searchHelper(currNode->left, data1);
  }
  return searchHelper(currNode->right, data1);
}

// function to search a data in the tree. This function calls the searchmispellingHelper()
// returns True if it exists otherwise False
 string BST::searchKey(string data1){
   Node* node = searchHelper(root, data1);
  if(node != nullptr){
    return node->correct;
  }
  //cout << data1 << " not present in the tree" << endl;
  return "";
}


//************************ PRINT TREE FUNCTION *********************************


/*
Method Name: printTreeHelper
Purpose: This function will traverse the tree rooted at "currNode" in an inorder fashion and print out the node elements.
Call this function from printTree()
return: none
*/
void BST::printTreeHelper(Node* currNode){
  if(currNode){
     printTreeHelper(currNode->left);
     cout << " " << currNode->mispelling;
     printTreeHelper(currNode->right);
  }
}


// function to print the tree (in an inorder fashion). This function calls the printTreeHelper()
void BST::printTree(){
  printTreeHelper(root);
  cout << endl;
}


//*************************** PRINT 2D TREE ************************************


void BST::print2DUtilHelper(Node *currNode, int space)
{
    // Base case
    if (currNode == NULL)
        return;

    // Increase distance between levels
    space += 10;

    // Process right child first
    print2DUtilHelper(currNode->right, space);

    // Print current node after space
    // count
    printf("\n");
    for (int i = 10; i < space; i++)
        printf(" ");
    printf("%d\n");
    cout <<  currNode->mispelling;

    // Process left child
    print2DUtilHelper(currNode->left, space);
}

// Prints the tree in a 2D fashion. This function calls print2DUtilHelper().
void BST::print2DUtil(int space){
  print2DUtilHelper(root, space);
}


//**************************** CONSTRUCTOR *************************************

/*
constructor
Purpose: perform all operations necessary to instantiate a class object
return: none
*/

// default constructor
BST::BST(){
  root = nullptr;
}

// parameterized constructor. It will create the root and put the 'data' in the root
BST::BST(string data1, string data2){
  root = createNode(data1, data2);
}


//**************************** DESTRUCTOR **************************************


/*
destructor
Purpose: free all resources that the object has acquired
return: none
*/

// This calls the destroyNode().
BST::~BST(){
  destroyNode(root);
}
