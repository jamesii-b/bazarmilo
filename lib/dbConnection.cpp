#include <sqlite3.h>
#include <iostream>
#include "../headers/dbConnection.h"
void dbConnection(sqlite3 *&DB)
{
    int exit = 0;
    exit = sqlite3_open("../bazarmilo.db", &DB);
    if (exit)
    {
        std::cerr << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
    }
    else
    {
        std::cout << "Opened Database Successfully!" << std::endl;
    }
}

void closeConnection(sqlite3 *DB)
{
    int exit = sqlite3_close(DB);

    if (exit != SQLITE_OK)
    {
        std::cerr << "Error closing DB: " << sqlite3_errmsg(DB) << std::endl;
    }
    else
    {
        std::cout << "Closed Database Successfully!" << std::endl;
    }
}