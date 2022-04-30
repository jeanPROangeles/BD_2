#ifndef EXTENDIBLE_HASH_H
#define EXTENDIBLE_HASH_H

#include "bucket.h"

template <typename TKey>
class ExtendibleHash
{
private:
    string fileName;
    string indexName;
    unordered_map<string, long> index;
    unordered_map<string, long> index_size;
    hash<TKey> _hash;
    long freeListBucket = -1;
    string hash_function(TKey key)
    {
        auto hash_code = _hash(key);
        string hash_code_string = bitset<HASH_HEIGHT>(hash_code).to_string();
        return hash_code_string;
    }
    void initIndex();
    void readIndex();
    void writeIndex();
    void insertInFreeList(fstream &f, int &accesos);
    void divideBucket(fstream &f, Bucket<TKey> &bucket, long pos, int &accesos);
    bool exists(TKey key, int &accesos);
    bool is_brother(string ref, string bro, long d);

public:
    ExtendibleHash(string _fileName, string _indexName)
    {
        this->fileName = _fileName + ".dat";
        this->indexName = _indexName + ".dat";
        if (isFileEmpty(indexName))
        {
            cout << "File initialization\n";
            initIndex();
        }
        readIndex();
        fopen(fileName);
        isfopen
        {
            f.seekg(0, ios::beg);
            read(f, freeListBucket);
            f.close();
        }
        else cout << "Hash error al abrir data en constructor para leer freelist\n";
    }

    ~ExtendibleHash()
    {
        writeIndex();
        fopen(fileName);
        isfopen
        {
            f.seekp(0, ios::beg);
            write(f, freeListBucket);
            f.close();
        }
        else cout << "Hash error al abrir data en constructor para guardar freelist\n";
    }
    void showAll()
    {
        cout << "FreeList: " << freeListBucket << "\n";
        fopen(fileName);
        isfopen
        {
            if (freeListBucket != -1)
            {
                long pos_free_list = freeListBucket;
                Bucket<TKey> bucket_free_list;
                int i_free_list = 1;
                while (pos_free_list != -1)
                {
                    f.seekg(pos_free_list, ios::beg);
                    read(f, bucket_free_list);
                    cout << "\nPos: " << pos_free_list;
                    cout << "\t\tBucket " << i_free_list++ << ":\n";
                    bucket_free_list.showNotAll();
                    pos_free_list = bucket_free_list.getNext();
                }
            }
            cout << "\nIndex:\n";
            for (long i = 0; i < (1 << HASH_HEIGHT); i++)
            {
                string cad = bitset<HASH_HEIGHT>(i).to_string();
                cout << i << " - " << cad << "\t" << index[cad] << "\t" << index_size[cad] << "\n";
                cout << "Bucket: ";
                Bucket<TKey> bucket;
                f.seekg(index[cad], ios::beg);
                read(f, bucket);
                bucket.showNotAll();
            }
            cout << "\nData:\n";
            for (long i = 0; i < (1 << HASH_HEIGHT); i++)
            {
                string cad = bitset<HASH_HEIGHT>(i).to_string();
                if (index_size[cad] > 0)
                {
                    cout << i << " - " << cad << " tiene " << index_size[cad] << " registros\n";
                    Bucket<TKey> bucket;
                    long pos = index[cad];
                    int cont = 1;
                    while (pos != -1)
                    {
                        f.seekg(pos, ios::beg);
                        read(f, bucket);
                        cout << "Bucket " << cont++ << ":\n";
                        bucket.showAll();
                        pos = bucket.getNext();
                    }
                    cout << "\n";
                }
            }

            f.close();
        }
        else cout << "Hash error al abrir data en showAll\n";
    }

