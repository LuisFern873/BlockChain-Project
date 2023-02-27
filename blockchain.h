# ifndef BLOCK_CHAIN_H
# define BLOCK_CHAIN_H

# include "record.h"
# include "block.h"
# include "index.h"
# include "structures/doublelist.h"

template <typename T>
class BlockChain
{
    public:
        BlockChain();
        void insert(T transfer);
        void update(T new_transfer, int id_block, int id_transfer);
        void remove(int id_block, int id_transfer);
        void display();
        int size();
        Index<T>* index;

    private:
        DoubleList<Block<T>*> chain;
        Block<T>* current;
        void create_genesis();
};

template <typename T>
BlockChain<T>::BlockChain()
{
    create_genesis();
    current = new Block<T>();
    current->id = 1;
    index = new Index<T>();
}

template <typename T>
void BlockChain<T>::insert(T transfer)
{
    current->insert(transfer);

    if (!current->data.is_full())
        return;
    
    current->previous_hash = chain.back()->hash;

    if (current->mine()) {
        chain.push_back(current);
        index->create_index(current);
    }
    else
        throw runtime_error("Block not mined");

    current = new Block<T>();
    current->id = chain.size();
}

template <typename T>
void BlockChain<T>::update(T new_transfer, int id_block, int id_transfer)
{
    new_transfer.id_block = id_block;
    // O(size): find block position
    auto iterator = chain.begin();
    while ((*iterator)->id != id_block)
        ++iterator;

    // O(N) + O(1): find transfer and replace transfer
    Transfer* transfer = &(*iterator)->data[id_transfer];
    index->remove_index(transfer);
    *transfer = new_transfer;
    index->create_index(&new_transfer);

    // O(size - position): Remining from updated block to the last block
    while (iterator != nullptr) {
        if ((*iterator)->mine())
            cout << "Block " << (*iterator)->id << " remined successfully. ✔️\n";
        else
            throw runtime_error("Block not remined");

        (*++iterator)->previous_hash = (*--iterator)->hash;
        ++iterator;
    }
    cout << "The transfer has been updated successfully. ✅\n";
}

template <typename T>
void BlockChain<T>::remove(int id_block, int id_transfer)
{
    Transfer* transfer = &chain[id_block]->data[id_transfer];
    index->remove_index(transfer);
    cout << "The following transfer has been removed successfully from the index. ✅\n";
    cout << *transfer << "\n";
}

template <typename T>
void BlockChain<T>::display()
{
    auto iterator = chain.end();
    for (int i = 0; i < 10; ++i) {
        cout << **iterator << "\n";
        cout << " 🢁 🢃 \n\n";
        --iterator;
    }
}

template <typename T>
void BlockChain<T>::create_genesis()
{
    auto genesis = new Block<T>();

    while (!genesis->data.is_full())
        genesis->insert(T());

    if (genesis->mine()) {
        chain.push_front(genesis);
    }
    else
        throw runtime_error("Block not mined");  
}

template <typename T>
int BlockChain<T>::size()
{
    return chain.size();
}


# endif // BLOCK_CHAIN_H