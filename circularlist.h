# ifndef CIRCULAR_LIST_H
# define CIRCULAR_LIST_H

# include <iostream>

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

template <typename T>
class CircularList
{
    public:
        typedef CirculatListIterator<T> iterator;
        iterator begin(){
            return iterator(head->next);
        }
        iterator end(){
            return iterator(head);
        }

    private:
        Node<T>* head; // sentinel
        int nodes;

    public:
        CircularList() {
            head = new Node<T>();
            head->next = head;
            head->prev = head;
            nodes = 0;
        }

        ~CircularList(){
            delete head;
        }

        T& front(){
            if(this->is_empty()){
                throw std::runtime_error("Circular list is empty");
            } 
            return head->next->data;
        }

        T& back(){
            if(this->is_empty()){
                throw std::runtime_error("Circular list is empty");
            }
            return head->prev->data;
        }

        void push_front(T data){
            auto node = new Node<T>(data);
            node->next = head->next;
            node->prev = head;

            head->next->prev = node;
            head->next = node;
            ++nodes;
        }

        void push_back(T data){
            auto node = new Node<T>(data);
            node->next = head;
            node->prev = head->prev;

            head->prev->next = node;
            head->prev = node;
            ++nodes;
        }

        T pop_front(){
            if(this->is_empty()){
                throw std::runtime_error("Circular list is empty");
            }
            auto front = head->next;
            T data = front->data;

            head->next = front->next;
            front->next->prev = head;
            delete front;
            --nodes;
            return data;
        }

        T pop_back(){
            if(this->is_empty()){
                throw std::runtime_error("Circular list is empty");
            }
            auto back = head->prev;
            T data = back->data;

            head->prev = back->prev;
            back->prev->next = head;
            delete back;
            --nodes;
            return data;
        }

        T insert(T data, int pos){
            if(pos < 0 or pos > nodes){
                throw std::runtime_error("Circular list index out of range");
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

        bool remove(int pos){
            if(pos < 0 or pos > nodes){
                throw std::runtime_error("Circular list index out of range");
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

        T& operator[](int pos){
            if(pos < 0 or nodes <= pos){
                throw std::runtime_error("Forward list index out of range");
            }
            auto current = head->next;
            while(pos--){
                current = current->next;
            }
            return current->data;
        }

        bool is_empty(){
            return !nodes;
        }

        int size(){
            return nodes;
        }

        void clear(){
            while (nodes > 0) {
                this->pop_front();
            }
        }

        bool is_sorted(){
            if(nodes <= 1) return true;

            auto current = head->next;
            while(current != head->prev){
                if(current->data > current->next->data){
                    return false;
                }
                current = current->next;
            }
            return true;
        }

        void reverse(){
            if(nodes <= 1) return;

            Node<T>* current = head->next;
            Node<T>* temporal;

            while (current != head) {
                temporal = current->prev;
                current->prev = current->next;
                current->next = temporal;
                current = current->prev;
            }
            temporal = head->prev;
            head->prev = head->next;
            head->next = temporal;
        }

        void display(std::ostream& os){
            auto current = head->next;
            os << "head ⇄ ";
            while(current != head){
                os << current->data << " ⇄ ";
                current = current->next;
            }
            os << "head\n";
        }
};

# endif // CIRCULAR_LIST_H