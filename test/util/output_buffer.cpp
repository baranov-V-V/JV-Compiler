#include "output_buffer.hpp"

OutputBuffer::OutputBuffer() {
  buf = new char[buf_size];
  memset(buf, 0, buf_size);
}

OutputBuffer::~OutputBuffer() {
  delete[] buf;
}

char* OutputBuffer::Data() {
  return buf;
}