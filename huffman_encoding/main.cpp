#include "huffman.h"
#include <iostream>
#include <string>

using namespace std;

void CompressStringTest() {
  string input = "This is a test string!";
  string compressed;
  string decompressed;
  HuffmanEncodeString(input, compressed);
  HuffmanDecodeString(compressed, decompressed);

  // Check if the strings are equal.
  if (input == decompressed) {
    cout << "The strings are equal." << endl;
  } else {
    cout << "The strings are not equal." << endl;
  }
}

void CompressFileTest(const string& input_file, const string& output_file) {
  string compressed_file = input_file + "__compressed";
  HuffmanEncodeFile(input_file, compressed_file);
  HuffmanDecodeFile(compressed_file, output_file);
}

// A small driver program that demonstrates the Huffman encoding API.
int main(int argc, char* argv[]) {
  if (argc == 3) {
    string input_file = argv[1];
    string output_file = argv[2];
    CompressFileTest(input_file, output_file);
  } else {
    CompressStringTest();
  }
  return 0;
}
