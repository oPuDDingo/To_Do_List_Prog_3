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
    void dropDatabase();
    void handleSQLError(int statementResult, char *errorMessage);

    static bool isValid(int id) {
        return id != INVALID_ID;
    }

    static ReminderApp::Core::Model::Reminder getReminderFromCallback(char **fieldValues, int startIndex);
    static ReminderApp::Core::Model::List getListFromCallback(char **fieldValues, int startIndex);

    static int queryListsCallback(void *data, int numberOfLists, char **fieldValues, char **columnNames);
    static int queryRemindersCallback(void *data, int numberOfLists, char **fieldValues, char **columnNames);

  public:
    SQLiteRepository();
    virtual ~SQLiteRepository();

    virtual ReminderApp::Core::Model::Board getBoard();
    virtual std::vector<ReminderApp::Core::Model::List> getLists();
    virtual std::optional<ReminderApp::Core::Model::List> getList(int id);
    virtual std::optional<ReminderApp::Core::Model::List> postList(std::string title);
    virtual std::optional<ReminderApp::Core::Model::List> putList(int id, std::string title);
    virtual void deleteList(int id);
    virtual std::vector<ReminderApp::Core::Model::Reminder> getReminders(int listId);
    virtual std::optional<ReminderApp::Core::Model::Reminder> getReminder(int listId, int reminderId);
    virtual std::optional<ReminderApp::Core::Model::Reminder> postReminder(int listId, std::string title, std::string date);
    virtual std::optional<ReminderApp::Core::Model::Reminder> putReminder(int listId, int reminderId, std::string title);

    virtual void deleteReminder(int listId, int reminderId);
    static inline std::string const boardTitle = "Kanban Board";

    static inline int const INVALID_ID = -1;

    static std::string const databaseFile;
};

} // namespace ReminderApp
