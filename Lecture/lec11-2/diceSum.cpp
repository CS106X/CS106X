#include "set.h"
#include "vector.h"
using namespace std;

int sumOfVector(Vector<int> chosen) {
    if (chosen.size() == 0) return 0;
    int n = chosen[0];
    chosen.remove(0);
    return n + sumOfVector(chosen);
}

void diceSumHelper(int n, int sum,Vector<int>& chosen) {
    if (n <= 0) {
        if (0 == sum) {
            cout << chosen << endl;
        }
    } else if (n > 0) {
        for (int i = 1; i <= 6; i++) {
            if (sum > i + (n-1)*6 || sum < i + (n-1)* 1) return;
            // choose
            chosen.add(i);
            // explore
            diceSumHelper(n - 1, sum-i,chosen);
            // unchoose
            chosen.remove(chosen.size() - 1);
        }
    }
}

void diceSum(int n, int sum) {
    Vector<int> v;
    diceSumHelper(n, sum, v);
}

int main() {
    diceSum(2, 6);
    return 0;
}
