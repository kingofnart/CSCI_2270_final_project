#ifndef BST_HPP
#define BST_HPP

#include <string>
using namespace std;

// Struct for a tree node
struct Node{
    string key; // data to be stored in the node
    Node* left = nullptr; // pointer to the leftchild node
    Node* right = nullptr; // pointer to the rightchild node
};

class BST{
    private:
      Node* createNode(string data);
      Node* root; // pointer to the root of the BST
      Node* addNodeHelper(Node* currNode, string data);
      Node* deleteNodeHelper(Node *currNode, string value);
      Node* searchKeyHelper(Node* currNode, string data);
      void destroyNode(Node *currNode);
      void printTreeHelper(Node* currNode);
      void print2DUtilHelper(Node *, int);

    public:

      BST();
      BST(string data);
      ~BST();
      Node* getRoot();
      void addNode(string);
      void deleteNode(string);
      void preOrder(Node *node);
      void inOrder(Node *node);
      void postOrder(Node *node);
      bool searchKey(string);
      void printTree();
      void print2DUtil(int space);

};
#endif
