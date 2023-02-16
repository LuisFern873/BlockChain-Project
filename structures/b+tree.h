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




template <typename TK, typename TV>
struct Node
{
    TK* key;
    TV** data;

    Node** ptr;
    int size;
    bool IS_LEAF;

    void display();
    Node();
    ~Node();
};


template <typename TK, typename TV>
Node<TK,TV>::Node()
{
    size = 0;
    key = new TK[MAX];
    data = new TV*[MAX];
    ptr = new Node*[MAX + 1];
}

template <typename TK, typename TV>
Node<TK,TV>::~Node()
{
    delete[] key;
    delete[] data;
    delete[] ptr;
}

template <typename TK, typename TV>
void display()
{

}


template <typename TK, typename TV>
class BPlusTree
{
    public:
        BPlusTree();
        void search(TK);
        void insert(TK, TV);
        void remove(TK);
        void displayPretty();
        size_t height();

        void iterateLeafNodes();

    private:
        using Node = Node<TK,TV>;
        Node* root;
        void insertInternal(TK, TV, Node*, Node*);
        Node* findParent(Node*, Node*);
        void displayGivenLevel(Node* node, int level);
        void removeInternal(TK x, TV y, Node *cursor, Node *child);
};

template <typename TK, typename TV>
BPlusTree<TK,TV>::BPlusTree() 
{
    root = nullptr;
}

template <typename TK, typename TV>
size_t BPlusTree<TK,TV>::height()
{
    if (root == nullptr)
        return 0;

    Node* current = root;
    size_t height = 1;

    while (current->IS_LEAF == false) {
        ++height;
        current = current->ptr[0];
    }

    return height;
}

template <typename TK, typename TV>
void BPlusTree<TK,TV>::displayPretty()
{
    for (int i = 1; i <= height(); ++i) {
        displayGivenLevel(root, i);
        cout << "\n";
    }
}

template <typename TK, typename TV>
void BPlusTree<TK,TV>::displayGivenLevel(Node* node, int level)
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

template <typename TK, typename TV>
void BPlusTree<TK,TV>::search(TK x)
{
    if (root == nullptr) {
        cout << "Tree is empty\n";
    } 
    else {
        Node* cursor = root;
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
                cout << *cursor->data[i] << "\n"; // Show content of data pointer
                return;
            }
        }
        cout << "Not found\n";
    }
}

template <typename TK, typename TV>
void BPlusTree<TK,TV>::iterateLeafNodes() 
{
    if (root == nullptr) {
        cout << "The tree is empty." << endl;
        return;
    }

    Node* cursor = root;
    while (cursor->IS_LEAF == false) {
        cursor = cursor->ptr[0];
    }

    while (cursor != nullptr) {
        cout << "cursor->size:" << cursor->size << "\n";
        for (int i = 0; i < cursor->size; i++) {
            cout << *cursor->data[i] << "\n";
        }
        cursor = cursor->ptr[cursor->size];
    }
}



