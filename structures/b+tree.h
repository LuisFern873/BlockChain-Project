# ifndef B_PLUS_TREE_H
# define B_PLUS_TREE_H

# include <iostream>

using namespace std;

// Searching on a B+ tree in C++

#include <climits>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

int MAX = 3;

struct entry 
{
    int key;
    int* data;
};

ostream& operator<<(ostream& os, const entry& entry)
{
    cout << "{" << entry.key << ": " << entry.data << "}";
    return os;
}


struct Node
{
    int* key;

    Node** ptr;
    int size;
    bool IS_LEAF;

    Node();

    void setAsLeaf();
};

Node::Node()
{
    key = new int[MAX];
    ptr = new Node *[MAX + 1];
}

// void Node::setAsLeaf()
// {
//     IS_LEAF = true;
//     value = new int*[MAX];
// }


// BP tree
class BPTree
{
    Node* root;

    void insertInternal(int, Node *, Node *);
    Node* findParent(Node *, Node *);

    public:
    BPTree();
    void search(int);
    void insert(int);
    void display(Node *);
    Node* getRoot();

    void displayPretty(){
      for (int i = 1; i <= height(); ++i) {
          displayGivenLevel(root, i);
          cout << "\n";
      }
    }
    void displayGivenLevel(Node* node, int level);

    void remove(int x);
    void removeInternal(int x, Node *cursor, Node *child);


    size_t height();


};

size_t BPTree::height()
{
    if (root == NULL)
        return 0;

    Node* current = root;
    size_t height = 1;

    while (current->IS_LEAF == false) {
        ++height;
        current = current->ptr[0];
    }

    return height;
}

void BPTree::displayGivenLevel(Node* node, int level)
{
    if (node == nullptr)
        return;
    if (level == 1) {
		cout << "[ ";
		for (int i = 0; i < node->size; ++i) {
			cout << node->key[i] << " ";
		}
		cout << "]";
	}
    else {
		for (int i = 0; i <= node->size; ++i) {
			displayGivenLevel(node->ptr[i], level - 1);
			cout << " ";
		}
    }
}


BPTree::BPTree() {
    root = NULL;
}

// Search operation
void BPTree::search(int x) {
  if (root == NULL) {
    cout << "Tree is empty\n";
  } else {
    Node *cursor = root;
    while (cursor->IS_LEAF == false) {
      for (int i = 0; i < cursor->size; i++) {
        if (x < cursor->key[i]) {
          cursor = cursor->ptr[i];
          break;
        }
        if (i == cursor->size - 1) {
          cursor = cursor->ptr[i + 1];
          break;
        }
      }
    }
    for (int i = 0; i < cursor->size; i++) {
      if (cursor->key[i] == x) {
        cout << "Found\n";
        return;
      }
    }
    cout << "Not found\n";
  }
}

// Insert Operation
void BPTree::insert(int x) {
    if (root == NULL) {
        root = new Node;
        root->key[0] = x;
        root->IS_LEAF = true;
        root->size = 1;
    }
    else {
        Node* cursor = root;
        Node* parent;

        while (cursor->IS_LEAF == false)
        {
            parent = cursor;
            for (int i = 0; i < cursor->size; i++) {
                if (x < cursor->key[i]) {
                    cursor = cursor->ptr[i];
                    break;
                }
                if (i == cursor->size - 1) {
                    cursor = cursor->ptr[i + 1];
                    break;
                }
            }
        }

        if (cursor->size < MAX) {
            int i = 0;
            while (x > cursor->key[i] && i < cursor->size)
                i++;
            for (int j = cursor->size; j > i; j--) {
                cursor->key[j] = cursor->key[j - 1];
            }
            cursor->key[i] = x;
            cursor->size++;
            cursor->ptr[cursor->size] = cursor->ptr[cursor->size - 1];
            cursor->ptr[cursor->size - 1] = NULL;
        }
        else {
            Node *newLeaf = new Node;
            int virtualNode[MAX + 1];

            for (int i = 0; i < MAX; i++) {
                virtualNode[i] = cursor->key[i];
            }
            int i = 0, j;

            while (x > virtualNode[i] && i < MAX)
                i++;

            for (int j = MAX + 1; j > i; j--) {
                virtualNode[j] = virtualNode[j - 1];
            }

            virtualNode[i] = x;
            newLeaf->IS_LEAF = true;
            cursor->size = (MAX + 1) / 2;
            newLeaf->size = MAX + 1 - (MAX + 1) / 2;
            cursor->ptr[cursor->size] = newLeaf;
            newLeaf->ptr[newLeaf->size] = cursor->ptr[MAX];
            cursor->ptr[MAX] = NULL;

            for (i = 0; i < cursor->size; i++) {
                cursor->key[i] = virtualNode[i];
            }
            for (i = 0, j = cursor->size; i < newLeaf->size; i++, j++) {
                newLeaf->key[i] = virtualNode[j];
            }

            if (cursor == root) {
                Node *newRoot = new Node;
                newRoot->key[0] = newLeaf->key[0];
                newRoot->ptr[0] = cursor;
                newRoot->ptr[1] = newLeaf;
                newRoot->IS_LEAF = false;
                newRoot->size = 1;
                root = newRoot;
            }
            else {
                insertInternal(newLeaf->key[0], parent, newLeaf);
            }
        }
    }

}

