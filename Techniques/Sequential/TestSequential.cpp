#include "sequential.h"

int main()
{

    /*
    cout << "---------------Borrando archivos---------------\n";
    init();
    Sequential<Record<char[25]>, string> seq("data", "daux");
    Record<char[25]> r("Bulbasaur", "Grass", 318, 1, false);
    seq.insert(r);
    r.setData("Ivysaur", "Grass", 405, 1, false);
    seq.insert(r);
    r.setData("Charmeleon", "Fire", 309, 1, false);
    seq.insert(r);
    seq.showAll();
    */
    //r.setData

    /*
    Sequential<int> seq("data", "daux");
    Record<int> r;
    vector<Record<int>> vr;
    r.setData(14);
    vr.push_back(r);
    r.setData(24);
    vr.push_back(r);
    r.setData(85);
    vr.push_back(r);
    r.setData(45);
    vr.push_back(r);
    cout << "\n---------------Insert all---------------\n";
    seq.insertAll(vr);
    seq.showAll();

    cout << "\n---------------Insert 4 records in aux---------------\n";
    cout << "-------Insert 16 22 Between 14 & 24-------\n";
    cout << "-------Insert 60 50 Between 45 & 85-------\n";
    r.setData(16);
    seq.insert(r);
    r.setData(22);
    seq.insert(r);
    r.setData(60);
    seq.insert(r);
    r.setData(50);
    seq.insert(r);
    seq.showAll();

    cout << "\n---------------Insert 1 record more in aux (max 5)---------------\n";
    cout << "---------------Insert 1 to refactor---------------\n";
    r.setData(1);
    seq.insert(r);
    seq.showAll();

    cout << "\n---------------Insert 4 records to aux---------------\n";
    cout << "\n---------------Insert 3, 13, 46, 65---------------\n";
    r.setData(3);
    seq.insert(r);
    r.setData(13);
    seq.insert(r);
    r.setData(46);
    seq.insert(r);
    r.setData(65);
    seq.insert(r);
    seq.showAll();

    cout << "\n---------------Search 5---------------\n";
    auto rs = seq.search(5);
    if (rs)
        rs->showData();
    cout << "\n---------------Search 50---------------\n";
    rs = seq.search(50);
    if (rs)
        rs->showData();
    cout << "\n---------------Search 3---------------\n";
    rs = seq.search(3);
    if (rs)
        rs->showData();
    cout << "\n---------------Search 85---------------\n";
    rs = seq.search(85);
    if (rs)
        rs->showData();
    cout << "\n---------------Search 100---------------\n";
    rs = seq.search(100);
    if (rs)
        rs->showData();

    cout << "\n---------------Search 3 to 20---------------\n";
    vr = seq.search(3, 20);
    cout << "Result size: " << vr.size() << "\n";
    for (auto rec : vr)
    {
        rec.showData();
    }

    cout << "\n---------------Search 40 to 100---------------\n";
    vr = seq.search(40, 100);
    cout << "Result size: " << vr.size() << "\n";
    for (auto rec : vr)
    {
        rec.showData();
    }

    cout << "\n---------------Erase 85---------------\n";
    seq.showAll();
    seq.erase(85);
    cout << "\n\t\tAfter erase\n";
    seq.showAll();
    cout << "\n---------------Search 85---------------\n";
    rs = seq.search(85);
    if (rs)
        rs->showData();

    cout << "\n---------------Erase 46---------------\n";
    seq.erase(46);
    cout << "\n\t\tAfter erase\n";
    seq.showAll();
    cout << "\n---------------Search 46---------------\n";
    rs = seq.search(46);
    if (rs)
        rs->showData();

    cout << "\n---------------Erase 1(REFACTOR)---------------\n";
    seq.erase(1);
    cout << "\n\t\tAfter erase\n";
    seq.showAll();
    cout << "\n---------------Search 1---------------\n";
    rs = seq.search(1);
    if (rs)
        rs->showData();
*/
    return 0;
}