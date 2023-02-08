# ifndef CIRCULAR_LIST_H
# define CIRCULAR_LIST_H

# include <iostream>

using namespace std;

template <typename T>
struct Node 
{
    T data{};
    Node<T>* next;
    Node<T>* prev;

    Node();
    Node(T value);   
};

template <typename T>
class CirculatListIterator
{
    public:
        CirculatListIterator();
        CirculatListIterator(Node<T>* node);
        bool operator!=(const CirculatListIterator& other);
        CirculatListIterator& operator++();
        CirculatListIterator& operator--();
        T& operator*();

    private:
        Node<T>* current;
};

template <typename T>
class CircularList
{
    public:
        CircularList();
        ~CircularList();
        T& front();
        T& back();
        void push_front(T data);
        void push_back(T data);
        T pop_front();
        T pop_back();
        T insert(T data, int pos);
        bool remove(int pos);
        T& operator[](int pos);
        bool is_empty();
        int size();
        void clear();

        typedef CirculatListIterator<T> iterator;
        iterator begin();
        iterator end();

    private:
        Node<T>* head; // sentinel
        int nodes;
};

// Node implementation

template <typename T>
Node<T>::Node()
{
    next = nullptr;
    prev = nullptr;
}

template <typename T>
Node<T>::Node(T value)
{ 
    data = value;
    next = nullptr;
    prev = nullptr;
}

// Circular List Iterator implementation

template <typename T>
CirculatListIterator<T>::CirculatListIterator()
{
    current = new Node<T>();
}

template <typename T>
CirculatListIterator<T>::CirculatListIterator(Node<T>* node)
{   
    current = node;
}

template <typename T>
bool CirculatListIterator<T>::operator!=(const CirculatListIterator& other)
{
    return current != other.current;
}

template <typename T>
CirculatListIterator<T>& CirculatListIterator<T>::operator++()
{
    current = current->next;
    return *this;
}

template <typename T>
CirculatListIterator<T>& CirculatListIterator<T>::operator--()
{
    current = current->prev;
    return *this;
}

template <typename T>
T& CirculatListIterator<T>::operator*()
{
    return current->data;
}

// Circular List implementation

template <typename T>
CircularList<T>::CircularList()
{
    head = new Node<T>();
    head->next = head;
    head->prev = head;
    nodes = 0;
}

template <typename T>
CircularList<T>::~CircularList()
{
    delete head;
}

template <typename T>
T& CircularList<T>::front()
{
    if(this->is_empty()){
        throw runtime_error("Circular list is empty");
    } 
    return head->next->data;
}

template <typename T>
T& CircularList<T>::back()
{
    if(this->is_empty()){
        throw runtime_error("Circular list is empty");
    }
    return head->prev->data;
}

template <typename T>
void CircularList<T>::push_front(T data)
{
    auto node = new Node<T>(data);
    node->next = head->next;
    node->prev = head;
    head->next->prev = node;
    head->next = node;
    ++nodes;
}

template <typename T>
void CircularList<T>::push_back(T data)
{
    auto node = new Node<T>(data);
    node->next = head;
    node->prev = head->prev;
    head->prev->next = node;
    head->prev = node;
    ++nodes;
}

template <typename T>
T CircularList<T>::pop_front()
{
    if(this->is_empty()){
        throw runtime_error("Circular list is empty");
    }
    auto front = head->next;
    T data = front->data;

    head->next = front->next;
    front->next->prev = head;

    delete front;
    --nodes;
    return data;
}

template <typename T>
T CircularList<T>::pop_back()
{
    if(this->is_empty()){
        throw runtime_error("Circular list is empty");
    }
    auto back = head->prev;
    T data = back->data;

    head->prev = back->prev;
    back->prev->next = head;
    delete back;
    --nodes;
    return data;
}

template <typename T>
T CircularList<T>::insert(T data, int pos)
{
    if(pos < 0 or pos > nodes){
        throw runtime_error("Circular list index out of range");
    }

    auto previous = head;
    while(pos--){
        previous = previous->next;
    }

    auto node = new Node<T>(data);
    node->prev = previous;
    node->next = previous->next;

    previous->next->prev = node;
    previous->next = node;
    ++nodes;

    return data;
}

template <typename T>
bool CircularList<T>::remove(int pos)
{
    if(pos < 0 or pos > nodes){
        throw runtime_error("Circular list index out of range");
        return false;
    }
    auto previous = head;
    while(pos--){
        previous = previous->next;
    }
    auto current = previous->next;
            
    previous->next = current->next;
    current->next->prev = previous;
    delete current;
    return true;
}

template <typename T>
T& CircularList<T>::operator[](int pos)
{
    if(pos < 0 or nodes <= pos){
        throw runtime_error("Forward list index out of range");
    }
    auto current = head->next;
    while(pos--){
        current = current->next;
    }
    return current->data;
}

template <typename T>
bool CircularList<T>::is_empty()
{
    return !nodes;
}

template <typename T>
int CircularList<T>::size()
{
    return nodes;
}

template <typename T>
void CircularList<T>::clear()
{
    while (nodes > 0) {
        this->pop_front();
    }
}

template <typename T>
CircularList<T>::iterator CircularList<T>::begin()
{
    return CircularList<T>::iterator(head->next);
}

template <typename T>
CircularList<T>::iterator CircularList<T>::end()
{
    return CircularList<T>::iterator(head);
}


# endif // CIRCULAR_LIST_H