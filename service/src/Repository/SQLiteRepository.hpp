#pragma once

#include "Core/Model/Reminder.hpp"
#include "Repository/RepositoryIf.hpp"
#include "sqlite3.h"
#include "Core/Model/List.hpp"
#include "Core/Model/Board.hpp"
#include <string>
#include <vector>
#include <optional>

namespace ReminderApp::Repository {

class SQLiteRepository : public RepositoryIf {
  private:
    sqlite3 *database;

    void initialize();
    void handleSQLError(int statementResult, char *errorMessage);

  public:
    SQLiteRepository();
    virtual ~SQLiteRepository();

    virtual ReminderApp::Core::Model::Board getBoard()
    virtual std::vector<ReminderApp::Core::Model::List> getLists()
    virtual std::optional<ReminderApp::Core::Model::List> getList(int id)
    virtual std::optional<ReminderApp::Core::Model::List> postList(std::string name, int position)
    virtual std::optional<ReminderApp::Core::Model::List> putList(int id, std::string name, int position)
    virtual void deleteList(int id)
    virtual std::vector<ReminderApp::Core::Model::Reminder> getReminders(int listId)
    virtual std::optional<ReminderApp::Core::Model::Reminder> getReminder(int listId, int reminderId)
    virtual std::optional<ReminderApp::Core::Model::Reminder> postReminder(int listId, std::string title, int position)
    virtual std::optional<ReminderApp::Core::Model::Reminder> putReminder(int listId, int reminderId, std::string title, int position)
    virtual void deleteReminder(int listId, int reminderId)

    static std::string const databaseFile;
};

} // namespace ReminderApp
