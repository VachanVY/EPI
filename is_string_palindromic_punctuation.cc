#include <cctype>
#include <string>

#include "test_framework/generic_test.h"
using std::string;
bool IsPalindrome(const string& s) {
  int i = 0, j = s.size() - 1;
  while (i < j) { // valid => (alpha num)
    // skip i until valid
    while (!isalnum(s[i]) && i < j) {i++;}

    // skip j until valid
    while (!isalnum(s[j]) && i < j) {j--;}

    // compare // ignore case
    if (tolower(s[i]) != tolower(s[j]))
      return false;

    // increment/decrement i and j
    i++; j--;
  }
  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "is_string_palindromic_punctuation.cc",
                         "is_string_palindromic_punctuation.tsv", &IsPalindrome,
                         DefaultComparator{}, param_names);
}
