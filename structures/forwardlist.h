# ifndef FORWARD_LIST_H
# define FORWARD_LIST_H

# include <iostream>

using namespace std;

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
        void insert(T data, int index);
        void remove(int index);
        T& operator[](int index);
        bool is_empty();
        int size();
        void clear();
        void display(ostream& os);

    private:
        struct Node 
        {
            T data{};
            Node* next;

            Node();
            Node(T value);   
        };

        Node* head;
        int nodes;

        Node* get_tail();
        Node* prev(Node* node);
        Node* get_node(int index);
        Node* get_middle(Node* start);
};

// Node implementation

template <typename T>
ForwardList<T>::Node::Node()
{
    next = nullptr;
}

template <typename T>
ForwardList<T>::Node::Node(T value)
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
    auto node = new Node(data);
    node->next = head;
    head = node;
    ++nodes;
}

template <typename T>
void ForwardList<T>::push_back(T data)
{
    if(is_empty()) push_front(data);
    else {
        auto node = new Node(data);
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
void ForwardList<T>::insert(T data, int index)
{
    if (index < 0 or nodes <= index)
        throw runtime_error("Forward list index out of range");

    auto node = new Node(data);
    auto prev_node = get_node(index - 1);
    auto next_node = get_node(index);

    prev_node->next = node;
    node->next = next_node;
    ++nodes;
}

template <typename T>
void ForwardList<T>::remove(int index)
{
    if (index < 0 or nodes <= index)
        throw runtime_error("Forward list index out of range");
    if (index == 0) 
        pop_front();
    else if (index == nodes - 1) 
        pop_back();
    else {
        auto node = get_node(index);
        auto prev_node = get_node(index - 1);
        auto next_node = get_node(index + 1);
        prev_node->next = next_node;
        delete node;
        --nodes;
    }
}

template <typename T>
T& ForwardList<T>::operator[](int index)
{
    if (index < 0 or nodes <= index)
        throw runtime_error("Forward list index out of range");
    auto node = get_node(index);
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
ForwardList<T>::Node* ForwardList<T>::get_tail()
{
    auto tail = head;
    while(tail->next){
        tail = tail->next;
    }
    return tail;
}

template <typename T>
ForwardList<T>::Node* ForwardList<T>::prev(Node* node)
{
    auto current = head;
    while(current->next != node){
        current = current->next;
    }
    return current;
}

template <typename T>
ForwardList<T>::Node* ForwardList<T>::get_node(int index)
{
    auto node = head;
    while(index--){
        node = node->next;
    }
    return node;
}

template <typename T>
ForwardList<T>::Node* ForwardList<T>::get_middle(Node* start){
    auto slow = start;
    auto fast = start->next;
    while (fast and fast->next){
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}


# endif // FORWARD_LIST_H