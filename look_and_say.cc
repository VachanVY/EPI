#include <string>

#include "test_framework/generic_test.h"
using std::string;

static string nextNumber(const string& s) {
  string ret;
  for (int i = 0; i < s.size(); i++) {
    long long numOcc = 1;
    char c = s[i];
    // count num occurances
    while (i + 1 < s.size() && s[i+1] == c) {
      numOcc += 1;
      i++;
    }
    ret += std::to_string(numOcc);
    ret.push_back(c);
  }
  return ret;
}

string LookAndSay(int n) {
  string ret = "1";
  for (int i = 1; i < n; i++) {
    ret = nextNumber(ret);
  }
  return ret;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  return GenericTestMain(args, "look_and_say.cc", "look_and_say.tsv",
                         &LookAndSay, DefaultComparator{}, param_names);
}
