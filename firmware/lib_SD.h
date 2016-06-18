#include "sd-card-library-photon-compat/sd-card-library-photon-compat.h"
#include "accel_gyro.h"

#ifndef lib_SD
#define lib_SD

File myFile;

int WriteFile(char *Folder, char *FName, String Text, int Final, int OverWrite = 0)
    {
    char FullAddr[40];
    FullAddr[0]=0;
    if (!((Folder[0] == 0)||((Folder[0] == '/')&(Folder[1]==0)))){
        if (!SD.exists(Folder)) {
            SD.mkdir(Folder);
        }
        sprintf(FullAddr,"%s/%s",Folder,FName);
    } else {
        strcat(FullAddr,FName);
    }
    
      // open the file. note that only one file can be open at a time,
      // so you have to close this one before opening another.
      if (OverWrite){
          myFile = SD.open(FullAddr, FILE_WRITE | O_TRUNC);
      }else{
          myFile = SD.open(FullAddr, FILE_WRITE);
      }

    // if the file opened okay, write to it:
      if (myFile) {
        if (Final){
            myFile.println(Text);
        } else {
            myFile.print(Text);
        }
      // close the file:
        myFile.close();
        return 1;
      } else {
        return 0;
      }
     
}

char *ReadFile(char *Folder, char *FName) {
    char FullAddr[40];
    char result[600];
    result[0]=0;
    char tmp[2];
    
    sprintf(FullAddr,"%s/%s",Folder,FName);
    
    myFile = SD.open(FullAddr);
    if (myFile) {
        Serial.println(FullAddr);
        
        // read from the file until there's nothing else in it:
        while (myFile.available()) {
          sprintf(tmp,"%c",myFile.read());
          strcat(result,tmp);
        }
        // close the file:
        myFile.close();
    }
  return result;
}

void GetCFG(uint8_t id){
    char result[600];
    result[0]=0;
    char tmpVal[20][10];
    char * pch;
    int i;
    
    sprintf(result,"%s",ReadFile("CONFIG",datacfg[id][0]));
    if (result[0]==0) {
        sprintf(result,"%s",datacfg[id][1]);
    }
    
    i=0;
    pch = strtok (result,"|");
    while (pch != NULL)
    {
        tmpVal[i][0]=0;
        strcat(tmpVal[i],pch);
        i++;
        pch = strtok (NULL, "|");
    }
    switch(id){
        case 0: //cfg accelero
              rx[0] = atof(tmpVal[0]);
              rx[1] = atof(tmpVal[1]);
              rx[2] = atof(tmpVal[2]);
              ry[0] = atof(tmpVal[3]);
              ry[1] = atof(tmpVal[4]);
              ry[2] = atof(tmpVal[5]);
              rz[0] = atof(tmpVal[5]);
              rz[1] = atof(tmpVal[7]);
              rz[2] = atof(tmpVal[8]);
              
              Serial.println("parametres :");
              Serial.println(rx[0],6);
              Serial.println(rx[1],6);
              Serial.println(rx[2],6);
              Serial.println(ry[0],6);
              Serial.println(ry[1],6);
              Serial.println(ry[2],6);
              Serial.println(rz[0],6);
              Serial.println(rz[1],6);
              Serial.println(rz[2],6);
              break;
        default:    //inexistant
                
            break;
    }

}

void SaveCFG(uint8_t id){
    char result[600];
    result[0]=0;
    switch(id){
        case 0: //cfg accelero
              sprintf(result,"%.6f|%.6f|%.6f|%.6f|%.6f|%.6f|%.6f|%.6f|%.6f",rx[0],rx[1],rx[2],ry[0],ry[1],ry[2],rz[0],rz[1],rz[2]);
              Serial.println(result);
              break;
        default:    //inexistant
                
            break;
    }
    
    WriteFile("CONFIG",datacfg[id][0],result,false,true);

}


#endif
