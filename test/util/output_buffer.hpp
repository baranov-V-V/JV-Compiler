#pragma once

#include <cstring>

class OutputBuffer {
 public:
  static const int buf_size = 1024;

  OutputBuffer();
  ~OutputBuffer();

  char* Data();

  OutputBuffer(const OutputBuffer&) = delete;
  OutputBuffer(OutputBuffer&&) noexcept = default;

  OutputBuffer& operator=(const OutputBuffer&) = delete;
  OutputBuffer& operator=(OutputBuffer&&) noexcept = default;

 private:
  char* buf;
};