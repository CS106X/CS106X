// 一遍成功！
#include <iostream>
#include <string>
#include "vector.h"
#include "gtypes.h"
using namespace std;

void travelHelper(GPoint& current, const GPoint& target, Vector<string>& path) {
    if (current == target) {
        for (string s : path) {
            cout << s << " ";
        }
        cout << endl;
    }

    if (current.x < target.x) {
        current.x += 1;
        path.add("E");
        travelHelper(current, target, path);
        current.x -= 1;
        path.remove(path.size() - 1);
    }

    if (current.y < target.y) {
        current.y += 1;
        path.add("N");
        travelHelper(current, target, path);
        current.y -= 1;
        path.remove(path.size() - 1);
    }

    if (current.x < target.x && current.y < target.y) {
        current.x += 1;
        current.y += 1;
        path.add("NE");
        travelHelper(current, target, path);
        current.x -= 1;
        current.y -= 1;
        path.remove(path.size() - 1);
    }
}

void travel(const GPoint& target) {
    GPoint current(0, 0);
    Vector<string> path;
    travelHelper(current, target, path);
}

int main() {
    GPoint a(2, 1);
    travel(a);
    return 0;
}
