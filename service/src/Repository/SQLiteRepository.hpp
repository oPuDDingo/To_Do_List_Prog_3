#pragma once

#include "Core/Model/Reminder.hpp"
#include "Repository/RepositoryIf.hpp"
#include "sqlite3.h"
#include <string>
#include <vector>

namespace ReminderApp {
namespace Repository {

class SQLiteRepository : public RepositoryIf {
  private:
    sqlite3 *database;

    void initialize();
    void handleSQLError(int statementResult, char *errorMessage);

  public:
    SQLiteRepository();
    virtual ~SQLiteRepository();

    virtual std::vector<ReminderApp::Core::Model::Reminder> getItems(int columnId);

    static std::string const databaseFile;
};

} // namespace Repository
} // namespace ReminderApp
