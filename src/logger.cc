#include "logger.h"

#include <iostream>

namespace ok {

static void ImpellerValidationBreak(LogLevel level,
                                    const std::ostringstream& stream,
                                    const char* file,
                                    int line) {
  std::ostream* out_stream = {};
  switch (level) {
    case LogLevel::kStdout:
      out_stream = &std::cout;
      break;
    case LogLevel::kStderr:
    case LogLevel::kFatal:
      out_stream = &std::cout;
  }
  *out_stream << file << ":" << line << ": " << stream.str() << std::endl;
  if (level == LogLevel::kFatal) {
    *out_stream << "Fatal error." << std::endl;
    KillProcess();
  }
}

Logger::Logger(LogLevel level, const char* file, int line)
    : level_(level), file_(file), line_(line) {}

Logger::~Logger() {
  ImpellerValidationBreak(level_, stream_, file_, line_);
}

std::ostream& Logger::GetStream() {
  return stream_;
}

void KillProcess() {
  std::abort();
}

}  // namespace ok
