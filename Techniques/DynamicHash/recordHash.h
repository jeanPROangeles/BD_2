#ifndef RECORD_HASH_H
#define RECORD_HASH_H

#include "../lib.h"

template <typename TKey>
class RecordHash
{
    TKey key;
    char C_name[35];
    char country[5];
    char points[15];
    float change;

public:
    RecordHash()
    {
        this->key = 0;
        string C_name = "C_name";
        strcpy(this->C_name, C_name.c_str());
        string Country = "country";
        strcpy(this->country, Country.c_str());
        string points = "points";
        strcpy(this->points, points.c_str());
        this->change = 0.0;
    }

    RecordHash(TKey key, string C_name, string country, string points, float change)
    {
        this->key = key;
        strcpy(this->C_name, C_name.c_str());
        strcpy(this->country, country.c_str());
        strcpy(this->points, points.c_str());
        this->change = change;
    }

    void setData(TKey key, string C_name, string country, string points, float change)
    {
        this->key = key;
        strcpy(this->C_name, C_name.c_str());
        strcpy(this->country, country.c_str());
        strcpy(this->points, points.c_str());
        this->change = change;
    }
    void setData(TKey key)
    {
        this->key = key;
        string C_name = "C_name", country = "country", points = "points";
        strcpy(this->C_name, C_name.c_str());
        strcpy(this->country, country.c_str());
        strcpy(this->points, points.c_str());
        this->change = 0.0;
    }

    void showData()
    {
        cout << "\tKey: " << key << "\n";
    }
    TKey getKey()
    {
        return key;
    }

    RecordHash &operator=(const RecordHash &a)
    {
        TKey key;
        char C_name[35];
        char country[15];
        char points[15];
        float change;

        this->key = a.key;
        for (int i = 0; i < 35; i++)
            this->C_name[i] = a.C_name[i];
        for (int i = 0; i < 5; i++)
            this->country[i] = a.country[i];
        for (int i = 0; i < 15; i++)
            this->points[i] = a.points[i];
        this->change = a.change;
        return *this;
    }
    bool operator<(const RecordHash &a) { return this->key < a.key; }
    bool operator>(const RecordHash &a) { return this->key > a.key; }
    bool operator<=(const RecordHash &a) { return this->key <= a.key; }
    bool operator>=(const RecordHash &a) { return this->key >= a.key; }
    bool operator==(const RecordHash &a) { return this->key == a.key; }
    bool operator!=(const RecordHash &a) { return this->key != a.key; }

    void showRecord(int cont)
    {

        cout << setw(5) << cont << setw(5) << key << setw(40) << C_name << setw(10) << country << setw(20) << points << setw(7) << change << "\n";
    }
};

#endif //RECORD_HASH.H