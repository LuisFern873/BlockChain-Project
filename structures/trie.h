# ifndef TRIE_H
# define TRIE_H

# include <iostream>
# include <algorithm>
# include <vector>
# include <map>
# include <stack>
# include <sstream>

using namespace std;

template <typename TV>
struct TrieNode 
{
    map<char, TrieNode*> children;
    vector<TV> values;
};

template <typename TV>
class Trie 
{
    public:
        Trie();
        void insert(string word, TV value);
        void remove(string word);
        template <typename FUNC>
        vector<TV> starts_with(string prefix, FUNC get_prefix);

    private:
        TrieNode<TV>* root;
};

template <typename TV>
Trie<TV>::Trie() 
{
    root = new TrieNode<TV>();
}

template <typename TV>
void Trie<TV>::insert(string word, TV value) 
{
    TrieNode<TV>* node = root;
    for (char c : word) {
        if (!node->children.contains(c)) {
            node->children[c] = new TrieNode<TV>();
        }
        node = node->children[c];
        node->values.push_back(value);
    }
}

template <typename TV>
void Trie<TV>::remove(string word) 
{
    TrieNode<TV>* node = root;
    vector<TrieNode<TV>*> nodes;
    for (char c : word) {
        if (!node->children.contains(c)) {
            return;
        }
        nodes.push_back(node);

        // remove value from values vector
        for (auto it = node->values.begin(); it != node->values.end(); ++it) {
            if ((*it)->get_sender() == word) {
                node->values.erase(it);
                break;
            }
        }
        node = node->children[c];
    }

    // remove empty nodes
    while (!nodes.empty() and node->values.empty() and node->children.empty()) {
        TrieNode<TV>* parent = nodes.back();
        nodes.pop_back();
        char c = word[nodes.size()];
        delete parent->children[c];
        parent->children.erase(c);
        node = parent;
    }
}

template <typename TV>
template <typename FUNC>
vector<TV> Trie<TV>::starts_with(string prefix, FUNC get_prefix) {
    vector<TV> report;
    TrieNode<TV>* node = root;
    for (char c : prefix) {
        if (!node->children.contains(c)) {
            return report;
        }
        node = node->children[c];
    }
    for (TV value : node->values) {
        if (get_prefix(value).substr(0, prefix.size()) == prefix) {
            report.push_back(value);
        }
    }
    return report;
}

# endif // TRIE_H