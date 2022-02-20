#pragma once

#include <string>
#include <optional>
#include "Core/Model/Board.hpp"

namespace ReminderApp::Api::Parser {

class ParserIf {
  public:
    virtual ~ParserIf() {}

    virtual std::string getEmptyResponseString() = 0;

    virtual std::string convertToApiString(ReminderApp::Core::Model::Board &board) = 0;

    virtual std::string convertToApiString(ReminderApp::Core::Model::List &list) = 0;
    virtual std::string convertToApiString(std::vector<ReminderApp::Core::Model::List> &lists) = 0;

    virtual std::string convertToApiString(ReminderApp::Core::Model::Reminder &reminder) = 0;
    virtual std::string convertToApiString(std::vector<ReminderApp::Core::Model::Reminder> &reminders) = 0;

    virtual std::optional<ReminderApp::Core::Model::List> convertListToModel(int listId, std::string &request) = 0;
    virtual std::optional<ReminderApp::Core::Model::Reminder> convertReminderToModel(int reminderId, std::string &request) = 0;
};

}
