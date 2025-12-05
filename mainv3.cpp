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
    cout << "\n*** ERROR: El codigo ya existe en el sistema ***\n";
  }
  return r;
}

// Módulo de búsqueda binaria en el ABB
Nodo *buscarProducto(Nodo *r, int cod) {
  if (r == NULL)
    return NULL;
  if (cod == r->codigo)
    return r;
  if (cod < r->codigo) {
    return buscarProducto(r->izq, cod);
  }
  return buscarProducto(r->der, cod);
}
//modulo para mostrar porictuoc
void mostrarReporteOrdenado(Nodo *r) {
  if (r != NULL) {
    mostrarReporteOrdenado(r->izq);
    cout << "   " << r->codigo << "\t\t" << r->nombre << "\t\tS/ " << r->precio << endl;
    mostrarReporteOrdenado(r->der);
  }
}

void mostrarPreorden(Nodo *r) {
  if (r != NULL) {
    cout << "   " << r->codigo << "\t\t" << r->nombre << "\t\tS/ " << r->precio << endl;
    mostrarPreorden(r->izq);
    mostrarPreorden(r->der);
  }
}

void mostrarPostorden(Nodo *r) {
  if (r != NULL) {
    mostrarPostorden(r->izq);
    mostrarPostorden(r->der);
    cout << "   " << r->codigo << "\t\t" << r->nombre << "\t\tS/ " << r->precio << endl;
  }
}

bool validarCodigo(int num) { return num > 0; }

bool validarPrecio(double pre) { return pre >= 0; }

void limpiarEntrada() {
  cin.clear();
  cin.ignore(10000, '\n');
}

int main() {
  Nodo *raiz = NULL;
  int opcion;

  cout << "\n****************************************************\n";
  cout << "*  SISTEMA DE GESTION DE PRODUCTOS - TIENDA       *\n";
  cout << "*  Arbol Binario de Busqueda (ABB)                *\n";
  cout << "****************************************************\n";

  do {
    cout << "\n============== MENU PRINCIPAL =============\n";
    cout << "  1. Agregar producto nuevo\n";
    cout << "  2. Mostrar reporte de productos ordenados\n";
    cout << "  3. Buscar producto por codigo\n";
    cout << "  4. Recorridos del arbol (Inorden/Preorden/Postorden)\n";
    cout << "  5. Salir del programa\n";
    cout << "===========================================\n";
    cout << "  Ingrese su opcion: ";
    cin >> opcion;

    if (cin.fail()) {
      limpiarEntrada();
      cout << "\n*** ERROR: Debe ingresar un numero valido ***\n";
      continue;
    }

    switch (opcion) {
      case 1: {
        int cod;
        string nom;
        double pre;

        cout << "\n---------- AGREGAR PRODUCTO NUEVO ----------\n";
        cout << "Codigo del producto: ";
        cin >> cod;

        if (cin.fail() || !validarCodigo(cod)) {
          limpiarEntrada();
          cout << "\n*** ERROR: Codigo invalido (debe ser positivo) ***\n";
          break;
        }

        if (buscarProducto(raiz, cod) != NULL) {
          cout << "\n*** ERROR: Ya existe un producto con ese codigo ***\n";
          break;
        }

        cin.ignore();
        cout << "Nombre del producto: ";
        getline(cin, nom);

        if (nom.empty()) {
          cout << "\n*** ERROR: El nombre no puede estar vacio ***\n";
          break;
        }

        cout << "Precio del producto: ";
        cin >> pre;

        if (cin.fail() || !validarPrecio(pre)) {
          limpiarEntrada();
          cout << "\n*** ERROR: Precio invalido (debe ser >= 0) ***\n";
          break;
        }

        raiz = insertar(raiz, cod, nom, pre);
        cout << "\n>>> Producto agregado exitosamente <<<\n";
        break;
      }

      case 2: {
        if (raiz == NULL) {
          cout << "\n*** No hay productos registrados en el sistema ***\n";
        } else {
          cout << "\n========== REPORTE DE PRODUCTOS ==========\n";
          cout << "   CODIGO\t\tNOMBRE\t\t\tPRECIO\n";
          cout << "   ------\t\t------\t\t\t------\n";
          mostrarReporteOrdenado(raiz);
          cout << "==========================================\n";
        }
        break;
      }

      case 3: {
        if (raiz == NULL) {
          cout << "\n*** No hay productos registrados en el sistema ***\n";
          break;
        }

        int cod;
        cout << "\n---------- BUSCAR PRODUCTO ----------\n";
        cout << "Ingrese el codigo a buscar: ";
        cin >> cod;

        if (cin.fail()) {
          limpiarEntrada();
          cout << "\n*** ERROR: Codigo invalido ***\n";
          break;
        }

        Nodo *resultado = buscarProducto(raiz, cod);

        if (resultado != NULL) {
          cout << "\n========== PRODUCTO ENCONTRADO ==========\n";
          cout << "  Codigo: " << resultado->codigo << endl;
          cout << "  Nombre: " << resultado->nombre << endl;
          cout << "  Precio: S/ " << resultado->precio << endl;
          cout << "=========================================\n";
        } else {
          cout << "\n*** Producto no encontrado en el sistema ***\n";
        }
        break;
      }

      case 4: {
        if (raiz == NULL) {
          cout << "\n*** No hay productos registrados en el sistema ***\n";
          break;
        }

        int tipoRecorrido;
        cout << "\n---------- RECORRIDOS DEL ARBOL ----------\n";
        cout << "  1. Inorden (Izquierda - Raiz - Derecha)\n";
        cout << "  2. Preorden (Raiz - Izquierda - Derecha)\n";
        cout << "  3. Postorden (Izquierda - Derecha - Raiz)\n";
        cout << "------------------------------------------\n";
        cout << "  Seleccione tipo de recorrido: ";
        cin >> tipoRecorrido;

        if (cin.fail()) {
          limpiarEntrada();
          cout << "\n*** ERROR: Opcion invalida ***\n";
          break;
        }

        cout << "\n========== RECORRIDO DEL ARBOL ==========\n";
        cout << "   CODIGO\t\tNOMBRE\t\t\tPRECIO\n";
        cout << "   ------\t\t------\t\t\t------\n";

        switch (tipoRecorrido) {
          case 1:
            cout << "  >> INORDEN (Ordenado de menor a mayor) <<\n\n";
            mostrarReporteOrdenado(raiz);
            break;
          case 2:
            cout << "  >> PREORDEN (Raiz primero) <<\n\n";
            mostrarPreorden(raiz);
            break;
          case 3:
            cout << "  >> POSTORDEN (Raiz al final) <<\n\n";
            mostrarPostorden(raiz);
            break;
          default:
            cout << "\n*** ERROR: Opcion no valida ***\n";
            break;
        }
        cout << "=========================================\n";
        break;
      }

      case 5: {
        cout << "\n>>> Gracias por usar el sistema. Hasta pronto! <<<\n";
        break;
      }

      default: {
        cout << "\n*** ERROR: Opcion no valida. Intente de nuevo ***\n";
        break;
      }
    }

  } while (opcion != 5);

  return 0;
}
