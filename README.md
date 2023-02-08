
# CapyCoin BlockChain

![](assets/logo.png "Capyraba")

## 1. Introduction


## 2. Objectives
- Implement a BlockChain that supports CapyCoin cryptocurrency transactions using data structures. 


## 3. Description

It allows users ...
- to register transactions in a safe way.
- make optimized queries through efficient indexing. 



## 4. Proof of work system


Computing hash


![](assets/hash.png "Sha256")

```cpp
template <typename T>
void Block<T>::update_hash()
{
    static Sha256<T,size_t> hasher;
    hash = hasher(data, nonce);
    is_valid = hash.starts_with("00");
}
```






