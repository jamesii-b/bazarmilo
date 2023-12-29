// main.cpp
#include <iostream>
#include "./headers/httplib.h"
#include "./headers/dbConnection.h"
#include "./headers/dbInitialization.h"
#include "./headers/json.hpp"
#include <sqlite3.h>
#include "./headers/controllers.h"


sqlite3 *DB; // Declare a global variable for database connection

int main(int argc, char **argv)
{
   
    dbConnection(DB);

    httplib::Server svr;

    // Routes
    svr.Get("/", [](const httplib::Request &req, httplib::Response &res)
            { res.set_content("hello~", "text/plain"); });

    svr.Post("/admin/login", [](const httplib::Request &req, httplib::Response &res)
             {
        nlohmann::json j = nlohmann::json::parse(req.body);
        adminLoginDB(j, res,DB); });

    svr.Post("/admin/register", [](const httplib::Request &req, httplib::Response &res)
             {
        nlohmann::json j = nlohmann::json::parse(req.body);
        adminRegisterDB(j, res,DB); });

    svr.Post("/user/login", [](const httplib::Request &req, httplib::Response &res)
             {
        nlohmann::json j = nlohmann::json::parse(req.body);
        userLoginDB(j, res,DB); });

    svr.Post("/user/register", [](const httplib::Request &req, httplib::Response &res)
             {
        nlohmann::json j = nlohmann::json::parse(req.body);
        userRegisterDB(j, res,DB); });
    svr.Get("/user/travel/:id", [&](const httplib::Request &req, httplib::Response &res)
            {
    auto ID = req.path_params.at("id");

                res.set_content("Database error", "text/plain");
                std::cout << ID << std::endl; });

    svr.Get("/user/datum/:id", [&](const httplib::Request &req, httplib::Response &res)
            {
    auto ID = req.path_params.at("id");
    userDatum(ID, res, DB); });

    svr.listen("localhost", 8080);
    closeConnection(DB);
    return 0;
}
