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

template <typename T>
class ForwardList
{
    
private:
    Node<T>* head;
    int nodes;


    Node<T>* get_tail(){ // O(n)
        auto tail = head;
        while(tail->next){
            tail = tail->next;
        }
        return tail;
    }

    Node<T>* prev(Node<T>* node){
        auto current = head;
        while(current->next != node){
            current = current->next;
        }
        return current;
    }

    Node<T>* get_node(int pos){
        auto node = head;
        while(pos--){
            node = node->next;
        }
        return node;
    }

    Node<T>* get_middle(Node<T>* start){
        auto slow = start;
        auto fast = start->next;
        while (fast and fast->next){
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }

    Node<T>* merge(Node<T>* left, Node<T>* right){

        auto dummyHead = new Node<T>();
        auto current = dummyHead;

        while(left and right){
            if (left->data <= right->data){
                current->next = left;
                left = left->next;
                current = current-> next;
            } else {
                current->next = right;
                right = right->next;
                current = current->next;
            }
        }

        while (left){
            current->next = left;
            left = left->next;
            current = current->next;
        }

        while (right){
            current->next = right;
            right = right->next;
            current = current->next;
        }

        return dummyHead->next;
    }

    Node<T>* merge_sort(Node<T>* start){
        if(!start->next) return start;

        auto middle = get_middle(start);
        auto start_right = middle->next;

        middle->next = nullptr; // breaking the linked list into two parts

        auto left = merge_sort(start);
        auto right = merge_sort(start_right);

        return merge(left, right);
    }



public:
    ForwardList() {
        head = nullptr;
        nodes = 0;
    }

    ~ForwardList(){
        clear();
        delete head;
    }

    T front(){
        if(is_empty()) 
            throw runtime_error("Forward list is empty");
        return head->data;
    }

    T back(){
        if(is_empty()) 
            throw runtime_error("Forward list is empty");
        auto tail = get_tail(); // O(n)
        return tail->data;
    }

    void push_front(T data){
        auto node = new  Node<T>(data);
        node->next = head;
        head = node;
        ++nodes;
    }

    void push_back(T data){
        if(is_empty()) push_front(data);
        else {
            auto node = new Node<T>(data);
            auto tail = get_tail();
            tail->next = node;
            ++nodes;
        }
    }

    T pop_front(){
        if(is_empty()) throw runtime_error("Forward list is empty");
        T front = head->data;
        auto temp = head;
        head = head->next;
        delete temp;
        --nodes;
        return front;
    }

    T pop_back(){
        if(is_empty()) throw runtime_error("Forward list is empty");

        if(nodes == 1) return pop_front();
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

    T insert(T data, int pos){
        if(pos < 0 or nodes <= pos){
            throw runtime_error("Forward list index out of range");
        };

        auto node = new Node<T>(data);
        auto prev_node = get_node(pos - 1);
        auto next_node = get_node(pos);

        prev_node->next = node;
        node->next = next_node;
        ++nodes;

        return data;
    }

    void remove(int pos){
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

    T& operator[](int pos){
        if (pos < 0 or nodes <= pos)
            throw runtime_error("Forward list index out of range");

        auto node = get_node(pos);
        return node->data;
    }

    bool is_empty(){
        return !nodes;
    }

    int size(){
        return nodes;
    }

    void clear(){
        while(nodes > 0){
            this->pop_front();
        }
        head = nullptr;
    }

    void sort(){
        head = merge_sort(head);
    }

    bool is_sorted(){
        if(nodes <= 1) return true;

        auto current = head;
        while(current->next){
            if(current->data > current->next->data){
                return false;
            }
            current = current->next;
        }
        return true;
    }

    void reverse(){
        if(nodes <= 1) return;
        // It's all about updating tha link part of the nodes and head pointer
        auto current = head;
        Node<T>* next = nullptr;
        Node<T>* prev = nullptr;

        while(current){
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        head = prev;
    }

    void display(ostream& os){
        auto current = head;
        while(current){
            os << current->data << " ⟶  ";
            current = current->next;
        }
        os << "null\n";
    }

};

# endif // FORWARD_LIST_H