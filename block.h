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
        CircularArray<T, N> features; 
        string hash;
        string previous_hash;
        bool is_valid;

        Block();
        void insert(T data);
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

}

template <typename T, size_t N>
void Block<T, N>::insert(T data)
{
    features.push_back(data);

    if (features.is_full())
        set_nonce(0);
}

template <typename T, size_t N>
T Block<T, N>::remove(size_t index)
{
    return features.remove(index);
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
    size_t nonce = 1;
    const size_t MAX_NONCE = 1'000'000;

    while (nonce < MAX_NONCE) {
        set_nonce(nonce);
        if(is_valid){
            return true;
        }
        ++nonce;
    }
    return false;
}

template <typename T, size_t N>
ostream& operator<<(ostream& os, Block<T,N>& block)
{
    os << "id: " << block.id << "\n";
    os << "Nonce: " << block.nonce << "\n";
    os << "Transaction data:\n";
    os << "\n";
    for (size_t i = 0; i < block.features.size(); ++i)
        cout << block.features[i] << "\n";
    os << "Hash: " << block.hash << "\n";
    os << "Previous hash: " << block.previous_hash << "\n";
    os << "Valid: " << boolalpha << block.is_valid << "\n";
    return os;
}

template <typename T, size_t N>
void Block<T, N>::update_hash()
{
    static Sha256<CircularArray<T, N>, size_t> hasher{};
    hash = hasher(features, nonce);
    is_valid = hash.starts_with("0");
}

# endif // BLOCK_H