template <typename TK, typename TV>
void BPlusTree<TK,TV>::insert(TK x, TV y) 
{
    if (root == nullptr) {
        root = new Node;
        root->key[0] = x;
        root->data[0] = &y; // Assign pointer to data
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
            while (x > cursor->key[i] && i < cursor->size) {
                i++;
            }

            for (int j = cursor->size; j > i; j--) {
                cursor->key[j] = cursor->key[j - 1];
                cursor->data[j] = cursor->data[j - 1]; // Along with keys, shift data pointers
            }
            cursor->key[i] = x;
            cursor->data[i] = &y; // Assign pointer to data

            cursor->size++;
            cursor->ptr[cursor->size] = cursor->ptr[cursor->size - 1];
            cursor->ptr[cursor->size - 1] = nullptr;
        }
        else {
            Node* newLeaf = new Node;
            TK virtualNode[MAX + 1];
            TV* virtualData[MAX + 1];

            for (int i = 0; i < MAX; i++) {
                virtualNode[i] = cursor->key[i];
                virtualData[i] = cursor->data[i];
            }

            int i = 0, j;

            while (x > virtualNode[i] && i < MAX)
                i++;

            for (int j = MAX; j > i; j--) {
                virtualNode[j] = virtualNode[j - 1];
                virtualData[j] = virtualData[j - 1];
            }

            virtualNode[i] = x;
            virtualData[i] = &y;

            newLeaf->IS_LEAF = true;
            cursor->size = (MAX + 1) / 2;
            newLeaf->size = MAX + 1 - (MAX + 1) / 2;
            cursor->ptr[cursor->size] = newLeaf;
            newLeaf->ptr[newLeaf->size] = cursor->ptr[MAX];
            cursor->ptr[MAX] = nullptr;

            for (i = 0; i < cursor->size; i++) {
                cursor->key[i] = virtualNode[i];
                cursor->data[i] = virtualData[i];
            }
            for (i = 0, j = cursor->size; i < newLeaf->size; i++, j++) {
                newLeaf->key[i] = virtualNode[j];
                newLeaf->data[i] = virtualData[j];
            }

            if (cursor == root) {
                Node* newRoot = new Node;
                newRoot->key[0] = newLeaf->key[0];
                newRoot->data[0] = newLeaf->data[0];

                newRoot->ptr[0] = cursor;
                newRoot->ptr[1] = newLeaf;
                newRoot->IS_LEAF = false;
                newRoot->size = 1;
                root = newRoot;
            }
            else {
                insertInternal(newLeaf->key[0], *newLeaf->data[0], parent, newLeaf);
            }
        }
    }
}

template <typename TK, typename TV>
void BPlusTree<TK,TV>::insertInternal(TK x, TV y, Node* cursor, Node* child)
{
    if (cursor->size < MAX) {
        int i = 0;
        while (x > cursor->key[i] && i < cursor->size)
            i++;
        for (int j = cursor->size; j > i; j--) {
            cursor->key[j] = cursor->key[j - 1];
            cursor->data[j] = cursor->data[j - 1];
        }
        for (int j = cursor->size + 1; j > i + 1; j--) {
            cursor->ptr[j] = cursor->ptr[j - 1];
        }
        cursor->key[i] = x;
        cursor->data[i] = &y;

        cursor->size++;
        cursor->ptr[i + 1] = child;
    } 
    else {
        Node* newInternal = new Node;
        TK virtualKey[MAX + 1];
        TV* virtualData[MAX + 1]; // MOD!!!!
        Node* virtualPtr[MAX + 2];

        for (int i = 0; i < MAX; i++) {
            virtualKey[i] = cursor->key[i];
            virtualData[i] = cursor->data[i];
        }
        for (int i = 0; i < MAX + 1; i++) {
            virtualPtr[i] = cursor->ptr[i];
        }

        int i = 0, j;
        while (x > virtualKey[i] && i < MAX)
            i++;
            
        for (int j = MAX; j > i; j--) {
            virtualKey[j] = virtualKey[j - 1];
            virtualData[j] = virtualData[j - 1];
        }

        virtualKey[i] = x;
        virtualData[i] = &y;

        for (int j = MAX + 1; j > i + 1; j--) {
            virtualPtr[j] = virtualPtr[j - 1];
        }
        virtualPtr[i + 1] = child;
        newInternal->IS_LEAF = false;
        cursor->size = (MAX + 1) / 2;
        newInternal->size = MAX - (MAX + 1) / 2;
        for (i = 0, j = cursor->size + 1; i < newInternal->size; i++, j++) {
            newInternal->key[i] = virtualKey[j];
            newInternal->data[i] = virtualData[j];
        }
        for (i = 0, j = cursor->size + 1; i < newInternal->size + 1; i++, j++) {
            newInternal->ptr[i] = virtualPtr[j];
        }
        if (cursor == root) {
            Node* newRoot = new Node;
            newRoot->key[0] = cursor->key[cursor->size];
            newRoot->data[0] = cursor->data[cursor->size];

            newRoot->ptr[0] = cursor;
            newRoot->ptr[1] = newInternal;
            newRoot->IS_LEAF = false;
            newRoot->size = 1;
            root = newRoot;
        } else {
            insertInternal(cursor->key[cursor->size], *cursor->data[cursor->size], findParent(root, cursor), newInternal);
        }
  }
}


