#ifndef POKEMON_MENU_H
#define POKEMON_MENU_H

#include "../Techniques/Sequential/sequential.h"
#include <stdio.h>
#include <time.h>
#define NOMBRE_ARCHIVO_POKEMON "Pokemon.csv"

using namespace std;

void post_insertar_aleatorio(Sequential<Record<char[25]>, string> &seq);

bool esEntero_p(string linea)
{
    bool esEntero = true;
    int longitud = linea.size();

    if (longitud == 0)
    {
        esEntero = false;
    }
    else if (longitud == 1 && !isdigit(linea[0]))
    {
        esEntero = false;
    }
    else
    {
        int indice = 0;
        if (linea[0] == '+' || linea[0] == '-')
        {
            indice = 1;
       }
        else
        {
            indice = 0;
        }

        while (indice < longitud)
        {
            if (!isdigit(linea[indice]))
            {
                esEntero = false;
                break;
            }
            indice++;
        }
    }

    return esEntero;
}

void insertar_secuencial(Sequential<Record<char[25]>, string> &seq)
{

    ifstream archivo(NOMBRE_ARCHIVO_POKEMON);
    string linea;
    char delimitador = ',';
    // Leemos la primea linea para descartarla, pues es el encabezado
    getline(archivo, linea);
    vector<Record<char[25]>> records;

    // Leemos todos las linea
    clock_t t;

    while (getline(archivo, linea))
    {
        int total = 0;
        int generation = 0;
        bool legendary = 0;

        stringstream stream(linea); //Convertir la cadena a un stream
        string Name, Type, Total, Generation, Legendary;
        //Extraer todos los valores
        getline(stream, Name, delimitador);
        getline(stream, Type, delimitador);
        getline(stream, Total, delimitador);
        getline(stream, Generation, delimitador);
        getline(stream, Legendary, delimitador);

        stringstream _total(Total);
        stringstream _generation(Generation);

        _total >> total;
        _generation >> generation;
        istringstream(Legendary) >> legendary;

        Record<char[25]> temp(Name, Type, total, generation, legendary);

        //guardar en vector
        records.push_back(temp);
    }
    t = clock();
    int accesos = seq.insertAll(records);
    t = clock() - t;
    double time_taken = ((double)t) / CLOCKS_PER_SEC; // calculate the elapsed time
    cout << endl;
    printf("El programa tomó %f segundos en insertar los %zu registros", time_taken, records.size());
    printf("\nEl programa tomó %d accesos a memoria secundaria", accesos);
    dump();
    post_insertar_aleatorio(seq);
}

void post_insertar_aleatorio(Sequential<Record<char[25]>, string> &seq)
{

    string input;
    int opcion;
    bool repite = true;
    do
    {
        cout << "\e[1;1H\e[2J";
        cout << "Se insertaron los datos existosamente" << endl;
        cout << endl;
        cout << "¿Deseas verlos?" << endl;
        cout << "-> Elige un número" << endl;
        cout << endl;
        cout << endl;
        cout << "1. Si -> Mostrar datos" << endl;
        cout << endl;
        cout << "2. No -> Regresar al menu de inicio" << endl;
        cout << endl;
        cout << "3. Salir" << endl;
        cout << endl;

        getline(cin, input);
        if (esEntero_p(input))
        {
            repite = false;
        }
    } while (repite);

    opcion = atoi(input.c_str());

    switch (opcion)
    {
    case 1:
        seq.showRecords();
        break;
    case 2:
        return;
        break;
    case 3:
        exit(-1);
        break;
    default:
        post_insertar_aleatorio(seq);
        break;
    }
    dump();
}
void insertar_registro_secuencial(Sequential<Record<char[25]>, string> &seq)
{
    cout << "\n\n----------Insertar----------\n\n";
    string nombre;
    string tipo;
    clock_t t;
    int total, generacion;
    bool legendario;

    cout << "Ingrese el Nombre (25 carac. max): ";
    cin >> nombre;
    cout << "Ingrese el tipo (8 carac. max): ";
    cin >> tipo;
    cout << "Ingrese el total: ";
    cin >> total;
    cout << "Ingrese la generacion: ";
    cin >> generacion;
    cout << "Ingrese si es legendario (0 = No o 1 = Si): ";
    cin >> legendario;
    t = clock();
    Record<char[25]> rec(toLower(nombre), toLower(tipo), total, generacion, legendario);
    int accesos = 0;
    seq.insert(rec, accesos);

    t = clock() - t;
    double time_taken = ((double)t) / CLOCKS_PER_SEC; // calculate the elapsed time
    cout << endl;
    printf("El programa tomó %f segundos en insertar el registro", time_taken);
    printf("\nEl programa tomó %d accesos a memoria secundaria", accesos);

    dump();
}

void buscar_registro_secuencial(Sequential<Record<char[25]>, string> &seq)
{
    cout << "\n\n----------Busqueda----------\n\n";
    cout << "Ingrese nombre a buscar: ";
    string key;
    clock_t t;

    cin >> key;
    int accesos = 0;
    t = clock();
    auto result = seq.search(toLower(key), accesos);
    if (result)
    {
        (*result).showRecord(1);
        t = clock() - t;
        double time_taken = ((double)t) / CLOCKS_PER_SEC; // calculate the  elapsed time
        cout << endl;
        printf("El programa tomó %f segundos en buscar el registro", time_taken);
        printf("\nEl programa tomó %d accesos a memoria secundaria", accesos);
    }
    else
    {
        cout << "No se encontro " << key << "\n";
    }
    dump();
}
void buscar_rango_registro_secuencial(Sequential<Record<char[25]>, string> &seq)
{
    cout << "\n\n----------Busqueda por rango----------\n\n";
    string key1, key2;
    clock_t t;
    cout << "Inserte registro inicial: ";
    cin >> key1;
    cout << "Inserte registro final: ";
    cin >> key2;
    if (key1 > key2)
    {
        auto t = key1;
        key1 = key2;
        key2 = t;
    }

    t = clock();
    auto result = seq.search(toLower(key1), toLower(key2));
    cout << "Resultados: " << result.size() << "\n";
    int cont = 1;
    for (auto r : result)
    {
        r.showRecord(cont++);
    }
    t = clock() - t;
    double time_taken = ((double)t) / CLOCKS_PER_SEC; // calculate the  elapsed time
    cout << endl;
    printf("El programa tomó %f segundos en buscar el rango de registros", time_taken);
    dump();
}

void eliminar_registro_secuencial(Sequential<Record<char[25]>, string> &seq)
{
    cout << "\n\n----------Eliminar----------\n\n";
    cout << "Ingrese codigo a eliminar: ";
    string key;
    cin >> key;
    if (seq.erase(toLower(key)))
    {
        cout << "Registro eliminado\n";
    }
    else
    {
        cout << "No se elimino\n";
    }
    dump();
}

void showData(Sequential<Record<char[25]>, string> &seq)
{
    seq.showRecords();
    dump();
}

#endif