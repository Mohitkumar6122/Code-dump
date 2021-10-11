/**
 * \file
 * \brief 
 * The [Knuth-Morris-Pratt
 * Algorithm](https://en.wikipedia.org/wiki/Knuth–Morris–Pratt_algorithm) for
 * finding a pattern within a piece of text with complexity O(n + m)
 *
 * 1. Preprocess pattern to identify any suffixes that are identical to
 * prefixes. This tells us where to continue from if we get a mismatch between a
 * character in our pattern and the text.
 * 2. Step through the text one character at a time and compare it to a
 * character in the pattern updating our location within the pattern if
 * necessary
 */

#include <iostream>
#include <vector>
#ifdef _MSC_VER
#include <string>  // use this for MS Visual C++
#else
#include <cstring>
#endif

/** \namespace string_search
 * \brief String search algorithms
 */
namespace string_search {
/**
 * Generate the partial match table aka failure function for a pattern to
 * search.
 * \param[in] pattern text for which to create the partial match table
 * \returns the partial match table as a vector array
 */
std::vector<int> getFailureArray(const std::string &pattern) {
    int pattern_length = pattern.size();
    std::vector<int> failure(pattern_length + 1);
    failure[0] = -1;
    int j = -1;

    for (int i = 0; i < pattern_length; i++) {
        while (j != -1 && pattern[j] != pattern[i]) {
            j = failure[j];
        }
        j++;
        failure[i + 1] = j;
    }
    return failure;
}

/**
 * KMP algorithm to find a pattern in a text
 * \param[in] pattern string pattern to search
 * \param[in] text text in which to search
 * \returns `true` if pattern was found
 * \returns `false` if pattern was not found
 */
bool kmp(const std::string &pattern, const std::string &text) {
    int text_length = text.size(), pattern_length = pattern.size();
    std::vector<int> failure = getFailureArray(pattern);

    int k = 0;
    for (int j = 0; j < text_length; j++) {
        while (k != -1 && pattern[k] != text[j]) {
            k = failure[k];
        }
        k++;
        if (k == pattern_length)
            return true;
    }
    return false;
}
}  // namespace string_search

using string_search::kmp;

typedef long long ll;
const int maxn = 1e5 + 5;
#define sz(x) (ll)(x).size()

ll lps[maxn]; // longest prefix array which is also a suffix

void kmp(std::string s)
{
    ll i = 1, j = 0;
    lps[0] = 0;
    while (i < sz(s))
    {
        if (s[i] == s[j])
        {
            lps[i++] = ++j;
        }
        else
            j = 0, i++;
    }
    //ff(i, 0, sz(s)) cout << lps[i] << " " ;
}

void match_sub(std::string s, std::string t)
{
    ll i = 0, j = 0;
    std::vector<int> v;
    while (i < s.size())
    {
        if (s[i] == t[j])
        {
            ++i, ++j;
            if (j == sz(t))
            {
                //cout << "std::string Found at\t" << i - j + 1 << endl ;
                v.push_back(i - j + 1);
                j = lps[j - 1];
            }
        }
        else
        {
            if (j)
                j = lps[j - 1];
            else
                ++i;
        }
    }
    if (!sz(v))
        std::cout << "Not Found\n";
    else
    {
        std::cout << sz(v) << "\n";
        for (auto x : v)
            std::cout << x << " ";
        std::cout << "\n";
    }
}

/** Main function */
int main() {
    std::string text = "alskfjaldsabc1abc1abc12k23adsfabcabc";
    std::string pattern = "abc1abc12l";

    if (kmp(pattern, text) == true) {
        std::cout << "Found" << std::endl;
    } else {
        std::cout << "Not Found" << std::endl;
    }

    text = "abcabc";
    pattern = "bca";
    if (kmp(pattern, text) == true) {
        std::cout << "Found" << std::endl;
    } else {
        std::cout << "Not Found" << std::endl;
    }

    return 0;
}
