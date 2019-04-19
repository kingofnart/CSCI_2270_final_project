#ifndef BST_HPP
#define BST_HPP

#include <string>
using namespace std;

// Struct for a tree node
struct Node{
    string correct; // correct spelling
    string mispelling; // misspelling
    Node* left = nullptr; // pointer to the leftchild node
    Node* right = nullptr; // pointer to the rightchild node
};

class BST{
    private:
      Node* createNode(string data1, string data2);
      Node* root; // pointer to the root of the BST
      Node* addNodeHelper(Node* currNode, string data1, string data2);
      Node* deleteNodeHelper(Node *currNode, string value);
      Node* searchHelper(Node* currNode, string data1);
      void destroyNode(Node *currNode);
      void printTreeHelper(Node* currNode);
      void print2DUtilHelper(Node *, int);

    public:

      BST();
      BST(string data1, string data2);
      ~BST();
      Node* getRoot();
      void addNode(string, string);
      void deleteNode(string);
      void preOrder(Node *node);
      void inOrder(Node *node);
      void postOrder(Node *node);
      string searchKey(string);
      void printTree();
      void print2DUtil(int space);

};
#endif
