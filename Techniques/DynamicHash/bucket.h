#ifndef BUCKET_H
#define BUCKET_H

#include "recordHash.h"

template <typename TKey>
class Bucket
{
    RecordHash<TKey> records[HASH_BUCKET_SIZE];
    long local_height = 1;
    long size = 0;
    long next = -1;

public:
    void setNext(long next) { this->next = next; }
    long getNext() { return next; }
    long getSize() { return size; }
    void setLocalHeight(long local_height) { this->local_height = local_height; }
    long getLocalHeight() { return local_height; }
    bool isEmpty() { return size == 0; }
    bool isFull() { return size == HASH_BUCKET_SIZE; }
    bool hasMaxLocalHeight() { return local_height == HASH_HEIGHT; }
    bool existsRecord(TKey key)
    {
        for (int i = 0; i < size; i++)
            if (records[i].getKey() == key)
                return true;
        return false;
    }
    RecordHash<TKey> *searchRecord(TKey key)
    {
        for (int i = 0; i < size; i++)
        {
            if (records[i].getKey() == key)
            {
                RecordHash<TKey> *record = new RecordHash<TKey>;
                (*record) = records[i];
                return record;
            }
        }
        return nullptr;
    }
    void insertRecord(RecordHash<TKey> record)
    {
        records[size++] = record;
    }
    void deleteRecord(TKey key)
    {
        int pos = 0;
        for (int i = 0; i < size; i++)
        {
            pos = i;
            if (records[i].getKey() == key)
                break;
        }
        for (int i = pos; i < size - 1; i++)
        {
            records[i] = records[i + 1];
        }
        size--;
    }
    Bucket<TKey> divide()
    {
        hash<TKey> _hash;
        Bucket<TKey> other;
        string cad;
        vector<TKey> to_delete;

        this->local_height++;
        other.setLocalHeight(this->local_height);

        for (int i = 0; i < size; i++)
        {
            cad = bitset<HASH_BUCKET_SIZE>(records[i].getKey()).to_string();
            cad = local_trim(cad, this->local_height);
            if (cad[0] == '1')
            {
                //Se va al otro bucket
                other.insertRecord(records[i]);
                to_delete.push_back(records[i].getKey());
            }
        }
        for (auto key : to_delete)
        {
            deleteRecord(key);
        }

        return other;
    }
    void showAll()
    {
        cout << "LocalH: " << local_height << "\tsize: " << size << "\tnext: " << next << "\n";
        for (int i = 0; i < size; i++)
        {
            records[i].showData();
        }
    }
    void showNotAll()
    {
        cout << "LocalH: " << local_height << "\tsize: " << size << "\tnext: " << next << "\n";
    }
    void searchRange(TKey key1, TKey key2, vector<RecordHash<TKey>> &vec)
    {
        for (int i = 0; i < size; i++)
        {
            if (key1 <= records[i].getKey() && records[i].getKey() <= key2)
            {
                vec.push_back(records[i]);
            }
        }
    }
    RecordHash<TKey> get_first_record()
    {
        RecordHash<TKey> dump;
        if (size == 0)
        {
            cout << "Error al traer el primer key\n";
            return dump;
        }
        return records[0];
        ;
    }
    void showRecords(int &cont)
    {
        for (int i = 0; i < size; i++)
        {
            records[i].showRecord(cont++);
        }
    }
};

#endif //BUCKET.H