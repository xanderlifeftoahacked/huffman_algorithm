#include <bits/stdc++.h>

struct Node {
  char ch;
  int freq;
  Node *left, *right;

  Node(char _ch, int _freq, Node *_left, Node *_right) {
    ch = _ch;
    freq = _freq;
    left = _left;
    right = _right;
  }
};

struct comp {
  bool operator()(Node *l, Node *r) { return l->freq > r->freq; }
};

void encode(Node *root, std::string str_input,
            std::unordered_map<char, std::string> &huffman_code) {
  if (root == nullptr)
    return;

  if (!root->left && !root->right) {
    huffman_code[root->ch] = str_input;
  }

  encode(root->left, str_input + "0", huffman_code);
  encode(root->right, str_input + "1", huffman_code);
}

void decode(Node *root, int &index, std::string str) {
  if (root == nullptr)
    return;

  if (!root->left && !root->right) {
    std::cout << root->ch;
    return;
  }

  index++;

  if (str[index] == '0')
    decode(root->left, index, str);
  else
    decode(root->right, index, str);
}

void build_huffman_tree(std::string text) {

  std::unordered_map<char, int> freq;

  for (char ch : text) {
    freq[ch]++;
  }

  std::priority_queue<Node *, std::vector<Node *>, comp> pq;

  for (auto pair : freq) {
    Node *nd = new Node(pair.first, pair.second, nullptr, nullptr);
    pq.push(nd);
  }

  while (pq.size() != 1) {
    Node *left = pq.top();
    pq.pop();
    Node *right = pq.top();
    pq.pop();

    int sum = left->freq + right->freq;
    Node *nd = new Node('\n', sum, left, right);
    pq.push(nd);
  }

  Node *root = pq.top();

  std::unordered_map<char, std::string> huffman_code;
  encode(root, "", huffman_code);

  std::cout << "Huffman Codes are :\n" << std::endl;

  for (auto pair : huffman_code) {
    std::cout << pair.first << " " << pair.second << std::endl;
  }

  std::cout << "\nOriginal string was :\n" << text << std::endl;

  std::string str = "";
  for (char ch : text) {
    str += huffman_code[ch];
  }

  std::cout << "\nEncoded string is :\n" << str << std::endl;

  int index = -1;
  std::cout << "\nDecoded string is:" << std::endl;

  int size = static_cast<int>(str.size());

  while (index < (size - 2)) {
    decode(root, index, str);
  }
};

int main() {
  std::string text = "abcdefgh";

  build_huffman_tree(text);

  return 0;
}
