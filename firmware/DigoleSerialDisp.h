#ifndef DigoleSerialDisp_h
#define DigoleSerialDisp_h

#include "application.h"

#define _TEXT_ 0
#define _GRAPH_ 1


// Set display width and height in pixels - common Digole display sizes are (HxW): 128x64, 160x128, 96x64
#define DISP_W  160  //screen width in pixels
#define DISP_H  128  //screen Hight in pixels

class DigoleSerialDisp : public Print {
public:

void begin(uint8_t pin_data, uint8_t pin_clock, uint8_t pin_SS, uint8_t pin_SI) {
        _Clockpin = pin_clock;
        _Datapin = pin_data;
        _SSpin = pin_SS;
        _SIpin = pin_SI;
        pinMode(_Clockpin, OUTPUT);
        pinMode(_Datapin, OUTPUT);
        pinMode(_SSpin, OUTPUT);
        digitalWrite(_SSpin, HIGH);
        digitalWrite(_Clockpin, LOW);
        digitalWrite(_Datapin, LOW);
        if (_SIpin != 0) {
            pinMode(_SIpin, INPUT);
        }
        _Comdelay = 6;
}

DigoleSerialDisp() {}

size_t write(uint8_t value){
    digitalWrite(_SSpin, LOW);
    delayMicroseconds(1);
    shiftOut(_Datapin, _Clockpin, MSBFIRST, value);
    delayMicroseconds(1);
    digitalWrite(_SSpin, HIGH);
    delay(2);
    return 1;
}

size_t read1(void)
{
    int t = 0;
    while (digitalRead(_SIpin) == LOW); //check to see the data is ready(1) or not(0)
    digitalWrite(_SSpin, LOW); //tell display module I will read data
    delayMicroseconds(20);
    t=shiftIn(_SIpin, _Clockpin, MSBFIRST);
    digitalWrite(_SSpin, HIGH);
    return t; // assume sucess
}

size_t print(const char *s){
    char p = s[0];
    int i = 0;
    while (p != 0){
        write(p);
        i++;
        p= s[i];
    }
    return 1;
}


size_t print(const int num){
    char s[12];
    sprintf(s,"%d",num);
    char p = s[0];
    int i = 0;
    while (p != 0){
        write(p);
        i++;
        p= s[i];
    }
    return 1;
}

   /*---------fucntions for Text and Graphic LCD adapters---------*/

    void disableCursor(void) {
        print("CS0");
    }

    void enableCursor(void) {
        print("CS1");
    }

    void clearScreen(void) {
        print("CL");
    }

    void displayConfig(uint8_t v) {
        print("DC");
        write(v);
    }
    
    /*----------Functions for Graphic LCD/OLED adapters only---------*/
    //the functions in this section compatible with u8glib
    void drawBitmap(unsigned int x, unsigned int y, unsigned int w, unsigned int h, const uint8_t *bitmap);
    void drawBitmap256(unsigned int x, unsigned int y, unsigned int w, unsigned int h, const uint8_t *bitmap);
    void drawBitmap262K(unsigned int x, unsigned int y, unsigned int w, unsigned int h, const uint8_t *bitmap);
    void setTrueColor(uint8_t r, uint8_t g, uint8_t b);
    void setRot90(void);
    void setRot180(void);
    void setRot270(void);
    void undoRotation(void);
    void setRotation(uint8_t);
    void setContrast(uint8_t);
    void drawBox(unsigned int x, unsigned int y, unsigned int w, unsigned int h);
    void drawCircle(unsigned int x, unsigned int y, unsigned int r, uint8_t = 0);
    void drawDisc(unsigned int x, unsigned int y, unsigned int r);
    void drawFrame(unsigned int x, unsigned int y, unsigned int w, unsigned int h);
    void drawPixel(unsigned int x, unsigned int y, uint8_t = 1);
    void drawLine(unsigned int x, unsigned int y, unsigned int x1, unsigned int y1);
    void drawLineTo(unsigned int x, unsigned int y);
    void drawHLine(unsigned int x, unsigned int y, unsigned int w);
    void drawVLine(unsigned int x, unsigned int y, unsigned int h);
    //-------------------------------
    //special functions for our adapters
    void setFont(uint8_t font); //set font, availale: 6,10,18,51,120,123, user font: 200-203
    void nextTextLine(void); //got to next text line, depending on the font size
    void setColor(uint8_t); //set color for graphic function
    void backLightOn(void); //Turn on back light
    void backLightOff(void); //Turn off back light
    void directCommand(uint8_t d); //send command to LCD drectly
    void directData(uint8_t d); //send data to LCD drectly
    void moveArea(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, char xoffset, char yoffset); //move a area of screen to another place
    void drawStr(unsigned int x, unsigned int y, const char *s);
    void drawAbsStr(unsigned int x, unsigned int y, const char *s);
    void setPrintPos(unsigned int x, unsigned int y, uint8_t = 0);
    void setLCDColRow(uint8_t col, uint8_t row);
    void setTextPosAbs(unsigned int x, unsigned int y);
    /*-----Touch screen functions---*/
    void calibrateTouchScreen(void);
    void readTouchScreen(void);
    void readClick(void);
    int readBattery(void);
    int readAux(void);
    int readTemperature(void);

    /*-----Flash memory functions---*/
    void flashErase(unsigned long int addr, unsigned long int length);
    void flashWriteL(unsigned long int addr, unsigned long int len, const unsigned char *data);
    void flashWrite(unsigned long int addr, unsigned long int len, const unsigned char *data);
    void flashReadStart(unsigned long int addr, unsigned long int len);
    void setFlashFont(unsigned long int addr);
    void runCommandSet(unsigned long int addr);
    size_t read(void);

    void write2B(unsigned int v);
    //--- new function on V3.0 firmware ----//

    void setBgColor(void) //set current color as background
    {
        print("BGC");
    }

    void setDrawWindow(unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
        print("DWWIN");
        write2B(x);
        write2B(y);
        write2B(width);
        write2B(height);
    }
    void resetDrawWindow(void)
    {
        print("RSTDW");
    }
    void cleanDrawWindow(void)
    {
        print("WINCL");
    }
//---end of V3.0 functions
    void displayStartScreen(uint8_t m) {
        print("DSS");
        write(m);
    } //display start screen

    void setMode(uint8_t m) {
        print("DM");
        write(m);
    } //set display mode

    void setTextPosBack(void) {
        print("ETB");
    } //set text position back to previous, only one back allowed

    void setTextPosOffset(char xoffset, char yoffset) {
        print("ETO");
        write(xoffset);
        write(yoffset);
    }

    void setLinePattern(uint8_t pattern) {
        print("SLP");
        write(pattern);
    }

    void setLCDChip(uint8_t chip) { //only for universal LCD adapter
        print("SLCD");
        write(chip);
    }

    void setBackLight(uint8_t bl) {
        print("BL");
        write(bl);
    }
    void uploadStartScreen(int lon, const unsigned char *data); //upload start screen
    void uploadUserFont(int lon, const unsigned char *data, uint8_t sect); //upload user font

    void digitalOutput(uint8_t x) {
        print("DOUT");
        write(x);
    }
    
private:
    uint8_t _Clockpin;
    uint8_t _Datapin;
    uint8_t _SSpin;
    uint8_t _SIpin;
    uint8_t _Comdelay;

};

extern DigoleSerialDisp Display;
#endif
