#include <Arduino_FreeRTOS.h>

void TaskS1( void *pvParameters );
void TaskS2( void *pvParameters );
void TaskS3( void *pvParameters );
void TaskS4( void *pvParameters );
void TaskS5( void *pvParameters );
//void TaskS6( void *pvParameters );
//void TaskS7( void *pvParameters );
//void TaskS8( void *pvParameters );
void TaskD1( void *pvParameters );


int directions[4]={0,0,0,0}; //direction bits= Forw,Right,Backw,Left
int rp=0; //Right prohibit: 0= allow going right, 1= forbid going right 
int dl=0; //delay on turning
int sp=10;
int dirPriority=0; //direction priority bit: 0=Forw, 1,...


int motoDrivers[] = {2, 3, 4, 5, 8, 9, 10, 11}; //=>L298N

int fr_in3 = motoDrivers[2]; //f -> front => fr_in3 = 4
int fr_in4 = motoDrivers[3];

int fl_in1 = motoDrivers[4];
int fl_in2 = motoDrivers[5];

int br_in1 = motoDrivers[0]; //b -> back
int br_in2 = motoDrivers[1];

int bl_in3 = motoDrivers[6];
int bl_in4 = motoDrivers[7];

int trig1 = 30;
int echo1 = 31;
int g1 = 32;
int r1 = 33;
int distance1=1;

int trig2 = 26;
int echo2 = 27;
int g2 = 28;
int r2 = 29;
int distance2=1;

int trig3 = 22;
int echo3 = 23;
int g3 = 24;
int r3 = 25;
int distance3=1;

int trig4 = 48;
int echo4 = 49;
int g4 = 46;
int r4 = 47;
int distance4=1;

int trig5 = 20;
int echo5 = 21;
int g5 = 18;
int r5 = 19;
int distance5=1;

int trig6 = 16;
int echo6 = 17;
int g6 = 14;
int r6 = 15;
int distance6=1;

int trig7 = 38;
int echo7 = 39;
int g7 = 41;
int r7 = 40;
int distance7=1;

int trig8 = 34;
int echo8 = 35;
int g8 = 36;
int r8 = 37;
int distance8=1;


// --------------------------------------------------------------------------------------------------------------------------------- //

void fr_stop(){
  analogWrite(fr_in3, 0);
  analogWrite(fr_in4, 0);
}

void fl_stop(){
  analogWrite(fl_in1, 0);
  analogWrite(fl_in2, 0);
}

void br_stop(){
  analogWrite(br_in1, 0);
  analogWrite(br_in2, 0);
}

void bl_stop(){
  analogWrite(bl_in3, 0);
  analogWrite(bl_in4, 0);
}

// --------------------------------------------------------------------------------------------------------------------------------- //

void fr_cw(int anaValue){
  analogWrite(fr_in3, anaValue);
  analogWrite(fr_in4, 0);
}

void fl_cw(int anaValue){
  analogWrite(fl_in1, 0);
  analogWrite(fl_in2, anaValue);
}

void br_cw(int anaValue){
  analogWrite(br_in1, anaValue);
  analogWrite(br_in2, 0);
}

void bl_cw(int anaValue){
  analogWrite(bl_in3, 0);
  analogWrite(bl_in4, anaValue);
}

// --------------------------------------------------------------------------------------------------------------------------------- //

void fr_ccw(int anaValue){
  analogWrite(fr_in3, 0);
  analogWrite(fr_in4, anaValue);
}

void fl_ccw(int anaValue){
  analogWrite(fl_in1, anaValue);
  analogWrite(fl_in2, 0);
}

void br_ccw(int anaValue){
  analogWrite(br_in1, 0);
  analogWrite(br_in2, anaValue);
}

void bl_ccw(int anaValue){
  analogWrite(bl_in3, anaValue);
  analogWrite(bl_in4, 0);
}

// --------------------------------------------------------------------------------------------------------------------------------- //

