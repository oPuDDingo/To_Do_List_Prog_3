#pragma once

#include <vector>
#include <optional>
#include "Core/Model/Board.hpp"

namespace ReminderApp::Repository {

class RepositoryIf {
  public:
    virtual ~RepositoryIf() {}

    virtual ReminderApp::Core::Model::Board getBoard() = 0;
    virtual std::vector<ReminderApp::Core::Model::List> getLists() = 0;
    virtual std::optional<ReminderApp::Core::Model::List> getList(int id) = 0;
    virtual std::optional<ReminderApp::Core::Model::List> postList(std::string title) = 0;
    virtual std::optional<ReminderApp::Core::Model::List> putList(int id, std::string title) = 0;
    virtual void deleteList(int id) = 0;
    virtual std::vector<ReminderApp::Core::Model::Reminder> getReminders(int listId) = 0;
    virtual std::optional<ReminderApp::Core::Model::Reminder> getReminder(int listId, int reminderId) = 0;
    virtual std::optional<ReminderApp::Core::Model::Reminder> postReminder(int listId, std::string title, std::string date) = 0;
    virtual std::optional<ReminderApp::Core::Model::Reminder> putReminder(int listId, int reminderId, std::string title) = 0;
    virtual void deleteReminder(int listId, int reminderId) = 0;
};

} // namespace ReminderApp
