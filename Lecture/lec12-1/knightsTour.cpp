// https://www.codestepbystep.com/r/problem/view/cpp/backtracking/knightsTour
bool knightsTourHelper(Grid<int>& board, Location current, int step) {
    // choose
    board[current.row][current.col] = step;
    if (step == board.height() * board.width()) {
        printBoard(board);
        return true;
    }

    for (Location p : getMoves(current)) {
        if (board.inBounds(p.row, p.col) &&
            board[p.row][p.col] == 0) {

            if (knightsTourHelper(board, p, step + 1)) {
                return true;
            }

        }
    }
    // unchoose
    board[current.row][current.col] = 0;
    return false;
}

void knightsTour(Grid<int>& board, Location start) {
    knightsTourHelper(board, start, 1);
}
