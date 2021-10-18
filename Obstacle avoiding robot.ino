#include <Servo.h>
#include <NewPing.h>

NewPing SONAR(11, 10, 50);  //tri  eco
Servo RADER;

#define LPWM 6
#define RPWM 5

#define LMF A1
#define LMB A0
#define RMF A2
#define RMB A3

#define SPD 100
#define DELAY 1000

void setup() {
  pinMode(13,OUTPUT);digitalWrite(13,1);
  pinMode(LMF,OUTPUT);   pinMode(LMB,OUTPUT);   pinMode(LPWM, OUTPUT);
  pinMode(RMF,OUTPUT);   pinMode(RMB,OUTPUT);   pinMode(RPWM, OUTPUT);
   
  RADER.attach(9);
  
  
 }


void loop() {
  RADER.write(80);
  int DIST= SONAR.ping_cm();
  
  if(DIST==0 or DIST >30)
      Set_Speed(SPD, SPD);
      
  else{
     Set_Speed(0, 0);
     int MAX=0;
     int ANG=95;
     for(int i=0; i<180; i++){
          RADER.write(i); delay(40);
          int DIST= SONAR.ping_cm();
          if(DIST>=MAX){
            MAX=DIST;
            ANG=i;
            }
        }

     if(ANG>170)
          Set_Speed(-200, 200), delay(DELAY);

      else if(ANG>140)
          Set_Speed(-150, 150), delay(DELAY);

      else if(ANG>110)
          Set_Speed(0, 150), delay(DELAY);

      else if(ANG>95)
          Set_Speed(100, 200), delay(DELAY);

      else if(ANG>80)
          Set_Speed(200, 100), delay(DELAY);
           
      else if(ANG>50)
          Set_Speed(150, 0), delay(DELAY);
           
      else if(ANG>20)
          Set_Speed(150, -150), delay(DELAY);

      else if(ANG<=20)
          Set_Speed(200, -200), delay(DELAY);

      }
      
 
    
    
}



inline void Set_Speed(int L, int R){
  if(L>=0)
    { digitalWrite(LMF,1); digitalWrite(LMB,0); analogWrite(LPWM, L);}
  else
    { digitalWrite(LMF,0); digitalWrite(LMB,1); analogWrite(LPWM, abs(L)); }

  if(R>=0)
    { digitalWrite(RMF,1); digitalWrite(RMB,0); analogWrite(RPWM, R);}
  else
    { digitalWrite(RMF,0); digitalWrite(RMB,1); analogWrite(RPWM, abs(R)); }

//Serial.print(L); Serial.print(' ');Serial.print(R); Serial.println(' ');
    
}
