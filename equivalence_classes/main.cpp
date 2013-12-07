// To compile and run this program be sure to add the .h and .cpp
// files from the filesystem_lib directory.

#include "filesystem.h"
#include "utils.h"

#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

// An example program that receives an absolute or relative path to a base
// directory and groups all files directly or indirectly contained in it
// forming equivalence classes with files of the same content.
//
// To pass command line arguments from Visual Studio:
//
// 1. In Solution Explorer, right-click the project, and then click Properties.
//
// 2. In Solution Explorer, right-click the project, and then click Properties.
//
// 3. Open the Configuration Properties folder, and then click Debug.
//
// 4. In the Command Line Arguments property, type the command-line parameters,
//    and click OK.
//
// It is advisable to try out the program on a directory that does not contain
// very large files or files with non-ASCII names.
int main(int argc, char* argv[]) {
  string error_message =
      "Please enter the absolute or relative path to a directory.";

  // Parse the command line arguments.
  if (argc != 2) {
    cout << error_message << endl;
    return 1;
  }
  string base_directory = string(argv[1]);
  if (!IsDirectory(base_directory)) {
    cout << error_message << endl;
    return 1;
  }

  // Find and print out equivalence class information.
  map<string, vector<string> > classes;
  GroupIntoEquivalenceClasses(base_directory, classes);

  int class_cnt = 0;
  for (map<string, vector<string> >::iterator it = classes.begin();
       it != classes.end();
       it++) {
    cout << "Equivalence class #" << (++class_cnt) << endl;
    vector<string>& filenames = it->second;
    for (int i = 0; i < filenames.size(); i++) {
      size_t bytes = FileSizeInBytes(filenames[i]);
      cout << filenames[i] << " (" << endl;
    }
    cout << endl;
  }
  return 0;
}