// Insert Operation
void BPTree::insertInternal(int x, Node *cursor, Node *child) {
  if (cursor->size < MAX) {
    int i = 0;
    while (x > cursor->key[i] && i < cursor->size)
      i++;
    for (int j = cursor->size; j > i; j--) {
      cursor->key[j] = cursor->key[j - 1];
    }
    for (int j = cursor->size + 1; j > i + 1; j--) {
      cursor->ptr[j] = cursor->ptr[j - 1];
    }
    cursor->key[i] = x;
    cursor->size++;
    cursor->ptr[i + 1] = child;
  } else {
    Node *newInternal = new Node;
    int virtualKey[MAX + 1];
    Node *virtualPtr[MAX + 2];
    for (int i = 0; i < MAX; i++) {
      virtualKey[i] = cursor->key[i];
    }
    for (int i = 0; i < MAX + 1; i++) {
      virtualPtr[i] = cursor->ptr[i];
    }
    int i = 0, j;
    while (x > virtualKey[i] && i < MAX)
      i++;
    for (int j = MAX + 1; j > i; j--) {
      virtualKey[j] = virtualKey[j - 1];
    }
    virtualKey[i] = x;
    for (int j = MAX + 2; j > i + 1; j--) {
      virtualPtr[j] = virtualPtr[j - 1];
    }
    virtualPtr[i + 1] = child;
    newInternal->IS_LEAF = false;
    cursor->size = (MAX + 1) / 2;
    newInternal->size = MAX - (MAX + 1) / 2;
    for (i = 0, j = cursor->size + 1; i < newInternal->size; i++, j++) {
      newInternal->key[i] = virtualKey[j];
    }
    for (i = 0, j = cursor->size + 1; i < newInternal->size + 1; i++, j++) {
      newInternal->ptr[i] = virtualPtr[j];
    }
    if (cursor == root) {
      Node *newRoot = new Node;
      newRoot->key[0] = cursor->key[cursor->size];
      newRoot->ptr[0] = cursor;
      newRoot->ptr[1] = newInternal;
      newRoot->IS_LEAF = false;
      newRoot->size = 1;
      root = newRoot;
    } else {
      insertInternal(cursor->key[cursor->size], findParent(root, cursor), newInternal);
    }
  }
}

// Find the parent
Node *BPTree::findParent(Node *cursor, Node *child) {
  Node *parent;
  if (cursor->IS_LEAF || (cursor->ptr[0])->IS_LEAF) {
    return NULL;
  }
  for (int i = 0; i < cursor->size + 1; i++) {
    if (cursor->ptr[i] == child) {
      parent = cursor;
      return parent;
    } else {
      parent = findParent(cursor->ptr[i], child);
      if (parent != NULL)
        return parent;
    }
  }
  return parent;
}

// Print the tree
void BPTree::display(Node *cursor) {
  if (cursor != NULL) {
    for (int i = 0; i < cursor->size; i++) {
      cout << cursor->key[i] << " ";
    }
    cout << "\n";
    if (cursor->IS_LEAF != true) {
      for (int i = 0; i < cursor->size + 1; i++) {
        display(cursor->ptr[i]);
      }
    }
  }
}

// Get the root
Node *BPTree::getRoot() {
  return root;
}













