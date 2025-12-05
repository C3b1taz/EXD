#include <iostream>
#include <string>
using namespace std;

struct Nodo {
  int codigo;
  string descripcion;
  double valor;
  Nodo *izq;
  Nodo *der;

  Nodo(int c, string d, double v) {
    codigo = c;
    descripcion = d;
    valor = v;
    izq = NULL;
    der = NULL;
  }
};

Nodo *insertar(Nodo *r, int cod, string desc, double val) {
  if (r == NULL) {
    return new Nodo(cod, desc, val);
  }
  if (cod < r->codigo) {
    r->izq = insertar(r->izq, cod, desc, val);
  } else if (cod > r->codigo) {
    r->der = insertar(r->der, cod, desc, val);
  } else {
    cout << "\n*** ERROR: El codigo ya existe en el sistema ***\n";
  }
  return r;
}

// Módulo de búsqueda binaria en el ABB
Nodo *buscarElemento(Nodo *r, int cod) {
  if (r == NULL)
    return NULL;
  if (cod == r->codigo)
    return r;
  if (cod < r->codigo) {
    return buscarElemento(r->izq, cod);
  }
  return buscarElemento(r->der, cod);
}

void mostrarReporteOrdenado(Nodo *r) {
  if (r != NULL) {
    mostrarReporteOrdenado(r->izq);
    cout << "   " << r->codigo << "\t\t" << r->descripcion << "\t\t" << r->valor << endl;
    mostrarReporteOrdenado(r->der);
  }
}

void mostrarPreorden(Nodo *r) {
  if (r != NULL) {
    cout << "   " << r->codigo << "\t\t" << r->descripcion << "\t\t" << r->valor << endl;
    mostrarPreorden(r->izq);
    mostrarPreorden(r->der);
  }
}

void mostrarPostorden(Nodo *r) {
  if (r != NULL) {
    mostrarPostorden(r->izq);
    mostrarPostorden(r->der);
    cout << "   " << r->codigo << "\t\t" << r->descripcion << "\t\t" << r->valor << endl;
  }
}

bool validarCodigo(int num) { return num > 0; }

bool validarValor(double val) { return val >= 0; }

void limpiarEntrada() {
  cin.clear();
  cin.ignore(10000, '\n');
}

int main() {
  Nodo *raiz = NULL;
  int opcion;

  cout << "\n****************************************************\n";
  cout << "*  SISTEMA DE GESTION DE DATOS - ABB             *\n";
  cout << "*  Arbol Binario de Busqueda                     *\n";
  cout << "****************************************************\n";

  do {
    cout << "\n============== MENU PRINCIPAL =============\n";
    cout << "  1. Agregar elemento nuevo\n";
    cout << "  2. Mostrar reporte de elementos ordenados\n";
    cout << "  3. Buscar elemento por codigo\n";
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
        string desc;
        double val;

        cout << "\n---------- AGREGAR ELEMENTO NUEVO ----------\n";
        cout << "Codigo del elemento: ";
        cin >> cod;

        if (cin.fail() || !validarCodigo(cod)) {
          limpiarEntrada();
          cout << "\n*** ERROR: Codigo invalido (debe ser positivo) ***\n";
          break;
        }

        if (buscarElemento(raiz, cod) != NULL) {
          cout << "\n*** ERROR: Ya existe un elemento con ese codigo ***\n";
          break;
        }

        cin.ignore();
        cout << "Descripcion del elemento: ";
        getline(cin, desc);

        if (desc.empty()) {
          cout << "\n*** ERROR: La descripcion no puede estar vacia ***\n";
          break;
        }

        cout << "Valor del elemento: ";
        cin >> val;

        if (cin.fail() || !validarValor(val)) {
          limpiarEntrada();
          cout << "\n*** ERROR: Valor invalido (debe ser >= 0) ***\n";
          break;
        }

        raiz = insertar(raiz, cod, desc, val);
        cout << "\n>>> Elemento agregado exitosamente <<<\n";
        break;
      }

      case 2: {
        if (raiz == NULL) {
          cout << "\n*** No hay elementos registrados en el sistema ***\n";
        } else {
          cout << "\n========== REPORTE DE ELEMENTOS ==========\n";
          cout << "   CODIGO\t\tDESCRIPCION\t\tVALOR\n";
          cout << "   ------\t\t-----------\t\t-----\n";
          mostrarReporteOrdenado(raiz);
          cout << "==========================================\n";
        }
        break;
      }

      case 3: {
        if (raiz == NULL) {
          cout << "\n*** No hay elementos registrados en el sistema ***\n";
          break;
        }

        int cod;
        cout << "\n---------- BUSCAR ELEMENTO ----------\n";
        cout << "Ingrese el codigo a buscar: ";
        cin >> cod;

        if (cin.fail()) {
          limpiarEntrada();
          cout << "\n*** ERROR: Codigo invalido ***\n";
          break;
        }

        Nodo *resultado = buscarElemento(raiz, cod);

        if (resultado != NULL) {
          cout << "\n========== ELEMENTO ENCONTRADO ==========\n";
          cout << "  Codigo: " << resultado->codigo << endl;
          cout << "  Descripcion: " << resultado->descripcion << endl;
          cout << "  Valor: " << resultado->valor << endl;
          cout << "=========================================\n";
        } else {
          cout << "\n*** Elemento no encontrado en el sistema ***\n";
        }
        break;
      }

      case 4: {
        if (raiz == NULL) {
          cout << "\n*** No hay elementos registrados en el sistema ***\n";
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
        cout << "   CODIGO\t\tDESCRIPCION\t\tVALOR\n";
        cout << "   ------\t\t-----------\t\t-----\n";

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
