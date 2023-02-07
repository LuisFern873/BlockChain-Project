# ifndef CHAIN_HASH_H
# define CHAIN_HASH_H

# include <iostream>
# include <forward_list>

using namespace std;

template <typename K, typename V>
struct Entry
{
	K key;
	V value;

	Entry(K key, V value);
};

template <typename K, typename V>
class ChainHash
{
	public:
    	ChainHash();
		void insert(K key, V value);
		void remove(K key);
		V find(K key);
		void display();

	private:
		forward_list<Entry<K,V>>* array;
		int capacity;
	    int size;
		const int MAX_COLLISIONS = 3;
		const float MAX_LOAD_FACTOR = 0.5;

		float load_factor();
		size_t hash_function(K key);
		V& operator[](K key);
		void rehashing();
};

// Entry implementation

template <typename K, typename V>
Entry<K,V>::Entry(K key, V value) : key(key), value(value) {}

template <typename K, typename V>
ostream& operator<<(ostream& os, const Entry<K,V>& entry){
	os << "{" << entry.key << ": " << entry.value << "}";
	return os;
}

// Chain Hash implementation

template <typename K, typename V>
ChainHash<K,V>::ChainHash()
{
	capacity = 10; 
	array = new forward_list<Entry<K,V>>[capacity];
	size = 0;
}

template <typename K, typename V>
void ChainHash<K,V>::insert(K key, V value)
{
	operator[](key) = value;
}

template <typename K, typename V>
V& ChainHash<K,V>::operator[](K key)
{
	if(load_factor() >= MAX_LOAD_FACTOR)
		rehashing();

	size_t index = hash_function(key);
	auto& chain = array[index];

	for(auto& entry : chain){
		if(entry.key == key)
			return entry.value;
	}

	Entry entry = {key, V()};
	chain.push_front(entry);
	++size;
	return chain.front().value;
}

template <typename K, typename V>
V ChainHash<K,V>::find(K key) 
{
	size_t index = hash_function(key);
	auto& chain = array[index];

	for(auto& entry : chain){
		if(entry.key == key)
			return entry.value;
	}
	throw invalid_argument("Key not found.");
}

template <typename K, typename V>
void ChainHash<K,V>::remove(K key)
{
	size_t index = hash_function(key);
	auto& chain = array[index];

	auto count = chain.remove_if([&](const Entry<K,V>& entry){ 
		return entry.key == key;
	});

	if(!count)
		throw invalid_argument("Key not found.");
}

template <typename K, typename V>
void ChainHash<K,V>::display() 
{
	size_t index = 0;
	for(int i = 0; i < capacity; ++i){
	    cout << index++ << "\t";
		const auto& chain = array[i];
	    for(const auto& entry : chain){
	        cout << entry << " ⟶  ";
	    }
	    cout << "null\n";
	}
	cout << "\n";
}

template <typename K, typename V>
float ChainHash<K,V>::load_factor()
{
	return float(size) / (float(capacity) * float(MAX_COLLISIONS));
}

template <typename K, typename V>
size_t ChainHash<K,V>::hash_function(K key)
{
	static hash<K> hasher{};
	return hasher(key) % capacity;
}

template <typename K, typename V>
void ChainHash<K,V>::rehashing()
{
	capacity *= 2;
	auto temporal = new forward_list<Entry<K,V>>[capacity];
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