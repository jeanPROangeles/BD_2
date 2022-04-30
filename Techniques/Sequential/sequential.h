#ifndef SEQ_H
#define SEQ_H

#include "record.h"

template <typename TRecord, typename TKey>
class Sequential
{
private:
    string fileName;
    string auxName;
    long sizeData = 0;
    long sizeAux = 0;

    const long sizeRecord = sizeof(TRecord);

    void refactor(int &accesos)
    {
        string newName = "temp.dat";
        fopen(fileName);
        isfopen
        {
            faopen(auxName);
            isfaopen
            {
                cleanFile(newName);
                fnopen(newName)
                {
                    TRecord record;
                    f.seekg(0, ios::beg);
                    read(f, record);
                    accesos++;

                    long next = 0;
                    char file = 'd';
                    long fn_pos = 0;

                    sizeAux = 0;
                    sizeData = 0;
                    do
                    {
                        f.seekg(next, ios::beg);
                        read(f, record);
                        accesos++;
                        next = record.getNext();
                        file = record.getFile();

                        record.setNext(fn_pos + sizeRecord, 'd');
                        fn.seekp(fn_pos, ios::beg);
                        write(fn, record);
                        accesos++;
                        sizeData++;
                        fn_pos += sizeRecord;

                        if (file == 'a')
                        {
                            //Entrar a aux, guardar datos en un vector, ordenar y guardar en temp.data
                            vector<TRecord> records_in_aux;
                            do
                            {
                                fa.seekg(next, ios::beg);
                                read(fa, record);
                                accesos++;
                                records_in_aux.push_back(record);
                                next = record.getNext();
                                file = record.getFile();
                            } while (file == 'a' && next != -1);
                            sort(records_in_aux.begin(), records_in_aux.end(), comp<TRecord>);
                            for (TRecord rec : records_in_aux)
                            {
                                rec.setNext(fn_pos + sizeRecord, 'd');
                                fn.seekp(fn_pos, ios::beg);
                                write(fn, rec);
                                accesos++;
                                sizeData++;
                                fn_pos += sizeRecord;
                            }
                        }
                    } while (next != -1);

                    //Cambiar el next del último a -1
                    fn.seekg(sizeRecord * (sizeData - 1), ios::beg);
                    read(fn, record);
                    accesos++;
                    record.setNext(-1, 'd');
                    fn.seekp(sizeRecord * (sizeData - 1), ios::beg);
                    write(fn, record);
                    accesos++;
                    fn.close();
                }
                else cout << "SequentialError al abrir newFile en refact\n";
                fa.close();
            }
            else cout << "SequentialError al abrir aux en refact\n";
            f.close();
        }
        else cout << "SequentialError al abrir data en refact\n";

        cleanFile(auxName);

        char fileNameArray[fileName.size() + 1];
        strcpy(fileNameArray, fileName.c_str());

        char newNameArray[newName.size() + 1];
        strcpy(newNameArray, newName.c_str());

        if (remove(fileNameArray) != 0)
            perror("Error deleting file");
        if (rename(newNameArray, fileNameArray) != 0)
            perror("Error renaming file");
    }

    long binarySearch(string key, int &accesos)
    {
        long res = 0;
        fopen(fileName);
        isfopen
        {
            TRecord tmp;
            //Menor
            f.seekg(0, ios::beg);
            read(f, tmp);
            accesos++;
            if (key <= tmp.getKey())
            {
                f.close();
                return 0;
            }
            //Mayor
            f.seekg((sizeData - 1) * sizeRecord, ios::beg);
            read(f, tmp);
            accesos++;
            if (key >= tmp.getKey())
            {
                f.close();
                return (sizeData - 1) * sizeRecord;
            }

            int lo = 0, hi = sizeData - 1, mi;
            while (1)
            {
                mi = (lo + hi) / 2;
                if (mi == lo)
                    break;
                f.seekg(mi * sizeRecord, ios::beg);
                read(f, tmp);
                accesos++;
                if (key == tmp.getKey())
                    break;
                else if (key < tmp.getKey())
                    hi = mi;
                else
                    lo = mi;
            }
            //mi * sizeRecord
            //Retroceder hasta encontrar un data válido
            f.seekg(mi * sizeRecord, ios::beg);
            read(f, tmp);
            while (tmp.getNext() == -2)
            {
                mi--;
                f.seekg(mi * sizeRecord, ios::beg);
                read(f, tmp);
            }
            f.close();
            return mi * sizeRecord;
        }
        else cout << "SequentialError al abrir data en binarySearch\n";
        return res;
    }

