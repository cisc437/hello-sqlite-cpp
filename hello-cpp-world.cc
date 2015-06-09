#include <iostream>
#include <sqlite3.h>
using namespace std;

//I borrowed this from http://www.tutorialspoint.com/sqlite/sqlite_c_cpp.htm
static int callback(void *data, int argc, char **argv, char **azColName){
   int i;
   for(i=0; i<argc; i++){
      printf("%s%s\n", argv[i] ? argv[i] : "NULL", i ? " " : ":");
   }
   printf("\n");
   return 0;
}

int main() {
    sqlite3 *db;
    int sql_status;
    char *zErrMsg = 0;
    char *sql;
    const char* data = "";
    
    sql_status = sqlite3_open("scrabble.sqlite", &db);
    
    if (sql_status){
        cout << "Not able to open" << endl;
        exit(0);
    }
    
    /* Create SQL statement */
    sql = (char *)"SELECT rack, words FROM racks WHERE length = 7 AND weight <= 10 ORDER BY random() LIMIT 0, 5";

    /* Execute SQL statement */
    sql_status = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
    if( sql_status != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
    }
    sqlite3_close(db);
}
