#pragma once

#include "Reminder.hpp"
#include <string>
#include <vector>

class List {
  private:
    int id;
    std::string title;
    std::vector<Reminder> reminders;

  public:
    List(int id, std::string givenTitle);
    ~List() {}

    int getId() const;
    void setId(int id);

    std::string getTitle() const;
    void setTitle(std::string title);

    void addReminder(Reminder &reminder);
};
