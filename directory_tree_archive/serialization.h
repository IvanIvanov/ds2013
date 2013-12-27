// A library for serializing and deserializing directory trees from and
// into the filesystem.
#ifndef SERIALIZATION_H_
#define SERIALIZATION_H_

#include "read_write_streams.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

// Creates a deep archive of the contents of "base_directory" and
// stores the resulting archive in "archive_filename". The function
// returns true on success and false on failure.
bool ArchiveDirectoryTree(const string& base_directory,
                          const string& archive_filename);

// Extracts an existing archive specified by "archive_filename" and dumps
// the resulting directory tree in the "base_directory" directory. The
// function returns true on success and false on failure.
bool ExtractDirectoryTree(const string& base_directory,
                          const string& archive_filename);

// Converts the deep contents "base_directory" into a flat sequence of bytes.
// The bytes are written to "write_stream". The function returns true on
// success and false on failure.
bool Serialize(const string& base_directory, WriteStream* write_stream);

// Converts the names and contents of all files in "filenames" into a sequence
// of bytes. The bytes are written to "write_stream". The names of all files
// in "filenames" are relative to "base_directory". The function returns true
// on success and false on failure.
bool SerializeFiles(const vector<string>& filenames,
                    const string& base_directory,
                    WriteStream* write_stream);

// Converts the names of all directories in "directories" into a sequence of
// bytes. The bytes are written to "write_stream". The function returns true
// on success and false on failure.
bool SerializeDirectories(const vector<string>& directories,
                          WriteStream* write_stream);

// Converts the name and content of the file "filename" into a sequence of
// bytes. The bytes are written to "write_stream". The name of the file is
// given relative to "base_directory". The function returns true on success
// and false on failure. 
bool SerializeFile(const string& filename,
                   const string& base_directory,
                   WriteStream* write_stream);

// Converts the name of the directory "directory_name" into a sequence of
// bytes. The bytes are written to "write_stream". The function returns
// true on success and false on failure.
bool SerializeDirectory(const string& directory_name,
                        WriteStream* write_stream);

// Converts the sequence of bytes from "read_stream" into a corresponding
// directory tree. The directory tree is dumped into the "base_directory"
// directory. The function returns true on success and false on failure.
bool Deserialize(const string& base_directory, ReadStream* read_stream);

// Converts the sequence of bytes from "read_stream" into a set of files.
// The files are created relative to the "base_directory" directory.
// The function returns true on success and false on failure.
bool DeserializeFiles(const string& base_directory, ReadStream* read_stream);

// Converts the sequence of bytes from "read_stream" into a set of directories.
// The directories are created relative to the "base_directory" directory.
// The function returns true on success and false on failure.
bool DeserializeDirectories(const string& base_directory,
                            ReadStream* read_stream);

// Converts the sequence of bytes from "read_stream" into a file. The file
// is created relative to the "base_directory" directory. The function returns
// true on success and false on failure.
bool DeserializeFile(const string& base_directory, ReadStream* read_stream);

// Converts the sequence of bytes from "read_stream" into a directory. The
// directory is created relative to the "base_directory" directory. The
// function returns true on success and false on failure.
bool DeserializeDirectory(const string& base_directory,
                          ReadStream* read_stream);

#endif // SERIALIZATION_H_ 
