#include "List.hpp"

using namespace ReminderApp::Core::Model;

List::List(int givenId, std::string givenTitle) : id(givenId), title(givenTitle) {}

int List::getId() const {
    return id;
}

void List::setId(int id) {
    this->id = id;
}

std::string List::getTitle() const {
    return title;
}

void List::setTitle(std::string title) {
    this->title = title;
}

std::vector<Reminder> List::getReminders() const {
    return reminders;
}

void List::addReminder(Reminder &reminder) {
    reminders.push_back(reminder);
}
