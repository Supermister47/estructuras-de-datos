#ifndef STRING_MAP_H_
#define STRING_MAP_H_

#include <string>

using namespace std;

template<typename T>
class string_map {
public:
    /**
    CONSTRUCTOR
    * Construye un diccionario vacio.
    **/
    string_map();

    /**
    CONSTRUCTOR POR COPIA
    * Construye un diccionario por copia.
    **/
    string_map(const string_map<T>& aCopiar);

    /**
    OPERADOR ASIGNACION
     */
    string_map& operator=(const string_map& d);

    /**
    DESTRUCTOR
    **/
    ~string_map();

    /**
    INSERT 
    * Inserta un par {clave, valor} en el diccionario
    **/
    void insert(const pair<string, T>&);

    /**
    COUNT
    * Devuelve la cantidad de apariciones de la clave (0 o 1).
    * Sirve para identificar si una clave está definida o no.
    **/

    int count(const string &clave) const;

    /**
    AT
    * Dada una clave, devuelve su significado.
    * PRE: La clave está definida.
    --PRODUCE ALIASING--
    -- Versión no modificable y modificable
    **/
    const T& at(const string& clave) const;
    T& at(const string& clave);

    /**
    ERASE
    * Dada una clave, la borra del diccionario junto a su significado.
    * PRE: La clave está definida.
    --PRODUCE ALIASING--
    **/
    void erase(const string& clave);

    /**
     SIZE
     * Devuelve cantidad de claves definidas */
    int size() const;

    /**
     EMPTY
     * devuelve true si no hay ningún elemento en el diccionario */
    bool empty() const;

    /**
    * operator[]
    * Acceso o definición de pares clave/valor
    -- Versión no modificable y modificable
    **/
    T& operator[](const string &clave);
    const T& operator[](const string &clave) const;

private:

    struct Nodo {
        vector<Nodo*> siguientes;
        T* definicion;

        Nodo(): siguientes(vector<Nodo*>(_tamAlfabeto, nullptr)), definicion() {};
    };

    Nodo* _raiz;
    int _size;
    static unsigned int _tamAlfabeto;

    void copiarNodos(Nodo* nodo, Nodo* oNodo);
    void destruirNodos(Nodo* nodo);
    bool estaVacio(const vector<Nodo*> &v) const;
    const Nodo* buscarClave(const string& clave) const;
    T& devolverPunteroSignificado(const string& clave);
};

#include "string_map.hpp"

#endif // STRING_MAP_H_
