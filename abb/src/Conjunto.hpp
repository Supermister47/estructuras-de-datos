
#include "Conjunto.h"




template <class T>
Conjunto<T>::Conjunto() {
    _raiz = nullptr;
}



template<class T>
void Conjunto<T>::destruirNodosRec(Conjunto::Nodo* nodo) {

    if (nodo == nullptr) {
        return;
    }

    destruirNodosRec(nodo->izq);
    destruirNodosRec(nodo->der);
    delete nodo;
}



template <class T>
Conjunto<T>::~Conjunto() { 
    destruirNodosRec(_raiz);
}



template <class T>
pair<typename Conjunto<T>::Nodo*, typename Conjunto<T>::Nodo*> Conjunto<T>::buscarNodoClaveYPadre(const T &clave) const {
    Nodo* nodoCandidato = _raiz;
    Nodo* nodoPadre = _raiz;
    bool elemEncontrado = false;

    while (nodoCandidato != nullptr && !elemEncontrado) {
        if (nodoCandidato->valor == clave) {
            elemEncontrado = true;
        }
        else {
            nodoPadre = nodoCandidato;
            if (nodoCandidato->valor < clave) {
                nodoCandidato = nodoCandidato->der;
            }
            else {
                nodoCandidato = nodoCandidato->izq;
            }
        }
    }

    return make_pair(nodoPadre, nodoCandidato);
}



template <class T>
bool Conjunto<T>::pertenece(const T& clave) const {
    const Nodo* nodo = buscarNodoClaveYPadre(clave).second;
    return nodo != nullptr;
}



template <class T>
void Conjunto<T>::insertar(const T& clave) {
    Nodo* nodoCandidato = _raiz;
    bool lugarEncontrado = false;


    if (_raiz == nullptr) {
        _raiz = new Nodo(clave);
        return;
    }

    while (!lugarEncontrado) {
        if (nodoCandidato->valor < clave) {
            if (nodoCandidato->der == nullptr) {
                lugarEncontrado = true;
                nodoCandidato->der = new Nodo(clave);
            }
            else {
                nodoCandidato = nodoCandidato->der;
            }
        }
        else if (nodoCandidato->valor > clave) {
            if (nodoCandidato->izq == nullptr) {
                lugarEncontrado = true;
                nodoCandidato->izq = new Nodo(clave);
            }
            else {
                nodoCandidato = nodoCandidato->izq;
            }
        }
        else {
            return;
        }
    }

}



template<class T>
bool Conjunto<T>::esHijoDerecho(Conjunto::Nodo* nodoPadre, Conjunto::Nodo* nodoHijo) const {
    return nodoPadre->der == nodoHijo;
}



template <class T>
void Conjunto<T>::remover(const T& e) {
    pair<Nodo*, Nodo*>  nodoPadreEHijo = buscarNodoClaveYPadre(e);
    Nodo* nodoAEliminar = nodoPadreEHijo.second;
    Nodo* nodoPadre = nodoPadreEHijo.first;


    // Chequeo si el nodoAEliminar está en el árbol
    if (nodoAEliminar == nullptr) {
        return;
    }

    // En este caso el nodo a eliminar será una hoja.
    if (nodoAEliminar->izq == nullptr && nodoAEliminar->der == nullptr) {

        // Si el nodoAlEliminar es raíz, entonces no tendrá nodoPadre
        if (nodoAEliminar == _raiz) {
            _raiz = nullptr;
        }

        else if (esHijoDerecho(nodoPadre, nodoAEliminar)) {
            nodoPadre->der = nullptr;
        }
        else {
            nodoPadre->izq = nullptr;
        }
        delete nodoAEliminar;
    }

    // Como el nodo no es hoja, me fijo si tiene al menos un hijo
    else if (nodoAEliminar->izq == nullptr || nodoAEliminar->der == nullptr) {

        Nodo* nodoAReenlazar;

        if (nodoAEliminar->izq != nullptr) {
            nodoAReenlazar = nodoAEliminar->izq;
        }
        else {
            nodoAReenlazar = nodoAEliminar->der;
        }

        // Si el nodoAlEliminar es raíz, entonces no tendrá nodoPadre
        if (nodoAEliminar == _raiz) {
            _raiz = nodoAReenlazar;
        }

        else if (esHijoDerecho(nodoPadre, nodoAEliminar)) {
            nodoPadre->der = nodoAReenlazar;
        } else {
            nodoPadre->izq = nodoAReenlazar;
        }

        delete nodoAEliminar;
    }

    // Como no se cumplió ninguno de los casos anteriores, entonces el nodoAEliminar tendrá dos hijos.
    // Busco el predecesor inmediato (anterior) del nodoAEliminar.
    else {
        Nodo* nodoPredecesorInmediato = maximoNodo(nodoAEliminar->izq);
        T valorPredecesor = nodoPredecesorInmediato->valor;
        remover(valorPredecesor);
        nodoAEliminar->valor = valorPredecesor;
    }
}



