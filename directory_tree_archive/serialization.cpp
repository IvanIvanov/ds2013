// This file contains implementations of the functions in "serialization.h".
//
// The binary format for encoding a directory tree is defined as follows:
//
// The encoding for a directory tree is divided into two parts:
//   1) Directories - encodes all the directories inside the directory tree.
//   2) Files - encodes all the files inside the directory tree. 
//
//                _______________________
//               |                      |
//               |      Directories     |
//               |______________________|
//               |                      |
//               |        Files         |
//               |______________________|
//
//
// The encoding of the "Directories" section begins with 4 bytes representing
// an unsigned 32 bit integer (n) that specifies the number of directories that
// are encoded. Then follow n entries with one entry for each directory. It is
// guaranteed that the encodings for parent directories will always appear
// before the encodings for child directories.
//
//           _______________________________
//          |       |       |       |       |
//      n:  | byte1 | byte2 | byte3 | byte4 |
//          |_______|_______|_______|_______|
//
//           ____________________________________
//          |                                    |
// entry_1: |  Encoding for directory entry....  |
//          |____________________________________|
// 
// ...............................................
// ...............................................
//           ____________________________________
//          |                                    |
// entry_n: |  Encoding for directory entry....  |
//          |____________________________________|
//
// Each entry encodes the name of a directory. The encoding starts with 4 bytes
// representing an unsigned 32 bit integer (n) that specifies the length in
// bytes of the name of the directory followed by that many bytes encoding
// the different characters of the name.
//
//           ____________________________________________________
//          | byte1 | byte2 | byte3 | byte4 |                    |
//   entry: |   n   |   n   |   n   |   n   | Name bytes ....    |
//          |_______|_______|_______|_______|____________________|
//
//
// The encoding of the "Files" section begins with 4 bytes representing
// an unsigned 32 bit integer (n) that specifies the number of files that
// are encoded. Then follow n entries with one entry for each file.
//
//           _______________________________
//          |       |       |       |       |
//      n:  | byte1 | byte2 | byte3 | byte4 |
//          |_______|_______|_______|_______|
//
//           _______________________________
//          |                               |
// entry_1: |  Encoding for file entry....  |
//          |_______________________________|
// 
// ...............................................
// ...............................................
//           _______________________________
//          |                               |
// entry_n: |  Encoding for file entry....  |
//          |_______________________________|
//
//
// Each entry encodes the name of a file followed by it's contents. The
// encoding starts with 4 bytes representing an unsigned 32 bit integer (n)
// that specifies the length in bytes of the name of the file followed by that
// many bytes encoding the different characters of the name. This is followed
// by 4 bytes representing an unsigned 32 bit integer (m) that specifies the
// number of bytes that the file contains. And finally follow m bytes with the
// contents of the file.
//
//           ____________________________________________________
//          | byte1 | byte2 | byte3 | byte4 |                    |
//   entry: |   n   |   n   |   n   |   n   | Name bytes ....    |
//          |_______|_______|_______|_______|____________________|
//           ____________________________________________________
//          | byte1 | byte2 | byte3 | byte4 |                    |
//          |   m   |   m   |   m   |   m   | Content bytes .... |
//          |_______|_______|_______|_______|____________________|
//
// All unsigned 32 bit integers used in the encodings have their bytes ordered
// using big-endian ordering.
//
#include "filesystem.h"
#include "read_write_streams.h"
#include "serialization.h"
#include <cstdlib>
#include <string>
#include <vector>

using std::string;
using std::vector;

bool ArchiveDirectoryTree(const string& base_directory,
                          const string& archive_filename) {
  FileWriteStream write_stream(archive_filename);
  bool success = Serialize(base_directory, &write_stream);
  write_stream.Flush();
  return success;
}

bool ExtractDirectoryTree(const string& base_directory,
                          const string& archive_filename) {
  FileReadStream read_stream(archive_filename);
  return Deserialize(base_directory, &read_stream);
}

bool Serialize(const string& base_directory, WriteStream* write_stream) {
  if (!IsValid(base_directory)) {
    return false;
  }

  // Get all files and directories contained in base_directory.
  vector<string> files_and_directories;
  GetFilesAndDirectoriesRecursive(base_directory, files_and_directories);

  // Separate files and directories and store their
  // names relative to base_directory.
  vector<string> files;
  vector<string> directories;
  for (int i = 0; i < files_and_directories.size(); i++) {
    string name = StripBasePath(
        files_and_directories[i], StripLastPathComponent(base_directory));
    if (IsFile(files_and_directories[i])) {
      files.push_back(name);
    } else {
      directories.push_back(name);
    }
  }

  if (!SerializeDirectories(directories, write_stream)) return false;
  if (!SerializeFiles(files, base_directory, write_stream)) return false;

  return true;
}

