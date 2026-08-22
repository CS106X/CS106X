// 为什么我们lec10不unchoose？因为string都是通过参数创建了新字符串（更不用引用）
#include "set.h"
#include "vector.h"
using namespace std;

Set<Vector<int>> counted;

void diceRolls(int n, Vector<int> chosen = {}) {
    if (n == 0) {
        Vector<int> key = chosen;
        sort(key.begin(), key.end());   // 标准化

        if (!counted.contains(key)) {
            cout << key << endl;
            counted.add(key);
        }
        return;
    }

    for (int i = 1; i <= 6; i++) {
        // choose
        chosen.add(i);
        //explore
        diceRolls(n - 1, chosen);
        // unchoose
        chosen.remove(chosen.size() - 1);
    }
}

int main() {
    diceRolls(1);
    return 0;
}
