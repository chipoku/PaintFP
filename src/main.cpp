#include <ncurses.h>

#define KEY_SPACE 32
#define KEY_BACKSPACE 127

class PaintFP {
private:
    int x = 1, y = 1;
    int min_x = 0, min_y = 0;
    int max_x = 255, max_y = 255;
public:
    int ch;


    PaintFP() {
        initscr();
        noecho();
        nodelay(stdscr, TRUE);
    }

    void check_pos() {
        mvprintw(0, 0, "PaintFP v1.0 - X: %i Y: %i", x, y);
    }
    void move_cur() {
        if (ch == 'l')
            x += 1;
        if (ch == 'k')
            y -= 1;
        if (ch == 'j')
            y += 1;
        if (ch == 'h')
            x -= 1;
        move(y, x);
    }
    void draw() {
        if (x < max_x && y < max_y && x > min_x && y > min_y) {
            if (ch == KEY_SPACE)
                addch('#');
            if (ch == KEY_BACKSPACE)
                addch(' ');
        }
    }

    ~PaintFP() {
        endwin();
    }
};

int main() {
PaintFP game;

    while (true){
        game.ch = getch();

        game.check_pos();
        game.move_cur();
        game.draw();

        if (game.ch == 'c')
            break;
    };
    return 0;
}