    long linealSearch(string key)
    {
        return 0;
    }

    long insideSearch(string key, int &accesos)
    {
        return binarySearch(key, accesos);
        //return linealSearch(key);
    }

public:
    Sequential(string _fileName, string _auxName)
    {
        this->fileName = _fileName + ".dat";
        this->auxName = _auxName + ".dat";
        sizeData = sizeFile<TRecord>(fileName);
        sizeAux = sizeFile<TRecord>(auxName);
    }

    ~Sequential()
    {
        //refactor();
    }

    int insertAll(vector<TRecord> records)
    {
        int accesos = 0;
        sort(records.begin(), records.end(), comp<TRecord>);
        for (TRecord record : records)
        {
            insert(record, accesos);
        }
        return accesos;
    }

    void showAll()
    {
        fopen(fileName);
        isfopen
        {
            faopen(auxName);
            isfaopen
            {
                TRecord tmp;
                f.seekg(0, ios::beg);
                read(f, tmp);
                long next = tmp.getNext();
                char file = tmp.getFile();
                cout << "\n"
                     << "data:";
                tmp.showData();

                while (next != -1)
                {
                    if (file == 'd')
                    {
                        f.seekg(next, ios::beg);
                        read(f, tmp);
                        cout << "data:";
                    }
                    else if (file == 'a')
                    {
                        fa.seekg(next, ios::beg);
                        read(fa, tmp);
                        cout << "aux:";
                    }
                    else
                    {
                        cout << "Algó falló\n";
                        f.close();
                        fa.close();
                        return;
                    }
                    tmp.showData();
                    next = tmp.getNext();
                    file = tmp.getFile();
                }
                fa.close();
                cout << "\n\n----- File Size -----\n\n";
                cout << "SizeData: " << sizeData << "\n";
                cout << "SizeAux: " << sizeAux << "\n";
            }
            else cout << "SequentialError al abrir aux en showAll\n";
            f.close();
        }
        else cout << "SequentialError al abrir data en showAll\n";
    }

    void insert(TRecord &record, int &accesos)
    {
        record.setNext(-1, 'd');
        if (sizeData == 0)
        {
            fopen(fileName);
            isfopen
            {
                f.seekp(0, ios::beg);
                write(f, record);
                accesos++;
                sizeData++;
                f.close();
                return;
            }
            else cout << "SequentialError al abrir archivo data en add, sizeData = 0\n";
        }
        //Hay datos, ubicar la posicion
        long pos = insideSearch(record.getKey(), accesos);
        fopen(fileName);
        isfopen
        {
            TRecord tmp;
            f.seekg(pos);
            read(f, tmp);
            accesos++;

            if (pos == 0 && record.getKey() < tmp.getKey())
            {
                //Debe estar antes del primero, entonces:
                //Si solo había un dato, agrego en dat
                if (tmp.getNext() == -1)
                {
                    long finalPos = sizeRecord;
                    f.seekp(finalPos, ios::end);
                    record.setNext(finalPos, 'd');
                    write(f, tmp);
                    accesos++;
                    f.seekp(pos, ios::beg);
                    write(f, record);
                    accesos++;
                    sizeData++;
                }
                else
                { //Sino, lo mando a aux
                    faopen(auxName);
                    isfaopen
                    {
                        fa.seekp(0, ios::end);
                        auto finalPosition = fa.tellp();
                        record.setNext(finalPosition, 'a');
                        write(fa, tmp);
                        accesos++;

                        f.seekp(pos, ios::beg);
                        write(f, record);
                        accesos++;

                        sizeAux++;
                        fa.close();
                        if (sizeAux == SEQ_MAX_SIZE_OF_AUX_FILE)
                        {
                            f.close();
                            refactor(accesos);
                        }
                    }
                    else cout << "SequentialError al abrir archivo aux en add record < pos0\n";
                }
            }
            else
            {
                if (tmp.getNext() == -1)
                {
                    //Es el último, actualiza tmp y escribe el record
                    f.seekp(0, ios::end);
                    auto finalPosition = f.tellp();
                    write(f, record);
                    accesos++;

                    tmp.setNext(finalPosition, 'd');
                    f.seekp(pos);
                    write(f, tmp);
                    accesos++;

                    sizeData++;
                }
                else
                {
                    //Si hay espacio disponible (registro eliminado antes) insertarlo ahí
                    TRecord tmpNext;
                    f.seekg(pos + sizeData);
                    read(f, tmpNext);
                    accesos++;
                    if (tmpNext.getNext() == -2)
                    {
                        record.setNext(tmp.getNext(), tmp.getFile());
                        tmp.setNext(pos + sizeData, 'd');
                        f.seekp(pos);
                        write(f, tmp);
                        accesos++;
                        f.seekp(pos + sizeData);
                        write(f, record);
                        accesos++;
                        sizeData++;
                    }
                    else
                    {
                        //Sino, escribir en región auxiliar
                        faopen(auxName);
                        isfaopen
                        {
                            fa.seekp(0, ios::end);
                            auto finalPosition = fa.tellp();
                            record.setNext(tmp.getNext(), tmp.getFile());
                            tmp.setNext(finalPosition, 'a');
                            write(fa, record);
                            accesos++;
                            f.seekp(pos, ios::beg);
                            write(f, tmp);
                            accesos++;
                            sizeAux++;
                            fa.close();
                            if (sizeAux == SEQ_MAX_SIZE_OF_AUX_FILE)
                            {
                                f.close();
                                refactor(accesos);
                            }
                        }
                        else cout << "SequentialError al abrir archivo aux en add\n";
                    }
                }
            }
            f.close();
        }
        else cout << "SequentialError al abrir archivo data en add\n";
    }

