#include <iostream>
#include <string>
using namespace std;

void permute(string s, string prefix = "") {
    static int l = s.length();
    if (prefix.length() == l) {
        cout << prefix << endl;
    } else {
        int len = s.length();
        for (int i = 0; i < len; i++) {
            string rest = s.substr(0, i) + s.substr(i + 1, len - i);
            permute(rest, prefix + s[i]);
        }
    }
}

int main() {
    permute("");
    return 0;
}
