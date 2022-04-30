#ifndef RECORD_H
#define RECORD_H

#include "../lib.h"

using namespace std;

template <typename TKey>
class Record
{
    TKey key; //nombre[25]
    char type[8];
    int total;
    int generation;
    bool legendary;

    long next = -1;
    char file = 'd';

public:
    Record()
    {
        string name = "No name";
        string type = "No type";
        strcpy(this->key, name.c_str());
        strcpy(this->type, type.c_str());
        this->total = 0;
        this->generation = 0;
        this->legendary = 0;
        this->next = -1;
        char file = 'd';
    }
    Record(string name, string type, int total, int generation, bool legendary)
    {
        strcpy(this->key, name.c_str());
        strcpy(this->type, type.c_str());
        this->total = total;
        this->generation = generation;
        this->legendary = legendary;
        this->next = -1;
        char file = 'd';
    }
    void setData(string name, string type, int total, int generation, bool legendary)
    {
        strcpy(this->key, name.c_str());
        strcpy(this->type, type.c_str());
        this->total = total;
        this->generation = generation;
        this->legendary = legendary;
        this->next = -1;
        char file = 'd';
    }

    void showData()
    {
        cout << "Key: " << key << "\n";
        cout << "Tipo: " << type << "\n";
        cout << "Total: " << total << "\n";
        cout << "Generacion: " << generation << "\n";
        cout << "Legendario: " << legendary << "\n";
        cout << "Next : " << next << "\n";
        cout << "NextFile : " << file << "\n\n";
    }
    void setNext(long _next, char _file)
    {
        next = _next;
        file = _file;
    }
    long getNext()
    {
        return next;
    }
    char getFile()
    {
        return file;
    }
    string getKey()
    {
        return string(key);
    }
    Record &operator=(const Record &a)
    {
        for (int i = 0; i < 25; i++)
            this->key[i] = a.key[i];

        for (int i = 0; i < 8; i++)
            this->type[i] = a.type[i];
        this->total = a.total;
        this->generation = a.generation;
        this->legendary = a.legendary;
        this->next = a.next;
        this->file = a.file;
        return *this;
    }
    bool operator<(const Record &a) { return string(this->key) < string(a.key); }
    bool operator>(const Record &a) { return string(this->key) > string(a.key); }
    bool operator<=(const Record &a) { return string(this->key) <= string(a.key); }
    bool operator>=(const Record &a) { return string(this->key) >= string(a.key); }
    bool operator==(const Record &a) { return string(this->key) == string(a.key); }
    bool operator!=(const Record &a) { return string(this->key) != string(a.key); }

    void showRecord(int cont)
    {
        if (cont == 1)
        {
            cout << setw(5) << "N°" << setw(30) << "Key" << setw(13) << "Type" << setw(10) << "Total" << setw(10) << "Generation" << setw(10) << "Legendary?"
                 << "\n";
        }
        cout << setw(5) << cont << setw(30) << key << setw(13) << type << setw(10) << total << setw(10) << generation << setw(10) << legendary << "\n";
    }
};

#endif //RECORD.H