class scroll
{
    public:
        float x,y;
        float sinus;
        float wys;
        float dx,dy;
        unsigned int frekwe=0;
        float gain;
        const char *txt;
        int dl;
        ALLEGRO_FONT    *font8 = al_create_builtin_font();
        ALLEGRO_FONT *fontttf = al_load_ttf_font("tahomabd.ttf",20,0 );
//ALLEGRO_FONT    *font8 = al_load_bitmap_font("courier_16.png");//  wskaünik do czcionki bitmapowej
        void show();
        void init();
};
