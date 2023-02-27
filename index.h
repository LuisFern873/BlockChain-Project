# ifndef INDEX_H
# define INDEX_H

# include <iostream>
# include "blockchain.h"
# include "structures/chainhash.h"
# include "structures/b+tree.h"
# include "structures/trie.h"
# include "record.h"

using namespace std;

enum class Member { sender, receiver };

template <typename T>
class Index
{
    public:
        void create_index(Block<T>* block);
        void remove_index(Block<T>* block);
        void create_index(T* transfer);
        void remove_index(T* transfer);

        T search(Member member, string key);
        vector<T*> range_search(double start, double end);
        vector<T*> starts_with(Member member, string prefix);
        vector<T*> contains(Member member, string pattern);
        T max_value();
        T min_value();

        Index() = default;
        ~Index() = default;

    private:
        ChainHash<string, T*> sender_index;
        ChainHash<string, T*> receiver_index;
        BPlusTree<double, T*> amount_index;
        Trie<T*> prefix_sender_index;
        Trie<T*> prefix_receiver_index;
};

template <typename T>
void Index<T>::create_index(Block<T, 5>* block)
{
    T* pointer;
    string sender;
    string receiver;
    double amount;

    for (int i = 0; i < block->size(); ++i) 
    {
        pointer = &block->data[i];
        sender = pointer->get_sender();
        receiver = pointer->get_receiver();
        amount = pointer->get_amount();

        // Hash index
        sender_index.insert(sender, pointer);
        receiver_index.insert(receiver, pointer);
        // B+ tree index
        amount_index.insert(amount, pointer);
        // Prefix tree index
        prefix_sender_index.insert(sender, pointer);
        prefix_receiver_index.insert(receiver, pointer);
    }
}

template <typename T>
void Index<T>::remove_index(Block<T, 5>* block)
{
    T* pointer;
    string sender;
    string receiver;
    double amount;

    for (int i = 0; i < block->size(); ++i) 
    {
        pointer = &block->data[i];
        sender = pointer->get_sender();
        receiver = pointer->get_receiver();
        amount = pointer->get_amount();

        // Hash index
        sender_index.remove(sender);
        receiver_index.remove(receiver);
        // B+ tree index
        amount_index.remove(amount);
        // Prefix tree index
        prefix_sender_index.remove(sender);
        prefix_receiver_index.remove(receiver);
    }
}

template <typename T>
void Index<T>::create_index(T* transfer)
{
    string sender = transfer->get_sender();
    string receiver = transfer->get_receiver();
    double amount = transfer->get_amount();

    // Hash index
    sender_index.insert(sender, transfer);
    receiver_index.insert(receiver, transfer);
    // B+ tree index
    amount_index.insert(amount, transfer);
    // Prefix tree index
    prefix_sender_index.insert(sender, transfer);
    prefix_receiver_index.insert(receiver, transfer);
}

template <typename T>
void Index<T>::remove_index(T* transfer)
{
    string sender = transfer->get_sender();
    string receiver = transfer->get_receiver();
    double amount = transfer->get_amount();

    // Hash index
    sender_index.remove(sender);
    receiver_index.remove(receiver);
    // B+ tree index
    amount_index.remove(amount);
    // Prefix tree index
    prefix_sender_index.remove(sender);
    prefix_receiver_index.remove(receiver);
}

template <typename T>
T Index<T>::search(Member member, string key)
{
    switch (member)
    {
    case Member::sender:
        return *sender_index.find(key);
    case Member::receiver:
        return *receiver_index.find(key);
    default:
        throw invalid_argument("Invalid block attribute");
    }
}

template <typename T>
vector<T*> Index<T>::range_search(double start, double end)
{
    return amount_index.rangeSearch(start, end);
}

template <typename T>
vector<T*> Index<T>::starts_with(Member member, string prefix)
{
    static auto get_sender = [](T* transfer) { 
        return transfer->get_sender(); 
    };

    static auto get_receiver = [](T* transfer) { 
        return transfer->get_receiver(); 
    };

    switch (member)
    {
    case Member::sender:
        return prefix_sender_index.starts_with(prefix, get_sender);
    case Member::receiver:
        return prefix_receiver_index.starts_with(prefix, get_receiver);
    default:
        throw invalid_argument("Invalid block attribute");
    }
}

template <typename T>
vector<T*> Index<T>::contains(Member member, string prefix)
{
    return vector<T*>();
}

template <typename T>
T Index<T>::max_value()
{
    return *amount_index.max();
}

template <typename T>
T Index<T>::min_value()
{
    return *amount_index.min();
}



# endif // INDEX_H