    TRecord *search(TKey key, int &accesos)
    {
        TRecord *tmp = new TRecord;
        long pos = insideSearch(key, accesos);
        fopen(fileName);
        isfopen
        {
            f.seekg(pos, ios::beg);
            read(f, *tmp);
            accesos++;
            if (tmp->getKey() == key)
            {
                f.close();
                if (tmp->getNext() == -2)
                {
                    cout << "Registro eliminado\n";
                    return nullptr;
                }
                else
                    return tmp;
            }
            if (tmp->getNext() == -1)
            {
                cout << "No existe el registro\n";
                f.close();
                return nullptr;
            }
            //Buscar en aux
            faopen(auxName);
            isfaopen
            {
                long posAux = tmp->getNext();
                char posFile = tmp->getFile();
                while (posFile == 'a')
                {
                    fa.seekg(posAux, ios::beg);
                    read(fa, *tmp);
                    accesos++;
                    if (tmp->getKey() == key)
                    {
                        fa.close();
                        f.close();
                        if (tmp->getNext() == -2)
                        {
                            cout << "Registro eliminado\n";
                            return nullptr;
                        }
                        else
                            return tmp;
                    }
                    posAux = tmp->getNext();
                    posFile = tmp->getFile();
                }
                fa.close();
            }
            else cout << "SequentialError al abrir aux en search\n";

            f.close();
        }
        else cout << "SequentialError al abrir data en search\n";
        cout << "No existe el registro\n";
        return nullptr;
    }
    vector<TRecord> search(TKey begin, TKey end)
    {
        vector<TRecord> result;
        int x = 0;
        long pos = insideSearch(begin, x);
        char file;
        TRecord tmp;
        fopen(fileName);
        isfopen
        {
            faopen(auxName);
            isfaopen
            {
                do
                {
                    f.seekg(pos, ios::beg);
                    read(f, tmp);
                    if (tmp.getKey() > end)
                        break;
                    if (tmp.getKey() >= begin && tmp.getKey() <= end)
                        result.push_back(tmp);
                    if (tmp.getFile() == 'a')
                    {
                        //Buscar en aux
                        pos = tmp.getNext();
                        do
                        {
                            fa.seekg(pos, ios::beg);
                            read(fa, tmp);
                            if (tmp.getKey() >= begin && tmp.getKey() <= end)
                                result.push_back(tmp);
                            pos = tmp.getNext();
                            file = tmp.getFile();
                        } while (file == 'a' && pos != -1);
                    }
                    else
                    {
                        pos = tmp.getNext();
                        file = tmp.getFile();
                    }
                } while (pos != -1);
                fa.close();
            }
            else cout << "SequentialError al abrir aux en searchRange\n";
            f.close();
        }
        else cout << "SequentialError al abrir data en searchRange\n";
        sort(result.begin(), result.end(), comp<TRecord>);
        return result;
    }

