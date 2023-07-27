#include <iostream>

#include "../lib/sql3.hpp"

using namespace std;

int main() {

    sql3 mydb("../example/example.db", false);

    // cout << mydb.ask("Select * from Tab1");
    // cout << mydb.ask("INSERT INTO Tab1 VALUES(3,'Pakora', 'marijanab@bitelex.ml');");

    // auto res = mydb.query("Select * from Tab1");
    auto res = mydb.query("INSERT INTO Tab1 VALUES(4,'Mare', 'marijanab@bitelex.co');");

    // for (auto i : res) 
    //     for (auto j: i.second)
    //         cout << i.first << " : " << j << endl;
    

    // cout << endl <<  res["NAME"][1];

    return 0;
}