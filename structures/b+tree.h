# ifndef B_PLUS_TREE_H
# define B_PLUS_TREE_H

# include <iostream>
# include <vector>
# include <climits>
# include <fstream>
# include <sstream>

using namespace std;

int MAX = 5;

template <typename TK, typename TV>
class BPlusTree
{
    public:
        BPlusTree();
        TV search(TK key);
        vector<TV> rangeSearch(TK start, TK end);
        TV min();
        TV max();

        void insert(TK key, TV value);
        void remove(TK key);
        void displayPretty();
        int height();

    private:
        struct Node {
            TK* key;
            TV* value;

            Node** children;
            int count;
            bool leaf;
    
            Node();
            ~Node();
        };

        Node* root;
        void rangeSearch(Node* node, TK start, TK end, vector<TV>& report);
        void insertInternal(TK, TV, Node*, Node*);
        Node* findParent(Node*, Node*);
        void displayGivenLevel(Node* node, int level);
        void removeInternal(TK x, TV y, Node* cursor, Node* child);
};

template <typename TK, typename TV>
BPlusTree<TK,TV>::Node::Node()
{
    count = 0;
    key = new TK[MAX];
    value = new TV[MAX];
    children = new Node*[MAX + 1];
}

template <typename TK, typename TV>
BPlusTree<TK,TV>::Node::~Node()
{
    delete[] key;
    delete[] value;
    delete[] children;
}

template <typename TK, typename TV>
BPlusTree<TK,TV>::BPlusTree() 
{
    root = nullptr;
}

template <typename TK, typename TV>
int BPlusTree<TK,TV>::height()
{
    if (root == nullptr)
        return 0;

    Node* current = root;
    int height = 1;

    while (current->leaf == false) {
        ++height;
        current = current->children[0];
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
		for (int i = 0; i < node->count; ++i) {
			cout << node->key[i] << " ";
		}
		cout << "]";
	}
    else {
		for (int i = 0; i <= node->count; ++i) {
			displayGivenLevel(node->children[i], level - 1);
			cout << " ";
		}
    }
}

template <typename TK, typename TV>
vector<TV> BPlusTree<TK,TV>::rangeSearch(TK start, TK end){
    vector<TV> report; 
	rangeSearch(root, start, end, report);
    return report;
}

template <typename TK, typename TV>
void BPlusTree<TK,TV>::rangeSearch(Node* node, TK start, TK end, vector<TV>& report){

    if (node == nullptr)
        return;

    int i = 0;
    while (i < node->count and node->key[i] < start)
		++i;

    while (i < node->count and node->key[i] <= end) {
		if (!node->leaf)
        	rangeSearch(node->children[i], start, end, report);
        else
            report.push_back(node->value[i]);
        ++i;
    }
		
	if (!node->leaf)
        rangeSearch(node->children[i], start, end, report);
}

template <typename TK, typename TV>
TV BPlusTree<TK,TV>::min()
{
	if (root == nullptr)
		throw runtime_error("B+ tree is empty");

	Node* current = root;

	while (current->leaf == false)
	{
		current = current->children[0];
	}

	return current->value[0];
}

template <typename TK, typename TV>
TV BPlusTree<TK,TV>::max()
{
	if (root == nullptr)
		throw runtime_error("B+ tree is empty");

	Node* current = root;

	while (current->leaf == false)
	{
		current = current->children[current->count];
	}

	return current->value[current->count - 1];
}

template <typename TK, typename TV>
TV BPlusTree<TK,TV>::search(TK x)
{
    if (root == nullptr)
        throw runtime_error("B+ tree is empty");
    
    Node* cursor = root;
    while (cursor->leaf == false) {
        for (int i = 0; i < cursor->count; i++) {
            if (x < cursor->key[i]) {
                cursor = cursor->children[i];
                break;
            }
            if (i == cursor->count - 1) {
                cursor = cursor->children[i + 1];
                break;
            }
        }
    }
    for (int i = 0; i < cursor->count; i++) {
        if (cursor->key[i] == x) {
            cout << "Found\n";
            return cursor->value[i];
        }
    }
    cout << "Not found\n";
    return TV();
}


