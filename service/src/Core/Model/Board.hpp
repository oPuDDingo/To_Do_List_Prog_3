#pragma once

#include "List.hpp"
#include <string>
#include <vector>

namespace ReminderApp {

namespace Core {

namespace Model {
class Board {
  private:
    std::string title;
    std::vector<List> lists;

  public:
    Board(std::string givenTitle);
    ~Board() {}

    std::string getTitle() const;

    std::vector<List> &getLists();
    void setLists(std::vector<List> const &lists);
};

} // namespace Model
} // namespace Core
} // namespace ReminderApp
