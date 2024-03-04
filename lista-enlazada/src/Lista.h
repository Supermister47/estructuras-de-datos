#ifndef _LISTA_ALUMNOS_H_
#define _LISTA_ALUMNOS_H_

#include <string>
#include <ostream>
#include <cassert>

using namespace std;

typedef unsigned long Nat;


class Lista {
public:

    /**
     * Constructor por defecto de la clase Lista.
     */
    Lista();

    /**
     * Constructor por copia de la clase Lista.
     */
    Lista(const Lista& l);

    /**
     * Destructor de la clase Lista.
     */
    ~Lista();

    /**
     * Operador asignación
     * @param aCopiar
     * @return
     */
    Lista& operator=(const Lista& aCopiar);

    /**
     * Agrega un elemento al principio de la Lista.
     * @param elem elemento a agregar
     */
    void agregarAdelante(const Nat& elem);

    /**
     * Agrega un elemento al final de la Lista.
     * @param elem elemento a agregar
     */
    void agregarAtras(const Nat& elem);

    /**
     * Elimina el i-ésimo elemento de la Lista.
     * @param i posición del elemento a eliminar
     */
    void eliminar(Nat i);

    /**
     * Devuelve la cantidad de elementos que contiene la Lista.
     * @return
     */
    int longitud() const;

    /**
     * Devuelve el elemento en la i-ésima posición de la Lista.
     * @param i posición del elemento a devolver.
     * @return referencia no modificable
     */
    const Nat& iesimo(Nat i) const;
    /**
     * Devuelve el elemento en la i-ésima posición de la Lista.
     * @param i posición del elemento a devolver.
     * @return referencia modificable
     */
    Nat& iesimo(Nat i);

    /**
     * Muestra la lista en un ostream
     * formato de salida: [a_0, a_1, a_2, ...]
     * @param o
     */
    void mostrar(ostream& o);

    /**
     * Utiliza el método mostrar(os) para sobrecargar el operador <<
     */
    friend ostream& operator<<(ostream& os, Lista& l) {
        l.mostrar(os);
        return os;
    }

    Nat& operator[](Nat i);

private:

    struct Nodo {
        Nodo* ant;
        Nodo* sig;
        Nat valor;

        Nodo(Nodo* ant, Nat v, Nodo* sig): ant(ant), valor(v), sig(sig) {};
    };

    Nodo* _prim;
    Nodo* _ult;

    void agregarUnElemento(const Nat& elem);
    Nodo* iesimoNodo(Nat i) const;
    void copiarNodos(const Lista& l);
    void destruirNodos();

};

#endif
