# ifndef FORWARD_LIST_H
# define FORWARD_LIST_H

# include <iostream>

using namespace std;

template <typename T>
struct Node 
{
    T data{};
    Node<T>* next;

    Node();
    Node(T value);   
};

template <typename T>
class ForwardList
{
    public:
        ForwardList();
        ~ForwardList();

        T& front();
        T& back();
        void push_front(T data);
        void push_back(T data);
        T pop_front();
        T pop_back();
        void insert(T data, int pos);
        void remove(int pos);
        T& operator[](int pos);
        bool is_empty();
        int size();
        void clear();
        void display(ostream& os);

    private:
        Node<T>* head;
        int nodes;

        Node<T>* get_tail();
        Node<T>* prev(Node<T>* node);
        Node<T>* get_node(int pos);
        Node<T>* get_middle(Node<T>* start);
};

// Node implementation

template <typename T>
Node<T>::Node()
{
    next = nullptr;
}

template <typename T>
Node<T>::Node(T value)
{ 
    data = value;
    next = nullptr;
}

// Forward List implementation

template <typename T>
ForwardList<T>::ForwardList() 
{
    head = nullptr;
    nodes = 0;
}

template <typename T>
ForwardList<T>::~ForwardList()
{
    clear();
    delete head;
}

template <typename T>
T& ForwardList<T>::front()
{
    if(is_empty()) 
        throw runtime_error("Forward list is empty");
    return head->data;
}

template <typename T>
T& ForwardList<T>::back()
{
    if(is_empty()) 
        throw runtime_error("Forward list is empty");
    auto tail = get_tail();
    return tail->data;
}

template <typename T>
void ForwardList<T>::push_front(T data)
{
    auto node = new Node<T>(data);
    node->next = head;
    head = node;
    ++nodes;
}

template <typename T>
void ForwardList<T>::push_back(T data)
{
    if(is_empty()) push_front(data);
    else {
        auto node = new Node<T>(data);
        auto tail = get_tail();
        tail->next = node;
        ++nodes;
    }
}

template <typename T>
T ForwardList<T>::pop_front()
{
    if(is_empty()) 
        throw runtime_error("Forward list is empty");
    T front = head->data;
    auto temp = head;
    head = head->next;
    delete temp;
    --nodes;
    return front;
}

template <typename T>
T ForwardList<T>::pop_back()
{
    if (is_empty()) 
        throw runtime_error("Forward list is empty");

    if (nodes == 1) 
        return pop_front();
    else {
        auto tail = get_tail();
        auto new_tail = prev(tail);
        T back = tail->data;
        delete tail;
        new_tail->next = nullptr;
        --nodes;
        return back;
    }
}

template <typename T>
void ForwardList<T>::insert(T data, int pos)
{
    if (pos < 0 or nodes <= pos)
        throw runtime_error("Forward list index out of range");

    auto node = new Node<T>(data);
    auto prev_node = get_node(pos - 1);
    auto next_node = get_node(pos);

    prev_node->next = node;
    node->next = next_node;
    ++nodes;
}

template <typename T>
void ForwardList<T>::remove(int pos)
{
    if (pos < 0 or nodes <= pos)
        throw runtime_error("Forward list index out of range");
    if (pos == 0) 
        pop_front();
    else if (pos == nodes - 1) 
        pop_back();
    else {
        auto node = get_node(pos);
        auto prev_node = get_node(pos - 1);
        auto next_node = get_node(pos + 1);
        prev_node->next = next_node;
        delete node;
        --nodes;
    }
}

template <typename T>
T& ForwardList<T>::operator[](int pos)
{
    if (pos < 0 or nodes <= pos)
        throw runtime_error("Forward list index out of range");
    auto node = get_node(pos);
    return node->data;
}

template <typename T>
bool ForwardList<T>::is_empty()
{
    return !nodes;
}

template <typename T>
int ForwardList<T>::size()
{
    return nodes;
}

template <typename T>
void ForwardList<T>::clear()
{
    while(nodes > 0){
        this->pop_front();
    }
    head = nullptr;
}

template <typename T>
void ForwardList<T>::display(ostream& os)
{
    auto current = head;
    while(current){
        os << current->data << " ⟶  ";
        current = current->next;
    }
    os << "null\n";
}

template <typename T>
Node<T>* ForwardList<T>::get_tail()
{
    auto tail = head;
    while(tail->next){
        tail = tail->next;
    }
    return tail;
}

template <typename T>
Node<T>* ForwardList<T>::prev(Node<T>* node)
{
    auto current = head;
    while(current->next != node){
        current = current->next;
    }
    return current;
}

template <typename T>
Node<T>* ForwardList<T>::get_node(int pos)
{
    auto node = head;
    while(pos--){
        node = node->next;
    }
    return node;
}

template <typename T>
Node<T>* ForwardList<T>::get_middle(Node<T>* start){
    auto slow = start;
    auto fast = start->next;
    while (fast and fast->next){
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}


# endif // FORWARD_LIST_H