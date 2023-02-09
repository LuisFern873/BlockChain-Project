# ifndef CIRCULAR_ARRAY_H
# define CIRCULAR_ARRAY_H

# include <iostream>

using namespace std;

template <typename T, size_t N>
class CircularArray
{  
    public:
        CircularArray();
        ~CircularArray();
        void push_front(T data);
        void push_back(T data);
        T pop_front();
        T pop_back();
        bool is_full();
        bool is_empty();
        int size();
        void clear();
        T& operator[](int index);

        template <typename T1, size_t N1>
        friend ostream& operator<<(ostream& os, CircularArray<T1, N1>& arr);

    private:
        T* array;
        int back, front;
        int next(int);
        int prev(int);
};

template <typename T, size_t N>
CircularArray<T, N>::CircularArray()
{
    array = new T[N];
    front = back = -1;
}

template <typename T, size_t N>
CircularArray<T, N>::~CircularArray()
{
    delete[] array;
}

template <typename T, size_t N>
bool CircularArray<T, N>::is_empty()
{
    return (front == -1 and back == -1);
}

template <typename T, size_t N>
bool CircularArray<T, N>::is_full()
{
    return (next(back) == front);
}

template <typename T, size_t N>
void CircularArray<T, N>::push_back(T data)
{
    if(is_full())
        throw runtime_error("Circular array is full");

    if(is_empty()) 
        front = back = 0;
    else 
        back = next(back);

    array[back] = data;
}

template <typename T, size_t N>
void CircularArray<T, N>::push_front(T data)
{
    if(is_full())
        throw runtime_error("Circular array is full");

    if(is_empty()) 
        front = back = 0;
    else 
        front = prev(front);

    array[front] = data;
}

template <typename T, size_t N>
T CircularArray<T, N>::pop_back()
{
    if(is_empty()) 
        throw runtime_error("Circular array is empty");

    T data = array[back];

    if(front == back) 
        front = back = -1;
    else 
        back = prev(back);

    return data;
}

template <typename T, size_t N>
T CircularArray<T, N>::pop_front()
{
    if(is_empty()) 
        throw runtime_error("Circular array is empty");

    T data = array[front];

    if(front == back) 
        front = back = -1;
    else 
        front = next(front);

    return data;
}

template <typename T, size_t N>
int CircularArray<T, N>::size()
{
    int distance = back - front + 1;
    return (front <= back) ? distance : distance + N;
};

template <typename T, size_t N>
T& CircularArray<T, N>::operator[](int index)
{
    return array[(front + index) % size()];
}


template <typename T, size_t N>
void CircularArray<T, N>::clear()
{
    while (size() > 0)
        pop_front();
}

template <typename T, size_t N>
ostream& operator<<(ostream& os, CircularArray<T, N>& arr)
{
    int current = arr.front;
    while(current != arr.back){
        os << arr.array[current] << " ";
        current = arr.next(current);
    }
    os << arr.array[arr.back];
    return os;
}

template <typename T, size_t N>
int CircularArray<T, N>::next(int index)
{
    return (index == N - 1) ? 0 : ++index;
}

template <typename T, size_t N>
int CircularArray<T, N>::prev(int index)
{
    return (index == 0) ? N - 1 : --index;
}


# endif // CIRCULAR_ARRAY_H