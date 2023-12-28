#include "../headers/controllers.h"
#include "../headers/json.hpp"
#include "../headers/httplib.h"
#include <iostream>

void userLoginDB(const nlohmann::json &data, httplib::Response &res, sqlite3 *DB)
{
    std::string username = data["username"];
    std::string password = data["password"];
    std::string command = "SELECT * FROM users WHERE username = ? AND password = ?;";
    sqlite3_stmt *stmt;
    int result = sqlite3_prepare_v2(DB, command.c_str(), -1, &stmt, nullptr);
    if (result != SQLITE_OK)
    {
        res.set_content("Database error", "text/plain");
        return;
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

    result = sqlite3_step(stmt);

    if (result == SQLITE_ROW)
    {
        res.status = 200;
        res.set_content("Authentication successful", "text/plain");
    }
    else
    {
        res.status = 404;
        res.set_content("Authentication failed", "text/plain");
    }

    sqlite3_finalize(stmt);
}

void userRegisterDB(const nlohmann::json &data, httplib::Response &res, sqlite3 *DB)
{
    std::string name = data["fullname"];
    std::string licensenum = data["licensenum"];
    std::string username = data["username"];
    std::string password = data["password"];
    std::string command = "INSERT INTO users (username, password, licensenum, fullname) VALUES (?, ?, ?, ?);";

    sqlite3_stmt *stmt;
    int result = sqlite3_prepare_v2(DB, command.c_str(), -1, &stmt, nullptr);

    if (result != SQLITE_OK)
    {
        res.status = 404;
        res.set_content("Registration failed", "text/plain");
        std::cerr << "SQL prepare error: " << sqlite3_errmsg(DB) << std::endl;
    }
    else
    {
        sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, licensenum.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 4, name.c_str(), -1, SQLITE_STATIC);

        result = sqlite3_step(stmt);

        if (result != SQLITE_DONE)
        {
            res.status = 404;
            res.set_content("Registration failed", "text/plain");
            std::cerr << "SQL execution error: " << sqlite3_errmsg(DB) << std::endl;
        }
        else
        {
            res.status = 200;
            res.set_content("Registration successful", "text/plain");
            std::cout << "Record inserted successfully!" << std::endl;
        }

        sqlite3_finalize(stmt);
    }

    std::cout << "Username: " << username << std::endl;
    std::cout << "Name: " << name << std::endl;
}