    void showBuckets()
    {
        cout << "FreeList: " << freeListBucket << "\n";
        fopen(fileName);
        isfopen
        {
            if (freeListBucket != -1)
            {
                long pos_free_list = freeListBucket;
                Bucket<TKey> bucket_free_list;
                int i_free_list = 1;
                while (pos_free_list != -1)
                {
                    f.seekg(pos_free_list, ios::beg);
                    read(f, bucket_free_list);
                    cout << "\nPos: " << pos_free_list;
                    cout << "\t\tBucket " << i_free_list++ << ":\n";
                    bucket_free_list.showNotAll();
                    pos_free_list = bucket_free_list.getNext();
                }
            }
            cout << "\nIndex:\n";
            for (long i = 0; i < (1 << HASH_HEIGHT); i++)
            {
                string cad = bitset<HASH_HEIGHT>(i).to_string();
                cout << i << " - " << cad << "\t" << index[cad] << "\t" << index_size[cad] << "\n";
                cout << "Bucket: ";
                Bucket<TKey> bucket;
                f.seekg(index[cad], ios::beg);
                read(f, bucket);
                bucket.showNotAll();
            }
            f.close();
        }
        else cout << "Hash error al abrir data en showAll\n";
    }
    int insertAll(vector<RecordHash<TKey>> vrecord)
    {
        int accesos = 0;
        for (auto vr : vrecord)
        {
            insert(vr, accesos);
        }
        return accesos;
    }
    void insert(RecordHash<TKey> record, int &accesos)
    {
        if (exists(record.getKey(), accesos))
        {
            cout << "Ya existe el registro " << record.getKey() << "\n";
            return;
        }
        string cad = hash_function(record.getKey());
        fopen(fileName);
        isfopen
        {
            Bucket<TKey> bucket;
            long pos = index[cad];
            f.seekg(pos, ios::beg);
            read(f, bucket);
            accesos++;

            if (bucket.isFull())
            {
                //required division or linked
                if (bucket.hasMaxLocalHeight())
                {
                    //Verificar si hay espacio en linked buckets
                    long prev_pos = pos; //En prev_pos está el bucket
                    while (1)
                    {
                        prev_pos = pos;
                        pos = bucket.getNext();
                        if (pos == -1)
                            break;
                        f.seekg(pos, ios::beg);
                        read(f, bucket);
                        accesos++;
                    }
                    if (bucket.isFull())
                    {
                        //insert new linked bucket
                        Bucket<TKey> new_bucket;
                        new_bucket.insertRecord(record);

                        insertInFreeList(f, accesos); //Posiciona al lugar donde se debe insertar un nuevo bucket

                        long new_pos = f.tellp();
                        bucket.setNext(new_pos);
                        write(f, new_bucket);
                        accesos++;
                        f.seekp(prev_pos, ios::beg);
                        write(f, bucket);
                        accesos++;
                    }
                    else
                    {
                        //insertar
                        bucket.insertRecord(record);
                        f.seekp(prev_pos, ios::beg);
                        write(f, bucket);
                        accesos++;
                    }
                }
                else
                {
                    //requiere division del bucket y sumar 1 a su local_height, puede hacerse hasta generar linkedlist
                    bool requiredLindekPage = false;
                    while (1)
                    {
                        divideBucket(f, bucket, pos, accesos);
                        pos = index[cad];
                        f.seekg(pos, ios::beg);
                        read(f, bucket);
                        accesos++;
                        if (bucket.isFull() && bucket.hasMaxLocalHeight())
                        {
                            requiredLindekPage = true;
                            break;
                        }
                        if (!bucket.isFull())
                            break;
                        //Si está lleno y no tiene el máx height, volver a hacer la división
                    }
                    //Si no requere linked, insertar en la posición dada
                    if (requiredLindekPage)
                    {
                        Bucket<TKey> new_bucket;
                        new_bucket.insertRecord(record);

                        insertInFreeList(f, accesos); //Posiciona al lugar donde se debe insertar un nuevo bucket

                        long new_pos = f.tellp();
                        bucket.setNext(new_pos);
                        write(f, new_bucket);
                        accesos++;
                        f.seekp(pos, ios::beg);
                        write(f, bucket);
                        accesos++;
                    }
                    else
                    {
                        //Inserta en bucket
                        bucket.insertRecord(record);
                        f.seekp(pos, ios::beg);
                        write(f, bucket);
                        accesos++;
                    }
                }
            }
            else
            {
                //Inserta en bucket
                bucket.insertRecord(record);
                f.seekp(pos, ios::beg);
                write(f, bucket);
                accesos++;
            }
            index_size[cad]++;
            f.close();
        }
        else cout << "Hash error al abrir data en insert\n";
    }

