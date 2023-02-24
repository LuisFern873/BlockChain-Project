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

    private:
        DoubleList<Block<T, N>*> chain;
        Block<T, N>* current;

        void create_genesis();

    friend class Index;
};

template <typename T, size_t N>
BlockChain<T, N>::BlockChain()
{
    create_genesis();
    current = new Block<T, N>();
    current->id = 1;
}

template <typename T, size_t N>
void BlockChain<T, N>::insert(T feature)
{
    current->insert(feature);

    if (!current->data.is_full())
        return;
    
    current->previous_hash = chain.back()->hash;

    if (current->mine()) {
        chain.push_back(current);
        current = new Block<T, N>();
        current->id = chain.size();
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