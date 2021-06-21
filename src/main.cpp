#include <ncurses.h>
#include <iostream>

#define KEY_SPACE 32
#define KEY_BACKSPACE 127

class PaintFP {
private:
    int x = 1, y = 1;
    const int min_x = 0, min_y = 0;
    const int width = 100, height = 100;

    WINDOW *help_win = nullptr;
    const char help_msg[150] = "1. UP,DOWN,LEFT,RIGHT - arrows\n"
                               " 2. SPACE - draw\n"
                               " 3. BACKSPACE - erasure\n"
                               " 4. h - help\n"
                               " 5. r - clear all\n"
                               " 6. q - quit\n";
public:
    int ch = static_cast<int>(NULL);


    PaintFP() {
        initscr();
        start_color();
        init_colors(COLOR_BLACK, COLOR_WHITE);
//        attron(COLOR_PAIR(1));
        noecho();
        nodelay(stdscr, TRUE);
    }
    static void init_colors(short font, short background) {
        init_pair(1, font, background);
    }
    void help_menu(){
        help_win = newwin(LINES/2, COLS/2, LINES/4, COLS/4);
        mvwprintw(help_win, 1, COLS/8, "Print For Paupers v1.1b - HELP");
        mvwaddstr(help_win, 4, 1, help_msg);
        box(help_win, 0, 0);
        wrefresh(help_win);
    }

    void check_pos() const {
        attron(COLOR_PAIR(1));
        mvprintw(0, 0, "PaintFP v1.1b - X: %i Y: %i, COLS: %i, LINES: %i", x, y, COLS, LINES);
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
        if (x < width && y < height && x > min_x && y > min_y) {
            if (ch == KEY_SPACE)
                addch('#');
            if (ch == KEY_BACKSPACE)
                addch(' ');
            if (ch == 'r')
                clear();
        }
    }

    ~PaintFP() {
//        attroff(COLOR_PAIR(1));
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
