/*
Compile: make reversi
Run: ./reversi
make reversi && ./reversi

Reversi Rules
- X moves first
- Pieces are reversed if surrounded (on two sides) by opponent pieces
- A valid move is one in which at least one piece is reversed
- If one player cannot make a move, play passes back to the other player
- When neither player can move, the game ends, the player with the most pieces wins

Details: https://en.wikipedia.org/wiki/Reversi
*/

#include "base.h"


struct Position {
    int x;
    int y;
};
struct Direction {
	int x;
	int y;
};

struct Direction make_direction(int x, int y) {
	struct Direction p;
    p.x = x;
    p.y = y;
    return p;
}
struct Position make_position(int x, int y) {
	struct Position p;
    p.x = x*2+1;
    p.y = y * 19;
    return p;
}

void print_position(struct Position p) {
    printf("(%d, %d)\n", (p.x-1)/2, p.y/19 -1);
}

#define N 8

struct Game{
    String board; 
    char my_stone; // 'X' or 'O'
};

// Initialize the board such that it looks like this if printed:
//  |A|B|C|D|E|F|G|H|
// 1|_|_|_|_|_|_|_|_|
// 2|_|_|_|_|_|_|_|_|
// 3|_|_|_|_|_|_|_|_|
// 4|_|_|_|O|X|_|_|_|
// 5|_|_|_|X|O|_|_|_|
// 6|_|_|_|_|_|_|_|_|
// 7|_|_|_|_|_|_|_|_|
// 8|_|_|_|_|_|_|_|_|
void init_game(char my_stone) {
	struct Game game;
	if (my_stone == 'X'){
    game.board = " |A|B|C|D|E|F|G|H| \n1|_|_|_|_|_|_|_|_| \n2|_|_|_|_|_|_|_|_| \n3|_|_|_|_|_|_|_|_| \n4|_|_|_|O|X|_|_|_| \n5|_|_|_|X|O|_|_|_| \n6|_|_|_|_|_|_|_|_| \n7|_|_|_|_|_|_|_|_| \n8|_|_|_|_|_|_|_|_|";
    }else{game.board = " |A|B|C|D|E|F|G|H| \n1|_|_|_|_|_|_|_|_| \n2|_|_|_|_|_|_|_|_| \n3|_|_|_|_|_|_|_|_| \n4|_|_|_|X|O|_|_|_| \n5|_|_|_|O|X|_|_|_| \n6|_|_|_|_|_|_|_|_| \n7|_|_|_|_|_|_|_|_| \n8|_|_|_|_|_|_|_|_|";
    }
    game.my_stone = my_stone;
    return 0;
}

// Print the board. The initial board should look like shown above.
void print_board(struct Game game) {
    printf("%s\n",game.board);
}

// Check whether position (x,y) is on the board.
bool out_of_bounds(struct Position p) {
    if (p.y > (19 * 9) || p.x > 18 || p.y < 20 || p.x < 3) return true;
    else return false;
}

// If it is X's turn, then "my stone" is 'X', otherwise it is 'O'.
char my_stone(struct Game game) {
    return game.my_stone;
}

// If it is X's turn, then "your stone" is 'O', otherwise it is 'X'.
char your_stone(struct Game game) {
	if (game.my_stone == 'X') return 'O';
	else return 'X';
}

// Switch the my stone and your stone ('X' <--> 'O')
void switch_stone(struct Game g) {
    g.my_stone = your_stone(g);
}

