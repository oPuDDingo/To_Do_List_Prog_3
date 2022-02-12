#define RAPIDJSON_ASSERT(x)

#include <iostream>
#include "JsonParser.hpp"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

using namespace ReminderApp::Api::Parser;
using namespace ReminderApp::Core::Model;
using namespace rapidjson;
using namespace std;

string JsonParser::convertToApiString(Board &board) {
    Document document;
    Document::AllocatorType &allocator = document.GetAllocator();

    Value jsonBoard = getJsonValueFromModel(board, allocator);
    return jsonValueToString(jsonBoard);
}

string JsonParser::convertToApiString(List &list) {
    Document document(kObjectType);

    Value jsonList = getJsonValueFromModel(list, document.GetAllocator());
    return jsonValueToString(jsonList);
}

rapidjson::Value JsonParser::getJsonValueFromModel(List const &list, rapidjson::Document::AllocatorType &allocator) {
    Value jsonList(kObjectType);

    jsonList.AddMember("id", list.getId(), allocator);
    jsonList.AddMember("title", Value(list.getTitle().c_str(), allocator), allocator);


    Value jsonReminders(kArrayType);

    for (Reminder const &reminder: list.getReminders()) {
        Value jsonReminder = getJsonValueFromModel(reminder, allocator);
        jsonReminders.PushBack(jsonReminder, allocator);
    }

    jsonList.AddMember("items", jsonReminders, allocator);

    return jsonList;
}

rapidjson::Value
JsonParser::getJsonValueFromModel(Reminder const &reminder, rapidjson::Document::AllocatorType &allocator) {
    Value jsonReminder(kObjectType);

    jsonReminder.AddMember("id", reminder.getId(), allocator);
    jsonReminder.AddMember("title", Value(reminder.getTitle().c_str(), allocator), allocator);
    jsonReminder.AddMember("timestamp", Value(reminder.getTimestamp().c_str(), allocator), allocator);

    return jsonReminder;
}

string JsonParser::jsonValueToString(rapidjson::Value const &json) {
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    json.Accept(writer);

    return buffer.GetString();
}

string JsonParser::convertToApiString(std::vector<List> &lists) {

    Document document(kObjectType);
    Document::AllocatorType &allocator = document.GetAllocator();

    for (List &list: lists) {
        Value jsonList = getJsonValueFromModel(list, allocator);
        document.PushBack(jsonList, allocator);

        return jsonValueToString(document);
    }

    return EMPTY_JSON;
}

string JsonParser::convertToApiString(Reminder &reminder) {

    string result = EMPTY_JSON;
    Document document(kObjectType);

    Value jsonReminder = getJsonValueFromModel(reminder, document.GetAllocator());
    result = jsonValueToString(jsonReminder);
    return result;
}

string JsonParser::convertToApiString(std::vector<Reminder> &reminders) {

    string result = EMPTY_JSON;

    Document document(kObjectType);
    Document::AllocatorType &allocator = document.GetAllocator();

    for (Reminder &reminder: reminders) {
        Value jsonReminder = getJsonValueFromModel(reminder, allocator);
        document.PushBack(jsonReminder, allocator);
    }

    return jsonValueToString(document);
}

std::optional<List> JsonParser::convertListToModel(int listId, std::string &request) {
    std::optional<List> resultColumn;
    Document document;
    document.Parse(request.c_str());

    if (isValidList(document)) {
        std::string title = document["title"].GetString();
        resultColumn = List(listId, title);
    }
    return resultColumn;
}

std::optional<Reminder> JsonParser::convertReminderToModel(int reminderId, std::string &request) {
    std::optional<Reminder> resultReminder;
    Document document;
    document.Parse(request.c_str());

    if (isValidReminder(document)) {
        std::string title = document["title"].GetString();
        resultReminder = Reminder(reminderId, title, "");
    }
    return resultReminder;
}

rapidjson::Value JsonParser::getJsonValueFromModel(Board &board, rapidjson::Document::AllocatorType &allocator) {
    Value jsonBoard(kObjectType);
    Value jsonLists(kArrayType);

    for (List &list: board.getLists()) {
        Value jsonList = getJsonValueFromModel(list, allocator);
        jsonLists.PushBack(jsonList, allocator);
    }

    jsonBoard.AddMember("title", Value(board.getTitle().c_str(), allocator), allocator);
    jsonBoard.AddMember("lists", jsonLists, allocator);

    return jsonBoard;
}

bool JsonParser::isValidList(rapidjson::Document const &document) {

    bool isValid = true;

    if (document.HasParseError()) {
        isValid = false;
    }
    if (!document["title"].IsString()) {
        isValid = false;
    }

    return isValid;
}

bool JsonParser::isValidReminder(rapidjson::Document const &document) {

    bool isValid = true;

    if (document.HasParseError()) {
        isValid = false;
    }
    if (!document["title"].IsString()) {
        isValid = false;
    }

    return isValid;
}