template <class T>
typename Conjunto<T>::Nodo* Conjunto<T>::siguienteNodo(const T& clave) {
    list<Nodo*> abbLista = inorderRec(_raiz);
    auto itLista = abbLista.begin();
    Nodo* sig;

    while (itLista != abbLista.end()) {
        if ((*itLista)->valor == clave) {
            // Por la pre, asumo que el elemento no es el máximo, o sea, que no es el que está al final de la lista
            // por lo que no puede pasar que i+1 indexe una posición fuera del arreglo
            sig = *(++itLista);
        }
        else {
            itLista++;
        }
    }

    return sig;
}



template <class T>
const T& Conjunto<T>::siguiente(const T& clave) {
    return siguienteNodo(clave)->valor;
}

template <class T>
typename Conjunto<T>::Nodo* Conjunto<T>::anteriorNodo(const T& clave) {
    list<Nodo*> abbLista = inorderRec(_raiz);
    auto itLista = --abbLista.end();
    Nodo* ant;

    while (itLista != abbLista.begin()) {
        if ((*itLista)->valor == clave) {
            // Por la pre, asumo que el elemento no es el mínimo, o sea, que no es el que está al principio de la lista
            // por lo que no puede pasar que i-1 indexe una posición fuera del arreglo
            ant = *(--itLista);
        }
        else {
            itLista--;
        }
    }

    return ant;
}



template <class T>
const T& Conjunto<T>::anterior(const T& clave) {
    return anteriorNodo(clave)->valor;
}



template <class T>
const T& Conjunto<T>::minimo() const {
    return minimoNodo(_raiz)->valor;
}



template <class T>
const T& Conjunto<T>::maximo() const {
    return maximoNodo(_raiz)->valor;
}



template <class T>
unsigned int Conjunto<T>::cardinalRec(Nodo* abb) const {
    if (abb == nullptr) {
        return 0;
    }
    else {
        return 1 + cardinalRec(abb->izq) + cardinalRec(abb->der);
    }
}



template <class T>
unsigned int Conjunto<T>::cardinal() const {
    return cardinalRec(_raiz);
}



template <class T>
void Conjunto<T>::mostrar(std::ostream& o) const {
    list<Nodo*> abbLista = inorderRec(_raiz);
    o << "{";
    auto listaIt = abbLista.begin();
    while (listaIt != abbLista.end()) {
        o << (*listaIt)->valor;
        if (listaIt != --abbLista.end()) {
            o << ", ";
        }
        ++listaIt;
    }
    o << "}";
}



template<class T>
list<T> Conjunto<T>::listaNodosAT(list<Nodo*> lstNodos) const {
    list<T> listaT;
    for (const Nodo* n: &listaT) {
        listaT.push_back(n->valor);
    }
    return listaT;
}



template<class T>
list<typename Conjunto<T>::Nodo*> Conjunto<T>::inorderRec(Conjunto::Nodo *nodo) const {
    if (nodo == nullptr) {
        return {};
    }
    list<Nodo*> lIzq = inorderRec(nodo->izq);
    list<Nodo*> lDer = inorderRec(nodo->der);
    lIzq.push_back(nodo);
    lIzq.insert(lIzq.end(), lDer.begin(), lDer.end());
    return lIzq;
}



template<class T>
list<T> Conjunto<T>::preorderRec(Conjunto::Nodo *nodo) const {
    if (nodo == nullptr) {
        return {};
    }
    list<Nodo*> lIzq = inorderRec(nodo->izq);
    list<Nodo*> lDer = inorderRec(nodo->der);
    lIzq.push_front(nodo);
    lIzq.insert(lIzq.end(), lDer.begin(), lDer.end());
    return lIzq;
}



template<class T>
list<T> Conjunto<T>::postorderRec(Conjunto::Nodo *nodo) const {
    if (nodo == nullptr) {
        return {};
    }
    list<Nodo*> lIzq = inorderRec(nodo->izq);
    list<Nodo*> lDer = inorderRec(nodo->der);
    lIzq.insert(lIzq.end(), lDer.begin(), lDer.end());
    lIzq.push_back(nodo);
    return lIzq;
}



template<class T>
list<T> Conjunto<T>::inorder() const {
    return listaNodosAT(inorderRec(_raiz));
}



template<class T>
list<T> Conjunto<T>::preorder() const {
    return listaNodosAT(preorderRec(_raiz));
}



template<class T>
list<T> Conjunto<T>::postorder() const {
    return listaNodosAT(postorderRec(_raiz));
}



template<class T>
typename Conjunto<T>::Nodo* Conjunto<T>::minimoNodo(Nodo* nodo) const {
    bool nodoEsMin = nodo->izq == nullptr;
    while (!nodoEsMin) {
        nodo = nodo->izq;
        nodoEsMin = nodo->izq == nullptr;
    }
    return nodo;
}



template<class T>
typename Conjunto<T>::Nodo* Conjunto<T>::maximoNodo(Nodo* nodo) const {
    bool nodoEsMax = nodo->der == nullptr;
    while (!nodoEsMax) {
        nodo = nodo->der;
        nodoEsMax = nodo->der == nullptr;
    }
    return nodo;
}
