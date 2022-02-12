#pragma once

#include <string>
namespace ReminderApp {

namespace Core {

namespace Model {
class Reminder {
  private:
    int id;
    std::string title;
    std::string date;

  public:
    Reminder(int id, std::string givenTitle, std::string givenDate);
    ~Reminder(){};

    int getId() const;
    std::string getTitle() const;
    std::string getDate() const;

    void setID(int id);
    void setTitle(std::string title);
    void setDate(std::string time);
};

} // namespace Model
} // namespace Core
} // namespace ReminderApp
