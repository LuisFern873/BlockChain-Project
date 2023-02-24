
# CapyCoin Blockchain

![](assets/logo.png "Capyraba")

## 1. Introducción

Blockchain es una tecnología que ha impulsado el comercio de criptomonedas debido a su seguridad en la validación de transacciones. Siguiendo con esta tendencia, decidí crear una nueva criptomoneda llamada "CapyCoin" la cual es soportada por la Blockchain implementada en presente proyecto. Esta hace uso de distintas estructuras de datos para la indexación y el procesamiento eficiente de consultas. Al aprovechar dichas estructuras de datos personalizadas, mi Blockchain podrá manejar grandes cantidades de datos y brindar un acceso rápido y confiable a esos datos para los usuarios y las aplicaciones creadas sobre la misma.

## 2. Objetivos
- Implementar un Blockchain que admita transacciones de criptomonedas "CapyCoin" utilizando estructuras de datos.
- Utilizar estructuras de datos de indexación como hash tables y B+ trees para el acceso rápido a la información contenida en la Blockchain.


## 3. Estructuras de datos de la Blockchain


## 4. Sistema de Proof-of-work

Para resguardar la integridad de los datos, la inserción de cada bloque a la Blockchain requiere que este se encuentre minado.

A cada bloque se le asigna un código hash de acuerdo a su contenido (historial de transacciones) y el nonce haciendo uso del algoritmo criptográfico sha256, como se ilustra en la imagen:


![](assets/hash.png "Sha256")

```cpp
template <typename T, size_t N>
void Block<T, N>::update_hash()
{
    static Sha256<CircularArray<T, N>, size_t> hasher{};
    hash = hasher(data, nonce);
    is_valid = hash.starts_with("00");
}
```

Para que el bloque sea válido su código hash debe empezar con 2 ceros. De este modo, el método mine busca el nonce adecuado para que este criterio se cumpla.

```cpp
template <typename T, size_t N>
bool Block<T, N>::mine()
{
    if (!data.is_full())
        throw runtime_error("Mining a non full block is not allowed");

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
```

## 5. Estructuras de datos de indexación y consultas

Para la consulta de datos eficiente de la Blockchain, las transacciones han sido indexadas con distintas estructuras de datos como se muestra en la imagen:
![](assets/schema.png "Schema")


### EqualTo
Para esta consulta se utilizó un de `ChainHash` implementado con array de `ForwardList`.

```cpp
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
        ...
};
```

### RangeSearh, MaxValue y MinValue
Para estas 3 consultas se utilizó un `B+ Tree`. 

```cpp
template <typename TK, typename TV>
class BPlusTree
{
    public:
        BPlusTree();
        ~BPlusTree();
        void insert(TK key, TV value);
        void remove(TK key);
        TV min();
        TV max();
        TV search(TK key);
        vector<TV> rangeSearch(TK start, TK end);
        void displayPretty();
        int height();

    private:
        struct Node {
            TK* key;
            TV* value;

            Node** children;
            int count;
            bool leaf;
    
            Node();
            ~Node();
        };

        Node* root;
        ...
}
```

### StartWith y Contains
Para estas 2 consultas se utilizó un `Trie estándar`.

```cpp

```

## 6. Análisis Big-O

## 7. Conclusiones
 

## 8. Referencias bibliográficas










