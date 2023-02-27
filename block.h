# ifndef BLOCK_H
# define BLOCK_H

# include <iostream>
# include "structures/circulararray.h"
# include "sha256.h"

using namespace std;

template <typename T, int N = 5>
class Block
{
    public:
        int id;
        int nonce;
        CircularArray<T, N> data{}; 
        string hash;
        string previous_hash;
        bool is_valid;

        Block();
        ~Block() = default;
        void insert(T feature);
        void remove(int index);
        void set_nonce(int new_nonce);
        bool mine();
        int size();

        template <typename T1, int N1>
        friend ostream& operator<<(ostream& os, const Block<T1,N1>& block);

    private:
        void update_hash();
};

template <typename T, int N>
Block<T, N>::Block() 
{
    id = 0;
    nonce = 0;
    hash = previous_hash = string(64, '0');
    is_valid = false;
}

template <typename T, int N>
void Block<T, N>::insert(T feature)
{
    feature.id_block = id;
    data.push_back(feature);
}

template <typename T, int N>
void Block<T, N>::remove(int index)
{
    data.remove(index);
}

template <typename T, int N>
int Block<T, N>::size()
{
    return data.size();
}

template <typename T, int N>
void Block<T, N>::set_nonce(int new_nonce)
{
    nonce = new_nonce;
    update_hash();
}

template <typename T, int N>
bool Block<T, N>::mine()
{
    if (!data.is_full())
        throw runtime_error("Mining a non full block is not allowed");
    
    int nonce = 0;
    const int MAX_NONCE = 1'000'000;

    while (nonce < MAX_NONCE) {
        set_nonce(nonce);
        if (is_valid) 
            return true;
        ++nonce;
    }
    return false;
}

template <typename T, int N>
ostream& operator<<(ostream& os, Block<T,N>& block)
{
    os << "Id: " << block.id << "\n";
    os << "Nonce: " << block.nonce << "\n";
    os << "Transaction data:\n";
    os << "\n";
    for (int i = 0; i < block.data.size(); ++i)
        cout << block.data[i] << "\n";
    os << "Hash: " << block.hash << "\n";
    os << "Previous hash: " << block.previous_hash << "\n";
    os << "Valid: " << boolalpha << block.is_valid << "\n";
    return os;
}

template <typename T, int N>
void Block<T, N>::update_hash()
{
    static Sha256<CircularArray<T, N>, int> hasher{};
    hash = hasher(data, nonce);
    is_valid = hash.starts_with("0");
}

# endif // BLOCK_H