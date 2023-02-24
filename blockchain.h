# ifndef BLOCK_CHAIN_H
# define BLOCK_CHAIN_H

# include "block.h"
# include "record.h"
# include "structures/doublelist.h"

template <typename T, size_t N = 5>
class BlockChain
{
    public:
        BlockChain();
        void insert(T feature);
        void update(T new_feature, size_t id_block, size_t id_feature);
        void remove(size_t id_block, size_t id_feature);
        void display();


        int size();

        Block<T, N>* block;

    private:
        DoubleList<Block<T, N>*> chain;

        void create_genesis();

    friend class Index;
};

template <typename T, size_t N>
BlockChain<T, N>::BlockChain()
{
    create_genesis();
    block = new Block<T, N>();
}

template <typename T, size_t N>
void BlockChain<T, N>::insert(T feature)
{
    block->insert(feature);

    if (!block->data.is_full())
        return;
    
    block->id = chain.size();
    block->previous_hash = chain.back()->hash;

    if (block->mine()) {
        chain.push_back(block);
        block = new Block<T, N>();
    }
    else
        throw runtime_error("Block not mined");

    // update index
    // Index::update();
}

template <typename T, size_t N>
void BlockChain<T, N>::update(T new_feature, size_t id_block, size_t id_feature)
{
    // O(size): find block position
    auto iterator = chain.begin();
    while ((*iterator)->id != id_block)
        ++iterator;

    // O(N) + O(1): find feature and replace feature
    (*iterator)->data[id_feature] = new_feature;

    // O(size - position): Remining from updated block to the last block
    while (iterator != nullptr) {
        if ((*iterator)->mine())
            cout << "Block " << (*iterator)->id << " remined successfully\n";
        else
            throw runtime_error("Block not remined");

        (*++iterator)->previous_hash = (*--iterator)->hash;
        ++iterator;
    }
}

template <typename T, size_t N>
void BlockChain<T, N>::remove(size_t id_block, size_t id_feature)
{
    // Just remove from index
}

template <typename T, size_t N>
void BlockChain<T, N>::display()
{
    auto iterator = chain.end();
    for (int i = 0; i < 10; ++i) {
        cout << **iterator << "\n";
        cout << " 🢁 🢃 \n\n";
        --iterator;
    }
}

template <typename T, size_t N>
void BlockChain<T, N>::create_genesis()
{
    auto genesis = new Block<T, N>();

    while (!genesis->data.is_full())
        genesis->insert(T());

    if (genesis->mine()) {
        chain.push_front(genesis);
    }
    else
        throw runtime_error("Block not mined");  
}

template <typename T, size_t N>
int BlockChain<T, N>::size()
{
    return chain.size();
}


# endif // BLOCK_CHAIN_H