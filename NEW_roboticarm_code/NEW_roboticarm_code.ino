#include <stdio.h>
#include <PololuMaestro.h>

#ifdef SERIAL_PORT_HARDWARE_OPEN
  #define maestroSerial SERIAL_PORT_HARDWARE_OPEN
#else
  #include <SoftwareSerial.h>
  SoftwareSerial maestroSerial(10, 11);
#endif

MicroMaestro maestro(maestroSerial);

int i;
int x=1400;
int y1=2022;
int y2=908;
int z1=1400;
int z2=610;
int g=2448;
int keuze;
int s1 = 13;
int s2 = 12;
int s3 = 11;
int s4 = 10;
int s5 = 9;
int s6 = 8;

void setup() {
    //Communicatie tussen arduino en pololu controller starten
  maestroSerial.begin(9600);
  
  pinMode(s1, INPUT_PULLUP); 
  pinMode(s2, INPUT_PULLUP); 
  pinMode(s3, INPUT_PULLUP); 
  pinMode(s4, INPUT_PULLUP); 
  pinMode(s5, INPUT_PULLUP); 
  pinMode(s6, INPUT_PULLUP); 
  
  //motorsnelheid instellen
  maestro.setAcceleration(0,10);
  maestro.setAcceleration(1,10);
  maestro.setAcceleration(2,10);
  maestro.setAcceleration(3,10);
  maestro.setAcceleration(4,10);
  maestro.setAcceleration(5,10);
  
  //BEGIN STAND(helemaal boven)
   maestro.setTarget(0, g);
   maestro.setTarget(1, z2);
   maestro.setTarget(2, z1);  
   maestro.setTarget(3., y2); 
   maestro.setTarget(4, y1);
   maestro.setTarget(5, x);

}

void loop() {
  if (digitalRead(s1) == HIGH){
    keuze = 1;
  }
  if (digitalRead(s2) == HIGH){
    keuze = 2;
  }
  if (digitalRead(s3) == HIGH){
    keuze = 3;
  }
  if (digitalRead(s4) == HIGH){
    keuze = 4;
  }
  if (digitalRead(s5) == HIGH){
    keuze = 5;
  }
  if (digitalRead(s6) == HIGH){
    keuze = 6;
  }
  
switch (keuze) {
  case 1:
    x = x + 1;
    if (x > 2200){
    x = 2200;
    }
    maestro.setTarget(5, x); 
    delay (10);
    break;
  case 2:
    x = x - 1;
    if (x < 1768){
    x = 1768;
    }
    maestro.setTarget(5, x);
    delay (10);
    break;
  case 3:
   y1 = y1 + 35;
   y2 = y2 - 35;
   z1 = z1 - 40;
   z2 = z2 - 77;
   if (y1 > 2022){
   y1=2022;
   }else if (y2 < 908){
   y2=908;
   }else if (z1 < 1400){
   z1=1400;
   }else if (z2 < 610){
   z2=610;
   }
   maestro.setTarget(1, z2);
   maestro.setTarget(2, z1);  
   maestro.setTarget(3, y2); 
   maestro.setTarget(4, y1);
   delay (200);
    break;
  case 4:
   y1 = y1 - 35;
   y2 = y2 + 35;
   z1 = z1 + 40;
   z2 = z2 + 77;
   if (y1 < 1322){
   y1=1322;
   }else if (y2 > 1608){
   y2=1608;
   }else if (z1 > 2200){
   z1=2200;
   }else if (z2 > 2150){
   z2=2150;
   }
   maestro.setTarget(1, z2);
   maestro.setTarget(2, z1);  
   maestro.setTarget(3, y2); 
   maestro.setTarget(4, y1);
   delay (200);
    break;
  case 5:
    g = g - 1;
    if (g < 1768){
    g = 1768;
    }
    maestro.setTarget(0, g);
    delay (10);
    break;
  case 6:
    g = g + 1;
    if (g > 2448){
    g = 2448;
    }
    maestro.setTarget(0, g);
    delay (10);
    break;
    
}
}
