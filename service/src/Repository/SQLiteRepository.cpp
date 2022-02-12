#include "SQLiteRepository.hpp"
#include <filesystem>
#include <iostream>

using namespace std;
using namespace ReminderApp::Repository;
using namespace ReminderApp::Core::Model;

#ifdef RELEASE_SERVICE
string const SQLiteRepository::databaseFile = "./data/reminder-app.db";
#else
string const SQLiteRepository::databaseFile = "../data/reminder-app.db";
#endif

SQLiteRepository::SQLiteRepository() : database(nullptr) {

    string databaseDirectory = filesystem::path(databaseFile).parent_path().string();

    if (!filesystem::is_directory(databaseDirectory)) {
        filesystem::create_directory(databaseDirectory);
    }

    int result = sqlite3_open(databaseFile.c_str(), &database);

    if (SQLITE_OK != result) {
        cout << "Cannot open database: " << sqlite3_errmsg(database) << endl;
    }

    initialize();
}

SQLiteRepository::~SQLiteRepository() {
    sqlite3_close(database);
}

void SQLiteRepository::initialize() {
    int result = 0;
    char *errorMessage = nullptr;

    string sqlCreateTableList =
        "create table if not exists list("
        "id integer not null primary key autoincrement,"
        "title text not null)";

    string sqlCreateTableReminder =
        "create table if not exists reminder("
        "id integer not null primary key autoincrement,"
        "title text not null,"
        "date text not null,"
        "done bit,"
        "flag bit,"
        "list_id integer not null,"
        "foreign key (list_id) references list (id))";


    result = sqlite3_exec(database, sqlCreateTableList.c_str(), NULL, 0, &errorMessage);
    handleSQLError(result, errorMessage);
    result = sqlite3_exec(database, sqlCreateTableReminder.c_str(), NULL, 0, &errorMessage);
    handleSQLError(result, errorMessage);
}

void SQLiteRepository::dropDatabase() {
    //WARNING: executing this code will WIPE OUT WHOLE DATABASE!!!
    string dropReminder = "drop table reminder";
    string dropList = "drop table list";

    int result = 0;
    char* errorMessage = nullptr;
    result = sqlite3_exec(database, dropReminder.c_str(), NULL, 0, &errorMessage);
    handleSQLError(result, errorMessage);
    result = sqlite3_exec(database, dropList.c_str(), NULL, 0, &errorMessage);
    handleSQLError(result, errorMessage);
}

Board SQLiteRepository::getBoard() {

    Board board = Board(boardTitle);

    vector<List> lists = getLists();
    board.setLists(lists);

    return board;
}

std::vector<List> SQLiteRepository::getLists() {

    std::vector<List> lists;

    string sqlQueryLists =
            "SELECT list.id, list.title, reminder.id, reminder.title, reminder.date from list "
            "left join reminder on reminder.list_id = list.id "
            "order by list.id, reminder.id";

    int result = 0;
    char *errorMessage = nullptr;

    result = sqlite3_exec(database, sqlQueryLists.c_str(), queryListsCallback, &lists, &errorMessage);
    handleSQLError(result, errorMessage);

    return lists;
}

std::optional<List> SQLiteRepository::getList(int id) {

    std::vector<List> lists;

    string sqlQueryLists =
            "SELECT list.id, list.title, reminder.id, reminder.title, reminder.date from list "
            "left join reminder on reminder.list_id = list.id where list.id = " +
            to_string(id) +
            " order by list.id, reminder.id";

    int result = 0;
    char *errorMessage = nullptr;

    result = sqlite3_exec(database, sqlQueryLists.c_str(), queryListsCallback, &lists, &errorMessage);
    handleSQLError(result, errorMessage);

    if (lists.size() == 1) {
        return lists.front();
    } else {
        return std::nullopt;
    }
}

std::optional<List> SQLiteRepository::postList(std::string title) {

    string sqlPostReminder =
            "INSERT INTO list('title') "
            "VALUES('" +
            title + "')";

    int result = 0;
    char *errorMessage = nullptr;

    result = sqlite3_exec(database, sqlPostReminder.c_str(), NULL, 0, &errorMessage);
    handleSQLError(result, errorMessage);

    if (SQLITE_OK == result) {
        int listId = sqlite3_last_insert_rowid(database);
        return List(listId, title);
    }

    return std::nullopt;
}

std::optional<ReminderApp::Core::Model::List> SQLiteRepository::putList(int id, std::string title) {

    string sqlUpdateList =
            "UPDATE list "
            "SET title = '" +
            title +
            "' WHERE id = " + to_string(id);

    int result = 0;
    char *errorMessage = nullptr;

    result = sqlite3_exec(database, sqlUpdateList.c_str(), NULL, 0, &errorMessage);
    handleSQLError(result, errorMessage);

    return getList(id);
}

void SQLiteRepository::deleteList(int id) {

    string sqlDeleteListReminders =
            "DELETE FROM reminder "
            "WHERE reminder.list_id = " +
            to_string(id);

    string sqlDeleteList =
            "DELETE FROM list "
            "WHERE list.id = " +
            to_string(id);

    int result = 0;
    char *errorMessage = nullptr;

    result = sqlite3_exec(database, sqlDeleteListReminders.c_str(), NULL, 0, &errorMessage);
    handleSQLError(result, errorMessage);

    result = sqlite3_exec(database, sqlDeleteList.c_str(), NULL, 0, &errorMessage);
    handleSQLError(result, errorMessage);
}

