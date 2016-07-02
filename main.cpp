#include <stdio.h>
#include "allegro5/allegro.h"
#include <allegro5/allegro_primitives.h>
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <math.h>       /* sin */

#include "deszcz.h"
#include "scroll.h"
#include "bars.h"
#include "box.h"

using namespace std;

int bump2d(int dxx, int dyy);
void point(unsigned char *pt, int xx, int yy,int r, int g, int b);
void pointbump(unsigned char *pt, int xx, int yy,int r, int g, int b);


const int screenW=800;
const int screenH=600;
int kolb=0;
float wspbump=0, dwspbump=0.005;
    int light[300][300][5];
	ALLEGRO_BITMAP  *swiatlobump   = NULL;
    ALLEGRO_BITMAP *tlobump = NULL;
    ALLEGRO_BITMAP *wyjsciebump = NULL;



int main(int argc, char **argv)
{
    srand( time( NULL ) );  // losowosc
	ALLEGRO_DISPLAY *display = NULL;    //ekran
	if(!al_init()) { fprintf(stderr, "Nie mozna zainicjalizowac allegro!\n"); }

    al_install_keyboard();  // init klawiatury
    ALLEGRO_KEYBOARD_STATE klawisz;
        al_set_new_display_flags(ALLEGRO_WINDOWED);
                                 //ALLEGRO_FULLSCREEN);
	display = al_create_display(800, 600);      // ekran
	if(!display) { fprintf(stderr, "Nie mozna utworzyc bitplanu!\n"); }
    al_init_image_addon();      // to musi byc jezeli wyswietlamy rysunek
	al_init_primitives_addon(); // to musi byc jezeli rysujemy prymitywy
	al_init_font_addon();
    al_init_ttf_addon();
  	al_install_audio();
	al_init_acodec_addon();

    ALLEGRO_SAMPLE *song = NULL;
    ALLEGRO_SAMPLE_INSTANCE *songIns = NULL;

    al_reserve_samples(1);
    song = al_load_sample("dubikos.ogg");
    songIns = al_create_sample_instance(song);

    al_set_sample_instance_playmode(songIns, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(songIns, al_get_default_mixer());

		al_play_sample_instance(songIns);

 //    al_play_sample(song, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);
   //  unsigned int al_get_sample_frequency(const ALLEGRO_SAMPLE *spl)
     unsigned int frekw;


//    if(!fontttf) {
//		al_destroy_display(display);
//    return -5;	}

// INICJACJA KROPEL DESZCZU I SCROLLU
    kropla k[100];
    for (int i=1; i<100; i++)   k[i].jest=false;
    for (int i=1; i<40; i++)    k[i].init();
    scroll mojscroll;
    mojscroll.init();

    for (int z=1; z<610; z++)                                                                          // POMNIEJSZONE 0 /10
    {
        if (z<550)      al_clear_to_color(al_map_rgb(0,0,0));   // cls
        else            al_clear_to_color(al_map_rgb((z-550)*4,(z-550)*4,(z-550)*4));   // cls

        for (int j=1; j<100; j++)   k[j].rysuj();
//    mojscroll.frekwe = al_get_sample_instance_position(songIns);
    mojscroll.gain = al_get_sample_instance_pan(songIns);
           mojscroll.show();


        al_get_keyboard_state( & klawisz );     // ESC? ->end
        if ( al_key_down( & klawisz, ALLEGRO_KEY_F1 )) return 0;
 		al_flip_display();										// wyswietlany narysowana bitmape (scrren swap w amosie)
		al_rest(0.01);											// opóŸnienie
	}

// ZACIEMNIENIE EKRANU
    for (int z=200; z>1; z--)
    {
 		al_clear_to_color(al_map_rgb(z,z,z));   // cls
        al_get_keyboard_state( & klawisz );     // ESC? ->end
        if ( al_key_down( & klawisz, ALLEGRO_KEY_F1 )) return 0;
 		al_flip_display();										// wyswietlany narysowana bitmape (scrren swap w amosie)
		al_rest(0.005);											// opóŸnienie
	}

// RYSOWANIE PASKOW
	bars bar1;
	bars bar2;
    bars bar3;
    bars bar4;
	bar1.init(100,50,100,50);
	bar2.init(553,400,100,100);
	bar3.init(600,550,100,150);
	bar4.init(247,100,100,200);
    al_clear_to_color(al_map_rgb(0,0,0));   // cls

    for (int z=1; z<550; z++)                                                           // POMNIEJSZONE 0 /10
    {
        bar2.rysujh();
        bar1.rysujw();
        bar3.rysujw();
        bar4.rysujh();
        bar1.y++;
        bar3.y--;
        bar2.x--;
        bar4.x++;

        al_get_keyboard_state( & klawisz );     // ESC? ->end
        if ( al_key_down( & klawisz, ALLEGRO_KEY_F1 )) return 0;
 		al_flip_display();										// wyswietlany narysowana bitmape (scrren swap w amosie)
		al_rest(0.004);											// opóŸnienie
	}

// INICJACJA I WYSWIETLANIE BOXOW
    box b[10];
    b[1].init(-10, 10, 10, 10, 10, -10, -10, -10, 400, 300, 1,1,0);
    b[2].init(-20, 20, 20, 20, 20, -20, -20, -20, 400, 300, 2,1.2,0);
    b[3].init(-30, 30, 30, 30, 30, -30, -30, -30, 400, 300, 3,1.4,0);
    b[4].init(-40, 40, 40, 40, 40, -40, -40, -40, 400, 300, 4,1.6,0);
    b[5].init(-50, 50, 50, 50, 50, -50, -50, -50, 400, 300, 5,1.8,0);
    b[6].init(-60, 60, 60, 60, 60, -60, -60, -60, 400, 300, 6,2,0);
    b[7].init(-70, 70, 70, 70, 70, -70, -70, -70, 400, 300, 7,2.2,0);

    for (int z=1; z<800; z++)                                                     // POMNIEJSZONE 0 /10
    {
        al_draw_filled_rectangle(200,200,600,400,al_map_rgba(0,0,0,160));
        for (int p=1; p<8; p++)
        {
            b[p].rysuj();
            b[p].obroc();
            if (z>150)   b[p].przesun();
        }

        al_get_keyboard_state( & klawisz );     // ESC? ->end
        if ( al_key_down( & klawisz, ALLEGRO_KEY_F1 )) return 0;
 		al_flip_display();										// wyswietlany narysowana bitmape (scrren swap w amosie)
		al_rest(0.02);											// opóŸnienie
	}


// ZACIEMNIENIE EKRANU
    for (int z=200; z>1; z--)
    {
 		al_clear_to_color(al_map_rgb(z,z,z));   // cls
        al_get_keyboard_state( & klawisz );     // ESC? ->end
        if ( al_key_down( & klawisz, ALLEGRO_KEY_F1 )) return 0;
 		al_flip_display();										// wyswietlany narysowana bitmape (scrren swap w amosie)
		al_rest(0.005);											// opóŸnienie
	}


// ZOOM & ROTATE BITMAP
    ALLEGRO_BITMAP  *bitmapa   = NULL;		// inicjujemy bitmape
    bitmapa = al_load_bitmap("plasma.png");	// ładujemy rysunek
    ALLEGRO_FONT *font = al_load_ttf_font("tahomabd.ttf",72,0 );
	if(!font) {
		al_destroy_display(display);
		return -5;	}
    float kat=0;
    float zoomx=2, zoomy=2;
    float zoomdx=0.02,zoomdy=0.02;

    for(int z=1; z<700; z++)                                                                 // POMNIEJSZONE 0 /100
    {
		al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_tinted_scaled_rotated_bitmap(bitmapa, al_map_rgb(kat*12,kat*20,kat*8), 400,300,400,300,zoomx,zoomy,kat,0);
        al_draw_text(font, al_map_rgb(255,255,255), 400, 500,ALLEGRO_ALIGN_CENTRE, "A tu jakis tekst :)");

        kat+=0.03;
        zoomx+=zoomdx;
        zoomy+=zoomdx;
        if (zoomx>3) zoomdx=-zoomdx;
        if (zoomy>3) zoomdy=-zoomdy;
        if (zoomx<1.5) zoomdx=-zoomdx;
        if (zoomy<1.5) zoomdy=-zoomdy;

        al_get_keyboard_state( & klawisz );     // ESC? ->end
        if ( al_key_down( & klawisz, ALLEGRO_KEY_F1 )) return 0;

 		al_flip_display();										// wyswietlany narysowana bitmape (scrren swap w amosie)
		al_rest(0.008);											// opóŸnienie
	}


zoomdx=-0.002;                // powinno byc 0.002
zoomdy=-0.002;
//    for(int z=1; z<700; z++)
        while (zoomx>0.01)
    {
        al_get_keyboard_state( & klawisz );
		al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_tinted_scaled_rotated_bitmap(bitmapa, al_map_rgb(kat*12,kat*20,kat*8), 400,300,400,300,zoomx,zoomy,kat,0);
        al_draw_text(font, al_map_rgb(255,255,255), 400, 500,ALLEGRO_ALIGN_CENTRE, "i druga linia tekstu");

        kat+=0.03;
        zoomx+=zoomdx;
        zoomy+=zoomdx;

        al_get_keyboard_state( & klawisz );     // ESC? ->end
        if ( al_key_down( & klawisz, ALLEGRO_KEY_F1 )) return 0;

 		al_flip_display();										// wyswietlany narysowana bitmape (scrren swap w amosie)
		al_rest(0.008);											// opóŸnienie
	}






    float kolor;
    double dx=8;
    float zx=2,zy=2,dkat=0.03;
    kat=0;
    float dzx=0.05, dzy=0.16;
    int w=800, h=600, roznica=0;
	int kol[800][600];

    for (int y=1; y<h; y++)    {
        for (int x=1; x<w; x++)        {
            kolor = (sin((x+y+dx)/dx)*128)+128;
            kolor=  (128.0 + (128.0 * sin(x / 8.0)) + 128.0 + (128.0 * sin(y / 8.0))) / 2+kolor/3;
           // kolor=  128.0 + (128.0 * sin(sqrt((x - w / 2.0) * (x - w / 2.0) + (y - h / 2.0) * (y - h / 2.0)) / dx));
              kolor=  ((128.0 + (128.0 * sin(x / 8.0)) + 128.0 + (128.0 * sin(y / 8.0))) / 2+kolor/2);
            if (kolor<0) kolor=0;
            if (kolor>255) kolor=255;
            kol[x][y]=kolor;
        }
    }



      for (int z=1; z<700; z++)                                                  // POMNIEJSZONE 0 /10
    {

	al_clear_to_color(al_map_rgb(0,0,0));

    ALLEGRO_LOCKED_REGION *lr = al_lock_bitmap(bitmapa, ALLEGRO_PIXEL_FORMAT_ABGR_8888, ALLEGRO_LOCK_WRITEONLY);
    unsigned char *ptr = (unsigned char *)lr->data;

    for (int y=1; y<h; y++)    {
        for (int x=1; x<w; x++) {
            kolor=  kol[x][y];
            point(ptr, x, y, kolor, kolor, kolor);
            kolor+=3;
            if (kolor<0) kolor=0;
            if (kolor>255)
            {
                roznica=kolor-255;
                kolor=roznica;
            }
            kol[x][y]=kolor;
        }
    }

    al_unlock_bitmap(bitmapa);
    al_draw_scaled_rotated_bitmap(bitmapa,400,300,400,300,zx,zy,kat,0);
                                  //, float cx, float cy, float dx, float dy, float xscale, float yscale,   float angle, int flags)
    zx+=dzx;
    zy+=dzy;
    if (zx>5) dzx=-dzx;
    if (zy>15) dzy=-dzy;
    if (zx<1.7) dzx=-dzx;
    if (zy<1.7) dzy=-dzy;
    kat+=dkat;
    kolb++;
    if (kolb>255) kolb=0;

   /// al_draw_bitmap(bitmapa, 0,0,0);

    al_get_keyboard_state( & klawisz );
    if ( al_key_down( & klawisz, ALLEGRO_KEY_F1 )) return 0;
 	al_flip_display();
	}

	swiatlobump = al_load_bitmap("swiatlo1.png");
    tlobump=al_load_bitmap("tlo1.png");
    wyjsciebump=al_load_bitmap("wyjscie.png");


        ALLEGRO_LOCKED_REGION *lock1;
    ALLEGRO_LOCKED_REGION *lock2;

    lock1 = al_lock_bitmap(swiatlobump, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_READONLY);
    lock2 = al_lock_bitmap(tlobump, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_READONLY);
 al_draw_bitmap(wyjsciebump, 0,0,0);


     unsigned char rr,gg,bb,aa;
    ALLEGRO_COLOR kolorbump;

         for (int y=1; y<220; y++)    {
        for (int x=1; x<220; x++)   {
            kolorbump = al_get_pixel(swiatlobump, x, y);
            al_unmap_rgba(kolorbump, &rr, &gg, &bb, &aa);
            light[x][y][1]=rr;
            light[x][y][2]=gg;
            light[x][y][3]=bb;
            light[x][y][4]=aa;
        }
    }


    int dxbump=50,dybump=50;
int ddxbump=3,ddybump=3;

    while( !al_key_down( & klawisz, ALLEGRO_KEY_F1 ) )
    {

		al_clear_to_color(al_map_rgb(0,0,0));

bump2d(dxbump,dybump);
//return -5;

//bump2d(dx+20,dy+20);

dxbump+=ddxbump;
dybump+=ddybump;
if (dxbump>500) ddxbump=-ddxbump;
if (dybump>400) ddybump=-ddybump;
if (dxbump<20) ddxbump=-ddxbump;
if (dybump<20) ddybump=-ddybump;

        al_get_keyboard_state( & klawisz );
 		al_flip_display();										// wyswietlany narysowana bitmape (scrren swap w amosie)
	//	al_rest(0.008);											// opoznienie
	}


    al_destroy_font(font);
	al_destroy_display(display);
    al_destroy_sample(song);
    al_destroy_sample_instance(songIns);
	return 0;
}




// BUMP2D

int bump2d(int dxx, int dyy)
{

  //  cout <<"wejscie do bump2d\n";

//    ALLEGRO_COLOR kolor;
    ALLEGRO_COLOR kolor1;
    ALLEGRO_COLOR kol;
    unsigned char rr,gg,bb,aa;
    unsigned char r1,g1,b1,a1;
    int r2,g2,b2,a2;
    bool ciemne=true;

ALLEGRO_LOCKED_REGION *lr = al_lock_bitmap(wyjsciebump, ALLEGRO_PIXEL_FORMAT_ABGR_8888, ALLEGRO_LOCK_WRITEONLY);
unsigned char *ptr = (unsigned char *)lr->data;

wspbump+=dwspbump;
if (wspbump>1.3) dwspbump=-dwspbump;
if (wspbump<0.001) dwspbump=-dwspbump;


   // cout <<"po sprawdzeniu wspbump.\n";

        for (int y=1; y<220; y++)    {
        for (int x=1; x<220; x++)   {


   // cout <<"x= "<<x<<"    y="<<y<<". ";
            rr=light[x][y][1];
            gg=light[x][y][2];
            bb=light[x][y][3];
            aa=light[x][y][4];

//    cout <<"rrggbb"<<rr<<"\n";

            kolor1= al_get_pixel(tlobump,dxx+x,dyy+y);
            al_unmap_rgba(kolor1, &r1, &g1, &b1, &a1);

  //  cout <<"unmap i kolor1"<<rr<<"\n";
ciemne=true;
            if(rr>0 && gg>0 && bb>0)            {
                ciemne=false;
                if (b1>1 )              {               // w zaleznosci od tego czy tlo biale czy czarne to >, lub < 0.001
                    r2=(rr+r1)*wspbump;
                    g2=(gg+g1)*wspbump;
                    b2=(bb+b1)*wspbump;
                    a2=aa+a1;
                    if (r2>255) r2=255;
                    if (g2>255) g2=255;
                    if (b2>255) b2=255;
                    kol= al_map_rgba(r2, g2, b2, a2);
                }
                else
                {   kol=al_map_rgba(0,0,0,0);
                    r2=0;
                    g2=0;
                    b2=0; }
            }
            else    {
                    kol=al_map_rgba(0,0,0,0);
                                r2=0;
                    b2=0; }
 //cout <<"a moze point???\n";

        //        pointbump(ptr, dxx+x,dyy+y,r2,g2,b2);

                    int pixel;
    pixel = (dxx+x)+((dyy+y)*screenW);

//    cout <<"\nPOINTER:"<<ptbump<<"   pixel:"<<pixel<<"  xx:"<<xx<<"    yy:"<<yy<<"   rgb:"<<r<<" "<<g<<" "<<b;

//    ptr[pixel*4] = (rand() % r2 )+1;
//    ptr[pixel*4+1] = g2;
//    ptr[pixel*4+2] = kolb;
if (pixel<(screenW*screenH) && ciemne==false )
{
    ptr[pixel*4] = r2;
    ptr[pixel*4+1] = g2;
    ptr[pixel*4+2] = b2;
}

        }
    }

al_unlock_bitmap(wyjsciebump);
al_draw_bitmap(wyjsciebump, 0,0,0);

return 0;
}



void point(unsigned char *pt, int xx, int yy,int r, int g, int b)
{
    int pixel;
    pixel = xx+yy*screenW;

 //   cout <<"\npixel:"<<pixel<<"  xx:"<<xx<<"    yy:"<<yy<<"   rgb:"<<r<<" "<<g<<" "<<b;

    pt[pixel*4] = (rand() % r )+1;
    pt[pixel*4+1] = g;
    pt[pixel*4+2] = kolb;
   // pt[pixel*4+3]=0;
}


void pointbump(unsigned char *ptbump, int xx, int yy,int r, int g, int b)
{
    int pixel;
    pixel = xx+yy*screenW;

    cout <<"\nPOINTER:"<<ptbump<<"   pixel:"<<pixel<<"  xx:"<<xx<<"    yy:"<<yy<<"   rgb:"<<r<<" "<<g<<" "<<b;

 //   pt[pixel*4] = (rand() % r )+1;
//    pt[pixel*4+1] = g;
//    pt[pixel*4+2] = kolb;
    ptbump[pixel*4] = 100;
    ptbump[pixel*4+1] = 100;
    ptbump[pixel*4+2] = 100;


   // pt[pixel*4+3]=0;
}