    RecordHash<TKey> *search(TKey key, int &accesos)
    {
        string cad = hash_function(key);
        if (index_size[cad] == 0)
            return nullptr;

        fopen(fileName);
        isfopen
        {
            Bucket<TKey> bucket;
            long pos = index[cad];
            while (pos != -1)
            {
                f.seekg(pos, ios::beg);
                read(f, bucket);
                accesos++;
                RecordHash<TKey> *rec = bucket.searchRecord(key);
                if (rec)
                {
                    f.close();
                    return rec;
                }
                pos = bucket.getNext();
            }
            return nullptr;
            f.close();
        }
        else cout << "Hash error al abrir data en search\n";
        return nullptr;
    }
    vector<RecordHash<TKey>> searchRange(TKey key1, TKey key2)
    {
        vector<RecordHash<TKey>> result;
        unordered_set<long> visited;
        fopen(fileName);
        isfopen
        {
            for (long i = 0; i < (1 << HASH_HEIGHT); i++)
            {
                string cad = bitset<HASH_HEIGHT>(i).to_string();
                long pos = index[cad];
                if (visited.count(pos))
                    continue;
                visited.insert(pos);

                while (pos != -1)
                {
                    Bucket<TKey> bucket;
                    f.seekg(pos, ios::beg);
                    read(f, bucket);
                    bucket.searchRange(key1, key2, result);
                    pos = bucket.getNext();
                }
            }
        }
        else cout << "Hash error al abrir data en search range\n";
        return result;
    }
    bool erase(TKey key)
    {
        int x = 0;
        if (!exists(key, x))
            return false;

        string cad = hash_function(key);
        fopen(fileName);
        isfopen
        {
            Bucket<TKey> bucket;
            long pos = index[cad];
            bool isBucketLink = false;
            while (pos != -1)
            {
                f.seekg(pos, ios::beg);
                read(f, bucket);
                if (bucket.existsRecord(key))
                {
                    //Encontré el registro y su bucket
                    bucket.deleteRecord(key);
                    f.seekp(pos, ios::beg);
                    write(f, bucket);
                    index_size[cad]--;

                    //    es bucket link         es bucket principal que tiene linked buckets
                    if (isBucketLink == true || bucket.getNext() != -1)
                    {
                        if (bucket.getNext() == -1)
                        {
                            //Es el último, entonces no necesita reacomodarse
                            //Si se vacea, entonces eliminar bucket
                            if (bucket.isEmpty())
                            {
                                //Buscar bucket previo y setear next a 0
                                long prev_pos = index[cad];
                                Bucket<TKey> prev_bucket;
                                f.seekg(prev_pos, ios::beg);
                                read(f, prev_bucket);
                                while (prev_bucket.getNext() != pos)
                                {
                                    prev_pos = prev_bucket.getNext();
                                    f.seekg(prev_pos, ios::beg);
                                    read(f, prev_bucket);
                                }
                                //Eliminar bucket
                                bucket.setNext(freeListBucket);
                                freeListBucket = pos;
                                bucket.setLocalHeight(1);
                                f.seekp(pos, ios::beg);
                                write(f, bucket);
                                //Setear el next de prev-bucket a -1
                                prev_bucket.setNext(-1);
                                f.seekp(prev_pos, ios::beg);
                                write(f, prev_bucket);
                            }
                            f.close();
                            return true;
                        }
                        //Traer el primer elemento del último bucket link
                        int last_pos = bucket.getNext();
                        int prev_last_pos = pos;
                        Bucket<TKey> last_bucket;
                        f.seekg(last_pos, ios::beg);
                        read(f, last_bucket);

                        while (last_bucket.getNext() != -1)
                        {
                            prev_last_pos = last_pos;
                            last_pos = last_bucket.getNext();
                            f.seekg(last_pos, ios::beg);
                            read(f, last_bucket);
                        }
                        //last_bucket es el último bucket, y last_pos la última posición
                        RecordHash<TKey> first_record_of_last_bucket = last_bucket.get_first_record();
                        bucket.insertRecord(first_record_of_last_bucket);

                        last_bucket.deleteRecord(first_record_of_last_bucket.getKey());
                        if (last_bucket.isEmpty())
                        {
                            //Eliminar last_bucket (añadir al freelist), y actualizar el next del bucket de prev_last_pos a -1
                            last_bucket.setNext(freeListBucket);
                            freeListBucket = last_pos;
                            //
                            last_bucket.setLocalHeight(1);

                            //Si prev_last_pos es pos, entonces actualizo el mismo bucket
                            if (prev_last_pos == pos)
                            {
                                bucket.setNext(-1);
                            }
                            else
                            { //Sino, trae el prev_last_bucket y actualiza next a -1
                                Bucket<TKey> prev_last_bucket;
                                f.seekg(prev_last_pos, ios::beg);
                                read(f, prev_last_bucket);
                                prev_last_bucket.setNext(-1);
                                f.seekp(prev_last_pos, ios::beg);
                                write(f, prev_last_bucket);
                            }
                        }

                        f.seekp(pos, ios::beg);
                        write(f, bucket);

                        f.seekp(last_pos, ios::beg);
                        write(f, last_bucket);
                    }
                    else
                    {
                        //El bucket es de los principales
                        //Si el bucket hermano tiene linked buckets, no podemos fusionarlos
                        //Si el bucket tiene un d > 1 y la cantidad de registros hermanos == Maximo registros
                        //Eliminar un bucket, juntar registros
                        if (bucket.getLocalHeight() > 1)
                        {
                            //Buscar bucket hermano
                            long brother_pos = -1;
                            long records_of_brothers = 0;
                            for (auto p : index)
                            {
                                if (is_brother(cad, p.first, bucket.getLocalHeight()))
                                {
                                    if (brother_pos == -1 && p.second != pos)
                                        brother_pos = p.second;
                                    records_of_brothers += index_size[p.first];
                                }
                            }
                            Bucket<TKey> brother_bucket;
                            f.seekg(brother_pos, ios::beg);
                            read(f, brother_bucket);
                            if (records_of_brothers <= HASH_BUCKET_SIZE / 2 && brother_bucket.getNext() == -1)
                            {
                                //Fusionar buckets
                                while (!brother_bucket.isEmpty())
                                {
                                    RecordHash<TKey> first_record_of_brother_bucket = brother_bucket.get_first_record();
                                    brother_bucket.deleteRecord(first_record_of_brother_bucket.getKey());
                                    bucket.insertRecord(first_record_of_brother_bucket);
                                }
                                //Borrar brother_bucket y actualizar el freelist
                                brother_bucket.setNext(freeListBucket);
                                freeListBucket = brother_pos;
                                brother_bucket.setLocalHeight(1);
                                f.seekp(brother_pos, ios::beg);
                                write(f, brother_bucket);
                                //Actualiza a todos los brothers con pos
                                for (auto &p : index)
                                {
                                    if (is_brother(cad, p.first, bucket.getLocalHeight()))
                                    {
                                        p.second = pos;
                                    }
                                }
                                //Resta el local_height -1 y guarda el bucket en su posición
                                bucket.setLocalHeight(bucket.getLocalHeight() - 1);
                                f.seekp(pos, ios::beg);
                                write(f, bucket);
                            }
                        }
                    }

                    f.close();
                    return true;
                }
                pos = bucket.getNext();
                isBucketLink = true;
            }
            f.close();
            return false;
        }
        else cout << "Hash error al abrir data en exists\n";

        return false;
    }

