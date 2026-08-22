#include <iostream>
#include <string>
#include "hashset.h"
#include "Vector.h"
using namespace std;

string unique(string s) {
    HashSet<char> used;
    string new_s = "";
    for (char c : s) {
        if (used.contains(c)) {
            continue;
        }
        new_s += c;
        used.add(c);
    }
    return new_s;
}  // 另一种方法，是在第22行判断n==0后再判断alreadyadded.contains

void combinationsHelper(string s, int n, string chosen, Vector<string>& v) {    
    if (n == 0) {
        // nothing to choose
        v.add(chosen);
    }
    for (int i = 0; i < s.length(); i++) {
        string new_s = s.substr(0, i) + s.substr(i + 1);
        combinationsHelper(new_s, n - 1, chosen + s[i], v);
    }
}

Vector<string> combinations(string s, int n) {
    s = unique(s);
    Vector<string> v;
    combinationsHelper(s, n, "", v);
    return v;
}

int main() {
    cout << combinations("google", 2) << endl;
    return 0;
}
