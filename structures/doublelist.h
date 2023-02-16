# ifndef DOUBLE_LIST_H
# define DOUBLE_LIST_H

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
class DoubleListIterator
{
    public:
        DoubleListIterator();
        DoubleListIterator(Node<T>* node);
        bool operator!=(const DoubleListIterator& other);
        DoubleListIterator& operator++();
        DoubleListIterator& operator--();
        T& operator*();

    private:
        Node<T>* current;
};

template <typename T>
class DoubleList 
{
    public:
        DoubleList();
        ~DoubleList();
        T& front();
        T& back();
        void push_front(T data);
        void push_back(T data);
        T pop_front();
        T pop_back();
        void insert(T data, int index);
        T remove(int index);
        T& operator[](int index);
        bool is_empty();
        int size();
        void clear();

        typedef DoubleListIterator<T> iterator;
        iterator begin();
        iterator end();
        
    private:
        Node<T>* head;
        Node<T>* tail;
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

// Double List Iterator implementation

template <typename T>
DoubleListIterator<T>::DoubleListIterator() : current(nullptr) {}

template <typename T>
DoubleListIterator<T>::DoubleListIterator(Node<T>* node) : current(node) {}

template <typename T>
bool DoubleListIterator<T>::operator!=(const DoubleListIterator& other)
{
    return current != other.current;
}

template <typename T>
DoubleListIterator<T>& DoubleListIterator<T>::operator++()
{
    current = current->next;
    return *this;
}

template <typename T>
DoubleListIterator<T>& DoubleListIterator<T>::operator--()
{
    current = current->prev;
    return *this;
}

template <typename T>
T& DoubleListIterator<T>::operator*()
{
    return current->data;
}

// Double List implementation

template <typename T>
DoubleList<T>::DoubleList()
{
    head = nullptr;
    tail = nullptr;
    nodes = 0;
}

template <typename T>
DoubleList<T>::~DoubleList()
{
    Node<T>* current = head;
    while (current != nullptr) {
        Node<T>* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    tail = nullptr;
    nodes = 0;
}

template <typename T>
T& DoubleList<T>::front()
{
    if(is_empty())
        throw runtime_error("Double list is empty");
    else
        return head->data;
}

template <typename T>
T& DoubleList<T>::back()
{
    if(is_empty())
        throw runtime_error("Double list is empty");
    else
        return tail->data;
}

template <typename T>
void DoubleList<T>::push_front(T data)
{
    Node<T>* node = new Node<T>(data);
    if (head == nullptr) 
    {
        head = node;
        tail = node;
        node->next = nullptr;
        node->prev = nullptr;
    }
    else 
    {
        head->prev = node;
        node->next = head;
        node->prev = nullptr;
        head = node;
    }
    ++nodes;
}

template <typename T>
void DoubleList<T>::push_back(T data) 
{
    Node<T>* node = new Node<T>(data);
    if (tail == nullptr) 
    {
        head = node;
        tail = node;
        node->next = nullptr;
        node->prev = nullptr;
    }
    else 
    {
        tail->next = node;
        node->prev = tail;
        node->next = nullptr;
        tail = node;
    }
    ++nodes;
}

template <typename T>
T DoubleList<T>::pop_front() 
{
    if (head == nullptr) 
        throw runtime_error("Double list is empty");
    
    T data = head->data;
    Node<T>* temp = head;
    head = head->next;
    if (head == nullptr) 
        tail = nullptr;
    else 
        head->prev = nullptr;
    delete temp;
    --nodes;
    return data;
}

template <typename T>
T DoubleList<T>::pop_back() 
{
    if (tail == nullptr) 
        throw runtime_error("Double list is empty");
    
    T data = tail->data;
    Node<T>* temp = tail;
    tail = tail->prev;
    if (tail == nullptr) 
        head = nullptr;
    else 
        tail->next = nullptr;
    delete temp;
    --nodes;
    return data;
}

template <typename T>
void DoubleList<T>::insert(T data, int index) 
{
    if (index < 0 or index > nodes) 
        throw runtime_error("Double list index out of range");

    if (index == 0) 
        push_front(data);
    else if (index == nodes) 
        push_back(data);
    else 
    {
        Node<T>* node = new Node<T>(data);
        Node<T>* current = head;
        for (int i = 0; i < index - 1; ++i) 
            current = current->next;
        node->prev = current;
        node->next = current->next;
        current->next->prev = node;
        current->next = node;
        ++nodes;
    }
}

template <typename T>
T DoubleList<T>::remove(int index)
{
    if (index < 0 or index >= nodes) 
        throw runtime_error("Double list index out of range");

    if (index == 0) 
        return pop_front();
    else if (index == nodes - 1) 
        return pop_back();
    else 
    {
        Node<T>* current = head;
        for (int i = 0; i < index; ++i) 
            current = current->next;
        T deletedValue = current->data;
        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
        --nodes;
        return deletedValue;
    }
}

template <typename T>
T& DoubleList<T>::operator[](int index)
{
    if (index < 0 || index >= nodes) 
        throw runtime_error("Double list index out of range");

    Node<T>* current = head;
    for (int i = 0; i < index; ++i) 
        current = current->next;

    return current->data;
}

template <typename T>
bool DoubleList<T>::is_empty()
{
    return nodes == 0;
}

template <typename T>
int DoubleList<T>::size()
{
    return nodes;
}

template <typename T>
void DoubleList<T>::clear()
{
    Node<T>* current = head;
    while (current != nullptr) 
    {
        Node<T>* next = current->next;
        delete current;
        current = next;
    }
    head = tail = nullptr;
    nodes = 0;
}

template <typename T>
DoubleList<T>::iterator DoubleList<T>::begin()
{
    return DoubleList<T>::iterator(head);
}

template <typename T>
DoubleList<T>::iterator DoubleList<T>::end()
{
    return DoubleList<T>::iterator(tail->next);
}


# endif // DOUBLE_LIST_H