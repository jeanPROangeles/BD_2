#ifndef LIB_H
#define LIB_H

#include <iostream>
#include <fstream>
#include <cstdio>
#include <map>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <cstring>
#include <algorithm>
#include <stdio.h>
#include <functional>
#include <bitset>
#include <iomanip>

#include <sys/stat.h>

#define fopen(n) \
    fstream f;   \
    f.open(n, ios::in | ios::out | ios::binary);
#define faopen(n) \
    fstream fa;   \
    fa.open(n, ios::in | ios::out | ios::binary);
#define fnopen(n)                                 \
    fstream fn;                                   \
    fn.open(n, ios::in | ios::out | ios::binary); \
    if (fn.is_open())
#define isfopen if (f.is_open())
#define isfaopen if (fa.is_open())
//#define isfnopen if(fn.is_open())

//secuential:
#define SEQ_MAX_SIZE_OF_AUX_FILE 50
#define SEQ_MAX_ERASED_RECORDS 100

//hash:
#define HASH_BUCKET_SIZE 3 //fb
#define HASH_HEIGHT 3      //D

using namespace std;

inline bool exists(const std::string &filename)
{
    struct stat buffer;
    return (stat(filename.c_str(), &buffer) == 0);
}

bool isFileEmpty(string fileName)
{
    fopen(fileName);
    isfopen
    {
        f.seekg(0, ios::beg);
        auto start = f.tellg();
        f.seekg(0, ios::end);
        auto end = f.tellg();
        return end == start;
        f.close();
    }
    cout << "No se abrió " << fileName << " en isFIleEmpty\n";
    return false;
}

template <typename Record>
long sizeFile(string name)
{
    fopen(name);
    isfopen
    {
        f.seekg(0, ios::beg);
        auto start = f.tellg();
        f.seekg(0, ios::end);
        auto end = f.tellg();
        f.close();
        return (long)(end - start) / sizeof(Record);
    }
    else
    {
        cout << "No se pudo obtener tamanio del archivo " << name << "\n";
        return 0;
    }
}

void cleanFile(string fileName)
{
    std::ofstream ofs;
    ofs.open(fileName, std::ofstream::out | std::ofstream::trunc);
    ofs.close();
}

void init()
{
    cleanFile("data.dat");
    cleanFile("daux.dat");
    cleanFile("dataHash.dat");
    cleanFile("index.dat");
}

template <typename T>
void write(fstream &f, T &t) { f.write((char *)&t, sizeof(t)); }

template <typename T>
void read(fstream &f, T &t) { f.read((char *)&t, sizeof(t)); }

template <typename T>
bool comp(T &a, T &b) { return a < b; }

string local_trim(string cad, long height)
{
    string new_cad = "";
    for (int i = cad.size() - height; i < cad.size(); i++)
        new_cad += cad[i];
    return new_cad;
}
std::string toLower(std::string s)
{
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c)
                   { return std::tolower(c); });
    s[0] = s[0] - 32;
    return s;
}
void dump()
{
    string dump;
    cout << "\n\nPresione cualquier tecla y enter...";
    cin >> dump;
}

#endif //LIB.H