#include "filesystem.h"
#include "serialization.h"
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

void ArchiveAndExtractExample(const string& base_directory,
                              const string& tmp_directory) {
  if (!IsValid(base_directory)) {
    cout << "Invalid directory: " << base_directory << endl;
    return;
  }

  if (!IsValid(tmp_directory)) {
    cout << "Invalid directory: " << base_directory << endl;
    return;
  }

  string archive_file = tmp_directory + "\\archive";
  string extract_directory = tmp_directory + "\\extract";

  if (!ArchiveDirectoryTree(base_directory, archive_file)) {
    cout << "Unable to archive the contents of: " << base_directory << endl;
    return;
  }

  if (!ExtractDirectoryTree(extract_directory, archive_file)) {
    cout << "Unable to extract the contents of: " << archive_file << endl;
    return;
  }

  cout << "Archive and extract completed." << endl;
}

// A small driver program that demonstrates the archive and extraction API.
//
// The program expects two command line arguments that specify a directory to
// be archived and another existing temporary directory in which to store the
// created archive and it's extracted contents.
int main(int argc, char* argv[]) {
  if (argc == 3) {
    string base_directory = argv[1];
    string tmp_directory = argv[2];
    ArchiveAndExtractExample(base_directory, tmp_directory);
  } else {
    cout << "Please specify a directory to be archived " 
         << "and a temporary directory in which to dump the archive file "
         << "and the result of extracting it's contents."
         << endl;
  }
  system("pause");
  return 0;
}
