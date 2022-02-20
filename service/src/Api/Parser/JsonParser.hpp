#pragma once

#include <optional>
#include "ParserIf.hpp"
#include "rapidjson/document.h"
#include "Core/Model/Reminder.hpp"
#include "Core/Model/List.hpp"
#include "Core/Model/Board.hpp"

namespace ReminderApp::Api::Parser {

class JsonParser : public ParserIf {
  private:
    static inline std::string const EMPTY_JSON = "{}";

    bool isValidList(rapidjson::Document const &document);
    bool isValidReminder(rapidjson::Document const &document);

    std::string jsonValueToString(rapidjson::Value const &json);

    rapidjson::Value getJsonValueFromModel(ReminderApp::Core::Model::Reminder const &reminder, rapidjson::Document::AllocatorType &allocator);
    rapidjson::Value getJsonValueFromModel(ReminderApp::Core::Model::List const &list, rapidjson::Document::AllocatorType &allocator);
    rapidjson::Value getJsonValueFromModel(ReminderApp::Core::Model::Board &board, rapidjson::Document::AllocatorType &allocator);

  public:
    JsonParser(){};
    virtual ~JsonParser(){};

    virtual std::string convertToApiString(ReminderApp::Core::Model::Board &board);

    virtual std::string convertToApiString(ReminderApp::Core::Model::List &list);
    virtual std::string convertToApiString(std::vector<ReminderApp::Core::Model::List> &lists);

    virtual std::string convertToApiString(ReminderApp::Core::Model::Reminder &reminder);
    virtual std::string convertToApiString(std::vector<ReminderApp::Core::Model::Reminder> &reminders);

    virtual std::optional<ReminderApp::Core::Model::List> convertListToModel(int listId, std::string &request);
    virtual std::optional<ReminderApp::Core::Model::Reminder> convertReminderToModel(int reminderId, std::string &request);

    virtual std::string getEmptyResponseString() {
        return JsonParser::EMPTY_JSON;
    }
};

}
