#ifndef button_class
#define button_class

#include "application.h"
#include "DigoleSerialDisp.h"

class Button {
private:
    int but_cord[10][4];
    char but_text[10][20];
    int but_text_pos[10][3];
    int but_color[10][2];
    int but_count;
protected:
    
public:
    Button();
    void init(int count,int *cord,char *text,int *position,int *color);
    void draw(int num);
    void drawClick(int num);
    void drawAll(void);
    void changetext(int num, char *text);
    void changecolor(int num, int *color);
    int CheckButtons(void (*but_click)(int),void (*out_but)(int,int));
    int BackColor=0;
    //DigoleSerialDisp *mydisp;
};


#endif
