#include <iostream>
#include <vector>
#include "vector.h"
using namespace std;

// not decide which to choose
// but to decide whether to include
void printSubVectorsHelper(vector<int>& v, Vector<int>& chosen) { // d方式1：不设为引用，不用回溯
    if (v.size() == 0) {
        cout << chosen << endl;
    } else {
        // choose
        int i = v[0];
        v.erase(v.begin());
        // explore
        chosen.add(i);
        printSubVectorsHelper(v, chosen);
        chosen.remove(chosen.size() - 1);
        printSubVectorsHelper(v, chosen);
        // unchoose
        v.insert(v.begin(), i);  // d方式2：用引用，但需要回溯(unchoose)
    }
}

void printSubVectors(vector<int>& v) {
    Vector<int> chosen;
    printSubVectorsHelper(v, chosen);
}

int main() {
    vector<int> v = {1, 2};
    printSubVectors(v);
    return 0;
}


