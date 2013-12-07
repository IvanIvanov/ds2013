#include "utils.h"
#include "filesystem.h"

#include <map>
#include <string>
#include <vector>

using std::map;
using std::string;
using std::vector;

void GroupIntoEquivalenceClasses(
    const string& base_directory,
    map<string, vector<string> >& classes) {

  classes.clear();
  if (!IsDirectory(base_directory)) {
    return;
  }

  vector<string> files_and_directories;
  GetFilesAndDirectoriesRecursive(base_directory, files_and_directories);

  for (int i = 0; i < files_and_directories.size(); i++) {
    string& name = files_and_directories[i];
    if (IsFile(name)) {
      classes[ReadFileContents(name)].push_back(name);
    }
  }
}
