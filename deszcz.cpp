#include <allegro5/allegro_primitives.h>
//#include "allegro5/allegro_image.h"
#include "deszcz.h"

void kropla::rysuj()
{
    if (jest==true)
    {
        al_draw_circle( x,  y,  promien, al_map_rgb(kolor,kolor,kolor),1);
        al_draw_circle( x,  y,  promien+2, al_map_rgb(kolor-2,kolor-2,kolor-2),1);
        promien+=dr;
        kolor=kolor-wygaszenie;
        if (kolor<5)
        {
             x=(rand() % 600 ) + 100;
             y=(rand() % 400 ) + 100;
             promien=2;
             wygaszenie=(rand() % 3)+1;
             kolor=(rand() % 150 ) + 100;
             dr=(((rand() % 15)+5)/10)+0.5;
            jest=true;
        }
    }
}

void kropla::init()
{
     x=(rand() % 600 ) + 100;
     y=(rand() % 400 ) + 100;
     promien=2;
     wygaszenie=(rand() % 2)+1;
     kolor=(rand() % 150 ) + 100;
     dr=(((rand() % 15)+5)/10)+0.5;
     jest=true;
}


void kropla::init1()
{
    // x=(rand() % 600 ) + 100;
     //y=(rand() % 400 ) + 100;
    x=dinit1;
    y=300;
    promien=2;
    wygaszenie=(rand() % 2)+1;
    // kolor=(rand() % 150 ) + 100;
    dr=(((rand() % 15)+5)/10)+0.5;
    jest=true;
}


