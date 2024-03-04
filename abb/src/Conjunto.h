#ifndef CONJUNTO_H_
#define CONJUNTO_H_

#include <string>
#include <iostream>
#include <list>

using namespace std;

template <class T>
class Conjunto
{
    public:

        // Constructor. Genera un conjunto vacío.
        Conjunto();

        // Destructor. Debe dejar limpia la memoria.
        ~Conjunto();

        // Inserta un elemento en el conjunto. Si este ya existe,
        // el conjunto no se modifica.
        void insertar(const T&);

        // Decide si un elemento pertenece al conjunto o no.
        bool pertenece(const T&) const;

        // Borra un elemento del conjunto. Si este no existe,
        // el conjunto no se modifica.
        void remover(const T&);

        // Devuelve el siguiente elemento al recibido por párametro, inorder.
        // Pre: el elemento está en el conjunto y no es el máximo del conjunto.
        const T& siguiente(const T& clave);

        // Devuelve el anterior elemento al recibido por párametro, inorder.
        // Pre: el elemento está en el conjunto y no es el mínimo del conjunto.
        const T& anterior(const T& clave);

        // Devuelve el mínimo elemento del conjunto según <.
        const T& minimo() const;

        // Devuelve el máximo elemento del conjunto según <.
        const T& maximo() const;

        // Devuelve la cantidad de elementos que tiene el conjunto.
        unsigned int cardinal() const;

        // Muestra el conjunto.
        void mostrar(std::ostream& o) const;

        list<T> inorder() const;
        list<T> preorder() const;
        list<T> postorder() const;

    private:

        struct Nodo {

            // El elemento al que representa el nodo.
            T valor;
            // Puntero a la raíz del subárbol izquierdo.
            Nodo* izq;
            // Puntero a la raíz del subárbol derecho.
            Nodo* der;

             // El constructor, toma el elemento al que representa el nodo.
            Nodo(const T& v): izq(nullptr), valor(v), der(nullptr) {};
        };

        // Puntero a la raíz de nuestro árbol.
        Nodo* _raiz;

        void destruirNodosRec(Nodo*);

        // La segunda coordenada tiene al nodo con el valor clave y la primer coordenada tiene al padre del mismo
        // Si clave no está también se devolverá un nodo padre.
        pair<Nodo*, Nodo*> buscarNodoClaveYPadre(const T& clave) const;
        bool esHijoDerecho(Conjunto::Nodo*, Conjunto::Nodo*) const;
        unsigned int cardinalRec(Nodo*) const;

        Nodo* anteriorNodo(const T& clave);
        Nodo* siguienteNodo(const T& clave);
        Nodo* minimoNodo(Nodo* nodo) const;
        Nodo* maximoNodo(Nodo* nodo) const;

        list<T> listaNodosAT(list<Nodo*>) const;

        list<Nodo*> inorderRec(Nodo* nodo) const;
        list<T> preorderRec(Nodo* nodo) const;
        list<T> postorderRec(Nodo* nodo) const;

};

template<class T>
std::ostream& operator<<(std::ostream& os, const Conjunto<T>& c) {
	 c.mostrar(os);
	 return os;
}

#include "Conjunto.hpp"

#endif // CONJUNTO_H_
