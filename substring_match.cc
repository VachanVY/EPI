#include <cstddef>
#include <string>
#include <unordered_map>

#include "test_framework/generic_test.h"
using std::string;

// Returns the index of the first character of the substring if found, -1
// otherwise.
int RabinKarp(const std::string& t, const std::string& s) {
  if (s.empty()) return 0;
  if (s.size() > t.size()) return -1;

  const long long BASE = 26;
  size_t m = s.size();

  std::unordered_map<char, int> code;
  int next_code = 0;

  for (char c : t) {
    if (!code.count(c))
      code[c] = next_code++;
  }
  for (char c : s) {
    if (!code.count(c))
      code[c] = next_code++;
  }

  long long hash_t = 0;
  long long hash_s = 0;
  long long highest_power = 1;  // BASE^(m-1)

  for (size_t i = 0; i < m; ++i) {
    hash_t = hash_t * BASE + code[t[i]];
    hash_s = hash_s * BASE + code[s[i]];

    if (i + 1 < m)
        highest_power *= BASE;
  }

  if (hash_t == hash_s && t.compare(0, m, s) == 0)
    return 0;

  for (size_t i = m; i < t.size(); ++i) {
    hash_t -= code[t[i - m]] * highest_power;

    hash_t *= BASE;

    hash_t += code[t[i]];

    size_t start = i - m + 1;

    if (hash_t == hash_s &&
      t.compare(start, m, s) == 0) {
      return start;
    }
  }
  return -1;
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"t", "s"};
  return GenericTestMain(args, "substring_match.cc", "substring_match.tsv",
                         &RabinKarp, DefaultComparator{}, param_names);
}
