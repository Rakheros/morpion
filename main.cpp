#include <iostream>
#include "AI_calculations.cpp"

void printBoard (char board[3][3]) {
    std::cout << "   A   B   C \n";
    for (int i = 0; i < 3; i++) {
        std::cout << i + 1 << "  " << board [i][0] << " | " << board [i][1] << " | " << board [i][2] << " \n";
        if (i < 2) {
            std::cout << "  ---+---+---\n";
        }
    }
}

std::string playerChoice () {
    std::string choice;
    std::cout << "Please choose a square (format : LetterNumber) ";
    std::cin >> choice;
    choice[0] = toupper(choice[0]);
    if (choice.length() != 2) {
        std::cout << "Your answer must contain only two characters\n";
        return playerChoice();
    } else if (!(choice [0] == 'A' || choice [0] == 'B' || choice [0] == 'C')) {
        std::cout << "The first character you enter must be A, B or C\n";
        return playerChoice();
    } else if (!(choice [1] == '1' || choice [1] == '2' || choice [1] == '3')) {
        std::cout << "The second character you enter must be 1, 2 or 3\n";
        return playerChoice();
    } else {
        return choice;
    }
}

int converter (char c) {
    switch (c) {
        case 'A': return 0;
        case 'B': return 1;
        case 'C': return 2;
        case '1': return 0;
        case '2': return 1;
        case '3': return 2;
    }
    return -1;
}

int main () {
    bool playing = true;
    do {
        AI ai;
        char board [3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
        char winner = ' ';
        char turn = 'X';
        char nextTurn = 'O';
        bool running = true;
        int AI_choice;
        std::string playerInput;
        int iChoice, jChoice;
        while (running) {
            if (turn == 'X') {
                printBoard(board);
                
                playerInput = playerChoice();
                iChoice = converter(playerInput[1]);
                jChoice = converter(playerInput[0]);
                while (board[iChoice][jChoice] != ' ') {
                    std::cout << "This square is already taken, please choose another one";
                    playerInput = playerChoice();
                    iChoice = converter(playerInput[1]);
                    jChoice = converter(playerInput[0]);
                }
            } else {
                AI_choice = ai.AI_choice(board);
                iChoice = AI_choice/0x10;
                jChoice = AI_choice%0x10;
            }

            board[iChoice][jChoice] = turn;
            ai.boardWeight[iChoice][jChoice] = 0;

            if (isWinner(board)) {
                winner = turn;
                running = false;
            } else if (isFull(board)) {
                running = false;
            } else {
                turn = nextTurn;
                nextTurn = board[iChoice][jChoice];
            }
        }

        printBoard(board);
        if (winner == ' ') {
            std::cout << "Draw\n";
        } else {
            std::cout << (winner == 'X' ? "You have" : "Computer has") << " won !\n";
        }

        std::cout << "Do you want to replay ? ";
        std::cin >> playerInput;
        if (playerInput == "n" || playerInput == "N" || playerInput == "no" || playerInput == "No" || playerInput == "NO") {
            playing = false;
        }
    } while (playing);
    return 0;
}

