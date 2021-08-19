//محمد عادل عبد العزيز محمد الشريف  
#define sensor_right1 4
#define sensor_right2 8
#define sensor_midel 10
#define sensor_left1 11
#define sensor_left2 7
#define c1 3
#define c2 5
#define c3 6
#define c4 9


// SPEED CINTER
// =============================================================================== 

void SpeedLogic(int spdL, int spdR) {
  spdR = -spdR;

  if (spdL < 0) {
    analogWrite(c2, 0);
    analogWrite(c1,-spdL);
  } else {
    analogWrite(c2, spdL);
    analogWrite(c1, 0);
  }

  if (spdR < 0) {
    analogWrite(c3, 0);
    analogWrite(c4, -spdR);
  } else {
    analogWrite(c3, spdR);
    analogWrite(c4, 0);
  }
} 
//================================================================================================
// LOGIC CINTER 

int Error = 0;
int outlineCnt = 0;

void sensLogic(int X) {
  switch (X) {
    case B00000:
      outlineCnt=0;
      Error=Error;
      break;
      
    case B11111:
      outlineCnt=0;
      Error = 0;
      break;
      
    case B00010:
    case B00110:
      outlineCnt = 0;
      Error = 1;
      break;
      
    case B00001:
    case B00011:
    case B00111:
      outlineCnt = 0;
      Error = 2;
      break;
      
    case B00100:
      outlineCnt = 0;
      Error = 0;
      break;
      
    case B01000:
    case B01100:
      outlineCnt = 0;
      Error = -1;
      break;
      
    case B10000:
    case B11000:
    case B11100:
      outlineCnt = 0;
      Error = -2;
      break;
      
    default:
      outlineCnt=0;
      Error=Error;
      break;
  }

  if (outlineCnt > 2) {
    SpeedLogic(0,0);
  } else {
    
    float ctrl = calcPid(Error);
    SpeedLogic(85-ctrl,85+ctrl);
  }
}
//===============================================================================================

// PID 
float Kp = 40;
float Ki = 0.45;
float Kd = 1000;
float error, errorLast, erroInte;

float calcPid(float input) {
  float errorDiff;
  float output;
  error = error * 0.7 + input * 0.3; // filter
  //error = input;
  errorDiff = error - errorLast;
  erroInte = constrain(erroInte + error, -50, 50);
  output = Kp * error + Ki * erroInte + Kd * errorDiff;

  errorLast = error;

  return output;
}
// TRACE ===================================================================================
int sensTrace() {
  int ret = B00000;
  int a[5]={digitalRead(sensor_right1),
            digitalRead(sensor_right2),
            digitalRead(sensor_midel),
            digitalRead(sensor_left1),
            digitalRead(sensor_left2)};
            
  for (int i = 0; i < 5; i++) {
    if (a[i] == HIGH) ret += (0x1 << i);
  }
  
  return ret;
}
//========================================================================================

void setup() {

  pinMode(sensor_right1,INPUT);
  pinMode(sensor_right2,INPUT);
  pinMode(sensor_midel,INPUT);
  pinMode(sensor_left1,INPUT);
  pinMode(sensor_left2,INPUT);
      pinMode(c1,OUTPUT);
      pinMode(c2,OUTPUT);
      pinMode(c3,OUTPUT);
      pinMode(c4,OUTPUT); 
 analogWrite(c1,0);
  analogWrite(c2,0);
  analogWrite(c3,0);
 analogWrite(c4,0);

}
//======================================================================================================

int pos;
void loop() {
  delay(4);
  pos = sensTrace();
  sensLogic(pos);
}
