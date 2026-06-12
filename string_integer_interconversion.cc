#include <string>
#include <algorithm>
#include <cstdlib>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
using std::string;

string IntToString(int x) {
  string s = "";
  bool neg = (x < 0);
  long long num = x;
  if (neg) num = -num;
  do {
    s.push_back(num % 10 + '0');
    num = num / 10;
  } while (num != 0);
  if (neg) s.push_back('-');
  reverse(s.begin(), s.end());
  return s;
}
int StringToInt(const string& s) {
  if (s.empty()) return 0;
  int start = (s[0] == '-' || s[0] == '+') ? 1 : 0;
  int sign = (s[0] == '-') ? -1 : 1;

  long long ret = 0;
  for (int i = start; i < s.size(); i++) {
    ret = ret * 10 + (s[i] - '0');
  }
  return ret * sign;
}
void Wrapper(int x, const string& s) {
  if (stoi(IntToString(x)) != x) {
    throw TestFailure("Int to string conversion failed");
  }

  if (StringToInt(s) != x) {
    throw TestFailure("String to int conversion failed");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "s"};
  return GenericTestMain(args, "string_integer_interconversion.cc",
                         "string_integer_interconversion.tsv", &Wrapper,
                         DefaultComparator{}, param_names);
}
