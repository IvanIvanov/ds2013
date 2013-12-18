// A library for Huffman encoding and decoding of streams of binary data.
#ifndef HUFFMAN_H_
#define HUFFMAN_H_

#include "read_write_streams.h"

#include <map>
#include <string>

using std::map;
using std::string;

struct HuffmanNode;

// Encodes the contents of "input_file" and stores the result in "output_file".
// The encoding is done using a Huffman encoding scheme.
void HuffmanEncodeFile(const string& input_file, const string& output_file);

// Decodes the contents of "input_file" and stores the result in "output_file".
// It is assumed that "input_file" is the result of a Huffman encoding scheme.
void HuffmanDecodeFile(const string& input_file, const string& output_file);

// Encodes "input_data" and stores the result in "encoded_data". The encoding
// is done using a Huffman encoding scheme. The built-in string type is used to
// store arbitrary binary data with each character encoding a single byte of
// data.
void HuffmanEncodeString(const string& input_data, string& encoded_data); 

// Decodes "input_data" and stores the result in "decoded_data". It is
// assumed that "input_data" is the result of a Huffman encoding scheme.
// The built-in string type is used to store arbitrary binary data with
// each character encoding a single byte of data.
void HuffmanDecodeString(const string& input_data, string& decoded_data);

// Encodes the contents of "read_stream" and writes the results in
// "write_stream". The encoding is done using a Huffman encoding scheme. 
void HuffmanEncode(ReadStream* read_stream, WriteStream* write_stream);

// Decodes the contents of "read_stream" and writes the result in
// "write_stream". It is assumed that the data in "read_stream" is the
// result of a Huffman encoding scheme.
void HuffmanDecode(ReadStream* read_stream, WriteStream* write_stream);

// Takes a mapping from byte value to frequency of occurrence, serializes it and
// writes it to "write_stream".
void EncodeFrequencyTable(map<char, unsigned int>& frequencies,
                          WriteStream* write_stream);

// Reads in a serialized form of a mapping from byte value to frequency of
// occurrence from "read_stream" and stores the mapping in "frequencies".
void DecodeFrequencyTable(ReadStream* read_stream,
                          map<char, unsigned int>& frequencies);

// Encodes all the bytes from "read_stream" by using the mappings in
// "encoding_table" and writes the result in "write_stream". "Encoding_table"
// is a mapping from byte value to a string of "0"s and "1"s representing the
// sequence of bits in the encoding for the given byte.
void EncodeData(ReadStream* read_stream,
                map<char, string>& encoding_table,
                WriteStream* write_stream);

// Decodes the binary contents of "read_stream" assuming it is encoded with
// the Huffman tree with root "root". The result of the decoding is written
// to "write_stream".
void DecodeData(ReadStream* read_stream,
                HuffmanNode* root,
                WriteStream* write_stream);

// Builds a Huffman tree from a table mapping bytes to their number of
// occurrences.
HuffmanNode* BuildHuffmanTree(map<char, unsigned int>& frequencies);

// Deallocates the memory used for the Huffman tree rooted at "root".
void DeleteHuffmanTree(HuffmanNode* root);

// Computes the encoding table corresponding to the Huffman tree rooted at
// "root". An encoding table is a mapping from byte value to a string of "0"s
// and "1"s representing the sequence of bits for the given byte.
map<char, string> BuildEncodingTable(HuffmanNode* root);

// Computes the encoding table corresponding to the Huffman tree rooted at
// "root" by recursively traversing the tree and storing the history of left
// and right branches in "encoding". An encoding table is a mapping from byte
// value to a string of "0"s and "1"s representing the sequence of bits for the
// given byte.
void BuildEncodingTableRecursive(HuffmanNode* root,
                                 string encoding,
                                 map<char, string>& encoding_table);

// Reads in all the bytes from "read_stream" and returns a frequency table
// that maps each encountered byte to the number of times it occurs.
map<char, unsigned int> CalculateByteFrequencies(ReadStream* read_stream);

// A structure that models a Huffman tree node. The same structure is used
// both for leaf nodes and inner nodes of the Huffman tree.
struct HuffmanNode {
  bool leaf;
  char byte;
  unsigned int freq;
  HuffmanNode* left;
  HuffmanNode* right;

  HuffmanNode();

  // Leaf node constructor.
  HuffmanNode(char byte, unsigned int freq);

  // Inner node constructor.
  HuffmanNode(unsigned int freq, HuffmanNode* left, HuffmanNode* right);
};

// A functor for comparing two Huffman nodes. The comparison is done by largest
// frequency first.
struct HuffmanNodeCompare {
  bool operator () (const HuffmanNode* node1, const HuffmanNode* node2);
};

#endif // HUFFMAN_H_
