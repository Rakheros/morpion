#define formatCoord(i, j) i*0x10 + j

enum PreventionStatut {
    NoWinDetected,
    ThreatenedWin,
    ImmediateWin,
};

bool isWinner (char boardW[3][3]) {
    if (boardW[0][0] == boardW[1][1] && boardW[1][1] == boardW[2][2] && boardW[1][1] != ' ')
        return true;
    if (boardW[0][2] == boardW[1][1] && boardW[1][1] == boardW[2][0] && boardW[1][1] != ' ')
        return true;
    for (int i = 0; i < 3; i++) {
        if (boardW[i][0] == boardW[i][1] && boardW[i][1] == boardW[i][2] && boardW[i][0] != ' ')
            return true;
        if (boardW[0][i] == boardW[1][i] && boardW[1][i] == boardW[2][i] && boardW[0][i] != ' ')
            return true;
    }
    return false;
}

bool isFull (char boardF[3][3]) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (boardF[i][j] == ' ')
                return false;
    return true;
}

void copyBoard(char boardIn[3][3], char boardOut[3][3]) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            boardOut[i][j] = boardIn[i][j];
    return;
}

class AI {
    public:
    int boardWeight[3][3] = {{34, 24, 33}, {23, 40, 22}, {32, 21, 31}};

    private:
    PreventionStatut statut;
    char board[3][3], boardAI[3][3];

    int threatsManager () {
        int tempChoice = 0;
        char boardAI1[3][3];
        copyBoard(boardAI, boardAI1);
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (boardAI[i][j] == ' ') {
                    boardAI1[i][j] = 'X';
                    if (isWinner(boardAI1)) {
                        statut = ThreatenedWin;
                        return formatCoord(i, j);
                    } else if (statut < ThreatenedWin) {
                        boardAI1[i][j] = 'O';
                        if (isWinner(boardAI1))
                            tempChoice = formatCoord(i, j);
                    }
                    boardAI1[i][j] = ' ';
                }
            }
        }
        return tempChoice;
    }

    int winsManager () {
        int tempChoice = 0;
        copyBoard(board, boardAI);
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    boardAI[i][j] = 'O';
                    if (isWinner(boardAI)) {
                        return formatCoord(i, j);
                    }
                    boardAI[i][j] = 'X';
                    if (isWinner(boardAI)) {
                        tempChoice = formatCoord(i, j);
                        statut = ImmediateWin;
                    } else if (statut < ImmediateWin) {
                        tempChoice = threatsManager();
                    }
                    boardAI[i][j] = ' ';
                }
            }
        }
        return tempChoice;
    }

    int emptySquaresManager () {
        int bestSquare, highestValue = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (boardWeight[i][j] > highestValue) {
                    highestValue = boardWeight[i][j];
                    bestSquare = formatCoord(i, j);
                }
            }
        }
        return bestSquare;
    }

    public:
    int AI_choice (char b[3][3]) {
        int threatsWins;
        statut = NoWinDetected;
        copyBoard(b, board);

        if (board[1][1] == ' ') { 
            return formatCoord(1, 1);
        }
        threatsWins = winsManager();
        if (threatsWins) {
            return threatsWins;
        }
        return emptySquaresManager();
    }
};