    bool erase(TKey key)
    {
        if (sizeData + sizeAux == 0)
        {
            cout << "No hay datos\n";
            return false;
        }
        int x = 0;
        auto record = search(key, x);
        if (!record)
            return false;

        fopen(fileName);
        isfopen
        {
            faopen(auxName);
            isfaopen
            {
                TRecord record;
                TRecord recordNext;
                f.seekg(0, ios::beg);
                read(f, record);
                long next = record.getNext(), nextPrev = 0;
                char file = record.getFile(), filePrev = 'd';
                if (record.getKey() == key)
                {
                    //Borrar el primer registro
                    //Caso 1: Solo hay un registro, borro el archivo
                    if (next == -1)
                    {
                        sizeData = 0;
                        f.close();
                        fa.close();
                        cleanFile(fileName);
                        return true;
                    }
                    else
                    {
                        //Caso 2: El primer registro apunta a un registro en data o aux, lo traigo a la primera posición
                        if (file == 'd')
                        {
                            f.seekg(next, ios::beg);
                            read(f, recordNext);
                            f.seekp(0, ios::beg);
                            write(f, recordNext);

                            recordNext.setNext(-2, 'd');
                            f.seekp(next, ios::beg);
                            write(f, recordNext);
                            sizeData--;
                        }
                        else
                        {
                            fa.seekg(next, ios::beg);
                            read(fa, recordNext);
                            f.seekp(0, ios::beg);
                            write(f, recordNext);

                            recordNext.setNext(-2, 'a');
                            fa.seekp(next, ios::beg);
                            write(fa, recordNext);
                            sizeAux--;
                        }
                    }
                }
                else
                {
                    while (1)
                    {
                        if (file == 'd')
                        {
                            f.seekg(next, ios::beg);
                            read(f, recordNext);
                        }
                        else
                        {
                            fa.seekg(next, ios::beg);
                            read(fa, recordNext);
                        }
                        if (recordNext.getKey() == key)
                            break;
                        nextPrev = next;
                        filePrev = file;
                        next = recordNext.getNext();
                        file = recordNext.getFile();
                        record = recordNext;
                    }

                    record.setNext(recordNext.getNext(), recordNext.getFile());
                    recordNext.setNext(-2, 'd');

                    if (filePrev == 'd')
                    {
                        f.seekp(nextPrev, ios::beg);
                        write(f, record);
                    }
                    else
                    {
                        fa.seekp(nextPrev, ios::beg);
                        write(fa, record);
                    }

                    if (file == 'd')
                    {
                        f.seekp(next, ios::beg);
                        write(f, recordNext);
                        sizeData--;
                    }
                    else
                    {
                        fa.seekp(next, ios::beg);
                        write(fa, recordNext);
                        sizeAux--;
                    }
                }

                f.close();
                fa.close();
                //Verificar si requiere reorganización por cantidad de eliminados
                auto sizeErased = sizeFile<TRecord>(fileName) + sizeFile<TRecord>(auxName) - sizeData - sizeAux;
                //cout << sizeErased << "\n";
                if (sizeErased >= SEQ_MAX_ERASED_RECORDS)
                {
                    int x;
                    refactor(x);
                    return true;
                }
                return true;
            }
            else cout << "SequentialError al abrir aux en searchRange\n";
        }
        else cout << "SequentialError al abrir dat en searchRange\n";
        return false;
    }

    void showRecords()
    {
        int cont = 1;
        fopen(fileName);
        isfopen
        {
            faopen(auxName);
            isfaopen
            {
                TRecord tmp;
                f.seekg(0, ios::beg);
                read(f, tmp);
                long next = tmp.getNext();
                char file = tmp.getFile();

                tmp.showRecord(cont++);

                while (next != -1)
                {
                    if (file == 'd')
                    {
                        f.seekg(next, ios::beg);
                        read(f, tmp);
                    }
                    else if (file == 'a')
                    {
                        fa.seekg(next, ios::beg);
                        read(fa, tmp);
                    }
                    else
                    {
                        cout << "Algó falló\n";
                        f.close();
                        fa.close();
                        return;
                    }
                    tmp.showRecord(cont++);
                    next = tmp.getNext();
                    file = tmp.getFile();
                }
                fa.close();
                cout << setw(5) << "N°" << setw(25) << "Key" << setw(13) << "Type" << setw(15) << "Total" << setw(15) << "Generation" << setw(10) << "Legendary?"
                     << "\n";
            }
            else cout << "SequentialError al abrir aux en showRecords\n";
            f.close();
        }
        else cout << "SequentialError al abrir data en showRecords\n";
    }
};
#endif //SEQ.H