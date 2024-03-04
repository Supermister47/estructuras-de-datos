#include "Lista.h"

Lista::Lista() {
    _prim = nullptr;
    _ult = nullptr;
}



Lista::Lista(const Lista& l) : Lista() {
    copiarNodos(l);
}



Lista::~Lista() {
    destruirNodos();
    delete _prim;
    delete _ult;
}



void Lista::destruirNodos() {
    int tam = this->longitud();
    Nodo* nodoActual = _prim;

    for (int i=0; i < tam; i++) {
        Nodo* nodoSig = nodoActual->sig;
        delete nodoActual;
        nodoActual = nodoSig;
    }
    _prim = nullptr;
    _ult = nullptr;
}



void Lista::copiarNodos(const Lista& l) {
    int tam = l.longitud();
    for (int i=0; i < tam; i++) {
        this->agregarAtras(l.iesimo(i));
    }
}



Lista& Lista::operator=(const Lista& aCopiar) {
    destruirNodos();
    copiarNodos(aCopiar);
    return *this;
}



void Lista::agregarUnElemento(const Nat& elem) {
    _prim = new Nodo(nullptr, elem, nullptr);
    _ult = _prim;
}



void Lista::agregarAdelante(const Nat& elem) {
    if (this->longitud() == 0) {
        agregarUnElemento(elem);
    }
    else {
        Nodo* exPrimerElem = _prim;
        _prim = new Nodo(nullptr, elem, exPrimerElem);
        exPrimerElem->ant = _prim;
    }
}



void Lista::agregarAtras(const Nat& elem) {
    if (this->longitud() == 0) {
        agregarUnElemento(elem);
    }
    else {
        Nodo* exUltimoElem = _ult;
        _ult = new Nodo(exUltimoElem, elem, nullptr);
        exUltimoElem->sig = _ult;
    }
}



void Lista::eliminar(Nat i) {
    Nodo* nodoAEliminar = iesimoNodo(i);
    if (this->longitud() == 1) {
        _prim = nullptr;
        _ult = nullptr;
    }
    else {
        if (nodoAEliminar == _prim) {
            (nodoAEliminar->sig)->ant = nullptr;
            _prim = nodoAEliminar->sig;
        }
        else if (nodoAEliminar == _ult) {
            (nodoAEliminar->ant)->sig = nullptr;
            _ult = nodoAEliminar->ant;

        }
        else {
            // Accedo al nodo siguiente y cambio su puntero ant al nodo anterior del nodo que quiero eliminar
            (nodoAEliminar->sig)->ant = nodoAEliminar->ant;
            // Accedo al nodo anterior y cambio su puntero sig al nodo siguiente del nodo que quiero eliminar
            (nodoAEliminar->ant)->sig = nodoAEliminar->sig;
        }
    }


    // Borro el nodo del heap, no puedo hacerlo en el destructor porque no voy a tener nada que apunte a ese nodo
    delete nodoAEliminar;
}



int Lista::longitud() const {
    int tam = 0;
    Nodo* sigNodo = _prim;
    while (sigNodo != nullptr) {
        tam++;
        sigNodo = sigNodo->sig;
    }
    return tam;
}



Lista::Nodo* Lista::iesimoNodo(Nat i) const {
    Nat contador = 0;
    Nodo* nodoAct = _prim;
    while (contador < i) {
        contador++;
        nodoAct = nodoAct->sig;
    }
    return nodoAct;
}



const Nat& Lista::iesimo(Nat i) const {
    const Nodo* const iNodo = iesimoNodo(i);
    return iNodo->valor;
}



Nat& Lista::iesimo(Nat i) {
    return iesimoNodo(i)->valor;
}



Nat& Lista::operator[](Nat i) {
    return iesimo(i);
}



void Lista::mostrar(ostream& o) {
    int tam = this->longitud();

    o << "<";
    for (int i=0; i < tam; i++) {

        o << this->iesimo(i);
        if (this->iesimoNodo(i) != _ult)
            o << ", ";
    }
    o << ">";
}