template <typename TK, typename TV>
void BPlusTree<TK,TV>::insert(TK x, TV y) 
{
    if (root == nullptr) {
        root = new Node;
        root->key[0] = x;
        root->value[0] = y; // Assign pointer to value
        root->leaf = true;
        root->count = 1;
    }
    else {
        Node* cursor = root;
        Node* parent;

        while (cursor->leaf == false)
        {
            parent = cursor;
            for (int i = 0; i < cursor->count; i++) {
                if (x < cursor->key[i]) {
                    cursor = cursor->children[i];
                    break;
                }
                if (i == cursor->count - 1) {
                    cursor = cursor->children[i + 1];
                    break;
                }
            }
        }

        if (cursor->count < MAX) {
            int i = 0;
            while (x > cursor->key[i] && i < cursor->count) {
                i++;
            }

            for (int j = cursor->count; j > i; j--) {
                cursor->key[j] = cursor->key[j - 1];
                cursor->value[j] = cursor->value[j - 1]; // Along with keys, shift value pointers
            }
            cursor->key[i] = x;
            cursor->value[i] = y; // Assign pointer to value

            cursor->count++;
            cursor->children[cursor->count] = cursor->children[cursor->count - 1];
            cursor->children[cursor->count - 1] = nullptr;
        }
        else {
            Node* newLeaf = new Node;
            TK virtualNode[MAX + 1];
            TV virtualvalue[MAX + 1];

            for (int i = 0; i < MAX; i++) {
                virtualNode[i] = cursor->key[i];
                virtualvalue[i] = cursor->value[i];
            }

            int i = 0, j;

            while (x > virtualNode[i] && i < MAX)
                i++;

            for (int j = MAX; j > i; j--) {
                virtualNode[j] = virtualNode[j - 1];
                virtualvalue[j] = virtualvalue[j - 1];
            }

            virtualNode[i] = x;
            virtualvalue[i] = y;

            newLeaf->leaf = true;
            cursor->count = (MAX + 1) / 2;
            newLeaf->count = MAX + 1 - (MAX + 1) / 2;
            cursor->children[cursor->count] = newLeaf;
            newLeaf->children[newLeaf->count] = cursor->children[MAX];
            cursor->children[MAX] = nullptr;

            for (i = 0; i < cursor->count; i++) {
                cursor->key[i] = virtualNode[i];
                cursor->value[i] = virtualvalue[i];
            }
            for (i = 0, j = cursor->count; i < newLeaf->count; i++, j++) {
                newLeaf->key[i] = virtualNode[j];
                newLeaf->value[i] = virtualvalue[j];
            }

            if (cursor == root) {
                Node* newRoot = new Node;
                newRoot->key[0] = newLeaf->key[0];
                newRoot->value[0] = newLeaf->value[0];

                newRoot->children[0] = cursor;
                newRoot->children[1] = newLeaf;
                newRoot->leaf = false;
                newRoot->count = 1;
                root = newRoot;
            }
            else {
                insertInternal(newLeaf->key[0], newLeaf->value[0], parent, newLeaf);
            }
        }
    }
}

