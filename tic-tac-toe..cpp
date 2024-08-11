#include <iostream>
#include <vector>
#include <string>

class Board {
private:
    std::vector<std::vector<char>> grid;
    const char EMPTY = ' ';

public:
    Board() : grid(3, std::vector<char>(3, EMPTY)) {}

    void display() const {
        std::cout << "\n  0   1   2\n";
        for (int i = 0; i < 3; ++i) {
            std::cout << i << " ";
            for (int j = 0; j < 3; ++j) {
                std::cout << " " << grid[i][j];
                if (j < 2) std::cout << " |";
            }
            std::cout << "\n";
            if (i < 2) std::cout << "  ---|---|---\n";
        }
        std::cout << "\n";
    }

    bool update(int row, int col, char symbol) {
        if (row < 0 || row >= 3 || col < 0 || col >= 3 || grid[row][col] != EMPTY) {
            return false;
        }
        grid[row][col] = symbol;
        return true;
    }

    char check_winner() const {
        for (int i = 0; i < 3; ++i) {
            if (grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2] && grid[i][0] != EMPTY)
                return grid[i][0];
            if (grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i] && grid[0][i] != EMPTY)
                return grid[0][i];
        }
        if (grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2] && grid[0][0] != EMPTY)
            return grid[0][0];
        if (grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0] && grid[0][2] != EMPTY)
            return grid[0][2];
        return EMPTY;
    }

    bool is_full() const {
        for (const auto& row : grid) {
            for (char cell : row) {
                if (cell == EMPTY) return false;
            }
        }
        return true;
    }

    void reset() {
        for (auto& row : grid) {
            std::fill(row.begin(), row.end(), EMPTY);
        }
    }
};

class Player {
private:
    std::string name;
    char symbol;

public:
    Player(const std::string& name, char symbol) : name(name), symbol(symbol) {}

    std::string get_name() const {
        return name;
    }

    char get_symbol() const {
        return symbol;
    }

    void get_move(int& row, int& col) const {
        std::cout << name << " (" << symbol << "), enter your move (row and column): ";
        std::cin >> row >> col;
    }
};

class Game {
private:
    Board board;
    Player player1;
    Player player2;
    Player* current_player;

    void switch_player() {
        current_player = (current_player == &player1) ? &player2 : &player1;
    }

    void announce_winner(char winner_symbol) const {
        if (winner_symbol == player1.get_symbol()) {
            std::cout << player1.get_name() << " wins!\n";
        } else if (winner_symbol == player2.get_symbol()) {
            std::cout << player2.get_name() << " wins!\n";
        } else {
            std::cout << "It's a draw!\n";
        }
    }

public:
    Game(const Player& p1, const Player& p2) : player1(p1), player2(p2), current_player(&player1) {}

    void play() {
        char winner = ' ';
        while (winner == ' ' && !board.is_full()) {
            board.display();
            int row, col;
            current_player->get_move(row, col);
            if (board.update(row, col, current_player->get_symbol())) {
                winner = board.check_winner();
                if (winner == ' ') {
                    switch_player();
                }
            } else {
                std::cout << "Invalid move. Try again.\n";
            }
        }
        board.display();
        announce_winner(winner);
    }

    void reset() {
        board.reset();
        current_player = &player1;
    }
};

int main() {
    std::string name1, name2;
    std::cout << "Enter name for player 1: ";
    std::cin >> name1;
    std::cout << "Enter name for player 2: ";
    std::cin >> name2;

    Player player1(name1, 'X');
    Player player2(name2, 'O');
    Game game(player1, player2);

    char play_again = 'n';
    do {
        game.play();
        std::cout << "Do you want to play again? (y/n): ";
        std::cin >> play_again;
        if (play_again == 'y') {
            game.reset();
        }
    } while (play_again == 'y');

    return 0;
}


