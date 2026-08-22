// https://www.codestepbystep.com/r/problem/view/cpp/backtracking/printAllDecimal
void printAllDecimal(int digits, string prefix = "") {
    if (digits == 0) {
        // nothing to choose, so print what was chosen.
        cout << prefix << endl;
    } else if (digits > 0) {
        for (int i = 0; i < 10; i++) {
            // all possible single choice I could made
            printAllDecimal(digits - 1, prefix + integerToString(i));
        }
    }
}