template <typename TK, typename TV>
Node<TK,TV>* BPlusTree<TK,TV>::findParent(Node* cursor, Node* child) 
{
    Node* parent;
    
    if (cursor->IS_LEAF || (cursor->ptr[0])->IS_LEAF)
        return nullptr;

    for (int i = 0; i < cursor->size + 1; i++) {
        if (cursor->ptr[i] == child) {
            parent = cursor;
            return parent;
        } 
        else {
            parent = findParent(cursor->ptr[i], child);
            if (parent != nullptr)
                return parent;
        }
    }
    return parent;
}




template <typename TK, typename TV>
void BPlusTree<TK,TV>::remove(TK x) {
    if (root == nullptr) {
        cout << "Tree empty\n";
    } 
    else {
        Node* cursor = root;
        Node* parent;
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
            cursor->data[i] = cursor->data[i + 1]; // MOD!!!
        }
        cursor->size--;

        if (cursor == root) {
            for (int i = 0; i < MAX + 1; i++) {
                cursor->ptr[i] = nullptr;
            }
            if (cursor->size == 0) {
                cout << "Tree died\n";
                delete cursor;
                root = nullptr;
            }
            return;
        }

        cursor->ptr[cursor->size] = cursor->ptr[cursor->size + 1];
        cursor->ptr[cursor->size + 1] = nullptr;
        if (cursor->size >= (MAX + 1) / 2) {
            return;
        }
        if (leftSibling >= 0) {
            Node* leftNode = parent->ptr[leftSibling];
            if (leftNode->size >= (MAX + 1) / 2 + 1) {
                for (int i = cursor->size; i > 0; i--) {
                    cursor->key[i] = cursor->key[i - 1];
                    cursor->data[i] = cursor->data[i - 1];
                }
                cursor->size++;
                cursor->ptr[cursor->size] = cursor->ptr[cursor->size - 1];
                cursor->ptr[cursor->size - 1] = nullptr;
                cursor->key[0] = leftNode->key[leftNode->size - 1];
                cursor->data[0] = leftNode->data[leftNode->size - 1];
                leftNode->size--;
                leftNode->ptr[leftNode->size] = cursor;
                leftNode->ptr[leftNode->size + 1] = nullptr;
                parent->key[leftSibling] = cursor->key[0];
                parent->data[leftSibling] = cursor->data[0];
                return;
            }
        }
        if (rightSibling <= parent->size) {
            Node* rightNode = parent->ptr[rightSibling];
            if (rightNode->size >= (MAX + 1) / 2 + 1) {
                cursor->size++;
                cursor->ptr[cursor->size] = cursor->ptr[cursor->size - 1];
                cursor->ptr[cursor->size - 1] = nullptr;
                cursor->key[cursor->size - 1] = rightNode->key[0];
                cursor->data[cursor->size - 1] = rightNode->data[0];
                rightNode->size--;
                rightNode->ptr[rightNode->size] = rightNode->ptr[rightNode->size + 1];
                rightNode->ptr[rightNode->size + 1] = nullptr;

                for (int i = 0; i < rightNode->size; i++) {
                    rightNode->key[i] = rightNode->key[i + 1];
                    rightNode->data[i] = rightNode->data[i + 1];
                }

                parent->key[rightSibling - 1] = rightNode->key[0];
                parent->data[rightSibling - 1] = rightNode->data[0];
                return;
            }
        }
        if (leftSibling >= 0) {
            Node* leftNode = parent->ptr[leftSibling];
            for (int i = leftNode->size, j = 0; j < cursor->size; i++, j++) {
                leftNode->key[i] = cursor->key[j];
                leftNode->data[i] = cursor->data[j];
            }
            leftNode->ptr[leftNode->size] = nullptr;
            leftNode->size += cursor->size;
            leftNode->ptr[leftNode->size] = cursor->ptr[cursor->size];
            removeInternal(parent->key[leftSibling], *parent->data[leftSibling], parent, cursor);

            delete cursor;
        }  
        else if (rightSibling <= parent->size) {
            Node* rightNode = parent->ptr[rightSibling];
            for (int i = cursor->size, j = 0; j < rightNode->size; i++, j++) {
                cursor->key[i] = rightNode->key[j];
                cursor->data[i] = rightNode->data[j];
            }
            cursor->ptr[cursor->size] = nullptr;
            cursor->size += rightNode->size;
            cursor->ptr[cursor->size] = rightNode->ptr[rightNode->size];
            cout << "Merging two leaf nodes\n";
            removeInternal(parent->key[rightSibling - 1], *parent->data[rightSibling - 1], parent, rightNode);

            delete rightNode;
        }
    }
}