bool SerializeFiles(const vector<string>& filenames,
                    const string& base_directory,
                    WriteStream* write_stream) {
  unsigned int n = (unsigned int) filenames.size();
  if (!write_stream->WriteUnsignedInt32(n)) return false;
  for (int i = 0; i < filenames.size(); i++) {
    if (!SerializeFile(filenames[i], base_directory, write_stream)) {
      return false;
    }
  }
  return true;
}

bool SerializeDirectories(const vector<string>& directories,
                          WriteStream* write_stream) {
  unsigned int n = (unsigned int) directories.size();
  if (!write_stream->WriteUnsignedInt32(n)) return false;
  for (int i = 0; i < (int) directories.size(); i++) {
    if (!SerializeDirectory(directories[i], write_stream)) return false;
  }
  return true;
}

bool SerializeFile(const string& filename,
                   const string& base_directory,
                   WriteStream* write_stream) {
  // Serialize file name.
  unsigned int length = (unsigned int) filename.size();
  if (!write_stream->WriteUnsignedInt32(length)) return false;
  for (int i = 0; i < (int) length; i++) {
    if (!write_stream->WriteByte(filename[i])) return false;
  }

  // Serialize file contents.
  string full_name = StripLastPathComponent(base_directory) + "\\" + filename;
  FileReadStream read_stream(full_name);
  unsigned int bytes = read_stream.Bytes();
  if (!write_stream->WriteUnsignedInt32(bytes)) return false;
  read_stream.Reset();
  while (bytes > 0) {
    char byte;
    if (!read_stream.ReadByte(byte)) return false;
    if (!write_stream->WriteByte(byte)) return false;
    bytes--;
  }
  return true;
}

bool SerializeDirectory(const string& directory_name,
                        WriteStream* write_stream) { 
  unsigned int length = (unsigned int) directory_name.size();
  write_stream->WriteUnsignedInt32(length);
  for (int i = 0; i < (int) length; i++) {
    write_stream->WriteByte(directory_name[i]);
  }
  return true;
}

bool Deserialize(const string& base_directory, ReadStream* read_stream) {
  if (!DeserializeDirectories(base_directory, read_stream)) return false;
  if (!DeserializeFiles(base_directory, read_stream)) return false;
  return true;
}

bool DeserializeFiles(const string& base_directory, ReadStream* read_stream) {
  unsigned int n;
  if (!read_stream->ReadUnsignedInt32(n)) return false; 
  for (int i = 0; i < (int) n; i++) {
    if (!DeserializeFile(base_directory, read_stream)) return false;
  }
  return true;
}

bool DeserializeDirectories(const string& base_directory,
                            ReadStream* read_stream) {
 
  // Make sure that the target base directory is empty.

  // Delete the target base directory.
  string command = "rmdir /S /Q \"" + base_directory + "\" 2>null";
  system(command.c_str());

  // Create an empty target base directory.
  command = "mkdir \"" + base_directory + "\"";
  system(command.c_str());

  unsigned int n;
  if (!read_stream->ReadUnsignedInt32(n)) return false;
  for (int i = 0; i < (int) n; i++) {
    if (!DeserializeDirectory(base_directory, read_stream)) return false;
  }
  return true;
}

bool DeserializeFile(const string& base_directory, ReadStream* read_stream) {
  unsigned int length;
  if (!read_stream->ReadUnsignedInt32(length)) return false;
  string filename;
  for(int i = 0; i < (int) length; i++) {
    char byte;
    if (!read_stream->ReadByte(byte)) return false;
    filename += byte;
  }
  filename = base_directory + "\\" + filename;

  unsigned int bytes;
  if (!read_stream->ReadUnsignedInt32(bytes)) return false;
  FileWriteStream write_stream(filename);
  while (bytes > 0) {
    char byte;
    if (!read_stream->ReadByte(byte)) return false;
    if (!write_stream.WriteByte(byte)) return false;
    bytes--;
  }
  write_stream.Flush();
  return true;
}

bool DeserializeDirectory(const string& base_directory,
                          ReadStream* read_stream) {
  unsigned int length;
  if (!read_stream->ReadUnsignedInt32(length)) return false;
  string directory_name;
  for (int i = 0; i < (int) length; i++) {
    char byte;
    if (!read_stream->ReadByte(byte)) return false;
    directory_name += byte;
  }

  directory_name = base_directory + "\\" + directory_name;
  string command = "mkdir \"" + directory_name + "\"";
  if (system(command.c_str())) return false;

  return true;
}
