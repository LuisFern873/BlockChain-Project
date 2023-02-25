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

// template <typename T, size_t N>
class Index
{
    public:
        void create_index(Block<Transfer, 5>* block);
        void remove_index(Block<Transfer, 5>* block);
        void update_index(Block<Transfer, 5>* block);

        Transfer search(Member member, string key);
        vector<Transfer*> range_search(double start, double end);
        vector<Transfer*> starts_with(Member member, string prefix);
        vector<Transfer*> contains(Member member, string pattern);
        Transfer max_value();
        Transfer min_value();

        Index() = default;

    private:
        ChainHash<string, Transfer*> sender_index;
        ChainHash<string, Transfer*> receiver_index;
        BPlusTree<double, Transfer*> amount_index;
        Trie<Transfer*> prefix_sender_index;
        Trie<Transfer*> prefix_receiver_index;
};

void Index::create_index(Block<Transfer, 5>* block)
{
    string sender;
    string receiver;
    double amount;
    Transfer* ptr;

    for (int i = 0; i < block->size(); ++i) 
    {
        sender = block->data[i].get_sender();
        receiver = block->data[i].get_receiver();
        amount = block->data[i].get_amount();
        ptr = &block->data[i];

        // Hash index
        sender_index.insert(sender, ptr);
        receiver_index.insert(receiver, ptr);
        // B+ tree index
        amount_index.insert(amount, ptr);
        // Prefix tree index
        prefix_sender_index.insert(sender, ptr);
        prefix_receiver_index.insert(receiver, ptr);
    }
}

void Index::remove_index(Block<Transfer, 5>* block)
{

}

void Index::update_index(Block<Transfer, 5>* block)
{

}

Transfer Index::search(Member member, string key)
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

vector<Transfer*> Index::range_search(double start, double end)
{
    return amount_index.rangeSearch(start, end);
}

vector<Transfer*> Index::starts_with(Member member, string prefix)
{
    static auto get_sender = [](Transfer* transfer) { 
        return transfer->get_sender(); 
    };

    static auto get_receiver = [](Transfer* transfer) { 
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

vector<Transfer*> Index::contains(Member member, string prefix)
{
    return vector<Transfer*>();
}

Transfer Index::max_value()
{
    return *amount_index.max();
}

Transfer Index::min_value()
{
    return *amount_index.min();
}



# endif // INDEX_H