template <typename TK, typename TV>
void BPlusTree<TK,TV>::removeInternal(TK x, TV y, Node *cursor, Node *child) {
    if (cursor == root) {
        if (cursor->size == 1) {
            if (cursor->ptr[1] == child) {
                delete child;
                root = cursor->ptr[0];
                delete cursor;
                cout << "Changed root node\n";
                return;
            } 
            else if (cursor->ptr[0] == child) {
                delete child;
                root = cursor->ptr[1];
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
        cursor->data[i] = cursor->data[i + 1];
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

    Node* parent = findParent(root, cursor);
    int leftSibling, rightSibling;

    for (pos = 0; pos < parent->size + 1; pos++) {
        if (parent->ptr[pos] == cursor) {
            leftSibling = pos - 1;
            rightSibling = pos + 1;
            break;
        }
    }

    if (leftSibling >= 0) {
        Node* leftNode = parent->ptr[leftSibling];
        if (leftNode->size >= (MAX + 1) / 2) {
            for (int i = cursor->size; i > 0; i--) {
                cursor->key[i] = cursor->key[i - 1];
                cursor->data[i] = cursor->data[i - 1];
            }
            cursor->key[0] = parent->key[leftSibling];
            cursor->data[0] = parent->data[leftSibling];

            parent->key[leftSibling] = leftNode->key[leftNode->size - 1];
            parent->data[leftSibling] = leftNode->data[leftNode->size - 1];

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
        Node* rightNode = parent->ptr[rightSibling];

        if (rightNode->size >= (MAX + 1) / 2) {
            cursor->key[cursor->size] = parent->key[pos];
            cursor->data[cursor->size] = parent->data[pos];
            parent->key[pos] = rightNode->key[0];
            parent->data[pos] = rightNode->data[0];

            for (int i = 0; i < rightNode->size - 1; i++) {
                rightNode->key[i] = rightNode->key[i + 1];
                rightNode->data[i] = rightNode->data[i + 1];
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
        Node* leftNode = parent->ptr[leftSibling];
        leftNode->key[leftNode->size] = parent->key[leftSibling];
        leftNode->data[leftNode->size] = parent->data[leftSibling];

        for (int i = leftNode->size + 1, j = 0; j < cursor->size; j++) {
            leftNode->key[i] = cursor->key[j];
            leftNode->data[i] = cursor->data[j];
        }
        for (int i = leftNode->size + 1, j = 0; j < cursor->size + 1; j++) {
            leftNode->ptr[i] = cursor->ptr[j];
            cursor->ptr[j] = nullptr;
        }
        leftNode->size += cursor->size + 1;
        cursor->size = 0;
        removeInternal(parent->key[leftSibling], *parent->data[leftSibling], parent, cursor);
    } 
    else if (rightSibling <= parent->size) {
        Node *rightNode = parent->ptr[rightSibling];
        cursor->key[cursor->size] = parent->key[rightSibling - 1];
        cursor->data[cursor->size] = parent->data[rightSibling - 1];

        for (int i = cursor->size + 1, j = 0; j < rightNode->size; j++) {
            cursor->key[i] = rightNode->key[j];
            cursor->data[i] = rightNode->data[j];
        }
        for (int i = cursor->size + 1, j = 0; j < rightNode->size + 1; j++) {
            cursor->ptr[i] = rightNode->ptr[j];
            rightNode->ptr[j] = nullptr;
        }
        cursor->size += rightNode->size + 1;
        rightNode->size = 0;
        removeInternal(parent->key[rightSibling - 1], *parent->data[rightSibling - 1], parent, rightNode);
    }
}   


# endif // B_PLUS_TREE_H