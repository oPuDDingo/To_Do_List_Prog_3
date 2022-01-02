#include "Manager.hpp"
#include <iostream>

using namespace ReminderApp::Core;
using namespace ReminderApp::Api::Parser;
using namespace ReminderApp::Repository;
using namespace std;

Manager::Manager(ParserIf &givenParser, RepositoryIf &givenRepository)
    : parser(givenParser), repository(givenRepository) {
}

Manager::~Manager() {
}
