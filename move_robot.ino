#define pwm1 5
#define pwm2 6
#define pwm3 9
#define pwm4 10

void setup() {
  pinMode(pwm1, OUTPUT);
  pinMode(pwm2, OUTPUT);
  pinMode(pwm3, OUTPUT);
  pinMode(pwm4, OUTPUT);
  Serial.begin(9600);
  Serial.setTimeout(1);
}
//speed[0] = kiri, sebaliknya
int speed[2] = {0, 0};
int kiri = 50;
int kanan = 45;
int state;

// Maju 
void maju(){
  speed[0]+=5;
  speed[1]+=5;
  speed[0] = speed[0] > kiri ? kiri : speed[0];
  speed[1] = speed[1] > kanan ? kanan : speed[1];
  return;
}

// Stop 
void stop(){
  speed[0]-=5;
  speed[1]-=5;
  speed[0] = speed[0] > 0 ? 0 : speed[0];
  speed[1] = speed[1] > 0 ? 0 : speed[1];
  return;
}

//Kanan
void kanan(){
  speed[0] += 5;
  speed[1] = 0;
  speed[0] = speed[0] > 15 ? 15 : speed[0];
  speed[1] = speed[1] > 0 ? 0 : speed[1];
  return;
} 

//Kiri
void kiri(){
  speed[0] = 0;
  speed[1] += 5;
  speed[0] = speed[0] > 0 ? 0 : speed[0];
  speed[1] = speed[1] > 15 ? 15 : speed[1];
  return;
} 

void loop() {
  if (Serial.available() > 0)
  {
    state = Serial.readString().toInt();  
  }
  if (state == 2|| state==3 && speed[1] != 0 && speed[0] != 0){
    state = 0;
  }
  switch(state){
    case 0 : stop()  break;
    case 1 : maju(); break;
    case 2 : kanan(); break;
    case 3 : kiri(); break;
  }

  analogWrite(pwm2, 0);
  analogWrite(pwm1, speed[0]);
  analogWrite(pwm4, 0);
  analogWrite(pwm3, speed[1]);
  delay(100);
  Serial.println(String(speed[0]) + "+" + String(speed[1]));
}
