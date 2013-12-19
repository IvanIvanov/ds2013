#include "read_write_streams.h"

#include <string>

using std::string;

StringReadStream::StringReadStream(string byte_string) {
  this->byte_string_ = byte_string;
  this->bit_index_ = 0;
  this->total_bits_ = (unsigned int) byte_string_.size() * 8;
}

StringReadStream::~StringReadStream() {
}

bool StringReadStream::ReadBit(char& bit) {
  if (bit_index_ >= total_bits_) {
    return false;
  }
  char byte = byte_string_[bit_index_ >> 3];
  bit = ((byte >> (7 - (bit_index_ & 7))) & 1);
  bit_index_++;
  return true;
}

bool StringReadStream::ReadByte(char& byte) {
  byte = 0;
  for (int i = 7; i >= 0; i--) {
    char bit;
    if (!ReadBit(bit)) {
      return false;
    }
    if (bit) {
      byte |= (1 << i);
    }
  }
  return true;
}

bool StringReadStream::ReadUnsignedInt32(unsigned int& value) {
  value = 0;
  for (int i = 0; i < 4; i++) {
    char byte;
    if (!ReadByte(byte)) {
      return false;
    }
    value = (value << 8) | ((unsigned char) byte);
  }
  return true;
}

bool StringReadStream::Reset() {
  bit_index_ = 0;
  return true;
}

unsigned int StringReadStream::Bytes() {
  Reset();
  unsigned int bytes = 0;
  while (true) {
    char byte;
    if (!ReadByte(byte)) {
      break;
    }
    bytes++;
  }
  return bytes;
}

FileReadStream::FileReadStream(const string& filename) {
  this->filename= filename;
  this->buffer_ = new char[STREAM_BUFFER_SIZE];
  this->file_stream_.clear();
  this->file_stream_.open(filename.c_str(), std::ifstream::binary);
  this->bit_index_ = 0;
  this->total_bits_ = 0;
}

FileReadStream::~FileReadStream() {
  file_stream_.close();
  delete [] buffer_;
}

bool FileReadStream::ReadBit(char& bit) {
  if (bit_index_ >= total_bits_) {
    file_stream_.read(buffer_, STREAM_BUFFER_SIZE);
    total_bits_ = (unsigned int) file_stream_.gcount() * 8;
    bit_index_ = 0;
    if (total_bits_ == 0) {
      return false;
    }
  }
  char byte = buffer_[bit_index_ >> 3];
  bit = ((byte >> (7 - (bit_index_ & 7))) & 1);
  bit_index_++;
  return true;
}

bool FileReadStream::ReadByte(char& byte) {
  byte = 0;
  for (int i = 7; i >= 0; i--) {
    char bit;
    if (!ReadBit(bit)) {
      return false;
    }
    if (bit) {
      byte |= (1 << i);
    }
  }
  return true;
}

bool FileReadStream::ReadUnsignedInt32(unsigned int& value) {
  value = 0;
  for (int i = 0; i < 4; i++) {
    char byte;
    if (!ReadByte(byte)) {
      return false;
    }
    value = (value << 8) | ((unsigned char) byte);
  }
  return true;
}

bool FileReadStream::Reset() {
  file_stream_.close();
  file_stream_.clear();
  file_stream_.open(filename.c_str(), std::ifstream::binary);
  bit_index_ = 0;
  total_bits_ = 0;
  return true;
}

unsigned int FileReadStream::Bytes() {
  Reset();
  unsigned int bytes = 0;
  while (true) {
    char byte;
    if (!ReadByte(byte)) {
      break;
    }
    bytes++;
  }
  return bytes;
}

StringWriteStream::StringWriteStream() {
  this->byte_string_ = "";
  this->bit_index_ = 0;
  this->total_bits_ = 0;
}

StringWriteStream::~StringWriteStream() {
}

string StringWriteStream::GetString() {
  return byte_string_;
}

bool StringWriteStream::WriteBit(char bit) {
  if (bit_index_ >= total_bits_) {
    byte_string_ += string(1, (char)0);
    total_bits_ += 8;
  }
  char& byte = byte_string_[bit_index_ >> 3];
  int bit_pos = 7 - (bit_index_ & 7);
  if (((byte >> bit_pos) & 1) != bit) {
    byte ^= (1 << bit_pos);
  }
  bit_index_++;
  return true;
}

bool StringWriteStream::WriteByte(char byte) {
  for (int i = 7; i >= 0; i--) {
    char bit = ((byte >> i) & 1);
    WriteBit(bit);
  }
  return true;
}

bool StringWriteStream::WriteUnsignedInt32(unsigned int value) {
  for (int i = 3; i >= 0; i--) {
    char byte = ((value >> (8 * i)) & 255);
    WriteByte(byte);
  }
  return true;
}

bool StringWriteStream::Flush() {
  return true;
}

FileWriteStream::FileWriteStream(const string& filename) {
  this->filename_ = filename;
  this->buffer_ = new char[STREAM_BUFFER_SIZE];
  this->file_stream_.open(filename.c_str(), std::ofstream::binary);
  this->bit_index_ = 0;
  this->total_bits_ = STREAM_BUFFER_SIZE * 8;
}

FileWriteStream::~FileWriteStream() {
  file_stream_.close();
  delete [] buffer_;
}

bool FileWriteStream::WriteBit(char bit) {
  if (bit_index_ >= total_bits_) {
    file_stream_.write(buffer_, STREAM_BUFFER_SIZE);
    bit_index_ = 0;
  }
  char& byte = buffer_[bit_index_ >> 3];
  int bit_pos = 7 - (bit_index_ & 7);
  if (((byte >> bit_pos) & 1) != bit) {
    byte ^= (1 << bit_pos);
  }
  bit_index_++;
  return true;
}

bool FileWriteStream::WriteByte(char byte) {
  for (int i = 7; i >= 0; i--) {
    char bit = ((byte >> i) & 1);
    WriteBit(bit);
  }
  return true;
}

bool FileWriteStream::WriteUnsignedInt32(unsigned int value) {
  for (int i = 3; i >= 0; i--) {
    char byte = ((value >> (8 * i)) & 255);
    WriteByte(byte);
  }
  return true;
}

bool FileWriteStream::Flush() {
  unsigned int bytes = (bit_index_ + 7) / 8;
  file_stream_.write(buffer_, bytes);
  file_stream_.flush();
  return true;
}
