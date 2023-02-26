# ifndef CHAIN_HASH_H
# define CHAIN_HASH_H

# include <iostream>
# include "forwardlist.h"

using namespace std;

template <typename TK, typename TV>
class ChainHash
{
	public:
    	ChainHash();
		~ChainHash();
		void insert(TK key, TV value);
		void remove(TK key);
		TV find(TK key);
		void display();

	private:
		struct Entry {
			TK key;
			TV value;

			Entry() = default;
			Entry(TK key, TV value);
		};

		ForwardList<Entry>* array;
		int capacity;
	    int size;
		const int MAX_COLLISIONS = 3;
		const float MAX_LOAD_FACTOR = 0.5;

		float load_factor();
		size_t hash_function(TK key);
		void rehashing();
};

// Entry implementation

template <typename TK, typename TV>
ChainHash<TK,TV>::Entry::Entry(TK key, TV value) : key(key), value(value) {}

// Chain Hash implementation

template <typename TK, typename TV>
ChainHash<TK,TV>::ChainHash()
{
	capacity = 10; 
	array = new ForwardList<Entry>[capacity];
	size = 0;
}

template <typename TK, typename TV>
ChainHash<TK,TV>::~ChainHash()
{
	delete[] array;
}

template <typename TK, typename TV>
void ChainHash<TK,TV>::insert(TK key, TV value)
{
	if(load_factor() >= MAX_LOAD_FACTOR)
		rehashing();

	size_t index = hash_function(key);
	auto& chain = array[index];

	for(int i = 0; i < chain.size(); ++i){
		if(chain[i].key == key)
			chain[i].value = value;
	}
	Entry entry(key, value);
	chain.push_front(entry);
	++size;
}

template <typename TK, typename TV>
TV ChainHash<TK,TV>::find(TK key) 
{
	size_t index = hash_function(key);
	auto& chain = array[index];

	for(int i = 0; i < chain.size(); ++i){
		if(chain[i].key == key)
			return chain[i].value;
	}
	throw out_of_range("Key not found.");
}

template <typename TK, typename TV>
void ChainHash<TK,TV>::remove(TK key)
{
	size_t index = hash_function(key);
	auto& chain = array[index];

	for(int i = 0; i < chain.size(); ++i){
		if(chain[i].key == key) {
			chain.remove(i);
			return;
		}
	}
	cout << "Key not found.\n"; 
}

template <typename TK, typename TV>
void ChainHash<TK,TV>::display() 
{
	size_t index = 0;
	for(int i = 0; i < capacity; ++i){
	    cout << index++ << "\t";
		auto& chain = array[i];
		for(int i = 0; i < chain.size(); ++i){
			cout << "{" << chain[i].key << ": " << chain[i].value << "} ⟶  ";
		}
	    cout << "null\n";
	}
	cout << "\n";
}

template <typename TK, typename TV>
float ChainHash<TK,TV>::load_factor()
{
	return float(size) / (float(capacity) * float(MAX_COLLISIONS));
}

template <typename TK, typename TV>
size_t ChainHash<TK,TV>::hash_function(TK key)
{
	static hash<TK> hasher{};
	return hasher(key) % capacity;
}

template <typename TK, typename TV>
void ChainHash<TK,TV>::rehashing()
{
	capacity *= 2;
	auto temporal = new ForwardList<Entry>[capacity];
	for(int i = 0; i < capacity / 2; ++i){
		auto& chain = array[i];
		for(int i = 0; i < chain.size(); ++i){
			size_t index = hash_function(chain[i].key);
			temporal[index].push_front(chain[i]);
		}
	}
    delete[] array;
    array = temporal;
}

# endif // CHAIN_HASH_H