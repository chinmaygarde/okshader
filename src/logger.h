#pragma once

#include <functional>
#include <sstream>

#include "macros.h"

namespace ok {

class Logger {
 public:
  Logger(const char* file, int line);

  ~Logger();

  std::ostream& GetStream();

 private:
  const char* file_ = nullptr;
  int line_ = 0;
  std::ostringstream stream_;

  OK_DISALLOW_COPY_ASSIGN_AND_MOVE(Logger);
};

#define OK_LOG ::ok::Logger{__FILE__, __LINE__}.GetStream()

}  // namespace ok
