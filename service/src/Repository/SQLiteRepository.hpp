#pragma once

#include "Repository/RepositoryIf.hpp"
#include "sqlite3.h"
#include <string>

namespace Reminder {
namespace Repository {

class SQLiteRepository : public RepositoryIf {
  private:
    sqlite3 *database;

    void initialize();
    void handleSQLError(int statementResult, char *errorMessage);

  public:
    SQLiteRepository();
    virtual ~SQLiteRepository();

    static std::string const databaseFile;
};

} // namespace Repository
} // namespace Reminder
