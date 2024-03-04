#include "gtest-1.8.1/gtest.h"
#include "../src/Lista.h"

/**
 * Para correr valgrind:
 * - Seleccionar arriba a la derecha la opción "correrValgrind"
 * - Hacer build del proyecto (Ctrl+F9)
 */

TEST(lista_test, test_constructor_vacio) {
    Lista l;
    ASSERT_EQ(l.longitud(), 0);
}

TEST(lista_test, test_agregar_un_elemento_adelante) {
    Lista l;
    l.agregarAdelante(42);
    ASSERT_EQ(l.longitud(), 1);
    ASSERT_EQ(l.iesimo(0), 42);
}

TEST(lista_test, test_agregar_un_elemento_atras) {
    Lista l;
    l.agregarAtras(42);
    ASSERT_EQ(l.longitud(), 1);
    ASSERT_EQ(l.iesimo(0), 42);
}

TEST(lista_test, test_agregar_varios_elementos_solo_adelante) {
    Lista l;
    l.agregarAdelante(42);
    l.agregarAdelante(41);
    l.agregarAdelante(40);
    l.agregarAdelante(39);
    ASSERT_EQ(l.longitud(), 4);
    ASSERT_EQ(l.iesimo(0), 39);
    ASSERT_EQ(l.iesimo(1), 40);
    ASSERT_EQ(l.iesimo(2), 41);
    ASSERT_EQ(l.iesimo(3), 42);
}

TEST(lista_test, test_agregar_varios_elementos_solo_atras) {
    Lista l;
    l.agregarAtras(42);
    l.agregarAtras(43);
    l.agregarAtras(44);
    l.agregarAtras(45);
    ASSERT_EQ(l.longitud(), 4);
    ASSERT_EQ(l.iesimo(0), 42);
    ASSERT_EQ(l.iesimo(1), 43);
    ASSERT_EQ(l.iesimo(2), 44);
    ASSERT_EQ(l.iesimo(3), 45);
}

TEST(lista_test, test_agregar_varios_elementos_adelante_y_atras) {
    Lista l;
    l.agregarAdelante(42);
    l.agregarAdelante(41);
    l.agregarAtras(43);
    l.agregarAdelante(40);
    l.agregarAtras(44);
    ASSERT_EQ(l.longitud(), 5);
    ASSERT_EQ(l.iesimo(0), 40);
    ASSERT_EQ(l.iesimo(1), 41);
    ASSERT_EQ(l.iesimo(2), 42);
    ASSERT_EQ(l.iesimo(3), 43);
    ASSERT_EQ(l.iesimo(4), 44);
}

TEST(lista_test, mostrar_vacio) {
    Lista l = Lista();

    cout << l << endl;
}

TEST(lista_test, mostrar_un_elemento) {
    Lista l = Lista();
    l.agregarAtras(4);

    cout << l << endl;
}

TEST(lista_test, mostrar_dos_elementos) {
    Lista l = Lista();
    l.agregarAtras(4);
    l.agregarAtras(7);

    cout << l << endl;
}

TEST(lista_test, mostrar_varios_elementos) {
    Lista l = Lista();
    l.agregarAtras(4);
    l.agregarAtras(7);
    l.agregarAtras(47);
    l.agregarAdelante(42);

    cout << l << endl;
}

TEST(lista_test, test_eliminar_elementos) {
    Lista l;
    l.agregarAtras(42);
    l.agregarAtras(43);
    l.agregarAtras(44);
    l.agregarAtras(45);

    l.eliminar(1);

    ASSERT_EQ(l.longitud(), 3);
    ASSERT_EQ(l.iesimo(0), 42);
    ASSERT_EQ(l.iesimo(1), 44);
    ASSERT_EQ(l.iesimo(2), 45);

    l.eliminar(2);

    ASSERT_EQ(l.longitud(), 2);
    ASSERT_EQ(l.iesimo(0), 42);
    ASSERT_EQ(l.iesimo(1), 44);

    l.eliminar(0);
    l.eliminar(0);

    ASSERT_EQ(l.longitud(), 0);
}

TEST(lista_test, test_constructor_por_copia) {
    Lista l;
    l.agregarAtras(42);
    l.agregarAtras(43);
    l.agregarAtras(44);
    l.agregarAtras(45);

    Lista otra(l);
    ASSERT_EQ(otra.longitud(), 4);
    ASSERT_EQ(otra.iesimo(0), 42);
    ASSERT_EQ(otra.iesimo(1), 43);
    ASSERT_EQ(otra.iesimo(2), 44);
    ASSERT_EQ(otra.iesimo(3), 45);

    // test aliasing interno
    l.iesimo(0) = 99;
    ASSERT_EQ(otra.iesimo(0), 42);
}

TEST(lista_test, test_operador_asignacion) {
    Lista l;
    l.agregarAtras(42);
    l.agregarAtras(43);
    l.agregarAtras(44);
    l.agregarAtras(45);

    Lista otra = l;
    ASSERT_EQ(otra.longitud(), 4);
    ASSERT_EQ(otra.iesimo(0), 42);
    ASSERT_EQ(otra.iesimo(1), 43);
    ASSERT_EQ(otra.iesimo(2), 44);
    ASSERT_EQ(otra.iesimo(3), 45);

    // test aliasing interno
    l.iesimo(0) = 99;
    ASSERT_EQ(otra.iesimo(0), 42);

    // test pisar memoria preexistente
    l.eliminar(0);
    otra = l;
    ASSERT_EQ(otra.longitud(), 3);

    otra = Lista();
    ASSERT_EQ(otra.longitud(), 0);
}

TEST(lista_test, test_subscript) {
    Lista l;
    l.agregarAtras(42);
    l.agregarAtras(43);
    l.agregarAtras(44);
    l.agregarAtras(45);

    ASSERT_EQ(l[0], l.iesimo(0));
    ASSERT_EQ(l[1], l.iesimo(1));
    ASSERT_EQ(l[2], l.iesimo(2));
    ASSERT_EQ(l[3], l.iesimo(3));

}
