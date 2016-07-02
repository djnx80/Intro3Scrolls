#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "scroll.h"
#include <math.h>       /* sin */
#include <string>

using namespace std;

void scroll::show()
{
    x-=3;
    sinus+=0.08;
    wys+=0.1;
    // radiany =( stopnie * M_PI ) / 180.0f;
    y=dy+(sin (sinus)*wys);

    float sinb=sinus;
    float yb=y;
    float wysb=wys;

    for (int k=0; k<dl; k++)
    {
      al_draw_textf (fontttf,al_map_rgb(255-k*2,6,6),dx+x+(k*12),yb,0,"%3c", txt[k]," ");
      al_draw_textf (fontttf,al_map_rgb(6,255-k*2,6),dx+x+(k*12.1),yb-30,0,"%3c", txt[k]," ");
      al_draw_textf (fontttf,al_map_rgb(6,6,255-k*2),dx+x+(k*12.2),yb+30,0,"%3c", txt[k]," ");
      al_draw_textf (fontttf,al_map_rgb(130-k,130-k,6),dx+x+(k*12.3),yb-60,0,"%3c", txt[k]," ");
      al_draw_textf (fontttf,al_map_rgb(130-k,6,130-k),dx+x+(k*12.4),yb+60,0,"%3c", txt[k]," ");
      sinb+=0.1;
      wysb+=0.02;
      yb=dy+(sin (sinb)*wysb);
    }
     al_draw_textf (fontttf,al_map_rgb(250,250,250),400,500,0,"%3f", gain," ");
}

void scroll::init()
{
 txt="SCROLL LECI SOBIE PO SINUSIE. MOZNA WSTAWIC TUTAJ CALKIEM DLUGI NAPIS. A KOLECZKA TO OSZUKANY DESZCZ :) TAKIE TAM NIBY RETRO.   ";
dl=125;
    x=0;
    y=400;
    dx=800;
    dy=300;
    sinus=0;
    wys=50;
}