void BPTree::remove(int x) {
  if (root == NULL) {
    cout << "Tree empty\n";
  } else {
    Node *cursor = root;
    Node *parent;
    int leftSibling, rightSibling;
    while (cursor->IS_LEAF == false) {
      for (int i = 0; i < cursor->size; i++) {
        parent = cursor;
        leftSibling = i - 1;
        rightSibling = i + 1;
        if (x < cursor->key[i]) {
          cursor = cursor->ptr[i];
          break;
        }
        if (i == cursor->size - 1) {
          leftSibling = i;
          rightSibling = i + 2;
          cursor = cursor->ptr[i + 1];
          break;
        }
      }
    }
    bool found = false;
    int pos;
    for (pos = 0; pos < cursor->size; pos++) {
      if (cursor->key[pos] == x) {
        found = true;
        break;
      }
    }
    if (!found) {
      cout << "Not found\n";
      return;
    }
    for (int i = pos; i < cursor->size; i++) {
      cursor->key[i] = cursor->key[i + 1];
    }
    cursor->size--;
    if (cursor == root) {
      for (int i = 0; i < MAX + 1; i++) {
        cursor->ptr[i] = NULL;
      }
      if (cursor->size == 0) {
        cout << "Tree died\n";
        delete[] cursor->key;
        delete[] cursor->ptr;
        delete cursor;
        root = NULL;
      }
      return;
    }
    cursor->ptr[cursor->size] = cursor->ptr[cursor->size + 1];
    cursor->ptr[cursor->size + 1] = NULL;
    if (cursor->size >= (MAX + 1) / 2) {
      return;
    }
    if (leftSibling >= 0) {
      Node *leftNode = parent->ptr[leftSibling];
      if (leftNode->size >= (MAX + 1) / 2 + 1) {
        for (int i = cursor->size; i > 0; i--) {
          cursor->key[i] = cursor->key[i - 1];
        }
        cursor->size++;
        cursor->ptr[cursor->size] = cursor->ptr[cursor->size - 1];
        cursor->ptr[cursor->size - 1] = NULL;
        cursor->key[0] = leftNode->key[leftNode->size - 1];
        leftNode->size--;
        leftNode->ptr[leftNode->size] = cursor;
        leftNode->ptr[leftNode->size + 1] = NULL;
        parent->key[leftSibling] = cursor->key[0];
        return;
      }
    }
    if (rightSibling <= parent->size) {
      Node *rightNode = parent->ptr[rightSibling];
      if (rightNode->size >= (MAX + 1) / 2 + 1) {
        cursor->size++;
        cursor->ptr[cursor->size] = cursor->ptr[cursor->size - 1];
        cursor->ptr[cursor->size - 1] = NULL;
        cursor->key[cursor->size - 1] = rightNode->key[0];
        rightNode->size--;
        rightNode->ptr[rightNode->size] = rightNode->ptr[rightNode->size + 1];
        rightNode->ptr[rightNode->size + 1] = NULL;
        for (int i = 0; i < rightNode->size; i++) {
          rightNode->key[i] = rightNode->key[i + 1];
        }
        parent->key[rightSibling - 1] = rightNode->key[0];
        return;
      }
    }
    if (leftSibling >= 0) {
      Node *leftNode = parent->ptr[leftSibling];
      for (int i = leftNode->size, j = 0; j < cursor->size; i++, j++) {
        leftNode->key[i] = cursor->key[j];
      }
      leftNode->ptr[leftNode->size] = NULL;
      leftNode->size += cursor->size;
      leftNode->ptr[leftNode->size] = cursor->ptr[cursor->size];
      removeInternal(parent->key[leftSibling], parent, cursor);
      delete[] cursor->key;
      delete[] cursor->ptr;
      delete cursor;
    } else if (rightSibling <= parent->size) {
      Node *rightNode = parent->ptr[rightSibling];
      for (int i = cursor->size, j = 0; j < rightNode->size; i++, j++) {
        cursor->key[i] = rightNode->key[j];
      }
      cursor->ptr[cursor->size] = NULL;
      cursor->size += rightNode->size;
      cursor->ptr[cursor->size] = rightNode->ptr[rightNode->size];
      cout << "Merging two leaf nodes\n";
      removeInternal(parent->key[rightSibling - 1], parent, rightNode);
      delete[] rightNode->key;
      delete[] rightNode->ptr;
      delete rightNode;
    }
  }
}
void BPTree::removeInternal(int x, Node *cursor, Node *child) {
  if (cursor == root) {
    if (cursor->size == 1) {
      if (cursor->ptr[1] == child) {
        delete[] child->key;
        delete[] child->ptr;
        delete child;
        root = cursor->ptr[0];
        delete[] cursor->key;
        delete[] cursor->ptr;
        delete cursor;
        cout << "Changed root node\n";
        return;
      } else if (cursor->ptr[0] == child) {
        delete[] child->key;
        delete[] child->ptr;
        delete child;
        root = cursor->ptr[1];
        delete[] cursor->key;
        delete[] cursor->ptr;
        delete cursor;
        cout << "Changed root node\n";
        return;
      }
    }
  }
  int pos;
  for (pos = 0; pos < cursor->size; pos++) {
    if (cursor->key[pos] == x) {
      break;
    }
  }
  for (int i = pos; i < cursor->size; i++) {
    cursor->key[i] = cursor->key[i + 1];
  }
  for (pos = 0; pos < cursor->size + 1; pos++) {
    if (cursor->ptr[pos] == child) {
      break;
    }
  }
  for (int i = pos; i < cursor->size + 1; i++) {
    cursor->ptr[i] = cursor->ptr[i + 1];
  }
  cursor->size--;
  if (cursor->size >= (MAX + 1) / 2 - 1) {
    return;
  }
  if (cursor == root)
    return;
  Node *parent = findParent(root, cursor);
  int leftSibling, rightSibling;
  for (pos = 0; pos < parent->size + 1; pos++) {
    if (parent->ptr[pos] == cursor) {
      leftSibling = pos - 1;
      rightSibling = pos + 1;
      break;
    }
  }
  if (leftSibling >= 0) {
    Node *leftNode = parent->ptr[leftSibling];
    if (leftNode->size >= (MAX + 1) / 2) {
      for (int i = cursor->size; i > 0; i--) {
        cursor->key[i] = cursor->key[i - 1];
      }
      cursor->key[0] = parent->key[leftSibling];
      parent->key[leftSibling] = leftNode->key[leftNode->size - 1];
      for (int i = cursor->size + 1; i > 0; i--) {
        cursor->ptr[i] = cursor->ptr[i - 1];
      }
      cursor->ptr[0] = leftNode->ptr[leftNode->size];
      cursor->size++;
      leftNode->size--;
      return;
    }
  }
  if (rightSibling <= parent->size) {
    Node *rightNode = parent->ptr[rightSibling];
    if (rightNode->size >= (MAX + 1) / 2) {
      cursor->key[cursor->size] = parent->key[pos];
      parent->key[pos] = rightNode->key[0];
      for (int i = 0; i < rightNode->size - 1; i++) {
        rightNode->key[i] = rightNode->key[i + 1];
      }
      cursor->ptr[cursor->size + 1] = rightNode->ptr[0];
      for (int i = 0; i < rightNode->size; ++i) {
        rightNode->ptr[i] = rightNode->ptr[i + 1];
      }
      cursor->size++;
      rightNode->size--;
      return;
    }
  }
  if (leftSibling >= 0) {
    Node *leftNode = parent->ptr[leftSibling];
    leftNode->key[leftNode->size] = parent->key[leftSibling];
    for (int i = leftNode->size + 1, j = 0; j < cursor->size; j++) {
      leftNode->key[i] = cursor->key[j];
    }
    for (int i = leftNode->size + 1, j = 0; j < cursor->size + 1; j++) {
      leftNode->ptr[i] = cursor->ptr[j];
      cursor->ptr[j] = NULL;
    }
    leftNode->size += cursor->size + 1;
    cursor->size = 0;
    removeInternal(parent->key[leftSibling], parent, cursor);
  } else if (rightSibling <= parent->size) {
    Node *rightNode = parent->ptr[rightSibling];
    cursor->key[cursor->size] = parent->key[rightSibling - 1];
    for (int i = cursor->size + 1, j = 0; j < rightNode->size; j++) {
      cursor->key[i] = rightNode->key[j];
    }
    for (int i = cursor->size + 1, j = 0; j < rightNode->size + 1; j++) {
      cursor->ptr[i] = rightNode->ptr[j];
      rightNode->ptr[j] = NULL;
    }
    cursor->size += rightNode->size + 1;
    rightNode->size = 0;
    removeInternal(parent->key[rightSibling - 1], parent, rightNode);
  }
}




