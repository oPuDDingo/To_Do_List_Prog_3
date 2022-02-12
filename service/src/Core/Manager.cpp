#include <iostream>
#include "Manager.hpp"

using namespace ReminderApp::Core;
using namespace ReminderApp::Api::Parser;
using namespace ReminderApp::Repository;
using namespace ReminderApp::Core::Model;
using namespace std;

Manager::Manager(ParserIf &givenParser, RepositoryIf &givenRepository)
    : parser(givenParser), repository(givenRepository) {
}

Manager::~Manager() {
}

std::string Manager::getBoard() {
    Board board = repository.getBoard();

    return parser.convertToApiString(board);
}

std::string Manager::getLists() {
    std::vector<List> lists = repository.getLists();

    return parser.convertToApiString(lists);
}

std::string Manager::getList(int listId) {

    std::optional<List> list = repository.getList(listId);
    if (list) {
        return parser.convertToApiString(list.value());
    } else {
        return parser.getEmptyResponseString();
    }
}

std::string Manager::postList(std::string body) {

    int const dummyId = -1;
    std::optional<List> parsedListOptional = parser.convertListToModel(dummyId, body);
    if (!parsedListOptional.has_value()) {
        return parser.getEmptyResponseString();
    }

    List parsedList = parsedListOptional.value();

    std::optional<List> postedList = repository.postList(parsedList.getTitle());

    if (postedList) {
        return parser.convertToApiString(postedList.value());
    } else {
        return parser.getEmptyResponseString();
    }
}

std::string Manager::updateList(int listId, std::string body) {

    std::optional<List> parsedListOptional = parser.convertListToModel(listId, body);

    if (!parsedListOptional.has_value()) {
        return parser.getEmptyResponseString();
    }
    List list = parsedListOptional.value();
    std::optional<List> putList = repository.putList(listId, list.getTitle());

    if (putList) {
        return parser.convertToApiString(putList.value());
    } else {
        return parser.getEmptyResponseString();
    }
}

void Manager::deleteList(int listId) {
    repository.deleteList(listId);
}

std::string Manager::getReminders(int listId) {
    std::vector<Reminder> reminders = repository.getReminders(listId);

    return parser.convertToApiString(reminders);
}

std::string Manager::getReminder(int listId, int reminderId) {

    std::optional<Reminder> reminder = repository.getReminder(listId, reminderId);

    if (reminder) {
        return parser.convertToApiString(reminder.value());
    } else {
        return parser.getEmptyResponseString();
    }
}

std::string Manager::postReminder(int listId, std::string body) {

    int const dummyId = -1;
    std::optional parsedReminderOptional = parser.convertReminderToModel(dummyId, body);
    if (!parsedReminderOptional.has_value()) {
        return parser.getEmptyResponseString();
    }

    Reminder reminder = parsedReminderOptional.value();
    std::optional<Reminder> postedReminder = repository.postReminder(listId, reminder.getTitle(), reminder.getDate());
    if (postedReminder) {
        return parser.convertToApiString(postedReminder.value());
    } else {
        return parser.getEmptyResponseString();
    }
}

std::string Manager::updateReminder(int listId, int reminderId, std::string body) {

    std::optional parsedReminderOptional = parser.convertReminderToModel(reminderId, body);
    if (!parsedReminderOptional.has_value()) {
        return parser.getEmptyResponseString();
    }

    Reminder reminder = parsedReminderOptional.value();
    std::optional<Reminder> putReminder = repository.putReminder(listId, reminderId, reminder.getTitle(), reminder.getDate());

    if (putReminder) {
        return parser.convertToApiString(putReminder.value());
    } else {
        return parser.getEmptyResponseString();
    }
}

void Manager::deleteReminder(int listId, int reminderId) {
    repository.deleteReminder(listId, reminderId);
}
