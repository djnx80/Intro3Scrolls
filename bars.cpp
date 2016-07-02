#include <allegro5/allegro_primitives.h>
#include "bars.h"

using namespace std;

void bars::rysujw()
{
    al_draw_line(x,y,x+szer,y,al_map_rgb(100,kolor,70),1);
}

void bars::rysujh()
{
    al_draw_line(x,y,x,y+szer,al_map_rgb(200,kolor,10),1);
}

void bars::init(float xa, float ya, float sza, float ka)
{
    x=xa;
    y=ya;
    szer=sza;
    kolor=ka;
}
