#pragma once

#include "Core/Manager.hpp"
#include "crow.h"

namespace ReminderApp {
namespace Api {

class Endpoint {
  public:
    Endpoint(crow::SimpleApp &givenApp, ReminderApp::Core::Manager &givenManager);
    ~Endpoint();

    void registerRoutes();

  private:
    crow::SimpleApp &app;
    ReminderApp::Core::Manager &manager;
};

} // namespace Api
} // namespace ReminderApp
