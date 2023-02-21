# ifndef CHAIN_HASH_H
# define CHAIN_HASH_H

# include <iostream>
# include <forward_list>

using namespace std;

template <typename TK, typename TV>
class ChainHash
{
	public:
    	ChainHash();
		void insert(TK key, TV value);
		void remove(TK key);
		TV find(TK key);
		void display();

	private:
		struct Entry {
			TK key;
			TV value;

			Entry(TK key, TV value);
		};

		forward_list<Entry>* array;
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
	array = new forward_list<Entry>[capacity];
	size = 0;
}

template <typename TK, typename TV>
void ChainHash<TK,TV>::insert(TK key, TV value)
{
	if(load_factor() >= MAX_LOAD_FACTOR)
		rehashing();

	size_t index = hash_function(key);
	auto& chain = array[index];

	for(auto& entry : chain){
		if(entry.key == key)
			entry.value = value;
	}

	Entry entry = {key, value};
	chain.push_front(entry);
	++size;
}

template <typename TK, typename TV>
TV ChainHash<TK,TV>::find(TK key) 
{
	size_t index = hash_function(key);
	auto& chain = array[index];

	for(auto& entry : chain){
		if(entry.key == key)
			return entry.value;
	}
	throw invalid_argument("Key not found");
}

template <typename TK, typename TV>
void ChainHash<TK,TV>::remove(TK key)
{
	size_t index = hash_function(key);
	auto& chain = array[index];

	auto count = chain.remove_if([&](const Entry& entry){ 
		return entry.key == key;
	});

	if(!count)
		throw invalid_argument("Key not found");
}

template <typename TK, typename TV>
void ChainHash<TK,TV>::display() 
{
	size_t index = 0;
	for(int i = 0; i < capacity; ++i){
	    cout << index++ << "\t";
		const auto& chain = array[i];
	    for(const auto& entry : chain){
			cout << "{" << entry.key << ": " << entry.value << "} ⟶  ";
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
	auto temporal = new forward_list<Entry>[capacity];
	for(int i = 0; i < capacity / 2; ++i){
		const auto& chain = array[i];
		for(const auto& entry : chain){
			size_t index = hash_function(entry.key);
			temporal[index].push_front(entry);
		}
	}
    delete[] array;
    array = temporal;
}

# endif // CHAIN_HASH_H