// template <typename T>
// struct Node {
//     bool leaf;
//     size_t degree; // maximum number of children
//     size_t size; // current number of item
//     T* item;
//     Node<T>** children;
//     Node<T>* parent;

// public:
//     Node(size_t _degree)
//     {
//         this->leaf = false;
//         this->degree = _degree;
//         this->size = 0;

//         T* _item = new T[degree-1];
//         for(int i=0; i<degree-1; i++){
//             _item[i] = 0;
//         }
//         this->item = _item;

//         Node<T>** _children = new Node<T>*[degree];
//         for(int i=0; i<degree; i++){
//             _children[i] = nullptr;
//         }
//         this->children = _children;

//         this->parent = nullptr;

//     }
// };

// template <typename T>
// class BPlusTree {
//     Node<T>* root;
//     size_t degree;
//     size_t height;

// public:
//     BPlusTree(size_t _degree)
//     {
//         this->root = nullptr;
//         this->degree = _degree;
//         this->height = 0;
//     }

//     ~BPlusTree()
//     {
//         clear(this->root);
//     }

//     Node<T>* getroot(){
//         return this->root;
//     }

//     Node<T>* BPlusTreeSearch(Node<T>* node, T key){
//         if(node == nullptr) { // if root is null, return nullptr
//             return nullptr;
//         }
//         else{
//             Node<T>* cursor = node; // cursor finding key

//             while(!cursor->leaf){ // until cusor pointer arrive leaf
//                 for(int i=0; i<cursor->size; i++){ //in this index node, find what we want key
//                     if(key < cursor->item[i]){ //find some range, and let find their child also.
//                         cursor = cursor->children[i];
//                         break;
//                     }
//                     if(i == (cursor->size)-1){
//                         cursor = cursor->children[i+1];
//                         break;
//                     }
//                 }
//             }

//             //search for the key if it exists in leaf node.
//             for(int i=0; i<cursor->size; i++){
//                 if(cursor->item[i] == key){
//                     return cursor;
//                 }
//             }

//             return nullptr;
//         }
//     }
//     Node<T>* BPlusTreeRangeSearch(Node<T>* node, T key){
//         if(node == nullptr) { // if root is null, return nullptr
//             return nullptr;
//         }
//         else{
//             Node<T>* cursor = node; // cursor finding key

//             while(!cursor->leaf){ // until cusor pointer arrive leaf
//                 for(int i=0; i<cursor->size; i++){ //in this index node, find what we want key
//                     if(key < cursor->item[i]){ //find some range, and let find their child also.
//                         cursor = cursor->children[i];
//                         break;
//                     }
//                     if(i == (cursor->size)-1){
//                         cursor = cursor->children[i+1];
//                         break;
//                     }
//                 }
//             }
//             return cursor;
//         }
//     }
//     int range_search(T start, T end, T* result_data, int arr_length) {
//         int index=0;

//         Node<T>* start_node = BPlusTreeRangeSearch(this->root,start);
//         Node<T>* cursor = start_node;
//         T temp= cursor->item[0];

//         while(temp<=end){
//             if(cursor == nullptr){
//                 break;
//             }
//             for(int i=0; i< cursor->size;i++){
//                 temp = cursor->item[i];
//                 if((temp >= start)&&(temp <= end)){
//                     result_data[index] = temp;
//                     index++;
//                 }
//             }
//             cursor = cursor->children[cursor->size];
//         }
//         return index;
//     }
//     bool search(T data) {  // Return true if the item exists. Return false if it does not.
//         return BPlusTreeSearch(this->root, data) != nullptr;
//     }

