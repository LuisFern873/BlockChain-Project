
# CapyCoin BlockChain

![](assets/logo.png "Capyraba")

## 1. Introduction

Blockchain es una tecnología que ha hecho posible el comercio de criptomonedas debido a su seguridad en la validación de transacciones. Siguiendo con esta tendencia, decidí crear una nueva criptomoneda llamada "CapyCoin" la cual es soportada por la Blockchain implementada en este proyecto. Esta hace uso de distintas estructuras de datos para la indexación y el procesamiento eficiente de consultas. Al aprovechar dichas estructuras de datos personalizadas, mi Blockchain podrá manejar grandes cantidades de datos y brindar un acceso rápido y confiable a esos datos para los usuarios y las aplicaciones creadas sobre la misma.

## 2. Objectives
- Implementar un Block Chain que admita transacciones de criptomonedas "CapyCoin" utilizando estructuras de datos.

## 3. Description

This application allows users ...
- To register transactions in a safe way.
- Make optimized queries through efficient indexing. 

## 4. Proof of work system

Computing hash:

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