// Check whether, if starting at (x,y), direction (dx,dy) is a legal direction
// to reverse stones. A direction is legal if (assuming my stone is 'X')
// the pattern in that direction is: O+X.* (one or more 'O's, followed by an 'X', 
// followed by zero or more arbitrary characters).
// (dx,dy) is element of { (a,b) | a, b in {-1, 0, 1} and (a,b) != (0,0) }
bool legal_dir(struct Game game, struct Position p, struct Direction dir) {
    int at = p.y *19 + p.x;
    if (dir.x == 0 && dir.y == 1) {
    for (int i=2; i<=8;i++){
    	struct Position up = make_position(p.x,p.y -19 * i);
    	if (game.my_stone == game.board[up.y*19+ up.x] && out_of_bounds(up) == false) return true;
    }
    }
    if (dir.x == 0 && dir.y == -1) {
    for (int i=2; i<=8;i++){
    	struct Position down = make_position(p.x,p.y +19 * i);
    	if (game.my_stone == game.board[down.y*19+ down.x] && out_of_bounds(down) == false) return true;
    }
    }
    if (dir.x == -1 && dir.y == 0) {
    for (int i=2; i<=8;i++){
    	struct Position left = make_position(p.x - 3 * i ,p.y);
    	if (game.my_stone == game.board[left.y*19+ left.x] && out_of_bounds(left) == false) return true;
    }
    }
    if (dir.x == 1 && dir.y == 0) {
    for (int i=2; i<=8;i++){
    	struct Position right = make_position(p.x + 3 * i,p.y);
    	if (game.my_stone == game.board[right.y*19+ right.x] && out_of_bounds(right) == false) return true;
    }
    }
    if (dir.x == 1 && dir.y == 1) {
    for (int i=2; i<=8;i++){
    	struct Position upr = make_position(p.x + 3 * i,p.y -19*i);
    	if (game.my_stone == game.board[upr.y*19+ upr.x] && out_of_bounds(upr) == false) return true;
    }
    }
    if (dir.x == -1 && dir.y == 1) {
    for (int i=2; i<=8;i++){
    	struct Position upl = make_position(p.x - 3 * i,p.y -19*i);
    	if (game.my_stone == game.board[upl.y*19+ upl.x] && out_of_bounds(upl) == false) return true;
    }
    }
    if (dir.x == 1 && dir.y == -1) {
    for (int i=2; i<=8;i++){
    	struct Position dor = make_position(p.x + 3* i,p.y +19 *i);
    	if (game.my_stone == game.board[dor.y*19+ dor.x] && out_of_bounds(dor) == false) return true;
    }
    }
    if (dir.x == -1 && dir.y == -1) {
    for (int i=2; i<=8;i++){
    	 struct Position dol = make_position(p.x -3*i,p.y + 19*i);
    	if (game.my_stone == game.board[dol.y*19+ dol.x] && out_of_bounds(dol) == false) return true;
    }
    }
    return false;
}

// Check whether (x,y) is a legal position to place a stone. A position is legal
// if it is empty ('_'), is on the board, and has at least one legal direction.
bool legal(struct Game game, struct Position p) {
	int at = p.y *19 + p.x;
    if (out_of_bound(p)) return false;
    else if (game.board[at] == 'X' || game.board[at] == 'O') return false;
    else return true;
}

// Reverse stones starting at (x,y) in direction (dx,dy), but only if the 
// direction is legal. May modify the state of the game.
// (dx,dy) is element of { (a,b) | a, b in {-1, 0, 1} and (a,b) != (0,0) }
void reverse_dir(struct Game game, struct Position p, struct Direction dir) {
    int start= p.y + p.x;
    for (int i = 1; i < 8; i++){
    	int field = p.y + p.x;
    	struct Position at = make_position(p.x + dir.x * 3 * i,p.y + dir.y * 19 * i);
    	if (game.my_stone != game.board[field] && out_of_bounds == false) game.board[field] = game.my_stone;
    	     	
}

// Reverse the stones in all legal directions starting at (x,y).
// May modify the state of the game.
void reverse(struct Game game, struct Position p) {
    	reverse_dir(game,p,make_direction(0,1));
    	reverse_dir(game,p,make_direction(0,-1));
    	reverse_dir(game,p,make_direction(-1,0));
    	reverse_dir(game,p,make_direction(1,0));
    	reverse_dir(game,p,make_direction(-1,1));
    	reverse_dir(game,p,make_direction(1,1));
    	reverse_dir(game,p,make_direction(-1,-1));
    	reverse_dir(game,p,make_direction(1,-1));
}

// Input a position of the form D6 or d6, i.e., giving the column first and 
// then the row. A1 corresponds to position (0,0). B1 corresponds to (1,0).
void input_position(struct Game g, char my_stone) {
    printf("%c's turn: ", g.my_stone);
    int x = 0;
    int y = 0;
    struct Position pos;
    String s = s_input(10);
    if (s_length(s) >= 1 && s[0] == 'q') exit(0);
    pos = make_position(-1,-1);
    if (s_length(s) >= 2) {
    	for (int i = 0;i <= 7;i++){
    		if (s[1]== 'a' + i) x = i +1;
    		}
    	if (x == 0){
    		for (int i = 0;i <= 7;i++){
    			if (s[1]== 'A' + i) x = i +1;
    		}
        y = (int)s[2];
       pos = make_position(x,y);
            }
    if (legal(g, pos)) {
        return pos;
    } else {
        printsln("Invalid position!");
        return input_position(g, g.my_stone);
    }
}

void count_stones(struct Game g, char c) {
    int cx = 0;
    for (int i = 0; i < 19 * 9; i++){
    	if (g.board[i] == c) cx = cx +1;
    	}
    printi(cx);
    return 0;
}

int main(void) {
    struct Game g = init_game('X');
    print_board(g);
    while (true) {
        Position pos = input_position(g, my_stone);
        reverse(g, pos);
        print_board(&g);
        int score = count_stones(g, my_stone(g)) - count_stones(g, your_stone(g));
        printf("Score for %c:\n", my_stone(g)); count_stones(g,g.my_stone);
        switch_stones(g);
    }
    return 0;
}