void stop_car(){
  fr_stop();
  fl_stop();
  br_stop();
  bl_stop();
//  int greens[] = {32, 28, 24, 46, 18, 14, 41, 36};
//  int reds[] = {33, 29, 25, 47, 19, 15, 40, 37};
//  for(int i=0; i<=7; i++ ){
//    digitalWrite(reds[i],0);
//    digitalWrite(greens[i],1);
//  }
//  delay(200);
//  for(int i=0; i<=7; i++ ){
//    digitalWrite(greens[i],0);
//    digitalWrite(reds[i],1);
//  }
//  delay(200);
}

void forward(int fr, int fl, int br, int bl){
  fr_cw(fr);
  fl_cw(fl);
  br_cw(br);
  bl_cw(bl);
}

void go_left(int fr, int fl, int br, int bl){
  fr_cw(fr);
  fl_ccw(fl);
  br_ccw(br);
  bl_cw(bl);
}

void go_right(int fr, int fl, int br, int bl){
  fr_ccw(fr);
  fl_cw(fl);
  br_cw(br);
  bl_ccw(bl);
}



void setup() {
  Serial.begin(9600);
  while (!Serial) {;}
    xTaskCreate(TaskD1, "d1", 256, NULL, 1, NULL);
    xTaskCreate(TaskS1, "s1", 256, NULL, 1, NULL);
    xTaskCreate(TaskS2, "s2", 256, NULL, 1, NULL);
    xTaskCreate(TaskS3, "s3", 256, NULL, 1, NULL);
    xTaskCreate(TaskS4, "s4", 256, NULL, 1, NULL);
    xTaskCreate(TaskS5, "s5", 256, NULL, 1, NULL);
//    xTaskCreate(TaskS6, "s6", 256, NULL, 1, NULL);
//    xTaskCreate(TaskS7, "s7", 256, NULL, 1, NULL);
//    xTaskCreate(TaskS8, "s8", 256, NULL, 1, NULL);

    vTaskStartScheduler();
};

void loop() {};

void TaskD1(void *pvParameters){
  (void) pvParameters;
  int h=0;
//  int v=0;
  delay(3000);
  for(int i=0; i<=7; i++ ){
    pinMode(motoDrivers[i],OUTPUT);
  }
  
  for (;;){
    if(distance1 - 1 >=sp+1 && distance2 >=sp -2 && distance3 - 1 >=sp+1) {
      directions[0]=1;
    } else directions[0]=0; 
    
    if(distance4 >=10) {  
      directions[1]=1;
    } else directions[1]=0; 
  
    if(distance6 >=14 && distance7 >=14 && distance8 >=14) {
      directions[2]=1;
    } else directions[2]=0;

    if(distance5 >= 10 ){
      directions[3]=1;
    } else directions[3]=0;
    
    if (rp==0){
      if (directions[0]==1) {
        if (h>0 && directions[3]==1) {
          if (dl<6) {
            forward(79,75,72,75);
            dl++;
          } else {
            go_left(75,75,82,62);
            h--;
            if (h==0){
              dl=0;
            } 
          } 
        } else {
          forward(79,75,72,75);
          dl=0;
        }
     } else {
       if (directions[1]==1){
        go_right(75,75,85,70);
        h++;
        dl=0;
       } else {
          rp = 1;
        }
     }  
    }

    if (rp==1){
      if (directions[0]==1) {
        if (h<0 && directions[1]==1) {
          if (dl<6) {
            forward(79,75,72,75);
            dl++;
          } else {
            go_right(75,75,85,70);
            h++;
            if (h==0){
              rp=0;
              dl=0;
            }
          }      
        } else {
          forward(79,75,72,75);
          dl=0;
        }
      } else {
        if (directions[3]==1){
          go_left(75,75,82,62);
          h--;
          dl=0;
        } else {
          stop_car();
        }
      }
    }  
  
  vTaskDelay(5);
  }
}

