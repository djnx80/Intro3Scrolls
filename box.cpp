#include <allegro5/allegro_primitives.h>
#include <math.h>       /* sin */
#include "box.h"

using namespace std;

void box::rysuj()
{
    al_draw_line(dx+x[1],dy-y[1],dx+x[2],dy-y[2],al_map_rgb(200,70,170),2);
    al_draw_line(dx+x[2],dy-y[2],dx+x[3],dy-y[3],al_map_rgb(50,250,250),2);
    al_draw_line(dx+x[3],dy-y[3],dx+x[4],dy-y[4],al_map_rgb(250,50,90),2);
    al_draw_line(dx+x[4],dy-y[4],dx+x[1],dy-y[1],al_map_rgb(20,70,200),2);
}

void box::obroc()
{
    float xt,yt;
    double sinusk=(sinus*3.14)/180;
    for (int i=1; i<5; i++)
    {
        xt=(x[i]*cos(sinusk))-(y[i]*sin(sinusk));
        yt=(y[i]*cos(sinusk))+(x[i]*sin(sinusk));
        x[i]=xt;
        y[i]=yt;
    }
}

void box::init(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float ddx, float ddy, float ssinus, float dxxx, float dyyy)
{
    x[1]=x1;
    y[1]=y1;
    x[2]=x2;
    y[2]=y2;
    x[3]=x3;
    y[3]=y3;
    x[4]=x4;
    y[4]=y4;
    dx=ddx;
    dy=ddy;
    dxx=dxxx;
    dyy=dyyy;
    sinus=ssinus;
}

void box::przesun()
{
    dx+=dxx;
    dy+=dyy;
    if (dx>500) dxx=-dxx;
    if (dx<300) dxx=-dxx;
}
