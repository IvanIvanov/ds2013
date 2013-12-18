// This file contains implementations of the functions in "huffman.h".
//
// The binary format used for Huffman encoded data is defined as follows:
//
// Encoded data is divided into two parts:
//   1) Header - contains the necessary data to construct a Huffman tree.
//   2) Body - the binary data that has been encoded with the Huffman tree
//             encoded in the Header.
//
//               ______________
//              |              |
//              |    Header    |
//              |______________|
//              |              |
//              |     Body     |
//              |______________|
//
// The header encodes a frequency table mapping bytes to the frequencies
// that they occur. The encoding of the frequency table starts with 4 bytes
// representing an unsigned 32 bit integer (n) that specifies the number of
// entries in the table. Then follow n entries. Each entry is encoded as a
// byte value followed by 4 bytes (representing an unsigned 32 bit integer)
// that specify the number of occurrences of the entry's byte. The bytes
// in the unsigned 32 bit integers are encoded using big-endian ordering. 
//
//           ___________________________________
//          |        |        |        |        |
//       n: | byte1  | byte2  | byte3  | byte4  |
//          |________|________|________|________|
//           ____________________________________________
//          |        | byte1  | byte2  | byte3  | byte4  |
// entry_1: | byte   |   #    |   #    |   #    |   #    |
//          |________|________|________|________|________|
//
// .......................................................
// .......................................................
//
//           ____________________________________________
//          |        | byte1  | byte2  | byte3  | byte4  |
// entry_n: | byte   |   #    |   #    |   #    |   #    |
//          |________|________|________|________|________|
//
// The body starts with 4 bytes representing an unsigned 32 bit integer (n)
// that specifies the number of bytes of data before Huffman encoding.  
// This is followed by a sequence of bits that encodes exactly n bytes.
// This sequence is obtained by concatenating the corresponding Huffman bit
// sequences for each byte of the pre-encoded data. It is possible that this
// bit sequence will not completely fill the last byte. In such a case the
// left over bits will be filled with "0"s.
//
//           ___________________________________________________________
//          | byte1  | byte2  | byte3  | byte4  |                       |
//    body: |   n    |   n    |   n    |   n    |  Encoded bits .....   |
//          |________|________|________|________|_______________________|
//
#include "huffman.h"
#include <cstdlib>
#include <fstream>
#include <queue>
#include <vector>

using std::map;
using std::priority_queue;
using std::string;
using std::vector;

void HuffmanEncodeFile(const string& input_file, const string& output_file) {
  FileReadStream* read_stream = new FileReadStream(input_file);
  FileWriteStream* write_stream = new FileWriteStream(output_file);
  HuffmanEncode(read_stream, write_stream);
  delete read_stream;
  delete write_stream;
}

void HuffmanDecodeFile(const string& input_file, const string& output_file) {
  FileReadStream* read_stream = new FileReadStream(input_file);
  FileWriteStream* write_stream = new FileWriteStream(output_file);
  HuffmanDecode(read_stream, write_stream);
  delete read_stream;
  delete write_stream;
}

void HuffmanEncodeString(const string& data, string& encoded_data) {
  StringReadStream* read_stream = new StringReadStream(data);
  StringWriteStream* write_stream = new StringWriteStream();
  HuffmanEncode(read_stream, write_stream);
  encoded_data = write_stream->GetString();
  delete read_stream;
  delete write_stream;
}

void HuffmanDecodeString(const string& data, string& decoded_data) {
  StringReadStream* read_stream = new StringReadStream(data);
  StringWriteStream* write_stream = new StringWriteStream();
  HuffmanDecode(read_stream, write_stream);
  decoded_data = write_stream->GetString();
  delete read_stream;
  delete write_stream;
}

void HuffmanEncode(ReadStream* read_stream, WriteStream* write_stream) {
  map<char, unsigned int> frequencies = CalculateByteFrequencies(read_stream);
  HuffmanNode* root = BuildHuffmanTree(frequencies);
  map<char, string> encoding_table = BuildEncodingTable(root);
  EncodeFrequencyTable(frequencies, write_stream);
  EncodeData(read_stream, encoding_table, write_stream);
  DeleteHuffmanTree(root);
  write_stream->Flush();
}

void HuffmanDecode(ReadStream* read_stream, WriteStream* write_stream) {
  map<char, unsigned int> frequencies;
  DecodeFrequencyTable(read_stream, frequencies);
  HuffmanNode* root = BuildHuffmanTree(frequencies);
  DecodeData(read_stream, root, write_stream);
  DeleteHuffmanTree(root);
  write_stream->Flush();
}

