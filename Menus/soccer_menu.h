#ifndef SOCCER_MENU_H
#define SOCCER_MENU_H

#include "../Techniques/DynamicHash/extendibleHash.h"
#define NOMBRE_ARCHIVO_SOCCER "Soccer.csv"
#include <stdio.h>
#include <time.h>

bool esEntero_r(string linea)
{
    bool esEntero = true;
    int longitud = linea.size();

    if (longitud == 1)
    {
        esEntero = false;
    }
    else if (longitud == 2 && !isdigit(linea[0]))
    {
        esEntero = false;
    }
    else
    {
        int indice = 1;
        if (linea[1] == '+' || linea[0] == '-')
        {
            indice = 2;
        }
        else
        {
            indice = 1;
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
void post_insertar_aleatorio_hash(ExtendibleHash<int> &eh);

void insertar_hash(ExtendibleHash<int> &eh)
{

    ifstream archivo(NOMBRE_ARCHIVO_SOCCER);
    string linea;
    clock_t t;
    char delimitador = ',';
    // Leemos la primea linea para descartarla, pues es el encabezado
    getline(archivo, linea);
    vector<RecordHash<int>> records;
    // Leemos todos las linea
    while (getline(archivo, linea))
    {
        stringstream stream(linea); //Convertir la cadena a un stream
        string Ranking, C_name, Country, points, change;
        //Extraer todos los valores
        getline(stream, Ranking, delimitador);
        getline(stream, C_name, delimitador);
        getline(stream, Country, delimitador);
        getline(stream, points, delimitador);
        getline(stream, change, delimitador);
        RecordHash<int> temp(stoi(Ranking), C_name, Country, points, stof(change));
        records.push_back(temp);
    }

    t = clock();
    int accesos = eh.insertAll(records);
    t = clock() - t;
    double time_taken = ((double)t) / CLOCKS_PER_SEC; // calculate the elapsed time
    cout << endl;
    printf("El programa toma %f segundos en insertar los %zu registros", time_taken, records.size());
    printf("\nEl programa toma %d accesos a memoria secundaria", accesos);
    dump();
    post_insertar_aleatorio_hash(eh);
}

void post_insertar_aleatorio_hash(ExtendibleHash<int> &eh)
{
    string input;
    int opcion;
    bool repite = true;
    do
    {
        cout << "\e[2;1H\e[2J";
        cout << "Se insertaron los datos existosamente" << endl;
        cout << endl;
        cout << "¿Deseas verlos?" << endl;
        cout << "-> Elige un numero" << endl;
        cout << endl;
        cout << endl;
        cout << "2. Si -> Mostrar datos" << endl;
        cout << endl;
        cout << "3. No -> Regresar al menu de inicio" << endl;
        cout << endl;
        cout << "4. Salir" << endl;
        cout << endl;

        getline(cin, input);
        if (esEntero_r(input))
        {
            repite = false;
        }
    } while (repite);

    opcion = atoi(input.c_str());

    switch (opcion)
    {
    case 2:
        eh.showRecords();
        break;
    case 3:
        return;
        break;
    case 4:
        exit(-1);
        break;
    default:
        post_insertar_aleatorio_hash(eh);
        break;
    }
    dump();
}

void insertar_registro_hash(ExtendibleHash<int> &eh)
{
    cout << "\n\n----------Insertar----------\n\n";
    string C_name, Country, points;
    float change;
    int codigo;
    clock_t t;
    cout << "Ingrese el codigo: ";
    cin >> codigo;
    cout << "Ingrese el nombre del club (36 carac. max): ";
    cin >> C_name;
    cout << "Ingrese el pais(6 carac. max): ";
    cin >> Country;
    cout << "Ingrese los puntos (16 carac. max): ";
    cin >> points;
    cout << "Ingrese como cambio de un anio para otro: ";
    cin >> change;

    RecordHash<int> rec(codigo, toLower(C_name), toLower(Country), toLower(points), change);
    int accesos = 1;
    t = clock();
    eh.insert(rec, accesos);
    t = clock() - t;
    double time_taken = ((double)t) / CLOCKS_PER_SEC; // calculate the elapsed time
    cout << endl;
    printf("El programa tomÃ³ %f segundos en insertar el registro", time_taken);
    printf("\nEl programa tomÃ³ %d accesos a memoria secundaria", accesos);
    dump();
}

void buscar_registro_hash(ExtendibleHash<int> &eh)
{
    cout << "\n\n----------Busqueda----------\n\n";
    cout << "Ingrese codigo a buscar: ";
    int key;
    clock_t t;
    cin >> key;
    int accesos = 1;
    t = clock();
    auto result = eh.search(key, accesos);
    if (result)
    {
        (*result).showRecord(2);
        t = clock() - t;
        double time_taken = ((double)t) / CLOCKS_PER_SEC; // calculate the elapsed time
        cout << endl;
        printf("El programa tomÃ³ %f segundos en buscar el registro", time_taken);
        printf("\nEl programa tomÃ³ %d accesos a memoria secundaria", accesos);
    }
    else
    {
        cout << "No se encontro " << key << "\n";
    }
    dump();
}

void buscar_rango_registro_hash(ExtendibleHash<int> &eh)
{
    cout << "\n\n----------Busqueda por rango----------\n\n";
    int key1, key2;
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
    auto result = eh.searchRange(key1, key2);
    cout << "Resultado: " << result.size() << "\n";
    int cont = 1;
    for (auto r : result)
    {
        r.showRecord(cont++);
    }
    t = clock() - t;
    double time_taken = ((double)t) / CLOCKS_PER_SEC; // calculate the elapsed time
    cout << endl;
    printf("El programa tomÃ³ %f segundos en buscar el rango de registros", time_taken);
    dump();
}

void eliminar_registro_hash(ExtendibleHash<int> &eh)
{
    cout << "\n\n----------Eliminar----------\n\n";
    cout << "Ingrese codigo a eliminar: ";
    int key;
    cin >> key;
    if (eh.erase(key))
    {
        cout << "Registro eliminado\n";
    }
    else
    {
        cout << "No se elimino\n";
    }

    dump();
}

#endif