//     int find_index(T* arr, T data, int len){
//         int index = 0;
//         for(int i=0; i<len; i++){
//             if(data < arr[i]){
//                 index = i;
//                 break;
//             }
//             if(i==len-1){
//                 index = len;
//                 break;
//             }
//         }
//         return index;
//     }
//     T* item_insert(T* arr, T data, int len){
//         int index = 0;
//         for(int i=0; i<len; i++){
//             if(data < arr[i]){
//                 index = i;
//                 break;
//             }
//             if(i==len-1){
//                 index = len;
//                 break;
//             }
//         }

//         for(int i = len; i > index; i--){
//             arr[i] = arr[i-1];
//         }

//         arr[index] = data;

//         return arr;
//     }
//     Node<T>** child_insert(Node<T>** child_arr, Node<T>*child,int len,int index){
//         for(int i= len; i > index; i--){
//             child_arr[i] = child_arr[i - 1];
//         }
//         child_arr[index] = child;
//         return child_arr;
//     }
//     Node<T>* child_item_insert(Node<T>* node, T data, Node<T>* child){
//         int item_index=0;
//         int child_index=0;
//         for(int i=0; i< node->size; i++){
//             if(data < node->item[i]){
//                 item_index = i;
//                 child_index = i+1;
//                 break;
//             }
//             if(i==node->size-1){
//                 item_index = node->size;
//                 child_index = node->size+1;
//                 break;
//             }
//         }
//         for(int i = node->size;i > item_index; i--){
//             node->item[i] = node->item[i-1];
//         }
//         for(int i=node->size+1;i>child_index;i--){
//             node->children[i] = node->children[i-1];
//         }

//         node->item[item_index] = data;
//         node->children[child_index] = child;

//         return node;
//     }
//     void InsertPar(Node<T>* par,Node<T>* child, T data){
//         //overflow check
//         Node<T>* cursor = par;
//         if(cursor->size < this->degree-1){//not overflow, just insert in the correct position
//             //insert item, child, and reallocate
//             cursor = child_item_insert(cursor,data,child);
//             cursor->size++;
//         }
//         else{//overflow
//             //make new node
//             auto* Newnode = new Node<T>(this->degree);
//             Newnode->parent = cursor->parent;

//             //copy item
//             T* item_copy = new T[cursor->size+1];
//             for(int i=0; i<cursor->size; i++){
//                 item_copy[i] = cursor->item[i];
//             }
//             item_copy = item_insert(item_copy,data,cursor->size);

//             auto** child_copy = new Node<T>*[cursor->size+2];
//             for(int i=0; i<cursor->size+1;i++){
//                 child_copy[i] = cursor->children[i];
//             }
//             child_copy[cursor->size+1] = nullptr;
//             child_copy = child_insert(child_copy,child,cursor->size+1,find_index(item_copy,data,cursor->size+1));

//             //split nodes
//             cursor->size = (this->degree)/2;
//             if((this->degree) % 2 == 0){
//                 Newnode->size = (this->degree) / 2 -1;
//             }
//             else{
//                 Newnode->size = (this->degree) / 2;
//             }

//             for(int i=0; i<cursor->size;i++){
//                 cursor->item[i] = item_copy[i];
//                 cursor->children[i] = child_copy[i];
//             }
//             cursor->children[cursor->size] = child_copy[cursor->size];
//             //todo 안지워짐. 뒤에것.

//             for(int i=0; i < Newnode->size; i++){
//                 Newnode->item[i] = item_copy[cursor->size + i +1];
//                 Newnode->children[i] = child_copy[cursor->size+i+1];
//                 Newnode->children[i]->parent=Newnode;
//             }
//             Newnode->children[Newnode->size] = child_copy[cursor->size+Newnode->size+1];
//             Newnode->children[Newnode->size]->parent=Newnode;

//             T paritem = item_copy[this->degree/2];

//             delete[] item_copy;
//             delete[] child_copy;

//             //parent check
//             if(cursor->parent == nullptr){//if there are no parent node(root case)
//                 auto* Newparent = new Node<T>(this->degree);
//                 cursor->parent = Newparent;
//                 Newnode->parent = Newparent;

//                 Newparent->item[0] = paritem;
//                 Newparent->size++;

//                 Newparent->children[0] = cursor;
//                 Newparent->children[1] = Newnode;

//                 this->root = Newparent;

//                 //delete Newparent;
//             }
//             else{//if there already have parent node
//                 InsertPar(cursor->parent, Newnode, paritem);
//             }
//         }
//     }

//     void insert(T data) {
//         if(this->root == nullptr){
//             this->root = new Node<T>(this->degree);
//             this->root->leaf = true;
//             this->root->item[0] = data;
//             this->root->size = 1;

//             this->height = 1;
//         }
//         else{ //if the tree has at least one node
//             Node<T>* cursor = this->root;

//             //move to leaf node
//             cursor = BPlusTreeRangeSearch(cursor, data);

//             //overflow check
//             if (cursor->size < (this->degree-1))
//             { // not overflow, just insert in the correct position
//                 //item insert and rearrange
//                 cursor->item = item_insert(cursor->item,data,cursor->size);
//                 cursor->size++;
//                 //edit pointer(next node)
//                 cursor->children[cursor->size] = cursor->children[cursor->size-1];
//                 cursor->children[cursor->size-1] = nullptr;
//             }
//             else{//overflow case
//                 //make new node
//                 auto* Newnode = new Node<T>(this->degree);
//                 Newnode->leaf = true;
//                 Newnode->parent = cursor->parent;