std::vector<Reminder> SQLiteRepository::getReminders(int listId) {

    std::vector<Reminder> reminders;

    string sqlQueryReminders =
            "SELECT reminder.id, reminder.title, reminder.date from reminder "
            "where reminder.list_id = " +
            std::to_string(listId) +
            " order by reminder.id";

    int result = 0;
    char *errorMessage = nullptr;

    result = sqlite3_exec(database, sqlQueryReminders.c_str(), queryRemindersCallback, &reminders, &errorMessage);
    handleSQLError(result, errorMessage);

    return reminders;
}

std::optional<Reminder> SQLiteRepository::getReminder(int listId, int reminderId) {

    std::vector<Reminder> reminders;

    string sqlQueryReminders =
            "SELECT reminder.id, reminder.title, reminder.date from reminder "
            "where reminder.list_id = " +
            std::to_string(listId) + " and reminder.id = " + std::to_string(reminderId) +
            " order by reminder.id";

    int result = 0;
    char *errorMessage = nullptr;

    result = sqlite3_exec(database, sqlQueryReminders.c_str(), queryRemindersCallback, &reminders, &errorMessage);
    handleSQLError(result, errorMessage);

    if (reminders.size() == 1) {
        return reminders.front();
    } else {
        return std::nullopt;
    }
}

std::optional<Reminder> SQLiteRepository::postReminder(int listId, std::string title, std::string date) {

    string sqlPostReminder =
            "INSERT INTO reminder ('title', 'date', 'list_id')"
            "VALUES ('" +
            title + "','" + date + "'," + to_string(listId) + ");";

    int result = 0;
    char *errorMessage = nullptr;

    result = sqlite3_exec(database, sqlPostReminder.c_str(), NULL, 0, &errorMessage);
    handleSQLError(result, errorMessage);

    int reminderId = INVALID_ID;
    if (SQLITE_OK == result) {
        reminderId = sqlite3_last_insert_rowid(database);
    }

    return getReminder(listId, reminderId);
}

std::optional<ReminderApp::Core::Model::Reminder> SQLiteRepository::putReminder(int listId, int reminderId, std::string title, std::string date) {

    string sqlUpdateReminder =
            "UPDATE reminder SET title = '" + title + "', date = '" + date + "'"
            " WHERE reminder.list_id = " + to_string(listId) + " AND reminder.id = " + to_string(reminderId);

    int result = 0;
    char *errorMessage = nullptr;

    result = sqlite3_exec(database, sqlUpdateReminder.c_str(), NULL, 0, &errorMessage);
    handleSQLError(result, errorMessage);

    return getReminder(listId, reminderId);
}

void SQLiteRepository::deleteReminder(int listId, int reminderId) {
    string sqlQueryReminder =
            "DELETE FROM reminder "
            "WHERE reminder.list_id = " +
            to_string(listId) +
            " AND reminder.id = " + to_string(reminderId);

    int result = 0;
    char *errorMessage = nullptr;

    result = sqlite3_exec(database, sqlQueryReminder.c_str(), NULL, 0, &errorMessage);
    handleSQLError(result, errorMessage);
}

Reminder SQLiteRepository::getReminderFromCallback(char **fieldValues, int startIndex) {
    int index = startIndex;

    int reminderId = fieldValues[index] ? atoi(fieldValues[index]) : INVALID_ID;
    index++;

    string title = fieldValues[index] ? fieldValues[index] : "";
    index++;

    string date = fieldValues[index] ? fieldValues[index] : "";

    Reminder reminder(reminderId, title, date);
    return reminder;
}

List SQLiteRepository::getListFromCallback(char **fieldValues, int startIndex) {
    int index = startIndex;

    int listId = fieldValues[index] ? atoi(fieldValues[index]) : INVALID_ID;
    index++;

    string title = fieldValues[index] ? fieldValues[index] : "";

    List list(listId, title);
    return list;
}

int SQLiteRepository::queryListsCallback(void *data, int numberOfLists, char **fieldValues, char **listNames) {

    auto *pLists = static_cast<std::vector<List> *>(data);
    std::vector<List> &lists = *pLists;

    Reminder reminder = getReminderFromCallback(fieldValues, 2);

    int listId = fieldValues[0] ? atoi(fieldValues[0]) : INVALID_ID;
    bool wasListAlreadyAdded = false;

    for (List &list : lists) {
        if (list.getId() == listId) {
            wasListAlreadyAdded = true;
            if (isValid(reminder.getId())) {
                list.addReminder(reminder);
            }
            break;
        }
    }

    if (!wasListAlreadyAdded) {
        List list = getListFromCallback(fieldValues, 0);

        if (isValid(reminder.getId())) {
            list.addReminder(reminder);
        }

        if (isValid(list.getId())) {
            lists.push_back(list);
        }
    }

    return 0;
}

int SQLiteRepository::queryRemindersCallback(void *data, int numberOfLists, char **fieldValues, char **listNames) {

    auto *result = static_cast<std::vector<Reminder> *>(data);

    Reminder reminder = getReminderFromCallback(fieldValues, 0);
    if (isValid(reminder.getId())) {
        result->push_back(reminder);
    }
    return 0;
}

void SQLiteRepository::handleSQLError(int statementResult, char *errorMessage) {

    if (statementResult != SQLITE_OK) {
        cout << "SQL error: " << errorMessage << endl;
        sqlite3_free(errorMessage);
    }
}