    void showRecords()
    {
        int cont = 1;
        cout << setw(5) << "N°" << setw(5) << "Review" << setw(40) << "Brand" << setw(10) << "Style" << setw(20) << "Country" << setw(7) << "Stars"
             << "\n";
        set<long> visited;
        fopen(fileName);
        isfopen
        {
            for (long i = 0; i < (1 << HASH_HEIGHT); i++)
            {
                string cad = bitset<HASH_HEIGHT>(i).to_string();
                if (index_size[cad] > 0 && !visited.count(index[cad]))
                {
                    Bucket<TKey> bucket;
                    long pos = index[cad];
                    while (pos != -1)
                    {
                        f.seekg(pos, ios::beg);
                        read(f, bucket);
                        bucket.showRecords(cont);
                        pos = bucket.getNext();
                    }
                    visited.insert(index[cad]);
                }
            }

            cout << setw(5) << "N°" << setw(5) << "Review" << setw(40) << "Brand" << setw(10) << "Style" << setw(20) << "Country" << setw(7) << "Stars"
                 << "\n";
            f.close();
        }
        else cout << "Hash error al abrir data en showRecords\n";
    }
};

template <typename TKey>
void ExtendibleHash<TKey>::initIndex()
{
    cleanFile(fileName);
    fopen(indexName);
    isfopen
    {
        faopen(fileName);
        isfaopen
        {
            freeListBucket = -1;
            write(fa, freeListBucket);
            Bucket<TKey> bucket0, bucket1;
            long pos0 = fa.tellp();
            write(fa, bucket0);
            long pos1 = fa.tellp();
            write(fa, bucket1);
            string cad;
            long size = 0;
            for (long i = 0; i < (1 << HASH_HEIGHT); i++)
            {
                cad = bitset<HASH_HEIGHT>(i).to_string();
                f.write(cad.c_str(), HASH_HEIGHT);
                if (cad[HASH_HEIGHT - 1] == '0')
                    write(f, pos0);
                else
                    write(f, pos1);
                write(f, size); //size = 0
            }
            f.close();
            fa.close();
        }
        else cout << "Hash error al abrir data en initIndex\n";
    }
    else cout << "Hash error al abrir index en initIndex\n";
}
template <typename TKey>
void ExtendibleHash<TKey>::readIndex()
{
    fopen(indexName);
    isfopen
    {
        string cad;
        long pos;
        long size;
        for (auto i = 0; i < (1 << HASH_HEIGHT); i++)
        {
            char *buffer = new char[HASH_HEIGHT + 1];
            //read cad
            f.read(buffer, HASH_HEIGHT);
            buffer[HASH_HEIGHT] = '\0';
            cad = buffer;
            delete[] buffer;
            if (cad == "")
                return;
            //read page
            f.read((char *)&pos, sizeof(pos));
            //read page
            f.read((char *)&size, sizeof(size));
            index[cad] = pos;
            index_size[cad] = size;
        }
        f.close();
    }
    else cout << "Hash error al abrir index en readIndex\n";
}

