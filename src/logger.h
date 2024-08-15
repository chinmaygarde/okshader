#pragma once

#include <functional>
#include <sstream>

#include "macros.h"

namespace ok {

enum class LogLevel {
  kStdout,
  kStderr,
  kFatal,
};

class Logger {
 public:
  Logger(LogLevel level, const char* file, int line);

  ~Logger();

  std::ostream& GetStream();

 private:
  const LogLevel level_;
  const char* file_ = nullptr;
  int line_ = 0;
  std::ostringstream stream_;

  OK_DISALLOW_COPY_ASSIGN_AND_MOVE(Logger);
};

#define OK_LOG \
  ::ok::Logger{ok::LogLevel::kStdout, __FILE__, __LINE__}.GetStream()

#define OK_ERROR \
  ::ok::Logger{ok::LogLevel::kStderr, __FILE__, __LINE__}.GetStream()

#define OK_CHECK(condition)                           \
  {                                                   \
    if (!(condition)) [[unlikely]] {                  \
      OK_ERROR << "Condition failed: " << #condition; \
      KillProcess();                                  \
    }                                                 \
  }

[[noreturn]] void KillProcess();

#define OK_UNREACHABLE                              \
  {                                                 \
    OK_LOG << "Reached unreachable code. Goodbye."; \
    KillProcess();                                  \
  }

}  // namespace ok
