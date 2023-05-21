#include <iostream>

#include "../lib/sql3.hpp"

using namespace std;

int main() {

    sql3 mydb("../example/example.db", true);

    //cout << mydb.ask("Select * from Tab1");
    // cout << mydb.ask("INSERT INTO Tab1 VALUES(3,'Pakora', 'marijanab@bitelex.ml');");

    auto res = mydb.query("Select * from Tab1");

    cout << endl <<  res["NAME"][0];

    return 0;
}