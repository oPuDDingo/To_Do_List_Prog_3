#include <iostream>
#include <string>

#include "Api/Endpoint.hpp"
#include "Api/Parser/JsonParser.hpp"
#include "Core/Manager.hpp"
#include "Repository/SQLiteRepository.hpp"
#include "crow.h"

int main() {
    crow::SimpleApp crowApplication;
    ReminderApp::Repository::SQLiteRepository sqliteRepository;
    ReminderApp::Api::Parser::JsonParser jsonParser;

    ReminderApp::Core::Manager manager(jsonParser, sqliteRepository);
    ReminderApp::Api::Endpoint endpoint(crowApplication, manager);

    crowApplication.port(8080)
        //        .multithreaded()
        .run();
}
