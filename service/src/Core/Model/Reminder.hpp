#pragma once

#include <string>

class Reminder {
  private:
    int id;
    std::string title;
    std::string timestamp;

  public:
    Reminder(int id, std::string givenTitle, std::string givenTimestamp);
    ~Reminder(){};

    int getId() const;
    std::string getTitle() const;
    std::string getTimestamp() const;

    void setID(int id);
    void setTitle(std::string title);
    void setTimestamp(std::string time);
};
