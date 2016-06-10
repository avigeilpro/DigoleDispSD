#ifndef button_class
#define button_class

#include "application.h"
#include "DigoleSerialDisp.h"

struct coord {
    int x;
    int y;
};

struct button {
    coord position;
    coord size;
    const uint8_t *graph;
    coord gsize;
    char text[20];
    int tsize;
    coord offset;
    int color;
    int bcolor;
    bool enable;
};

class NButton {
private:
    button buttons[10];
    int count;
protected:
    
public:
    void addbutton(int x,int y,int w,int h,const uint8_t *graph,int gx,int gy,char *text,int ox,int oy,int tsize,int color,int bcolor);
    void draw(int num);
    void drawClick(int num);
    void drawAll(void);
    void changetext(int num, char *text);
    void changecolor(int num, int text_color, int back_color);
    int CheckButtons(void (*but_click)(int),void (*out_but)(int,int));
    void reset();
    
    int BackColor=0;
    NButton();
};

#endif
