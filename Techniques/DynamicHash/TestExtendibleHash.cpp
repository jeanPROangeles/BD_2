#include "extendibleHash.h"

using namespace std;

int main()
{
    cout << "---------------Borrando archivos---------------\n";
    cleanFile("data.dat");
    cleanFile("index.dat");
    int tmp = 0;
    ExtendibleHash<int> extendibleHash("data", "index");
    extendibleHash.showAll();
    RecordHash<int> r;
    r.setData(1); //001
    extendibleHash.insert(r, tmp);
    r.setData(2); //010
    extendibleHash.insert(r, tmp);
    r.setData(10); //010
    extendibleHash.insert(r, tmp);
    r.setData(18); //010
    extendibleHash.insert(r, tmp);
    extendibleHash.showAll();
    cout << "\n-----------------------DIVISION-----------------------\n";
    r.setData(26); //010
    extendibleHash.insert(r, tmp);
    extendibleHash.showAll();
    /*r.setData(34); //010
    extendibleHash.insert(r, tmp);
    r.setData(42); //010
    extendibleHash.insert(r, tmp);
    r.setData(50); //010
    extendibleHash.insert(r, tmp);
    extendibleHash.showAll();

    cout << "\n-----------------------SEARCH-----------------------\n";
    auto rs = extendibleHash.search(1, tmp);
    if (rs)
        (*rs).showData();
    else
        cout << "No existe 1\n";
    rs = extendibleHash.search(8, tmp);
    if (rs)
        (*rs).showData();
    else
        cout << "No existe 8\n";
    rs = extendibleHash.search(26, tmp);
    if (rs)
        (*rs).showData();
    else
        cout << "No existe 26\n";
    rs = extendibleHash.search(50, tmp);
    if (rs)
        (*rs).showData();
    else
        cout << "No existe 50\n";

    cout << "\n-----------------------RANGE SEARCH-----------------------\n";
    auto rv = extendibleHash.searchRange(1, 5);
    cout << rv.size() << "\n";
    for (auto rec : rv)
        rec.showData();

    cout << "\n-----------------------ERASE 34-----------------------\n";
    extendibleHash.erase(34);
    extendibleHash.erase(26);
    extendibleHash.erase(42);
    extendibleHash.erase(50);
    extendibleHash.erase(18);
    extendibleHash.erase(10);
    //r.setData(18); //010
    //extendibleHash.insert(r);
    extendibleHash.showAll();
    extendibleHash.erase(2);
    extendibleHash.showAll();
    r.setData(2);
    extendibleHash.insert(r, tmp);
    r.setData(4);
    extendibleHash.insert(r, tmp);
    r.setData(6);
    extendibleHash.insert(r, tmp);
    r.setData(8);
    extendibleHash.insert(r, tmp);
    extendibleHash.showAll();
    extendibleHash.erase(6);
    extendibleHash.erase(8);
    extendibleHash.erase(4);
    extendibleHash.showAll();

    cout << "\n----------------------------------------------\n";
    r.setData(10);
    extendibleHash.insert(r, tmp);
    r.setData(18);
    extendibleHash.insert(r, tmp);
    r.setData(26);
    extendibleHash.insert(r, tmp);
    extendibleHash.showAll();
*/
    return 0;
}