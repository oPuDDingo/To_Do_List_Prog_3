#pragma once

#include "Core/Manager.hpp"
#include "crow.h"

namespace ReminderApp::Api {

class Endpoint {
  public:
    Endpoint(crow::SimpleApp &givenApp, ReminderApp::Core::Manager &givenManager);
    ~Endpoint();

    void registerRoutes();

  private:
    crow::SimpleApp &app;
    ReminderApp::Core::Manager &manager;
};

} // namespace ReminderApp
