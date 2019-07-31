#include <iostream>
#include <stdio.h>
#include <mysql>
#include <string>

using namespace std;

int main(){
    MYSQL mysql;

    if(!mysql_init(&mysql)){
        printf("mysql_init() failed!\n");
        return 1;
    }

    if(!mysql_real_connect(&mysql, "localhost", "root", "dbtest", 3306, NULL, CLIENT_MULTI_STATEMENTS)){
        printf("mysql_real_connect() failed!\n");
        mysql_close(&mysql);
        mysql_library_end(&mysql);
        return 2;
    }

    strcpy(query, "call ")
}