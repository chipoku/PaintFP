#include <ncurses.h>
#include <iostream>

#define KEY_SPACE 32
#define KEY_BACKSPACE 127 // default KEY_BACKSPACE not working with ncurses.

class PaintFP {
private:
    int x = 1,
        y = 1;
    int &width = COLS,
        &height = LINES;
    /*
     * int hw_width = static_cast<int>(NULL),
     *     hw_height = static_cast<int>(NULL);
     */

    WINDOW *help_win = nullptr;

    const char help_msg[117] = "1. UP,DOWN,LEFT,RIGHT - arrows\n"
                               " 2. DRAW - SPACE\n"
                               " 3. ERASURE - BACKSPACE\n"
                               " 4. HELP - h\n"
                               " 5. CLEAR ALL - r\n"
                               " 6. QUIT - q\n";
public:
    int ch = static_cast<int>(NULL);


    PaintFP() {
        initscr();
        start_color();
        init_colors(COLOR_BLACK,
                    COLOR_WHITE);
        noecho();
        nodelay(stdscr, TRUE);
    }

    static void init_colors(short font, short background) {
        init_pair(1, font,
                     background);
    }
    void help_menu(){
        /*
        hw_height = LINES/2,
        hw_width = COLS/2;
        */
        help_win = newwin(height/2, width/2,
                          LINES/4, COLS/4);

        mvwprintw(help_win,
                  1, width/8,
                  "Print For Paupers v1.1.1b - HELP:");
        mvwaddstr(help_win,
                4, 1,
                  help_msg);
        box(help_win,
                0, 0);

        wrefresh(help_win);
    }
    void check_pos() const {
        attron(COLOR_PAIR(1));
        mvprintw(0, 0,
                 "PaintFP v1.1.1 - X: %i Y: %i, WIDTH: %i, HEIGHT: %i",
                 x, y, width, height);
        attroff(COLOR_PAIR(1));
    }
    void move_cur() {
        if (ch == 67)
            x += 1;
        if (ch == 65)
            y -= 1;
        if (ch == 66)
            y += 1;
        if (ch == 68)
            x -= 1;
        move(y, x);
    }
    void draw() const {
        if (x < width && y < height && x > 0 && y > 0) {
            if (ch == KEY_SPACE)
                addch('#');
            if (ch == KEY_BACKSPACE)
                addch(' ');
            if (ch == 'r')
                clear();
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

        if (game.ch == 'h')
             game.help_menu();
        if (game.ch == 'q')
             break;
    }

    endwin();
    return 0;
}