template <typename TKey>
void ExtendibleHash<TKey>::writeIndex()
{
    fopen(indexName);
    isfopen
    {
        for (long i = 0; i < (1 << HASH_HEIGHT); i++)
        {
            string cad = bitset<HASH_HEIGHT>(i).to_string();
            f.write(cad.c_str(), HASH_HEIGHT);
            f.write((char *)&index[cad], sizeof(index[cad]));
            f.write((char *)&index_size[cad], sizeof(index_size[cad]));
        }
        f.close();
    }
    else cout << "Hash error al abrir index en writeIndex\n";
}

template <typename TKey>
void ExtendibleHash<TKey>::insertInFreeList(fstream &f, int &accesos)
{
    if (freeListBucket == -1)
    {
        //Inserta al final
        f.seekp(0, ios::end);
    }
    else
    {
        //Inserta en la posición disponible y actualiza freelist
        Bucket<TKey> deleted_bucket;
        f.seekg(freeListBucket, ios::beg);
        read(f, deleted_bucket);
        accesos++;
        f.seekp(freeListBucket, ios::beg);
        freeListBucket = deleted_bucket.getNext();
    }
}

template <typename TKey>
void ExtendibleHash<TKey>::divideBucket(fstream &f, Bucket<TKey> &bucket, long pos, int &accesos)
{
    //Dividir bucket: new tiene a los que empiezan con 1, y bucket se queda con los que empiezan con 0
    Bucket<TKey> new_bucket = bucket.divide();

    //Actualiza buckets
    f.seekp(pos);
    write(f, bucket);
    accesos++;

    insertInFreeList(f, accesos); //Posiciona al lugar donde se debe insertar un nuevo bucket

    long new_pos = f.tellp();
    f.seekp(new_pos);
    write(f, new_bucket);
    accesos++;

    //Actualiza index
    long local_height = bucket.getLocalHeight();
    for (auto &p : index)
        if (p.first[HASH_HEIGHT - local_height] == '1' && p.second == pos)
            p.second = new_pos;
}

template <typename TKey>
bool ExtendibleHash<TKey>::exists(TKey key, int &accesos)
{
    string cad = hash_function(key);
    if (index_size[cad] == 0)
        return false;

    fopen(fileName);
    isfopen
    {
        Bucket<TKey> bucket;
        long pos = index[cad];
        while (pos != -1)
        {
            f.seekg(pos, ios::beg);
            read(f, bucket);
            accesos++;
            if (bucket.existsRecord(key))
            {
                f.close();
                return true;
            }
            pos = bucket.getNext();
        }
        f.close();
        return false;
    }
    else cout << "Hash error al abrir data en exists\n";
    return false;
}

template <typename TKey>
bool ExtendibleHash<TKey>::is_brother(string cad1, string cad2, long d)
{
    //Los últimos d-1 caracteres deben ser iguales
    for (int i = HASH_HEIGHT - 1; i >= HASH_HEIGHT - d + 1; i--)
        if (cad1[i] != cad2[i])
            return false;
    return true;
}

#endif //EXTENDIBLE_HASH.H