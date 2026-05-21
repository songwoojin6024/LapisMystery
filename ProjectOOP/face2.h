#ifndef FACE2_H
#define FACE2_H

#include <iostream>
#include "Common.h"
using namespace std;

void face2(int x = 0, int y = 0) {
    gotoxy(x, y++); cout << "                    #######_                 ";
    gotoxy(x, y++); cout << "                _############¡¬                ";
    gotoxy(x, y++); cout << "             /#################¡¬               ";
    gotoxy(x, y++); cout << "            /###'        #######¡¬          ";
    gotoxy(x, y++); cout << "           /###             '####¡¬                ";
    gotoxy(x, y++); cout << "           ####              '####            ";
    gotoxy(x, y++); cout << "           ###  ¢Ö===¢Ø    ¢Ö===¢Ø ##|               ";
    gotoxy(x, y++); cout << "            ##¤Ñ[ /¡á¡¬]¤Ñ[/¡á¡¬]¤Ñ/                      ";
    gotoxy(x, y++); cout << "            ¡¬|                |/)                   ";
    gotoxy(x, y++); cout << "              |      \\__/      |                         ";
    gotoxy(x, y++); cout << "               |  { ______ }  /                      ";
    gotoxy(x, y++); cout << "               ¡¬     --     /                       ";
    gotoxy(x, y++); cout << "                ¡¬          /                   ";
    gotoxy(x, y++); cout << "                | ¡¬______¢Ö |                               ";
    gotoxy(x, y++); cout << "           _____|           |____                 ";
    gotoxy(x, y++); cout << "       ___£¯    ¡¬          /    ¡¬___        ";
    gotoxy(x, y++); cout << "                 ¡¬__    __/                   ";
    gotoxy(x, y++); cout << "       [      ]   |  ¡¬ /  |                        ";
    gotoxy(x, y++); cout << "                                                 ";
}

#endif