template <typename TK, typename TV>
void BPlusTree<TK,TV>::insertInternal(TK x, TV y, Node* cursor, Node* child)
{
    if (cursor->count < MAX) {
        int i = 0;
        while (x > cursor->key[i] && i < cursor->count)
            i++;
        for (int j = cursor->count; j > i; j--) {
            cursor->key[j] = cursor->key[j - 1];
            cursor->value[j] = cursor->value[j - 1];
        }
        for (int j = cursor->count + 1; j > i + 1; j--) {
            cursor->children[j] = cursor->children[j - 1];
        }
        cursor->key[i] = x;
        cursor->value[i] = y;

        cursor->count++;
        cursor->children[i + 1] = child;
    } 
    else {
        Node* newInternal = new Node;
        TK virtualKey[MAX + 1];
        TV virtualvalue[MAX + 1]; // MOD!!!!
        Node* virtualchildren[MAX + 2];

        for (int i = 0; i < MAX; i++) {
            virtualKey[i] = cursor->key[i];
            virtualvalue[i] = cursor->value[i];
        }
        for (int i = 0; i < MAX + 1; i++) {
            virtualchildren[i] = cursor->children[i];
        }

        int i = 0, j;
        while (x > virtualKey[i] && i < MAX)
            i++;
            
        for (int j = MAX; j > i; j--) {
            virtualKey[j] = virtualKey[j - 1];
            virtualvalue[j] = virtualvalue[j - 1];
        }

        virtualKey[i] = x;
        virtualvalue[i] = y;

        for (int j = MAX + 1; j > i + 1; j--) {
            virtualchildren[j] = virtualchildren[j - 1];
        }
        virtualchildren[i + 1] = child;
        newInternal->leaf = false;
        cursor->count = (MAX + 1) / 2;
        newInternal->count = MAX - (MAX + 1) / 2;
        for (i = 0, j = cursor->count + 1; i < newInternal->count; i++, j++) {
            newInternal->key[i] = virtualKey[j];
            newInternal->value[i] = virtualvalue[j];
        }
        for (i = 0, j = cursor->count + 1; i < newInternal->count + 1; i++, j++) {
            newInternal->children[i] = virtualchildren[j];
        }
        if (cursor == root) {
            Node* newRoot = new Node;
            newRoot->key[0] = cursor->key[cursor->count];
            newRoot->value[0] = cursor->value[cursor->count];

            newRoot->children[0] = cursor;
            newRoot->children[1] = newInternal;
            newRoot->leaf = false;
            newRoot->count = 1;
            root = newRoot;
        } else {
            insertInternal(cursor->key[cursor->count], cursor->value[cursor->count], findParent(root, cursor), newInternal);
        }
  }
}


