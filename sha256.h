# ifndef SHA256_H
# define SHA256_H

# include <iostream>
# include <string>
# include <iomanip> 
# include <openssl/sha.h>

using namespace std;

template <typename T>
class Sha256
{
    public:
        string operator()(T data);

    private:
        string stringify(T data);
        unsigned char* sha256_init(string data);
        string sha256_final(unsigned char* initial_hash);
};

template <typename T>
string Sha256<T>::operator()(T data)
{
    auto str_data = stringify(data);
    auto initial_hash = sha256_init(str_data);
    auto final_hash = sha256_final(initial_hash);
    return final_hash;
}

template <typename T>
string Sha256<T>::stringify(T data)
{
    if constexpr (is_convertible_v<T, string>) 
        return data;
    else 
        return to_string(data);
}

template <typename T>
unsigned char* Sha256<T>::sha256_init(string data)
{
    auto initial_hash = new unsigned char[SHA256_DIGEST_LENGTH];
    auto uchar_data = reinterpret_cast<const unsigned char*>(data.c_str());
    SHA256(uchar_data, data.length(), initial_hash);
    return initial_hash;
}

template <typename T>
string Sha256<T>::sha256_final(unsigned char* initial_hash)
{
    stringstream final_hash;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
        final_hash << hex << static_cast<int>(initial_hash[i]);
    return final_hash.str();
};

# endif // SHA256_H