//                 //copy item
//                 T* item_copy = new T[cursor->size+1];
//                 for(int i=0; i<cursor->size; i++){
//                     item_copy[i] = cursor->item[i];
//                 }

//                 //insert and rearrange
//                 item_copy = item_insert(item_copy,data,cursor->size);

//                 //split nodes
//                 cursor->size = (this->degree)/2;
//                 if((this->degree) % 2 == 0){
//                     Newnode->size = (this->degree) / 2;
//                 }
//                 else{
//                     Newnode->size = (this->degree) / 2 + 1;
//                 }

//                 for(int i=0; i<cursor->size;i++){
//                     cursor->item[i] = item_copy[i];
//                 }
//                 for(int i=0; i < Newnode->size; i++){
//                     Newnode->item[i] = item_copy[cursor->size + i];
//                 }

//                 cursor->children[cursor->size] = Newnode;
//                 Newnode->children[Newnode->size] = cursor->children[this->degree-1];
//                 cursor->children[this->degree-1] = nullptr;

//                 delete[] item_copy;

//                 //parent check
//                 T paritem = Newnode->item[0];

//                 if(cursor->parent == nullptr){//if there are no parent node(root case)
//                     auto* Newparent = new Node<T>(this->degree);
//                     cursor->parent = Newparent;
//                     Newnode->parent = Newparent;

//                     Newparent->item[0] = paritem;
//                     Newparent->size++;

//                     Newparent->children[0] = cursor;
//                     Newparent->children[1] = Newnode;

//                     this->root = Newparent;
//                 }
//                 else{//if there already have parent node
//                     InsertPar(cursor->parent, Newnode, paritem);
//                 }
//             }
//             this->height += 1;
//         }
//     }

//     void remove(T data) { // Remove an item from the tree.
//         //make cursor
//         Node<T>* cursor = this->root;

//         //move to leaf node
//         cursor = BPlusTreeRangeSearch(cursor,data);

//         //make sibling index
//         int sib_index =-1;
//         for(int i=0; i<cursor->parent->size+1;i++){
//             if(cursor == cursor->parent->children[i]){
//                 sib_index = i;
//             }
//         }
//         int left=sib_index-1;
//         int right=sib_index+1;


//         //find data
//         int del_index=-1;
//         for(int i=0; i< cursor->size; i++){
//             if(cursor->item[i] == data){
//                 del_index = i;
//                 break;
//             }
//         }
//         //if data dosen't exist, nothing happen
//         if(del_index==-1){
//             return; // there is no match remove value
//         }

//         //remove data
//         for(int i=del_index; i<cursor->size-1;i++){
//             cursor->item[i] = cursor->item[i+1];
//         }
//         cursor->item[cursor->size-1] = 0;
//         cursor->size--;

//         //if cursor is root, and there are no more data -> clean!
//         if(cursor == this->root && cursor->size==0){//root case
//             clear(this->root);
//             this->root = nullptr;
//             return;
//         }
//         cursor->children[cursor->size] = cursor->children[cursor->size+1];
//         cursor->children[cursor->size+1] = nullptr;


//         //underflow check
//         if(cursor == this->root){
//             return;
//         }
//         if(cursor->size < degree/2){//underflow case

//             if(left >= 0){// left_sibiling exists
//                 Node<T>* leftsibling= cursor->parent->children[left];

//                 if(leftsibling->size > degree/2){ //if data number is enough to use this node
//                     T* temp = new T[cursor->size+1];

//                     //copy item
//                     for(int i=0; i<cursor->size; i++){
//                         temp[i]=cursor->item[i];
//                     }

//                     //insert and rearrange
//                     item_insert(temp,leftsibling->item[leftsibling->size -1],cursor->size);
//                     for(int i=0; i<cursor->size+1; i++){
//                         cursor->item[i] = temp[i];
//                     }
//                     cursor->size++;
//                     delete[] temp;

//                     //pointer edit
//                     cursor->children[cursor->size] = cursor->children[cursor->size-1];
//                     cursor->children[cursor->size-1] = nullptr;

//                     //sibling property edit
//                     leftsibling->item[leftsibling->size-1] = 0;
//                     leftsibling->size--;
//                     leftsibling->children[leftsibling->size] = leftsibling->children[leftsibling->size+1]; //cursor
//                     leftsibling->children[leftsibling->size+1]= nullptr;

//                     //parent property edit
//                     cursor->parent->item[left] = cursor->item[0];

//                     return;
//                 }
//             }
//             if(right <= cursor->parent->size){// right_sibiling exists
//                 Node<T>* rightsibling = cursor->parent->children[right];

//                 if(rightsibling->size >degree/2){//if data number is enough to use this node
//                     T* temp = new T[cursor->size+1];

//                     //copy item
//                     for(int i=0; i<cursor->size; i++){
//                         temp[i]=cursor->item[i];
//                     }
//                     //insert and rearrange
//                     item_insert(temp,rightsibling->item[0],cursor->size);
//                     for(int i=0; i<cursor->size+1; i++){
//                         cursor->item[i] = temp[i];
//                     }
//                     cursor->size++;
//                     delete[] temp;

//                     //pointer edit
//                     cursor->children[cursor->size] = cursor->children[cursor->size-1];
//                     cursor->children[cursor->size-1] = nullptr;

