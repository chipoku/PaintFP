#include <ncurses.h>
#include <iostream>

#define KEY_SPACE 32
#define KEY_ENTER 10

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
    WINDOW *color_win = nullptr;

    const char help_msg[155] = "1. UP,DOWN,LEFT,RIGHT - arrows\n"
                               " 2. SELECT - ENTER\n"
                               " 3. DRAW - SPACE\n"
                               " 4. ERASURE - BACKSPACE\n"
                               " 5. COLOR MENU - C\n"
                               " 6. HELP - h\n"
                               " 7. CLEAR ALL - r\n"
                               " 8. QUIT - q\n";

    const std::string color_menu_ch[10] = {"COLOR_BLACK",
                                        "COLOR_RED",
                                        "COLOR_GREEN",
                                        "COLOR_YELLOW",
                                        "COLOR_BLUE",
                                        "COLOR_MAGENTA",
                                        "COLOR_CYAN",
                                        "COLOR_WHITE",
                                        "BACKGROUND COLOR SELECT",
                                        "FOREGROUND COLOR SELECT"};

public:
    int ch = static_cast<int>(NULL);


    PaintFP() {
        initscr();
        start_color();
        init_colors(COLOR_WHITE,
                    COLOR_BLACK);
        bkgd(COLOR_PAIR(1));
        attron(COLOR_PAIR(1));
        noecho();
        nodelay(stdscr, TRUE);
        keypad(stdscr, TRUE);
    }

    static void init_colors(short font, short background) {
        init_pair(1, font,
                     background);
    }
    void help_menu(){
        /*
         * hw_height = LINES/2,
         * hw_width = COLS/2;
        */
        help_win = newwin(height/2, width/2,
                          LINES/4, COLS/4);

        mvwprintw(help_win,
                  1, width/8,
                  "Print For Paupers v1.2_beta - HELP:");
        mvwaddstr(help_win,
                4, 1,
                  help_msg);
        box(help_win,
                0, 0);

        wrefresh(help_win);
    }
    void color_menu() {
        int page = 0;
        short highlighted = 0;
        short font = 0;
        short background = 0;
        color_win = newwin(height/2, width/2,
                           LINES/4, COLS/4);

        keypad(stdscr, FALSE);
        keypad(color_win, TRUE);
        box(color_win,
            0, 0);

        wrefresh(color_win);


        while (true) {
            if (page)
                mvwprintw(color_win,
                          10, width/8,
                          color_menu_ch[8].c_str());
            else
                mvwprintw(color_win,
                          10, width/8,
                          color_menu_ch[9].c_str());

            for (int i = 0; i <= 7; i++){
                if (highlighted == i)
                    wattron(color_win, A_REVERSE);
                mvwprintw(color_win, i+1, 1, color_menu_ch[i].c_str());
                wattroff(color_win, A_REVERSE);
            }


            ch = wgetch(color_win);

            if (ch == KEY_UP)
                highlighted--;
            else if (ch == KEY_DOWN)
                highlighted++;
            else if (ch == KEY_RIGHT)
                page++;
            else if (ch == KEY_LEFT)
                page--;

            if (highlighted >= 8)
                highlighted = 0;
            else if (highlighted < 0)
                highlighted = 7;
            if (page > 1)
                page = 0;
            else if (page < 0)
                page = 1;

            if (ch == KEY_ENTER) {
                if (page)
                    background = highlighted;
                else
                    font = highlighted;
            }


            if (ch == 'c') {
                keypad(stdscr, TRUE);
                keypad(color_win, FALSE);
                init_colors(font, background);
                bkgd(COLOR_PAIR(1));
                refresh();
                break;
            }

        }
    }
    void check_pos() const {
        mvprintw(0, 0,
                 "PaintFP v1.2_beta - X: %i Y: %i, WIDTH: %i, HEIGHT: %i",
                 x, y, width, height);
    }
    void move_cur() {
        if (ch == KEY_RIGHT)
            x += 1;
        if (ch == KEY_UP)
            y -= 1;
        if (ch == KEY_DOWN)
            y += 1;
        if (ch == KEY_LEFT)
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
        attroff(COLOR_PAIR(1));
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
        if (game.ch == 'c')
            game.color_menu();
        if (game.ch == 'q')
            break;
    }

    return 0;
}
