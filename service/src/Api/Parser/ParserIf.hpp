#pragma once

#include <string>

namespace ReminderApp::Api::Parser {

class ParserIf {
  public:
    virtual ~ParserIf() {}

    virtual std::string getEmptyResponseString() = 0;
};

} // namespace Reminder
