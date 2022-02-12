#include "Reminder.hpp"

using namespace ReminderApp::Core::Model;

Reminder::Reminder(int id, std::string givenTitle, std::string givenDate) : id(id), title(givenTitle), date(givenDate) {}

int Reminder::getId() const {
    return id;
}

std::string Reminder::getTitle() const {
    return title;
}

std::string Reminder::getDate() const {
    return date;
}

void Reminder::setID(int id) {
    id = id;
}

void Reminder::setTitle(std::string title) {
    title = title;
}

void Reminder::setDate(std::string time) {
    date = time;
}
