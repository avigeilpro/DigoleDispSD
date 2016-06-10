#include "button_class.h"
NButton::NButton(){
    count=0;
    }

void NButton::reset(){
    count=0;
}
void NButton::addbutton(int x,int y,int w,int h,const uint8_t *graph,int gx,int gy,char *text,int ox,int oy,int tsize,int color,int bcolor){
    buttons[count].position.x = x;
    buttons[count].position.y = y;
    buttons[count].size.x = w;
    buttons[count].size.y = h;
    buttons[count].graph = graph;
    buttons[count].gsize.x = gx;
    buttons[count].gsize.y = gy;
    buttons[count].tsize = tsize;
    buttons[count].offset.x = ox;
    buttons[count].offset.y = oy;
    buttons[count].color = color;
    buttons[count].bcolor = bcolor;
    
    size_t destination_size = strlen(text);
    strncpy(buttons[count].text,text, destination_size);
    buttons[count].text[destination_size] = '\0';
    
    count++;
}

void NButton::draw(int num){
        
        int x=buttons[num].position.x;
        int y=buttons[num].position.y;
        int w=buttons[num].size.x;
        int h=buttons[num].size.y;

        int gx = buttons[num].gsize.x;
        int gy = buttons[num].gsize.y;

        int btnbackColor=buttons[num].bcolor;
        int btnColor=buttons[num].color;
        
        int offsetx=buttons[num].offset.x;
        int offsety=buttons[num].offset.y;
        int FontSize=buttons[num].tsize;
        
        Display.setColor(btnColor);
        Display.drawBox(x,y,w,h);
        Display.setColor(btnbackColor);
        Display.drawFrame(x + 5,y + 5,w - 10,h - 10);
        
        Display.drawLine(x + 1,y+1,x + 5,y + 5);
        Display.drawLine(x+w-1,y+1,x+w - 5,y + 5);
        Display.drawLine(x+1,y+h-1,x+5,y+h-5);
        Display.drawLine(x+w-1,y+h-1,x+w-5,y+h-5);
        
        Display.setColor(btnColor);
        Display.setBgColor();
        Display.setColor(btnbackColor);
        if (buttons[num].graph == NULL){
            Display.setFont(FontSize);
            Display.drawAbsStr(x+offsetx,y+offsety,buttons[num].text);
        } else {
            Display.drawBitmap(x+offsetx,y+offsety,gx,gy,buttons[num].graph);
        }
        
        Display.setColor(BackColor);
        Display.setBgColor();
        Display.setColor(1);

}

void NButton::drawAll(void){
    for (int i=0; i<count;i++){
        draw(i);
    }
}

void NButton::drawClick(int num){
        
        int x=buttons[num].position.x;
        int y=buttons[num].position.y;
        int w=buttons[num].size.x;
        int h=buttons[num].size.y;

        int btnbackColor=buttons[num].bcolor;
        int btnColor=buttons[num].color;

        int offsetx=buttons[num].offset.x;
        int offsety=buttons[num].offset.y;
        int FontSize=buttons[num].tsize;

        Display.setColor(0);
        Display.drawFrame(x + 5,y + 5,w - 10,h - 10);
        
        Display.drawLine(x + 1,y+1,x + 5,y + 5);
        Display.drawLine(x+w-1,y+1,x+w - 5,y + 5);
        Display.drawLine(x+1,y+h-1,x+5,y+h-5);
        Display.drawLine(x+w-1,y+h-1,x+w-5,y+h-5);
        
        Display.setColor(btnColor);
        Display.setBgColor();
        Display.setColor(0);
        if (buttons[num].graph == NULL){
            Display.setFont(FontSize);
            Display.drawAbsStr(x+offsetx,y+offsety,buttons[num].text);
        } else {
            //Display.drawBitmap(x,y,offsetx,offsety,buttons[num].graph);
        }

        delay(100);
        
        Display.setColor(btnbackColor);
        Display.drawFrame(x + 5,y + 5,w - 10,h - 10);
        
        Display.drawLine(x + 1,y+1,x + 5,y + 5);
        Display.drawLine(x+w-1,y+1,x+w - 5,y + 5);
        Display.drawLine(x+1,y+h-1,x+5,y+h-5);
        Display.drawLine(x+w-1,y+h-1,x+w-5,y+h-5);
        
        Display.setColor(btnColor);
        Display.setBgColor();
        Display.setColor(btnbackColor);
        if (buttons[num].graph == NULL){
            Display.setFont(FontSize);
            Display.drawAbsStr(x+offsetx,y+offsety,buttons[num].text);
        } else {
            //Display.drawBitmap(x,y,offsetx,offsety,buttons[num].graph);
        }
        
        Display.setColor(BackColor);
        Display.setBgColor();
        Display.setColor(1);

}
void NButton::changetext(int num, char *text){

    size_t destination_size = sizeof (text);
    strncpy(buttons[num].text,text, destination_size);
    buttons[num].text[destination_size] = '\0';
}

void NButton::changecolor(int num, int text_color, int back_color){
    buttons[num].color=text_color;
    buttons[num].bcolor=back_color;
}

int NButton::CheckButtons(void (*but_click)(int),void (*out_but)(int,int)){
    
    int x,y,a,b,c,d;
    int but=-1;
    //Serial.println("a");
    Display.readTouchScreen();
    Serial.println("b");
    delay(1);
    x = Display.read1() << 8;
    delay(1);
    x |= Display.read1();
    delay(1);
    y = Display.read1() << 8;
    delay(1);
    y |= Display.read1();
    delay(1);
Serial.println("c");

    //évite le plantage
    Display.write((uint8_t)0);

//Serial.println("d");
    //click sur l'écran
    if ((x<320)&&(y<240)){
        for (int i=0; i<count;i++){
            a=buttons[i].position.x;
            b=buttons[i].position.y;
            c=buttons[i].size.x;
            d=buttons[i].size.y;
            if ((x>=a)&&(x<=(a+c))&&(y>=b)&&(y<=(b+d))){
                but=i;
                break;
            }
        }
        if (but!=-1){
            drawClick(but);
            //main_button_click(buttonpressed);
            but_click(but);
        } else {
            out_but(x,y);
        }
    }
//Serial.println("e");
    return but;
}
