# ifndef TRIE_H
# define TRIE_H

# include <iostream>
# include <vector>
# include <map>
# include <stack>
# include <sstream>

using namespace std;

// template <typename TV>
// vector<TV> starts_with(string prefix)

// TrieSimple<string, TV> start_sender_index;


// Trie<Transfer*> start_sender_index;
// Trie<Transfer*> start_receiver_index;

template <typename TV>
struct TrieNode {
    map<char, TrieNode*> children;
    vector<TV> values;
};

template <typename TV>
class Trie {
public:
    Trie() {
        root = new TrieNode<TV>();
    }

    void insert(string word, TV value) {
        TrieNode<TV>* node = root;
        for (char c : word) {
            if (!node->children.contains(c)) {
                node->children[c] = new TrieNode<TV>();
            }
            node = node->children[c];
            node->values.push_back(value);
        }
    }

    template <typename FUNC>
    vector<TV> starts_with(string prefix, FUNC get_prefix) {
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

private:
    TrieNode<TV>* root;
    // Assumes that TV has a method get_word() that returns a string

};






// class TrieSimple
// {
//     public:
//         TrieSimple(): root(new TrieNode()) {}
//         void insert(string key);
//         bool search(string key);
//         void remove(string key);
//         int height();    
//         string toString(string sep);
//         void displayPretty();

//     private:
//         struct TrieNode {
//             map<char, TrieNode*> children;  // self-balancing binary search tree      
//             bool endWord;
//             TrieNode();        
//             ~TrieNode();
//         };

//         TrieNode* root;

//         int height(TrieNode* node);
//         void displayGivenLevel(TrieNode* node, int level);
//         void toString(TrieNode* node, string& prefix, string sep, stringstream& out);
// };

// TrieSimple::TrieNode::TrieNode()
// {
//     endWord = false;
// }

// TrieSimple::TrieNode::~TrieNode()
// {
//     auto iterator = children.begin();

//     while (iterator != children.end()) {
//         delete iterator->second;
//         ++iterator;
//     }
// }


// void TrieSimple::insert(string key)
// {
//     TrieNode* current = root;

//     for (const char& c : key) {
//         if (!current->children.contains(c)) {
//             current->children[c] = new TrieNode();
//         }
//         current = current->children[c];
//     }
//     current->endWord = true;
// }

// bool TrieSimple::search(string key)
// {
//     TrieNode* current = root;

//     for (const char& c : key) {
//         if (!current->children.contains(c)) {
//             return false;
//         }
//         current = current->children[c];
//     }
//     return current->endWord;
// }

// void TrieSimple::remove(string key)
// {
//     TrieNode* current = root;

//     stack<pair<TrieNode*, char>> nodeStack;

//     for (const char& c : key) {
//         auto child = current->children.find(c);
//         if (child == current->children.end()) {
//             return;
//         }
//         nodeStack.push({current, c});
//         current = child->second;
//     }

//     if (!current->endWord) {
//         return;
//     }

//     current->endWord = false;

//     while (!nodeStack.empty()) {
//         auto [node, c] = nodeStack.top();
//         nodeStack.pop();
//         TrieNode* child = node->children[c];
//         if (child->children.empty() and !child->endWord) {
//             node->children.erase(c);
//             delete child;
//         } else {
//             break;
//         }
//     }
// }

// string TrieSimple::toString(string sep)
// {
//     string prefix = "";
//     stringstream out;
//     toString(root, prefix, sep, out);
//     return out.str();
// }

// void TrieSimple::toString(TrieNode* node, string& prefix, string sep, stringstream& out)
// {
//     if (node->endWord)
//         out << prefix << sep;
    
//     for (auto& [c, child] : node->children) {
//         prefix.push_back(c);
//         toString(child, prefix, sep, out);
//         prefix.pop_back();
//     }
// }

// int TrieSimple::height()
// {
//     if (root->children.empty())
//         return 0;
//     else
//         return height(root);
// }

// int TrieSimple::height(TrieNode* node)
// {
//     int maxHeight = 0;
//     for (auto& child : node->children) {
//         int childHeight = height(child.second);
//         maxHeight = max(maxHeight, childHeight);
//     }
//     return maxHeight + 1;
// }

// void TrieSimple::displayPretty()
// {
//     for (int i = 1; i <= height(); ++i) {
//         displayGivenLevel(root, i);
//         cout << "\n";
//     }
// }

// void TrieSimple::displayGivenLevel(TrieNode* node, int level)
// {
//     if (node == nullptr)
//         return;
//     if (level == 1) {
// 		for (const auto& child : node->children) {
// 			cout << "{" << child.first << "} ";
// 		}
// 	}
//     else {
// 		for (const auto& child : node->children) {
// 			displayGivenLevel(child.second, level - 1);
// 		}
//     }
// }

# endif // TRIE_H