void TaskS1(void *pvParameters){
  (void) pvParameters;
  pinMode(trig1,OUTPUT);
  pinMode(echo1,INPUT);
  pinMode(g1,OUTPUT);
  pinMode(r1,OUTPUT);
  
  for (;;){
    unsigned long duration;
    
    digitalWrite(trig1,0);
    delayMicroseconds(2);
    digitalWrite(trig1,1);
    delayMicroseconds(5);
    digitalWrite(trig1,0);
    
    duration = pulseIn(echo1,HIGH);
    distance1 = int(duration/2/29.412);
    
    if(distance1-2 <=sp && distance1 > 0){
      digitalWrite(g1,0);
      digitalWrite(r1,1);
     }else{
      digitalWrite(r1,0);
      digitalWrite(g1,1);
     }
    vTaskDelay(5);   
  }
}

void TaskS2(void *pvParameters){
  (void) pvParameters;
  pinMode(trig2,OUTPUT);
  pinMode(echo2,INPUT);
  pinMode(g2,OUTPUT);
  pinMode(r2,OUTPUT);
  
  for (;;){
    unsigned long duration2;
    
    digitalWrite(trig2,0);
    delayMicroseconds(2);
    digitalWrite(trig2,1);
    delayMicroseconds(5);
    digitalWrite(trig2,0);
    
    duration2 = pulseIn(echo2,HIGH);
    distance2 = int(duration2/2/29.412);

    if(distance2 <=sp && distance2 > 0){
      digitalWrite(g2,0);
      digitalWrite(r2,1);
    }else{
      digitalWrite(r2,0);
      digitalWrite(g2,1);
    }
    vTaskDelay(5);  
  }
}

void TaskS3(void *pvParameters){
  (void) pvParameters;
  pinMode(trig3,OUTPUT);
  pinMode(echo3,INPUT);
  pinMode(g3,OUTPUT);
  pinMode(r3,OUTPUT);
  
  for (;;){
    unsigned long duration;
   
    digitalWrite(trig3,0);
    delayMicroseconds(2);
    digitalWrite(trig3,1);
    delayMicroseconds(5);
    digitalWrite(trig3,0);
    
    duration = pulseIn(echo3,HIGH);
    distance3 = int(duration/2/29.412);
        if(distance3-2 <=sp && distance3 > 0){
      digitalWrite(g3,0);
      digitalWrite(r3,1);
     }else{
      digitalWrite(r3,0);
      digitalWrite(g3,1);
     }
    vTaskDelay(5);   
  }
}

void TaskS4(void *pvParameters){
  (void) pvParameters;
  pinMode(trig4,OUTPUT);
  pinMode(echo4,INPUT);
  pinMode(g4,OUTPUT);
  pinMode(r4,OUTPUT);
  
  for (;;){
    unsigned long duration4;
    
    digitalWrite(trig4,0);
    delayMicroseconds(2);
    digitalWrite(trig4,1);
    delayMicroseconds(5);
    digitalWrite(trig4,0);
    
    duration4 = pulseIn(echo4,HIGH);
    distance4 = int(duration4/2/29.412);

    if(distance4 <=10 && distance4 > 0){
      digitalWrite(g4,0);
      digitalWrite(r4,1);
    }else{
      digitalWrite(r4,0);
      digitalWrite(g4,1);
    }
    vTaskDelay(5);  
  }
}

void TaskS5(void *pvParameters){
  (void) pvParameters;
  pinMode(trig5,OUTPUT);
  pinMode(echo5,INPUT);
  pinMode(g5,OUTPUT);
  pinMode(r5,OUTPUT);
  
  for (;;){
    unsigned long duration;
    
    digitalWrite(trig5,0);
    delayMicroseconds(2);
    digitalWrite(trig5,1);
    delayMicroseconds(5);
    digitalWrite(trig5,0);
    
    duration = pulseIn(echo5,HIGH);
    distance5 = int(duration/2/29.412);
        if(distance5-1 <=10 && distance5 > 0){
      digitalWrite(g5,0);
      digitalWrite(r5,1);
     }else{
      digitalWrite(r5,0);
      digitalWrite(g5,1);
     }
    vTaskDelay(5);   
  }
}
