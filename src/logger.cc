#include "logger.h"

#include <iostream>

namespace ok {

static void ImpellerValidationBreak(const std::ostringstream& stream,
                                    const char* file,
                                    int line) {
  std::cout << file << ":" << line << ": " << stream.str() << std::endl;
}

Logger::Logger(const char* file, int line) : file_(file), line_(line) {}

Logger::~Logger() {
  ImpellerValidationBreak(stream_, file_, line_);
}

std::ostream& Logger::GetStream() {
  return stream_;
}

}  // namespace ok
