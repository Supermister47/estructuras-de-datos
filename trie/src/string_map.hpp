
#include "string_map.h"

template <typename T>
unsigned int string_map<T>::_tamAlfabeto = 256;




template <typename T>
string_map<T>::string_map() {
    _raiz = new Nodo();   // O(_tamAlfabeto), según cppreference
    _size = 0;
}



template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() {
    *this = aCopiar;
    _size = aCopiar._size;
}



template<typename T>
void string_map<T>::copiarNodos(string_map::Nodo* nodo, string_map::Nodo* oNodo) {
    if (oNodo->definicion != nullptr) {
        // Asumo que T tiene un constructor por copia
        nodo->definicion = new T(*(oNodo->definicion));
    }
    for (int i = 0; i < _tamAlfabeto; i++) {
        if (oNodo->siguientes[i] != nullptr) {
            nodo->siguientes[i] = new Nodo();
            copiarNodos(nodo->siguientes[i], oNodo->siguientes[i]);
        }
    }
}



template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d) {
    destruirNodos(_raiz);
    _raiz = new Nodo();
    copiarNodos(_raiz, d._raiz);
    return *this;
}



template<typename T>
void string_map<T>::destruirNodos(string_map::Nodo *nodo) {
    if (nodo == nullptr) {
        return;
    }
    for (int i = 0; i < _tamAlfabeto; i++) {
        destruirNodos(nodo->siguientes[i]);
    }
    delete nodo->definicion;
    delete nodo;
}



template <typename T>
string_map<T>::~string_map(){
    destruirNodos(_raiz);
}



template<typename T>
T& string_map<T>::devolverPunteroSignificado(const string &clave) {
    Nodo* nodoRecorrido = _raiz;

    // Recorro el trie con la palabra, creando vectores si no están definidos
    for (const char& c: clave) {
        int intLetra = int((unsigned char)c);
        Nodo* proxNodo = nodoRecorrido->siguientes[intLetra];

        // Me fijo si tiene un vector creado en la posición de la letra
        if (proxNodo == nullptr) {
            nodoRecorrido->siguientes[intLetra] = new Nodo();
        }
        // Sigo recorriendo el trie hasta llegar al final
        nodoRecorrido = nodoRecorrido->siguientes[intLetra];
    }

    // Una vez recorrido el trie, nodoRecorrido estará en el vector cuya definición
    // deberá ser el significado de la clave a insertar

    // No aumento el tamaño del trie si hay un significado ya definido
    if (nodoRecorrido->definicion == nullptr) {
        _size++;
        nodoRecorrido->definicion = new T();
    }
    // No hace falta hacer delete del significado anterior, sino redefinir el valor en el heap si el operador[]
    // es lvalue. Si es rvalue se devuelve una referencia al valor que ya está en el heap.
    // delete nodoRecorrido->definicion;

    return *(nodoRecorrido->definicion);
}



template<typename T>
void string_map<T>::insert(const pair<string, T> &claveSignificado) {
    T& pSignificado = devolverPunteroSignificado(claveSignificado.first);
    pSignificado = claveSignificado.second;
}



template <typename T>
T& string_map<T>::operator[](const string& clave) {
    return at(clave);
}



template<typename T>
const T& string_map<T>::operator[](const string &clave) const {
    return at(clave);
}



// Devuelve el nodo en el cual se termina de recorrer la clave en el trie
template<typename T>
const typename  string_map<T>::Nodo* string_map<T>::buscarClave(const string &clave) const {
    Nodo* nodoRecorrido = _raiz;
    auto itClave = clave.begin();

    // Recorro el trie con la palabra
    while (itClave != clave.end() && nodoRecorrido != nullptr) {
        int intLetra = int((unsigned char)(*itClave));
        nodoRecorrido = nodoRecorrido->siguientes[intLetra];
        itClave++;
    }

    // Una vez recorrido el trie, nodoRecorrido estará en el vector cuyo significado
    // será el el de la clave que se está buscando
    return nodoRecorrido;
}



template <typename T>
int string_map<T>::count(const string& clave) const {
    const Nodo* nodoClave = buscarClave(clave);
    return !(nodoClave == nullptr || nodoClave->definicion == nullptr);
}



template <typename T>
const T& string_map<T>::at(const string& clave) const {

    return *(buscarClave(clave)->definicion);
}



template <typename T>
T& string_map<T>::at(const string& clave) {

    return devolverPunteroSignificado(clave);
}



// O(_tamAlfabeto) en el mejor y peor caso
template<typename T>
bool string_map<T>::estaVacio(const vector<Nodo*> &v) const {
    bool esVacio = true;
    for (const Nodo* n: v) {
        esVacio &= n == nullptr;
    }
    return esVacio;
}



// Se recorre el trie, borrando los vectores que quedarían vacíos unas vez eliminada la clave
template <typename T>
void string_map<T>::erase(const string& clave) {
    Nodo* nodoRecorrido = _raiz;
    auto itClave = clave.begin();

    // Recorro el trie con la palabra
    while (itClave != clave.end() && nodoRecorrido != nullptr) {
        int intLetra = int((unsigned char)(*itClave));
        Nodo* nodoAux = nodoRecorrido->siguientes[intLetra];

        // Ignora si el nodoRecorrido es la raíz, ya que siempre tiene que quedar definida
        if (nodoRecorrido == _raiz);
        else {
            if (estaVacio(nodoRecorrido->siguientes)) {
                delete nodoRecorrido->definicion;
                delete nodoRecorrido;
            }
        }
        // Sigo recorriendo el trie hasta llegar al final
        nodoRecorrido = nodoAux;
        itClave++;
    }

    // Una vez recorrido el trie, nodoRecorrido estará en el vector cuyo significado
    // será el el de la clave que se está buscando
    // Si este vector sigue definido, quiere decir de que hay más palabras cuyo prefijo es la clave, por lo que
    // habría que borrar el significado de esta clave aparte
    // (Si se borrase todo el nodo, entonces la definición se borra también)
    if (nodoRecorrido != nullptr) {
        delete nodoRecorrido->definicion;
        nodoRecorrido->definicion = nullptr;
    }
    if (!empty()) {
        _size--;
    }

}



template <typename T>
int string_map<T>::size() const {
    return _size;
}



template <typename T>
bool string_map<T>::empty() const {
    return _size == 0;
}