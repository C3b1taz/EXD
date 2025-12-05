#include <iostream>
#include <string>
using namespace std;

struct Nodo {
  int codigo;
  string nombre;
  double precio;
  Nodo *izq;
  Nodo *der;

  Nodo(int c, string n, double p) {
    codigo = c;
    nombre = n;
    precio = p;
    izq = NULL;
    der = NULL;
  }
};

Nodo *insertar(Nodo *r, int cod, string nom, double pre) {
  if (r == NULL) {
    return new Nodo(cod, nom, pre);
  }
  if (cod < r->codigo) {
    r->izq = insertar(r->izq, cod, nom, pre);
  } else if (cod > r->codigo) {
    r->der = insertar(r->der, cod, nom, pre);
  } else {
    cout << "\nError: El codigo ya existe\n";
  }
  return r;
}

Nodo *buscar(Nodo *r, int cod) {
  if (r == NULL)
    return NULL;
  if (cod == r->codigo)
    return r;
  if (cod < r->codigo) {
    return buscar(r->izq, cod);
  }
  return buscar(r->der, cod);
}

void mostrarInorden(Nodo *r) {
  if (r != NULL) {
    mostrarInorden(r->izq);
    cout << "Codigo: " << r->codigo << " | Nombre: " << r->nombre
         << " | Precio: S/" << r->precio << endl;
    mostrarInorden(r->der);
  }
}

void mostrarArbol(Nodo *r, int nivel) {
  if (r != NULL) {
    mostrarArbol(r->der, nivel + 1);
    for (int i = 0; i < nivel; i++) {
      cout << "    ";
    }
    cout << r->codigo << endl;
    mostrarArbol(r->izq, nivel + 1);
  }
}

bool validarNumero(int num) { return num > 0; }

bool validarPrecio(double pre) { return pre >= 0; }

void limpiarBuffer() {
  cin.clear();
  cin.ignore(10000, '\n');
}

int main() {
  Nodo *raiz = NULL;
  int op;

  do {
    cout << "\n========================================\n";
    cout << "   SISTEMA DE GESTION DE PRODUCTOS\n";
    cout << "========================================\n";
    cout << "1. Agregar producto\n";
    cout << "2. Mostrar productos (ordenados)\n";
    cout << "3. Buscar producto por codigo\n";
    cout << "4. Visualizar estructura del arbol\n";
    cout << "5. Salir\n";
    cout << "========================================\n";
    cout << "Seleccione una opcion: ";
    cin >> op;

    if (cin.fail()) {
      limpiarBuffer();
      cout << "\nError: Ingrese un numero valido\n";
      continue;
    }

    if (op == 1) {
      int cod;
      string nom;
      double pre;

      cout << "\n--- AGREGAR NUEVO PRODUCTO ---\n";
      cout << "Ingrese codigo: ";
      cin >> cod;

      if (cin.fail() || !validarNumero(cod)) {
        limpiarBuffer();
        cout << "\nError: Codigo invalido (debe ser mayor a 0)\n";
        continue;
      }

      if (buscar(raiz, cod) != NULL) {
        cout << "\nError: El codigo ya existe en el sistema\n";
        continue;
      }

      cin.ignore();
      cout << "Ingrese nombre: ";
      getline(cin, nom);

      if (nom.empty()) {
        cout << "\nError: El nombre no puede estar vacio\n";
        continue;
      }

      cout << "Ingrese precio: ";
      cin >> pre;

      if (cin.fail() || !validarPrecio(pre)) {
        limpiarBuffer();
        cout << "\nError: Precio invalido (debe ser mayor o igual a 0)\n";
        continue;
      }

      raiz = insertar(raiz, cod, nom, pre);
      cout << "\nProducto agregado exitosamente\n";
    } else if (op == 2) {
      if (raiz == NULL) {
        cout << "\nNo hay productos registrados\n";
      } else {
        cout << "\n========================================\n";
        cout << "   LISTA DE PRODUCTOS (ORDENADOS)\n";
        cout << "========================================\n";
        mostrarInorden(raiz);
        cout << "========================================\n";
      }
    } else if (op == 3) {
      if (raiz == NULL) {
        cout << "\nNo hay productos registrados\n";
        continue;
      }

      int cod;
      cout << "\n--- BUSCAR PRODUCTO ---\n";
      cout << "Ingrese codigo a buscar: ";
      cin >> cod;

      if (cin.fail()) {
        limpiarBuffer();
        cout << "\nError: Codigo invalido\n";
        continue;
      }

      Nodo *res = buscar(raiz, cod);

      if (res != NULL) {
        cout << "\n========================================\n";
        cout << "         PRODUCTO ENCONTRADO\n";
        cout << "========================================\n";
        cout << "Codigo: " << res->codigo << endl;
        cout << "Nombre: " << res->nombre << endl;
        cout << "Precio: S/" << res->precio << endl;
        cout << "========================================\n";
      } else {
        cout << "\nProducto no encontrado\n";
      }
    } else if (op == 4) {
      if (raiz == NULL) {
        cout << "\nNo hay productos registrados\n";
      } else {
        cout << "\n========================================\n";
        cout << "     ESTRUCTURA DEL ARBOL (ABB)\n";
        cout << "========================================\n";
        mostrarArbol(raiz, 0);
        cout << "========================================\n";
      }
    } else if (op == 5) {
      cout << "\nSaliendo del sistema...\n";
    } else {
      cout << "\nOpcion invalida. Intente nuevamente\n";
    }

  } while (op != 5);

  return 0;
}
