#include "Endpoint.hpp"

#include <iostream>

using namespace Reminder::Api;
using namespace Reminder::Core;
using namespace crow;

Endpoint::Endpoint(SimpleApp &givenApp, Manager &givenManager) : app(givenApp),
                                                                 manager(givenManager) {
    registerRoutes();
}

Endpoint::~Endpoint() {
}

void Endpoint::registerRoutes() {

    CROW_ROUTE(app, "/api/board")
    ([this](const request &req, response &res) {
        res.write(manager.getBoard());
        res.end();
    });

    CROW_ROUTE(app, "/api/board/lists")
        .methods(HTTPMethod::Get, HTTPMethod::Post)([this](const request &req, response &res) {
            std::string jsonLists;
            switch (req.method) {
            case HTTPMethod::Get:
                jsonLists = manager.getLists();
                break;
            case HTTPMethod::Post:
                jsonLists = manager.postList(req.body);
                res.code = 201;
                break;
            }
            res.write(jsonLists);
            res.end();
        });

    CROW_ROUTE(app, "/api/board/lists/<int>")
        .methods(HTTPMethod::Get, HTTPMethod::Put, HTTPMethod::Delete)([this](const request &req, response &res, int listId) {
            std::string jsonList = "{}";
            switch (req.method) {
            case HTTPMethod::Get:
                jsonList = manager.getList(listId);
                break;
            case HTTPMethod::Put:
                jsonList = manager.upadteList(listId, req.body);
                break;
            case HTTPMethod::Delete:
                manager.deleteList(listId);
                break;
            }
            res.write(jsonList);
            res.end();
        });

    CROW_ROUTE(app, "/api/board/lists/<int>/reminders")
        .methods(HTTPMethod::Get, HTTPMethod::Post)([this](const request &req, response &res, int listId) {
            std::string jsonReminders;
            switch (req.method) {
            case HTTPMethod::Get:
                jsonReminders = manager.getReminders(listId);
                break;
            case HTTPMethod::Post:
                jsonReminders = manager.postReminder(listId, req.body);
                res.code = 201;
                break;
            }
            res.write(jsonReminders);
            res.end();
        });

    CROW_ROUTE(app, "/api/board/lists/<int>/reminders/<int>")
        .methods(HTTPMethod::Get, HTTPMethod::Put, HTTPMethod::Delete)([this](const request &req, response &res, int listId, int reminderId) {
            std::string jsonReminder = "{}";
            switch (req.method) {
            case HTTPMethod::Get:
                jsonReminder = manager.getReminder(listId, reminderId);
                break;
            case HTTPMethod::Put:
                jsonReminder = manager.updateReminder(listId, reminderId, req.body);
                break;
            case HTTPMethod::Delete:
                manager.deleteReminder(listId, reminderId);
                break;
            }
            res.write(jsonReminder);
            res.end();
        });
}
