#ifndef UTILS_H_
#define UTILS_H_

#include <map>
#include <string>
#include <vector>

using std::map;
using std::string;
using std::vector;

// Recursively traverses the files in a base directory and creates a map
// from file contents to a vector of filenames. The contents of the files
// are represented as C++ strings where each character represents a byte
// from the file. This results in a grouping in which the names of all
// files with the same content are put into the same vector. 
void GroupIntoEquivalenceClasses(
    const string& base_directory,
    map<string, vector<string> >& classes);

#endif // UTILS_H_
