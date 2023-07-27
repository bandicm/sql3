#include <iostream>

#include "../lib/sql3.hpp"

using namespace std;

int main() {
    try {

    sql3 mydb("../example/example.db", false);

    // cout << mydb.ask("Select * from Tab1");
    // cout << mydb.ask("INSERT INTO Tab1 VALUES(3,'Pakora', 'marijanab@bitelex.ml');");

    auto res = mydb.query("Select * from Tab1");
    // cout << endl <<  res["NAME"][1];

    // cout << endl <<  res["MAIL"][1];

    for (auto i : res) {
        for (auto j: i.second) {
            cout << i.first << " : " << j << endl; 
        }
    }

    } catch (const string err) {
        cout << err << endl;
    }

    return 0;
}