void EncodeFrequencyTable(map<char, unsigned int>& frequencies,
                          WriteStream* write_stream) {
  unsigned int elements = frequencies.size();
  write_stream->WriteUnsignedInt32(elements);
  for (map<char, unsigned int>::iterator it = frequencies.begin();
      it != frequencies.end();
      it++) {
    write_stream->WriteByte(it->first);
    write_stream->WriteUnsignedInt32(it->second);
  }
}

void DecodeFrequencyTable(ReadStream* read_stream,
                          map<char, unsigned int>& frequency_table) {
  unsigned int elements;
  read_stream->ReadUnsignedInt32(elements);
  for (int i = 0; i < elements; i++) {
    char byte;
    read_stream->ReadByte(byte);
    unsigned int freq;
    read_stream->ReadUnsignedInt32(freq);
    frequency_table[byte] = freq;
  }
}

void EncodeData(ReadStream* read_stream,
                map<char, string>& encoding_table,
                WriteStream* write_stream) {
  unsigned int bytes = read_stream->Bytes();
  read_stream->Reset();
  write_stream->WriteUnsignedInt32(bytes);
  while (true) {
    char byte;
    if (!read_stream->ReadByte(byte)) {
      break;
    }
    string encoding = encoding_table[byte];
    for (int i = 0; i < encoding.size(); i++) {
      write_stream->WriteBit(encoding[i]);
    }
  }
}

void DecodeData(ReadStream* read_stream,
                HuffmanNode* root,
                WriteStream* write_stream) {
  unsigned int bytes;
  read_stream->ReadUnsignedInt32(bytes);
  while (bytes > 0) {
    HuffmanNode* node = root;
    while (!node->leaf) {
      char bit;
      read_stream->ReadBit(bit);
      node = (bit == 0) ? node->left : node->right;
    }
    write_stream->WriteByte(node->byte);
    bytes--;
  }
}

HuffmanNode::HuffmanNode() {}

HuffmanNode::HuffmanNode(char byte, unsigned int freq) {
  this->leaf = true;
  this->byte = byte;
  this->freq = freq;
  this->left = NULL;
  this->right = NULL;
}

HuffmanNode::HuffmanNode(unsigned int freq,
                         HuffmanNode* left,
                         HuffmanNode* right) {
  this->leaf = false;
  this->byte = 0;
  this->freq = freq;
  this->left = left;
  this->right = right;
}

bool HuffmanNodeCompare::operator () (
    const HuffmanNode* node1,
    const HuffmanNode* node2) {
  
  return node1->freq > node2->freq;
}

HuffmanNode* BuildHuffmanTree(map<char, unsigned int>& frequencies) {
  priority_queue<HuffmanNode*, vector<HuffmanNode*>, HuffmanNodeCompare> que;

  // Add leaf nodes.
  for (map<char, unsigned int>::iterator it = frequencies.begin();
       it != frequencies.end(); 
       it++) {
    que.push(new HuffmanNode(it->first, it->second));
  }

  // Create inner nodes.
  while (que.size() >= 2) {
    HuffmanNode* min_freq_node1 = que.top();
    que.pop();
    HuffmanNode* min_freq_node2 = que.top();
    que.pop();
    que.push(new HuffmanNode(min_freq_node1->freq + min_freq_node2->freq,
                             min_freq_node1,
                             min_freq_node2));
  }

  HuffmanNode* root = que.top();
  que.pop();

  return root;
}

void DeleteHuffmanTree(HuffmanNode* root) {
  if (root == NULL) {
    return;
  } else {
    DeleteHuffmanTree(root->left);
    DeleteHuffmanTree(root->right);
    delete root;
  }
}

void BuildEncodingTableRecursive(HuffmanNode* root,
                                 string encoding,
                                 map<char, string>& encoding_table) {
  if (root == NULL) {
    return;
  } else if (root->leaf) {
    encoding_table[root->byte] = encoding;
  } else {
    BuildEncodingTableRecursive(
        root->left, encoding + string(1, (char) 0), encoding_table);
    BuildEncodingTableRecursive(
        root->right, encoding + string(1, (char) 1), encoding_table);
  }
}

map<char, string> BuildEncodingTable(HuffmanNode* root) {
  map<char, string> encoding_table;
  BuildEncodingTableRecursive(root, "", encoding_table);
  return encoding_table;
}

map<char, unsigned int> CalculateByteFrequencies(ReadStream* read_stream) {
  map<char, unsigned int> freq;
  while (true) {
    char byte;
    if (!read_stream->ReadByte(byte)) {
      break;
    }
    freq[byte]++;
  }
  return freq;
}
