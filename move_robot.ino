#define pwm1 5
#define pwm2 6
#define pwm3 9
#define pwm4 10

// String stringOne; // Initial type of class
int i;

void setup() {
  pinMode(pwm1, OUTPUT);
  pinMode(pwm2, OUTPUT);
  pinMode(pwm3, OUTPUT);
  pinMode(pwm4, OUTPUT);
  Serial.begin(9600);
  Serial.setTimeout(1);
}

int kiri = 0;
int kanan = 0;

void adjustSpeed(int leftWheel, int rightWheel) {
  kiri = leftWheel;
  kanan = 0.84 * rightWheel;
};

void loop() {
  if (Serial.available() > 0)
  {
    int data;
    i = Serial.readString().toInt();
    if (i == 0){
        if (kiri < 50)
          {
              if (kiri >= 50)
              {
                  kiri = 50;
                  kanan = 50;
              }
              else
              {
                  kiri+=5;
                  kanan+=5;
              }
              analogWrite(pwm1, 0);
              analogWrite(pwm2, kiri);
              analogWrite(pwm3, 0);
              analogWrite(pwm4, kanan);
              delay(100); 
          }
         if (kiri > 50)
          {
              if (kiri <= 55)
              {
                  kiri = 50;
                  kanan = 50;
              }
              else
              {
                  kiri-=5;
                  kanan-=5;
              }
              analogWrite(pwm1, 0);
              analogWrite(pwm2, kiri);
              analogWrite(pwm3, 0);
              analogWrite(pwm4, kanan);
              delay(100); 
          }
    }else if (i == 1){
        if (kiri < 0)
          {
              if (kiri >= 0)
              {
                  kiri = 0;
                  kanan = 0;
              }
              else
              {
                  kiri+=5;
                  kanan+=5;
              }
              analogWrite(pwm1, 0);
              analogWrite(pwm2, kiri);
              analogWrite(pwm3, 0);
              analogWrite(pwm4, kanan);
              delay(100); 
          }
         if (kiri > 0)
          {
              if (kiri <= 5)
              {
                  kiri = 0;
                  kanan = 0;
              }
              else
              {
                  kiri-=5;
                  kanan-=5;
              }
              analogWrite(pwm1, 0);
              analogWrite(pwm2, kiri);
              analogWrite(pwm3, 0);
              analogWrite(pwm4, kanan);
              delay(100); 
          }
      } else if (i == 2){
        if (kiri < 55)
          {
              if (kiri >= 45 )
              {
                  kiri = 55;
              }
              else
              {
                  kiri+=5;
              }
              analogWrite(pwm1, 0);
              analogWrite(pwm2, kiri);
              analogWrite(pwm3, 0);
              analogWrite(pwm4, kanan);
              delay(100); 
          }
        if (kanan < 0)//0
          {
              if (kanan >= 0)//0
              {
                  kanan = 0;//0
              }
              else
              {
                  kanan+=5;
              }
              analogWrite(pwm1, 0);
              analogWrite(pwm2, kiri);
              analogWrite(pwm3, 0);
              analogWrite(pwm4, kanan);
              delay(100); 
          }
          if (kiri > 55 )
          {
              if (kiri <= 65 )
              {
                  kiri = 55;
              }
              else
              {
                  kiri-=5;
              }
              analogWrite(pwm1, 0);
              analogWrite(pwm2, kiri);
              analogWrite(pwm3, 0);
              analogWrite(pwm4, kanan);
              delay(100); 
          }
          if (kanan > 0)//0
          {
              if (kanan <= 5)//ni ubah 5
              {
                  kanan = 0;//ubah 0
              }
              else
              {
                  kanan-=5;
              }
              analogWrite(pwm1, 0);
              analogWrite(pwm2, kiri);
              analogWrite(pwm3, 0);
              analogWrite(pwm4, kanan);
              delay(100); 
          }
          
        }
     
//        stringOne = String("Lantai");
       else if (i == 3){
        if (kiri < 0)//0
          {
              if (kiri >= 0 )//0
              {
                  kiri = 0;//0
              }
              else
              {
                  kiri+=5;
              }
              analogWrite(pwm1, 0);
              analogWrite(pwm2, kiri);
              analogWrite(pwm3, 0);
              analogWrite(pwm4, kanan);
              delay(100); 
          }
        if (kanan < 55)
          {
              if (kanan >= 45)
              {
                  kanan = 55;
              }
              else
              {
                  kanan+=5;
              }
              analogWrite(pwm1, 0);
              analogWrite(pwm2, kiri);
              analogWrite(pwm3, 0);
              analogWrite(pwm4, kanan);
              delay(100); 
          }
          if (kiri > 0)//ubah 0
          {
              if (kiri <= 5)// 5
              {
                  kiri = 0;//0
              }
              else
              {
                  kiri-=5;
              }
              analogWrite(pwm1, 0);
              analogWrite(pwm2, kiri);
              analogWrite(pwm3, 0);
              analogWrite(pwm4, kanan);
              delay(100); 
          }
          if (kanan > 55)
          {
              if (kanan <= 65)
              {
                  kanan = 55;
              }
              else
              {
                  kanan-=5;
              }
              analogWrite(pwm1, 0);
              analogWrite(pwm2, kiri);
              analogWrite(pwm3, 0);
              analogWrite(pwm4, kanan);
              delay(100); 
          }
      }       
    }
    
    delay(100);

    Serial.println(String(kiri) + "+" + String(kanan));
    // Serial.println(String(kanan));
  }