//                     //sibling property edit
//                     for(int i=0; i<rightsibling->size-1;i++){
//                         rightsibling->item[i] = rightsibling->item[i+1];
//                     }
//                     rightsibling->item[rightsibling->size-1] = 0;
//                     rightsibling->size--;
//                     rightsibling->children[rightsibling->size] = rightsibling->children[rightsibling->size+1]; //cursor
//                     rightsibling->children[rightsibling->size+1]= nullptr;

//                     //parent property edit
//                     cursor->parent->item[right-1] = rightsibling->item[0];

//                     return;
//                 }
//             }

//             //if sibling is not enought to use their data
//             //we have to merge step

//             if(left>=0){ // left_sibling exists
//                 Node<T>* leftsibling = cursor->parent->children[left];

//                 //merge two leaf node
//                 for(int i=0; i<cursor->size; i++){
//                     leftsibling->item[leftsibling->size+i]=cursor->item[i];
//                 }
//                 //edit pointer
//                 leftsibling->children[leftsibling->size] = nullptr;
//                 leftsibling->size = leftsibling->size+cursor->size;
//                 leftsibling->children[leftsibling->size] = cursor->children[cursor->size];

//                 //parent property edit
//                 Removepar(cursor, left, cursor->parent);
//                 for(int i=0; i<cursor->size;i++){
//                     cursor->item[i]=0;
//                     cursor->children[i] = nullptr;
//                 }
//                 cursor->children[cursor->size] = nullptr;

//                 delete[] cursor->item;
//                 delete[] cursor->children;
//                 delete cursor;

//                 return;

//             }
//             if(right<=cursor->parent->size){ // right_sibiling exists
//                 Node<T>* rightsibling = cursor->parent->children[right];

//                 //merge two leaf node
//                 for(int i=0; i<rightsibling->size; i++){
//                     cursor->item[i+cursor->size]=rightsibling->item[i];
//                 }
//                 //edit pointer
//                 cursor->children[cursor->size] = nullptr;
//                 cursor->size = rightsibling->size+cursor->size;
//                 cursor->children[cursor->size] = rightsibling->children[rightsibling->size];

//                 //parent property edit
//                 Removepar(rightsibling, right-1, cursor->parent);

//                 for(int i=0; i<rightsibling->size;i++){
//                     rightsibling->item[i]=0;
//                     rightsibling->children[i] = nullptr;
//                 }
//                 rightsibling->children[rightsibling->size] = nullptr;

//                 delete[] rightsibling->item;
//                 delete[] rightsibling->children;
//                 delete rightsibling;
//                 return;

//             }

//         }
//         else{
//             return;
//         }
//     }

//     void Removepar(Node<T>* node, int index, Node<T>* par){
//         Node<T>* remover = node;
//         Node<T>* cursor = par;
//         T target = cursor->item[index];

//         //if cursor is root, and there are no more data -> child node is to be root!
//         if(cursor == this->root && cursor->size==1){//root case
//             if(remover == cursor->children[0]){
//                 delete[] remover->item;
//                 delete[] remover->children;
//                 delete remover;
//                 this->root = cursor->children[1];
//                 delete[] cursor->item;
//                 delete[] cursor->children;
//                 delete cursor;
//                 return;
//             }
//             if(remover == cursor->children[1]){
//                 delete[] remover->item;
//                 delete[] remover->children;
//                 delete remover;
//                 this->root = cursor->children[0];
//                 delete[] cursor->item;
//                 delete[] cursor->children;
//                 delete cursor;
//                 return;
//             }
//         }

//         //remove data
//         for(int i=index; i<cursor->size-1;i++){
//             cursor->item[i] = cursor->item[i+1];
//         }
//         cursor->item[cursor->size-1] = 0;

//         //remove pointer
//         int rem_index = -1;
//         for(int i=0; i<cursor->size+1;i++){
//             if(cursor->children[i] == remover){
//                 rem_index = i;
//             }
//         }
//         if(rem_index == -1){
//             return;
//         }
//         for(int i=rem_index; i<cursor->size;i++){
//             cursor->children[i] = cursor->children[i+1];
//         }
//         cursor->children[cursor->size] = nullptr;
//         cursor->size--;

//         //underflow check
//         if(cursor == this->root){
//             return;
//         }
//         if(cursor->size < degree/2){//underflow case

//             int sib_index =-1;
//             for(int i=0; i<cursor->parent->size+1;i++){
//                 if(cursor == cursor->parent->children[i]){
//                     sib_index = i;
//                 }
//             }
//             int left=sib_index-1;
//             int right=sib_index+1;

//             if(left >= 0){// left_sibiling exists
//                 Node<T>* leftsibling= cursor->parent->children[left];

//                 if(leftsibling->size > degree/2){ //if data number is enough to use this node
//                     T* temp = new T[cursor->size+1];

//                     //copy item
//                     for(int i=0; i<cursor->size; i++){
//                         temp[i]=cursor->item[i];
//                     }

//                     //insert and rearrange at cursor
//                     item_insert(temp, cursor->parent->item[left],cursor->size);
//                     for(int i=0; i<cursor->size+1; i++){
//                         cursor->item[i] = temp[i];
//                     }
//                     cursor->parent->item[left] = leftsibling->item[leftsibling->size-1];
//                     delete[] temp;

