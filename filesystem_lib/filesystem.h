// A very basic Win32 based library for filesystem manipulation.
//
// TODO: add greater functionality.

#ifndef FILESYSTEM_H_
#define FILESYSTEM_H_

#include <string>
#include <vector>

#define BUFFER_SIZE 1024

using std::string;
using std::vector;

// Checks whether the given absolute or relative path is a valid file.
bool IsFile(const string& path);

// Checks whether the given absolute or relative path is a valid directory. 
bool IsDirectory(const string& path);

// Checks whether the given absolute or relative path actually exists in the
// filesystem.
bool IsValid(const string& path);

// If path has base_path as it's prefix the prefix is removed along with any
// leading forward or backward slashes. If path does not have base_path as
// it's prefix then the value of path is returned.
string StripBasePath(const string& path, const string& base_path);

// Reads a file given by a absolute or relative path by treating it's
// contents as binary bytes and packs them in a string which is returned.
string ReadFileContents(const string& filename);

// Returns the number of bytes the given file contains.
size_t FileSizeInBytes(const string& filename);

// Returns the names of all files and directories directly contained in a
// given directory specified by its absolute or relative path.
vector<string> GetFilesAndDirectoriesFlat(const string& directory);

// Returns the names of all files and directories directly or indirectly
// (recursively) contained in a given directory specified by it's absolute
// or relative path. The names are stored in the output parameter:
// files_and_directories and are included using an in-order traversal of
// the filesystem.
void GetFilesAndDirectoriesRecursive(
    const string& base_path,
    vector<string>& files_and_directories);

#endif // FILESYSTEM_H_
