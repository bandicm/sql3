#ifndef _SQL3_
#define _SQL3_

#include <stdio.h>
#include <sqlite3.h>
#include <string.h>

#include <string>
#include <vector>
#include <map>
// #include <algorithm>
#include <iostream>

using namespace std;

static string responseDatabase;
static int callback(void* data, int argc, char** argv, char** azColName);

class sql3 {
    public:

    sqlite3* db;
    string path;
    bool keepOpen;
    string Answer;
    map<string, vector<string>> parsed;
    
    sql3(const string path, bool _keepOpen = false);
    bool open();
    bool close();
    bool run(const string sql_command);
    string answer();
    void mapit();

    string ask(const string sql_command);
    map<string, vector<string>> query(const string sql_command);
    
    ~sql3();

};


#endif