template <typename TK, typename TV>
BPlusTree<TK,TV>::Node* BPlusTree<TK,TV>::findParent(Node* cursor, Node* child) 
{
    Node* parent;
    
    if (cursor->leaf || (cursor->children[0])->leaf)
        return nullptr;

    for (int i = 0; i < cursor->count + 1; i++) {
        if (cursor->children[i] == child) {
            parent = cursor;
            return parent;
        } 
        else {
            parent = findParent(cursor->children[i], child);
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

        while (cursor->leaf == false) {
            for (int i = 0; i < cursor->count; i++) {
                parent = cursor;
                leftSibling = i - 1;
                rightSibling = i + 1;
                if (x < cursor->key[i]) {
                    cursor = cursor->children[i];
                    break;
                }
                if (i == cursor->count - 1) {
                    leftSibling = i;
                    rightSibling = i + 2;
                    cursor = cursor->children[i + 1];
                    break;
                }
            }
        }

        bool found = false;
        int pos;

        for (pos = 0; pos < cursor->count; pos++) {
            if (cursor->key[pos] == x) {
                found = true;
                break;
            }
        }
        
        if (!found) {
            cout << "Not found\n";
            return;
        }

        for (int i = pos; i < cursor->count; i++) {
            cursor->key[i] = cursor->key[i + 1];
            cursor->value[i] = cursor->value[i + 1]; // MOD!!!
        }
        cursor->count--;

        if (cursor == root) {
            for (int i = 0; i < MAX + 1; i++) {
                cursor->children[i] = nullptr;
            }
            if (cursor->count == 0) {
                cout << "Tree died\n";
                delete cursor;
                root = nullptr;
            }
            return;
        }

        cursor->children[cursor->count] = cursor->children[cursor->count + 1];
        cursor->children[cursor->count + 1] = nullptr;
        if (cursor->count >= (MAX + 1) / 2) {
            return;
        }
        if (leftSibling >= 0) {
            Node* leftNode = parent->children[leftSibling];
            if (leftNode->count >= (MAX + 1) / 2 + 1) {
                for (int i = cursor->count; i > 0; i--) {
                    cursor->key[i] = cursor->key[i - 1];
                    cursor->value[i] = cursor->value[i - 1];
                }
                cursor->count++;
                cursor->children[cursor->count] = cursor->children[cursor->count - 1];
                cursor->children[cursor->count - 1] = nullptr;
                cursor->key[0] = leftNode->key[leftNode->count - 1];
                cursor->value[0] = leftNode->value[leftNode->count - 1];
                leftNode->count--;
                leftNode->children[leftNode->count] = cursor;
                leftNode->children[leftNode->count + 1] = nullptr;
                parent->key[leftSibling] = cursor->key[0];
                parent->value[leftSibling] = cursor->value[0];
                return;
            }
        }
        if (rightSibling <= parent->count) {
            Node* rightNode = parent->children[rightSibling];
            if (rightNode->count >= (MAX + 1) / 2 + 1) {
                cursor->count++;
                cursor->children[cursor->count] = cursor->children[cursor->count - 1];
                cursor->children[cursor->count - 1] = nullptr;
                cursor->key[cursor->count - 1] = rightNode->key[0];
                cursor->value[cursor->count - 1] = rightNode->value[0];
                rightNode->count--;
                rightNode->children[rightNode->count] = rightNode->children[rightNode->count + 1];
                rightNode->children[rightNode->count + 1] = nullptr;

                for (int i = 0; i < rightNode->count; i++) {
                    rightNode->key[i] = rightNode->key[i + 1];
                    rightNode->value[i] = rightNode->value[i + 1];
                }

                parent->key[rightSibling - 1] = rightNode->key[0];
                parent->value[rightSibling - 1] = rightNode->value[0];
                return;
            }
        }
        if (leftSibling >= 0) {
            Node* leftNode = parent->children[leftSibling];
            for (int i = leftNode->count, j = 0; j < cursor->count; i++, j++) {
                leftNode->key[i] = cursor->key[j];
                leftNode->value[i] = cursor->value[j];
            }
            leftNode->children[leftNode->count] = nullptr;
            leftNode->count += cursor->count;
            leftNode->children[leftNode->count] = cursor->children[cursor->count];
            removeInternal(parent->key[leftSibling], parent->value[leftSibling], parent, cursor);

            delete cursor;
        }  
        else if (rightSibling <= parent->count) {
            Node* rightNode = parent->children[rightSibling];
            for (int i = cursor->count, j = 0; j < rightNode->count; i++, j++) {
                cursor->key[i] = rightNode->key[j];
                cursor->value[i] = rightNode->value[j];
            }
            cursor->children[cursor->count] = nullptr;
            cursor->count += rightNode->count;
            cursor->children[cursor->count] = rightNode->children[rightNode->count];
            cout << "Merging two leaf nodes\n";
            removeInternal(parent->key[rightSibling - 1], parent->value[rightSibling - 1], parent, rightNode);

            delete rightNode;
        }
    }
}

template <typename TK, typename TV>
void BPlusTree<TK,TV>::removeInternal(TK x, TV y, Node* cursor, Node* child) {
    if (cursor == root) {
        if (cursor->count == 1) {
            if (cursor->children[1] == child) {
                delete child;
                root = cursor->children[0];
                delete cursor;
                cout << "Changed root node\n";
                return;
            } 
            else if (cursor->children[0] == child) {
                delete child;
                root = cursor->children[1];
                delete cursor;
                cout << "Changed root node\n";
                return;
            }
        }
    }
    int pos;
    for (pos = 0; pos < cursor->count; pos++) {
        if (cursor->key[pos] == x) {
            break;
        }
    }
    for (int i = pos; i < cursor->count; i++) {
        cursor->key[i] = cursor->key[i + 1];
        cursor->value[i] = cursor->value[i + 1];
    }
    for (pos = 0; pos < cursor->count + 1; pos++) {
        if (cursor->children[pos] == child) {
            break;
        }
    }
    for (int i = pos; i < cursor->count + 1; i++) {
        cursor->children[i] = cursor->children[i + 1];
    }
    cursor->count--;
    if (cursor->count >= (MAX + 1) / 2 - 1) {
        return;
    }
    if (cursor == root)
        return;

    Node* parent = findParent(root, cursor);
    int leftSibling, rightSibling;

    for (pos = 0; pos < parent->count + 1; pos++) {
        if (parent->children[pos] == cursor) {
            leftSibling = pos - 1;
            rightSibling = pos + 1;
            break;
        }
    }

    if (leftSibling >= 0) {
        Node* leftNode = parent->children[leftSibling];
        if (leftNode->count >= (MAX + 1) / 2) {
            for (int i = cursor->count; i > 0; i--) {
                cursor->key[i] = cursor->key[i - 1];
                cursor->value[i] = cursor->value[i - 1];
            }
            cursor->key[0] = parent->key[leftSibling];
            cursor->value[0] = parent->value[leftSibling];

            parent->key[leftSibling] = leftNode->key[leftNode->count - 1];
            parent->value[leftSibling] = leftNode->value[leftNode->count - 1];

            for (int i = cursor->count + 1; i > 0; i--) {
                cursor->children[i] = cursor->children[i - 1];
            }
            cursor->children[0] = leftNode->children[leftNode->count];
            cursor->count++;
            leftNode->count--;
            return;
        }
    }
    if (rightSibling <= parent->count) {
        Node* rightNode = parent->children[rightSibling];

        if (rightNode->count >= (MAX + 1) / 2) {
            cursor->key[cursor->count] = parent->key[pos];
            cursor->value[cursor->count] = parent->value[pos];
            parent->key[pos] = rightNode->key[0];
            parent->value[pos] = rightNode->value[0];

            for (int i = 0; i < rightNode->count - 1; i++) {
                rightNode->key[i] = rightNode->key[i + 1];
                rightNode->value[i] = rightNode->value[i + 1];
            }
            cursor->children[cursor->count + 1] = rightNode->children[0];
            for (int i = 0; i < rightNode->count; ++i) {
                rightNode->children[i] = rightNode->children[i + 1];
            }
            cursor->count++;
            rightNode->count--;
            return;
        }
    }
    if (leftSibling >= 0) {
        Node* leftNode = parent->children[leftSibling];
        leftNode->key[leftNode->count] = parent->key[leftSibling];
        leftNode->value[leftNode->count] = parent->value[leftSibling];

        for (int i = leftNode->count + 1, j = 0; j < cursor->count; j++) {
            leftNode->key[i] = cursor->key[j];
            leftNode->value[i] = cursor->value[j];
        }
        for (int i = leftNode->count + 1, j = 0; j < cursor->count + 1; j++) {
            leftNode->children[i] = cursor->children[j];
            cursor->children[j] = nullptr;
        }
        leftNode->count += cursor->count + 1;
        cursor->count = 0;
        removeInternal(parent->key[leftSibling], parent->value[leftSibling], parent, cursor);
    } 
    else if (rightSibling <= parent->count) {
        Node* rightNode = parent->children[rightSibling];
        cursor->key[cursor->count] = parent->key[rightSibling - 1];
        cursor->value[cursor->count] = parent->value[rightSibling - 1];

        for (int i = cursor->count + 1, j = 0; j < rightNode->count; j++) {
            cursor->key[i] = rightNode->key[j];
            cursor->value[i] = rightNode->value[j];
        }
        for (int i = cursor->count + 1, j = 0; j < rightNode->count + 1; j++) {
            cursor->children[i] = rightNode->children[j];
            rightNode->children[j] = nullptr;
        }
        cursor->count += rightNode->count + 1;
        rightNode->count = 0;
        removeInternal(parent->key[rightSibling - 1], parent->value[rightSibling - 1], parent, rightNode);
    }
}   


# endif // B_PLUS_TREE_H