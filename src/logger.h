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

#define OK_LOG_LEVEL(level) \
  ::ok::Logger{(level), __FILE__, __LINE__}.GetStream()

#define OK_LOG OK_LOG_LEVEL(::ok::LogLevel::kStdout)
#define OK_ERROR OK_LOG_LEVEL(ok::LogLevel::kStderr)
#define OK_FATAL OK_LOG_LEVEL(ok::LogLevel::kFatal)

#define OK_CHECK(condition)                           \
  {                                                   \
    if (!(condition)) [[unlikely]] {                  \
      OK_ERROR << "Condition failed: " << #condition; \
      KillProcess();                                  \
    }                                                 \
  }

#ifndef NDEBUG
#define OK_DCHECK OK_CHECK
#else  // NDEBUG
#define OK_DCHECK(condition) ((void)(condition));
#endif  // NDEBUG

[[noreturn]] void KillProcess();

#define OK_UNREACHABLE                              \
  {                                                 \
    OK_LOG << "Reached unreachable code. Goodbye."; \
    KillProcess();                                  \
  }

#define OK_UNIMPLEMENTED \
  { OK_FATAL << "Unimplemented"; }

}  // namespace ok
