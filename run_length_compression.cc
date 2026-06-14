#include <cctype>
#include <string>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
using std::string;

// "4a1b3c2a" => "aaaabcccaa"
string Decoding(const string &s) {
  string ret;
  for (int i = 0; i < s.size(); i++) {
    // get the number
    long long numOcc = 0;
    while (isdigit(s[i])) {
      numOcc = numOcc * 10 + (s[i] - '0');
      i++;
    }
    // numOcc number of times add the char to ret
    for (long long j = 0; j < numOcc; j++) {
      ret += s[i];
    }
  }
  return ret;
}

/// "aaaabcccaa" => "4a1b3c2a"
string Encoding(const string &s) {
  string ret;
  for (int i = 0; i < s.size(); i++) {
    long long num = 1;
    char c = s[i];
    while (i + 1 < s.size() && s[i + 1] == c) {
      num++; i++;
    }
    ret += std::to_string(num);
    ret.push_back(c);
  }
  return ret;
}
void RleTester(const string &encoded, const string &decoded) {
  if (Decoding(encoded) != decoded) {
    throw TestFailure("Decoding failed");
  }
  if (Encoding(decoded) != encoded) {
    throw TestFailure("Encoding failed");
  }
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"encoded", "decoded"};
  return GenericTestMain(args, "run_length_compression.cc",
                         "run_length_compression.tsv", &RleTester,
                         DefaultComparator{}, param_names);
}
