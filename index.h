# ifndef INDEX_H
# define INDEX_H

# include <iostream>
# include "blockchain.h"
# include "structures/chainhash.h"
# include "structures/b+tree.h"
# include "record.h"

using namespace std;

enum class Member { sender, receiver };

struct Index
{
    // Equal To Request O(1)
    void create_hash_index(BlockChain<Transfer>& blockchain)
    {
        string sender;
        string receiver;
        Transfer* ptr;

        for (int i = 1; i < blockchain.size(); ++i)
        {
            auto block = blockchain.chain[i];

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

    // Max value and Min Value Request O(logn)
    void create_BPlusTree_index(BlockChain<Transfer>& blockchain)
    {
        double amount;
        Transfer* ptr;

        for (int i = 1; i < blockchain.size(); ++i)
        {
            auto block = blockchain.chain[i];

            for (int i = 0; i < block->size(); ++i) 
            {
                amount = block->data[i].get_amount();
                ptr = &block->data[i];

                amount_index.insert(amount, ptr);
            }
        }
    }

    Transfer EqualTo(Member member, string key)
    {
        switch (member)
        {
        case Member::sender:
            return *sender_index.find(key);
        case Member::receiver:
            return *receiver_index.find(key);
        default:
            throw runtime_error("Requested data was not found");
        }
    }

    Transfer MaxValue()
    {
        return *amount_index.max();
    }

    Transfer MinValue()
    {
        return *amount_index.min();
    }

    vector<Transfer*> RangeSearch(double start, double end)
    {
        return amount_index.rangeSearch(start, end);
    }

    BPlusTree<double, Transfer*> amount_index;
    ChainHash<string, Transfer*> sender_index;
    ChainHash<string, Transfer*> receiver_index;
};


# endif // INDEX_H