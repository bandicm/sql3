#include "../lib/sql3.hpp"

sql3::sql3(const string _path, bool _keepOpen) {
   path = _path;
   keepOpen = _keepOpen;

   if (keepOpen) {
      if (open()) {
         throw string("[ERROR] Unable to open database ");
      }
   }

}

bool sql3::open() {
   uint operationStatus = sqlite3_open(path.c_str(), &db);
   return operationStatus != SQLITE_OK;
}

bool sql3::close() {
   uint operationStatus = sqlite3_close(db);
   db = NULL;
   return operationStatus != SQLITE_OK;
}

map<string, vector<string>> sql3::query(const string sql_command) {
   io.lock();
   if (!keepOpen) {
      if (open()) {
         io.unlock();
         throw string("[ERROR] Unable to open database ");
      }
   }

   bool r = true;
   char *messaggeError;
   uint exec_stuts;
   exec_stuts = sqlite3_exec(db, sql_command.c_str(), callback, NULL, &messaggeError);

   if (exec_stuts != SQLITE_OK) {
      sqlite3_free(messaggeError);
      r = false;
   }
   else  {
      Answer = responseDatabase;
   }

   if (!keepOpen) {
      if(close()) {
         io.unlock();
         throw string("[ERROR] Unable to close database ");
      }
   }

   map<string, vector<string>> _parsed;

   cout << Answer << endl;

   if (!r) {
      io.unlock();
      throw string("[ERROR] Unable to read database ");
   }

   else {
      mapit();
      _parsed = parsed;
      parsed.clear();
   }
   io.unlock();
   return _parsed;
}

void sql3::mapit() {
   string a = Answer;

   while (a.find("\n") < a.length()) {
      uint lineend = a.find("\n");
      string oneline = a.substr(0, lineend);
      a.erase(0, lineend+1);
      
      size_t sep = oneline.find(" = ");
      string key = oneline.substr(0, sep);
      string value = oneline.substr(sep + 3, oneline.length());
      value = value.substr(0, value.length());
      
      parsed[key].push_back(value);
   }


}

sql3::~sql3() {
   if(close()) {
      throw string("[ERROR] Unable to close database ");
   }
}


/**
 * Callback funkcija za sqlite3 
*/

static int callback(void* data, int argc, char** argv, char** azColName) {
   int i;
   fprintf(stderr, "%s: ", (const char*)data);
   char res[1000];
   responseDatabase.clear();
   for (i = 0; i < argc; i++) {
      sprintf(res, "%s = %s", azColName[i], argv[i] ? argv[i] : "NULL");
      responseDatabase += res;
      responseDatabase += '\n';
   }
   return 0;
}
