#include <algorithm>
#include <cstdio>
#include <string>

#include "test_framework/generic_test.h"
using std::string;

string ConvertBase(const string& num_as_string, int b1, int b2) {
  // convert to base 10 from b1
  bool neg = num_as_string[0] == '-' ? true : false;
  int start = neg ? 1 : 0;

  long long base10 = 0;
  for (int i = start; i < num_as_string.size(); i++) {
    char c = num_as_string[i];
    int num = c >= 'A' ? c - 55: (c - '0');
    base10 = base10 * b1 + num;
  }

  // convert to base b2 from base 10
  string ret;
  do {
    int digit = base10 % b2;
    char c = (digit >= 10) ? ('A' + (digit - 10)) : (digit + '0');
    base10 = base10 / b2;
    ret.push_back(c);
  } while (base10 != 0);
  if (neg) ret.push_back('-');
  reverse(ret.begin(), ret.end());
  return ret;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num_as_string", "b1", "b2"};
  return GenericTestMain(args, "convert_base.cc", "convert_base.tsv",
                         &ConvertBase, DefaultComparator{}, param_names);
}
