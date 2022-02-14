#include "Reminder.hpp"

using namespace ReminderApp::Core::Model;

Reminder::Reminder(int id, std::string givenTitle, std::string givenDate, bool givenFlagged) : id(id), title(givenTitle), date(givenDate), flagged(givenFlagged) {}

int Reminder::getId() const {
    return id;
}

std::string Reminder::getTitle() const {
    return title;
}

std::string Reminder::getDate() const {
    return date;
}

bool Reminder::isFlagged() const {
    return flagged;
}

void Reminder::setID(int id) {
    this->id = id;
}

void Reminder::setTitle(std::string title) {
    this->title = title;
}

void Reminder::setDate(std::string time) {
    date = time;
}

void Reminder::setFlagged(bool flagged) {
    this->flagged = flagged;
}