//                     Node<T>** child_temp = new Node<T>*[cursor->size+2];
//                     //copy child node
//                     for(int i=0; i<cursor->size+1; i++){
//                         child_temp[i]=cursor->children[i];
//                     }
//                     //insert and rearrange at child
//                     child_insert(child_temp,leftsibling->children[leftsibling->size],cursor->size,0);

//                     for(int i=0; i<cursor->size+2; i++){
//                         cursor->children[i] = child_temp[i];
//                     }
//                     delete[] child_temp;

//                     //size edit
//                     cursor->size++;
//                     leftsibling->size--;
//                     return;

//                 }
//             }

//             if(right <= cursor->parent->size){// right_sibiling exists
//                 Node<T>* rightsibling = cursor->parent->children[right];

//                 if(rightsibling->size > degree/2){//if data number is enough to use this node
//                     T* temp = new T[cursor->size+1];

//                     //copy item
//                     for(int i=0; i<cursor->size; i++){
//                         temp[i]=cursor->item[i];
//                     }
//                     //insert and rearrange at cursor
//                     item_insert(temp,cursor->parent->item[sib_index],cursor->size);
//                     for(int i=0; i<cursor->size+1; i++){
//                         cursor->item[i] = temp[i];
//                     }
//                     cursor->parent->item[sib_index] = rightsibling->item[0];
//                     delete[] temp;

//                     //insert and reaarange at child

//                     cursor->children[cursor->size+1] = rightsibling->children[0];
//                     for(int i=0; i<rightsibling->size; i++){
//                         rightsibling->children[i] = rightsibling->children[i+1];
//                     }
//                     rightsibling->children[rightsibling->size] = nullptr;

//                     cursor->size++;
//                     rightsibling->size--;
//                     return;

//                 }
//             }

//             //if sibling is not enought to use their data
//             //we have to merge step
//             if(left>=0){ // left_sibling exists
//                 Node<T>* leftsibling = cursor->parent->children[left];

//                 leftsibling->item[leftsibling->size] = cursor->parent->item[left];
//                 //merge two leaf node
//                 for(int i=0; i<cursor->size; i++){
//                     leftsibling->item[leftsibling->size+i+1]=cursor->item[i];
//                 }
//                 for(int i=0; i<cursor->size+1;i++){
//                     leftsibling->children[leftsibling->size+i+1] = cursor->children[i];
//                     cursor->children[i]->parent = leftsibling;
//                 }
//                 for(int i=0; i<cursor->size+1; i++){
//                     cursor->children[i] = nullptr;
//                 }
//                 leftsibling->size = leftsibling->size+cursor->size+1;
//                 //delete recursion
//                 Removepar(cursor, left,cursor->parent);
//                 return;

//             }
//             if(right<=cursor->parent->size){ // right_sibiling exists
//                 Node<T>* rightsibling = cursor->parent->children[right];

//                 cursor->item[cursor->size] = cursor->parent->item[right-1];
//                 //merge two leaf node
//                 for(int i=0; i<rightsibling->size; i++){
//                     cursor->item[cursor->size+1+i]=rightsibling->item[i];
//                 }
//                 for(int i=0; i<rightsibling->size+1;i++){
//                     cursor->children[cursor->size+i+1] = rightsibling->children[i];
//                     rightsibling->children[i]->parent=rightsibling;
//                 }
//                 for(int i=0; i<rightsibling->size+1; i++){
//                     rightsibling->children[i] = nullptr;
//                 }
//                 //edit pointer
//                 rightsibling->size = rightsibling->size+cursor->size+1;
//                 //parent property edit
//                 Removepar(rightsibling, right-1,cursor->parent);
//                 return;
//             }
//         }
//         else{
//             return;
//         }
//     }

//     void clear(Node<T>* cursor){
//         if(cursor != nullptr){
//             if(!cursor->leaf){
//                 for(int i=0; i <= cursor->size; i++){
//                     clear(cursor->children[i]);
//                 }
//             }
//             delete[] cursor->item;
//             delete[] cursor->children;
//             delete cursor;
//         }
//     }
//     void bpt_print(){
//         print(this->root);
//     }
//     void print(Node<T>* cursor) {
//         // You must NOT edit this function.
//         if (cursor != NULL) {
//             for (int i = 0; i < cursor->size; ++i) {
//                 cout << cursor->item[i] << " ";
//             }
//             cout << "\n";

//             if (!cursor->leaf) {
//                 for (int i = 0; i < cursor->size + 1; ++i) {
//                     print(cursor->children[i]);
//                 }
//             }
//         }
//     }

//     void displayPretty()
//     {
//         for (int i = 1; i <= height; ++i) {
//             displayGivenLevel(root, i);
//             cout << "\n";
//         }
//     }

//     void displayGivenLevel(Node<T>* node, int level)
//     {
//         if (node == nullptr)
//             return;
//         if (level == 1) {
// 	    	cout << "[ ";
// 	    	for (int i = 0; i < node->size; ++i) {
// 	    		cout << node->item[i] << " ";
// 	    	}
// 	    	cout << "]";
// 	    }
//         else {
// 	    	for (int i = 0; i <= node->size; ++i) {
// 	    		displayGivenLevel(node->children[i], level - 1);
// 	    		cout << " ";
// 	    	}
//         }
//     }
// };


# endif // B_PLUS_TREE_H