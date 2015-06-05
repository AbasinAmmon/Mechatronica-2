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
int x=0;
int y=0;
int z=0;
int g=0;
void links();
void rechts();
void omhoog();
void omlaag();
void grijper_open();
void grijper_dicht();
DDRB = DDRB | B00000000;
PORTB = B00000000;


void setup(){
  //Communicatie tussen arduino en pololu controller starten
  maestroSerial.begin(9600);
  //motorsnelheid instellen
  maestro.setAcceleration(0,10);
  maestro.setAcceleration(1,10);
  maestro.setAcceleration(2,10);
  maestro.setAcceleration(3,10);
  maestro.setAcceleration(4,10);
  maestro.setAcceleration(5,10);
  
  //BEGIN STAND(helemaal boven)
   maestro.setTarget(0, 2448);
   maestro.setTarget(1, 610);
   maestro.setTarget(2, 1400);  
   maestro.setTarget(3., 908); 
   maestro.setTarget(4, 2022);
   maestro.setTarget(5, 1400);
  
  //oneindige loop voor het inlezen van de richting
  for(;;){
    if (PORTB == 0x01){
      x=1;
      links();
    }
    if (PORTB == 0x02){
      x=1;
      rechts();
    }
    if (PORTB == 0x04){
      y=1;
      omhoog();
    }
    if (PORTB == 0x08){
      y=1;
      omlaag();
    }
    if (PORTB == 0x10){
      g=0;
      grijper_dicht();
    }
    if (PORTB == 0x20){
      g=1;
      grijper_open();
    }
  }

}

void links(){
 for(i=0;x==1;i++){
   if (portb != 0x01){
     x=0;
   }
   maestro.setTarget(5, 400+i);  
 }
}

void rechts(){
 for(i=2200;x==1;i--){
   if (portb != 0x02){
     x=0;
   }
   maestro.setTarget(5, 2200-i); 
  if (i>400){
   x=0;
   }
 }
}

void omhoog(){
 for(i=0;y==1;i++){
   if (portb != 0x04){
     y=0;
   }
   maestro.setTarget(1, 2150-(i*77));
   maestro.setTarget(2, 2200-(i*40));  
   maestro.setTarget(3., 1608-(i*35)); 
   maestro.setTarget(4, 1322+(i*35)); 
   if (i==20){
   y=0;}
 } 
}
 
 void omlaag(){
 for(i=0;y==1;i++){
   if (portb != 0x08){
     y=0;
   }
   maestro.setTarget(1, 610+(i*77));
   maestro.setTarget(2, 1400+(i*40));  
   maestro.setTarget(3., 908+(i*35)); 
   maestro.setTarget(4, 2022+(i*35));  
  if (i==20){
   y=0;}
 } 
}

void grijper_open(){
  for(i=0;g==0;i++){
   if (portb != 0x10){
     g=0;
   }
   maestro.setTarget(0, 2448-i);  
   if (i<1768){
   y=0;
   }
 }

}

void grijper_dicht(){
 for(i=0;g==0;i++){
   if (portb != 0x20){
     g=0;
   }
   maestro.setTarget(0, 1768+i);  
   if (i>2448){
   y=0;
   }
 }

}
