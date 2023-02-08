# ifndef AVL_TREE_H
# define AVL_TREE_H

# include <queue>
# include <stack>
# include <sstream>
# include <cmath>

using namespace std;

template <typename T>
struct NodeBT 
{
    T data;
    int height;
    NodeBT* left; 
    NodeBT* right;

    NodeBT(); 
    NodeBT(T value);
    void killSelf();
};

// NodeBT implementation

template <typename T>
NodeBT<T>::NodeBT()
{
    height = 0;
    left = nullptr;
    right = nullptr;
}

template <typename T>
NodeBT<T>::NodeBT(T value)
{
    data = value;
    height = 0;
    left = nullptr;
    right = nullptr;
}

template <typename T>
void NodeBT<T>::killSelf()
{
    if (left != nullptr) 
        left->killSelf();
    if (right != nullptr) 
        right->killSelf();
    delete this;
}


template <typename T>
class AVLTree
{
private:
    NodeBT<T> *root;

public:
    AVLTree() : root(nullptr) {}
    void insert(T value)
    {
        insert(this->root, value);
    }
    bool find(T value)
    {
        return find(this->root, value);
    }
    string getPreOrder(){
        return getPreOrder(this->root);
    }
    int height()
    {
        return height(this->root);
    }
    T minValue()
    {
        return minValue(this->root);
    }
    T maxValue()
    {
        return maxValue(this->root);
    }
    bool isBalanced()
    {
        return isBalanced(this->root);
    }
    int size()
    {
        return size(this->root);
    }
    void remove(T value)
    {
        remove(this->root, value);
    }

    void displayPretty();

    ~AVLTree(){
        if(this->root != nullptr)
            this->root->killSelf();
    }

private:
    void insert(NodeBT<T> *&node, T value);//*
    bool find(NodeBT<T> *node, T value);
    string getPreOrder(NodeBT<T> *node);
    int height(NodeBT<T> *node);//*
    bool isBalanced(NodeBT<T> *node);//*
    T minValue(NodeBT<T> *node);
    T maxValue(NodeBT<T> *node);
    int size(NodeBT<T> *node);
    void remove(NodeBT<T> *&node, T value);//*
    void displayGivenLevel(NodeBT<T> *node, int level);

    // Add for AVL
    int balancingFactor(NodeBT<T> *node);
    void updateHeight(NodeBT<T> *node);
    void balance(NodeBT<T> *&node);
    void left_rota(NodeBT<T> *&node); 
    void right_rota(NodeBT<T> *&node); 
};

// AVL Tree implementation 

template <typename T>
void AVLTree<T>::insert(NodeBT<T> *&node, T value) // O(logn)
{
    if (node == nullptr)
        node = new NodeBT<T>(value);
    else if (value < node->data)
        insert(node->left, value);
    else
        insert(node->right, value);
        
    updateHeight(node);
    balance(node);
}

template <typename T>
bool AVLTree<T>::find(NodeBT<T> *node, T value)
{
    if (node == nullptr)
        return false;
    else if (value < node->data)
        return find(node->left, value);
    else if (value > node->data)
        return find(node->right, value);
    else
        return true;
}

template <typename T>
string AVLTree<T>::getPreOrder(NodeBT<T> *node)
{
    if (node == nullptr)
        return "";
    
    stringstream report;
    stack<NodeBT<T>*> stack;
    NodeBT<T>* current = nullptr;
    stack.push(node);

    while (!stack.empty()) {
        current = stack.top();
        report << current->data << " ";
        stack.pop();

        if (current->right)
            stack.push(current->right);
        if (current->left)
            stack.push(current->left);
    }

    return report.str();
}

template <typename T>
int AVLTree<T>::height(NodeBT<T> *node) // O(1)
{
    if (node == nullptr)
        return -1;
    else
        return node->height;
}

template <typename T>
bool AVLTree<T>::isBalanced(NodeBT<T> *node)
{
    if (node == nullptr)
        return true;
    else
        return abs(balancingFactor(node)) <= 1 and isBalanced(node->left) and isBalanced(node->right);
}

template <typename T>
T AVLTree<T>::minValue(NodeBT<T> *node)
{
    if (node == nullptr)
        throw("The tree is empty");
    else if (node->left == nullptr)
        return node->data;
    else
        return minValue(node->left);
}

template <typename T>
T AVLTree<T>::maxValue(NodeBT<T> *node)
{
    if (node == nullptr)
        throw("The tree is empty");
    else if (node->right == nullptr)
        return node->data;
    else
        return maxValue(node->right);
}

template <typename T>
int AVLTree<T>::size(NodeBT<T> *node)
{
    if (node == nullptr)
        return 0;
    else
        return 1 + size(node->left) + size(node->right);
}

template <typename T>
void AVLTree<T>::remove(NodeBT<T> *&node, T value)
{
    if (node == nullptr)
        return;
    else if (value < node->data)
        remove(node->left, value);
    else if (value > node->data)
        remove(node->right, value);
    else
    {
        if (node->left == nullptr and node->right == nullptr)
        {
            delete node;
            node = nullptr;
        }
        else if (node->left == nullptr)
        {
            NodeBT<T> *temp = node;
            node = node->right;
            delete temp;
        }
        else if (node->right == nullptr)
        {
            NodeBT<T> *temp = node;
            node = node->left;
            delete temp;
        }
        else
        {
            T temp = maxValue(node->left);
            node->data = temp;
            remove(node->left, temp);
        }
    }

    // Extra operations for holding AVL tree invariant...
    updateHeight(node);
    balance(node);
}

template <typename T>
void AVLTree<T>::displayPretty()
{
    for(int i = 1; i <= height(root) + 1; i++){
        displayGivenLevel(root, i);
        cout << "\n";
    }
}

template <typename T>
void AVLTree<T>::displayGivenLevel(NodeBT<T> *node, int level)
{
    if (node == nullptr)
        return;
    if (level == 1)
        cout << node->data << " ";
    else {
        displayGivenLevel(node->left, level - 1);
        displayGivenLevel(node->right, level - 1);
    }
}


// Extra method for AVL tree

template <typename T>
void AVLTree<T>::updateHeight(NodeBT<T> *node) // O(1)
{
    if (node == nullptr)
        return;
    else
        node->height = 1 + max(height(node->left), height(node->right));
}

template <typename T>
int AVLTree<T>::balancingFactor(NodeBT<T> *node) // O(1)
{
    if (nullptr == node)
        return 0;
    else
        return height(node->left) - height(node->right);
}

template <typename T>
void AVLTree<T>::balance(NodeBT<T> *&node) // O(1)
{
    // Left left case
    if (balancingFactor(node) == 2) {
        // Left right case
        if (balancingFactor(node->left) == -1)
            left_rota(node->left);
        right_rota(node);
    }

    // Right right case
    if (balancingFactor(node) == -2) {
        // Right left case
        if (balancingFactor(node->right) == 1)
            right_rota(node->right);
        left_rota(node);
    }
}

template <typename T>
void AVLTree<T>::left_rota(NodeBT<T> *&node)
{
    NodeBT<T>* nodeRight = node->right;

    node->right = nodeRight->left;
    nodeRight->left = node;

    updateHeight(node);
    updateHeight(nodeRight);

    node = nodeRight;
}

template <typename T>
void AVLTree<T>::right_rota(NodeBT<T> *&node)
{
    NodeBT<T>* nodeLeft = node->left;
    node->left = nodeLeft->right;
    nodeLeft->right = node;

    updateHeight(node);
    updateHeight(nodeLeft);

    node = nodeLeft;
}


# endif // AVL_TREE_H