#include "Board.hpp"

using namespace ReminderApp::Core::Model;

Board::Board(std::string givenTitle) : title(givenTitle) {}

std::string Board::getTitle() const {
    return title;
}

std::vector<List> &Board::getLists() {
    return lists;
}

void Board::setLists(std::vector<List> const &lists) {
    this->lists = lists;
}
