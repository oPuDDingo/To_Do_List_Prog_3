#include "Reminder.hpp"

using namespace ReminderApp::Core::Model;

Reminder::Reminder(int id, std::string givenTitle, std::string givenTimestamp) : id(id), title(givenTitle), timestamp(givenTimestamp) {}

int Reminder::getId() const {
    return id;
}

std::string Reminder::getTitle() const {
    return title;
}

std::string Reminder::getTimestamp() const {
    return timestamp;
}

void Reminder::setID(int id) {
    id = id;
}

void Reminder::setTitle(std::string title) {
    title = title;
}

void Reminder::setTimestamp(std::string time) {
    timestamp = time;
}
