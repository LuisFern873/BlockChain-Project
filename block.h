# ifndef BLOCK_H
# define BLOCK_H

# include <iostream>
# include "structures/circulararray.h"
# include "sha256.h"

using namespace std;

template <typename T, size_t N>
class Block
{
    public:
        size_t id;
        size_t nonce;
        CircularArray<T, N> data{}; 
        string hash;
        string previous_hash;
        bool is_valid;

        Block();
        void insert(T feature);
        T remove(size_t index);

        void set_nonce(size_t new_nonce);
        bool mine();

        template <typename T1, size_t N1>
        friend ostream& operator<<(ostream& os, const Block<T1,N1>& block);

    private:
        void update_hash();
};

template <typename T, size_t N>
Block<T, N>::Block() 
{
    id = 0;
    nonce = 0;
    hash = previous_hash = string(64, '0');
    is_valid = false;
}

template <typename T, size_t N>
void Block<T, N>::insert(T feature)
{
    data.push_back(feature);
}

template <typename T, size_t N>
T Block<T, N>::remove(size_t index)
{
    return data.remove(index);
}

template <typename T, size_t N>
void Block<T, N>::set_nonce(size_t new_nonce)
{
    nonce = new_nonce;
    update_hash();
}

template <typename T, size_t N>
bool Block<T, N>::mine()
{
    if (!data.is_full())
        throw runtime_error("Mining a non full block is not allowed");
    
    cout << "Mining block #" << id << "...\n";
    size_t nonce = 0;
    const size_t MAX_NONCE = 1'000'000;

    while (nonce < MAX_NONCE) {
        set_nonce(nonce);
        if (is_valid) 
            return true;
        ++nonce;
    }
    return false;
}

template <typename T, size_t N>
ostream& operator<<(ostream& os, Block<T,N>& block)
{
    os << "Id: " << block.id << "\n";
    os << "Nonce: " << block.nonce << "\n";
    os << "Transaction data:\n";
    os << "\n";
    for (size_t i = 0; i < block.data.size(); ++i)
        cout << block.data[i] << "\n";
    os << "Hash: " << block.hash << "\n";
    os << "Previous hash: " << block.previous_hash << "\n";
    os << "Valid: " << boolalpha << block.is_valid << "\n";
    return os;
}

template <typename T, size_t N>
void Block<T, N>::update_hash()
{
    static Sha256<CircularArray<T, N>, size_t> hasher{};
    hash = hasher(data, nonce);
    is_valid = hash.starts_with("0");
}

# endif // BLOCK_H