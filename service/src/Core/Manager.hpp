#pragma once

#include "Api/Parser/ParserIf.hpp"
#include "Repository/RepositoryIf.hpp"

namespace ReminderApp::Core {

class Manager {
  private:
    ReminderApp::Repository::RepositoryIf &repository;
    ReminderApp::Api::Parser::ParserIf &parser;

  public:
    Manager(ReminderApp::Api::Parser::ParserIf &givenParser, ReminderApp::Repository::RepositoryIf &givenRepository);
    ~Manager();

    std::string getBoard();

    std::string getLists();
    std::string postList(std::string body);
    std::string getList(int listId);
    std::string updateList(int listId, std::string body);
    void deleteList(int listId);

    std::string getReminders(int listId);
    std::string postReminder(int listId, std::string body);
    std::string getReminder(int listId, int reminderId);
    std::string updateReminder(int listId, int reminderId, std::string body);
    void deleteReminder(int listId, int reminderId);
};

} // namespace ReminderApp
