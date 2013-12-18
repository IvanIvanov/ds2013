#ifndef READ_WRITE_STREAM_H
#define READ_WRITE_STREAM_H

#include <fstream>
#include <string>

#define STREAM_BUFFER_SIZE 4096

using std::ifstream;
using std::ofstream;
using std::string;

// A binary stream of data that can be read bit by bit or byte by byte or
// 32 bit unsigned integer by 32 bit unsigned integer or by any combination
// of the above. Concrete stream classes can read data from files, in-memory
// representations, networks, databases or other sources. The "Read*" methods
// return true if the read operation is successful or false otherwise.
class ReadStream {
public:
  virtual ~ReadStream() {}
  virtual bool ReadBit(char& bit) = 0;
  virtual bool ReadByte(char& byte) = 0;
  virtual bool ReadUnsignedInt32(unsigned int& value) = 0;
  virtual bool Reset() = 0; //Resets the stream to it's beginning.
  virtual unsigned int Bytes() = 0; // The number of bytes in the stream.
};

// A concrete ReadStream that reads binary data stored in-memory and
// represented as a string. The string is treated as a sequence of bytes
// with the i-th byte being the i-th character in the string.
class StringReadStream : public ReadStream {
public:
  StringReadStream(string byte_string);
  virtual ~StringReadStream();
  virtual bool ReadBit(char& bit);
  virtual bool ReadByte(char& byte);
  virtual bool ReadUnsignedInt32(unsigned int& value);
  virtual bool Reset();
  virtual unsigned int Bytes();
private:
  string byte_string_;
  unsigned int bit_index_;
  unsigned int total_bits_;
};

// A concrete ReadStream that reads binary data stored in a file.
// Reading data from the file is optimized by buffering.
class FileReadStream : public ReadStream {
public:
  FileReadStream(const string& filename);
  virtual ~FileReadStream();
  virtual bool ReadBit(char& bit);
  virtual bool ReadByte(char& byte);
  virtual bool ReadUnsignedInt32(unsigned int& value);
  virtual bool Reset();
  virtual unsigned int Bytes();
private:
  string filename;
  char* buffer_;
  ifstream file_stream_;
  unsigned int bit_index_;
  unsigned int total_bits_;
};

// A binary stream of data that can be written bit by bit or byte by byte or
// 32 bit unsigned integer by 32 bit unsigned integer or by any combination
// of the above. Concrete stream classes can write data to files, in-memory
// representations, networks, databases or other sources. The "Write*" methods
// return true if the write operation is successful or false otherwise.
class WriteStream {
public:
  virtual ~WriteStream() {}
  virtual bool WriteBit(char bit) = 0;
  virtual bool WriteByte(char byte) = 0;
  virtual bool WriteUnsignedInt32(unsigned int value) = 0;
  virtual bool Flush() = 0; // Forces a write to all written data.
};

// A concrete WriteStream that writes binary data to a string stored
// in-memory. The string is treated as a sequence of bytes with the
// i-th byte being the i-th character in the string.
class StringWriteStream : public WriteStream {
public:
  StringWriteStream();
  virtual ~StringWriteStream();
  virtual string GetString();
  virtual bool WriteBit(char bit);
  virtual bool WriteByte(char byte);
  virtual bool WriteUnsignedInt32(unsigned int value);
  virtual bool Flush();
private:
  string byte_string_;
  unsigned int bit_index_;
  unsigned int total_bits_;
};

// A concrete WriteStream that writes binary data into a file.
// Writing data to the file is optimized by buffering.
class FileWriteStream : public WriteStream {
public:
  FileWriteStream(const string& filename);
  virtual ~FileWriteStream();
  virtual bool WriteBit(char bit);
  virtual bool WriteByte(char byte);
  virtual bool WriteUnsignedInt32(unsigned int value);
  virtual bool Flush();
private:
  string filename_;
  char* buffer_;
  ofstream file_stream_;
  unsigned int bit_index_;
  unsigned int total_bits_;
};

#endif // READ_WRITE_STREAM_H
