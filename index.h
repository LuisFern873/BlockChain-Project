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

class Index
{
    public:
        void create_hash_index(); // search O(1)
        void create_tree_index(); // max_value and min_value O(logn), range_search O(t*log(t*n)), t = 5
        void create_trie_index(); // starts_with O(m)

        Transfer search(Member member, string key);
        vector<Transfer*> range_search(double start, double end);
        vector<Transfer*> starts_with(Member member, string prefix);
        vector<Transfer*> contains(Member member, string pattern);
        Transfer max_value();
        Transfer min_value();

        Index(BlockChain<Transfer>& Blockchain) : blockchain(&Blockchain) {}

    private:
        BlockChain<Transfer>* blockchain;

        BPlusTree<double, Transfer*> amount_index;
        ChainHash<string, Transfer*> sender_index;
        ChainHash<string, Transfer*> receiver_index;
        Trie<Transfer*> start_sender_index;
        Trie<Transfer*> start_receiver_index;
};


void Index::create_hash_index()
{
    string sender;
    string receiver;
    Transfer* ptr;

    for (int i = 1; i < blockchain->size(); ++i)
    {
        auto block = blockchain->chain[i];

        for (int i = 0; i < block->size(); ++i) 
        {
            sender = block->data[i].get_sender();
            receiver = block->data[i].get_receiver();
            ptr = &block->data[i];

            sender_index.insert(sender, ptr);
            receiver_index.insert(receiver, ptr);
        }
    }
}

void Index::create_tree_index()
{
    double amount;
    Transfer* ptr;

    for (int i = 1; i < blockchain->size(); ++i)
    {
        auto block = blockchain->chain[i];

        for (int i = 0; i < block->size(); ++i) 
        {
            amount = block->data[i].get_amount();
            ptr = &block->data[i];

            amount_index.insert(amount, ptr);
        }
    }
}


void Index::create_trie_index()
{
    string sender;
    string receiver;
    Transfer* ptr;

    for (int i = 1; i < blockchain->size(); ++i)
    {
        auto block = blockchain->chain[i];

        for (int i = 0; i < block->size(); ++i) 
        {
            sender = block->data[i].get_sender();
            receiver = block->data[i].get_receiver();
            ptr = &block->data[i];

            start_sender_index.insert(sender, ptr);
            start_receiver_index.insert(receiver, ptr);
        }
    }
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
        return start_sender_index.starts_with(prefix, get_sender);
    case Member::receiver:
        return start_receiver_index.starts_with(prefix, get_receiver);
    default:
        throw invalid_argument("Invalid block attribute");
    }
}

vector<Transfer*> Index::contains(Member member, string prefix)
{

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