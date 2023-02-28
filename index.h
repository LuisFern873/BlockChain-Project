# ifndef INDEX_H
# define INDEX_H

# include <iostream>
# include "blockchain.h"
# include "structures/chainhash.h"
# include "structures/b+tree.h"
# include "structures/trie.h"
# include "structures/forwardlist.h"

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
        BPlusTree<double, T*> amount_index;
        ChainHash<string, T*> sender_index, receiver_index;
        Trie<T*> prefix_sender_index, prefix_receiver_index;
        ForwardList<pair<string, T*>> senders, receivers;
        bool boyer_moore(string text, string pattern);
};

template <typename T>
void Index<T>::create_index(Block<T>* block)
{
    T* pointer;
    for (int i = 0; i < block->size(); ++i) {
        pointer = &block->data[i];
        create_index(pointer);
    }
}

template <typename T>
void Index<T>::remove_index(Block<T>* block)
{
    T* pointer;

    for (int i = 0; i < block->size(); ++i) 
    {
        pointer = &block->data[i];
        remove_index(pointer);
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
    // For pattern searching
    senders.push_back({sender, transfer});
    receivers.push_back({receiver, transfer});
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
    // For pattern searching
    for (int i = 0; i < senders.size(); ++i) {
        auto [name, pointer] = senders[i];
        if (name == sender) {
            senders.remove(i);
            break;
        }
    }
    for (int i = 0; i < receivers.size(); ++i) {
        auto [name, pointer] = receivers[i];
        if (name == receiver) {
            receivers.remove(i);
            break;
        }
    }
}

template <typename T>
T Index<T>::search(Member member, string key)
{
    return member == Member::sender ? *sender_index.find(key) : *receiver_index.find(key);
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

    return member == Member::sender ? 
        prefix_sender_index.starts_with(prefix, get_sender) : 
        prefix_receiver_index.starts_with(prefix, get_receiver);
}

template <typename T>
vector<T*> Index<T>::contains(Member member, string pattern)
{
    vector<T*> report;
    auto list = member == Member::sender ? &senders : &receivers;
    for (int i = 0; i < list->size(); ++i) {
        auto [attribute, pointer] = (*list)[i];
        if (boyer_moore(attribute, pattern)) {
            report.push_back(pointer);
        }
    }
    return report;
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

template <typename T>
bool Index<T>::boyer_moore(string text, string pattern) 
{
    vector<int> positions;

    int n = text.size();
    int m = pattern.size();

    if (m > n) {
        return false;
    }

    vector<int> badChar(256, -1);
    for (int i = 0; i < m; i++) {
        badChar[(int)pattern[i]] = i;
    }

    vector<int> suffix(m);
    int j = m;
    for (int i = m - 1; i >= 0; i--) {
        while (j < m && pattern[i] != pattern[j - 1]) {
            j = suffix[j];
        }
        suffix[i] = --j;
    }

    int i = 0;
    while (i <= n - m) {
        int j = m - 1;
        while (j >= 0 && pattern[j] == text[i + j]) {
            j--;
        }
        if (j < 0) {
            positions.push_back(i);
            i += (i + m < n) ? m - badChar[(int)text[i + m]] : 1;
        } else {
            i += max(1, j - suffix[j]);
        }
    }

    return !positions.empty();
}


# endif // INDEX_H