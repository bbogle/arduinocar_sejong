//아두이노 나노 -초음파센서(HC-SR04)
//초음파센서로 거리 측정중 장애물과 거리가 20cm 이내면 1초 정지 후
//랜덤으로 좌회전 또는 우회전 하고 다시 전진

//모터 PIN 설정
#define Motor_A1 9 //왼쪽 바퀴_빨
#define Motor_A2 10 //왼쪽 바퀴_검
#define Motor_B1 11 //오른쪽 바퀴_검
#define Motor_B2 3 //오른쪽 바퀴_빨

//초음파 센서 PIN 설정
#define IR_TRIG 5 //TRIG 핀 설정 (초음파 보내는 핀)
#define IR_ECHO 6 //ECHO 핀 설정 (반사된 초음파 받는 핀)

long duration = 0;
int Lspeed = 170; // 좌측 모터 속도
int Rspeed = 200; // 우측 모터 속도
                                                                                                                          
void setup() {
  Serial.begin(9600);   //시리얼모니터

  //모터 핀모드 설정
  pinMode(Motor_A1, OUTPUT);  // D9
  pinMode(Motor_A2, OUTPUT);  // D3
  pinMode(Motor_B1, OUTPUT);  // D10
  pinMode(Motor_B2, OUTPUT);  // D11

  //초음파 센서 핀모드 설정
  pinMode(IR_TRIG, OUTPUT);
  pinMode(IR_ECHO, INPUT);
}

void loop() {
  digitalWrite(IR_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(IR_TRIG, LOW);

  // echoPin 이 HIGH를 유지한 시간
  duration = pulseIn(IR_ECHO, HIGH);
  // HIGH 였을 때 시간(초음파가 보냈다가 다시 들어온 시간)을 가지고 거리를 계산 한다.
  // 340은 초당 초음파(소리)의 속도, 10000은 밀리세컨드를 세컨드로, 왕복거리이므로 2로 나눠주면 거리가 cm 로 나옴
  //distance = ((float)(340 * duration) / 10000) / 2;
  long distance = ( duration * 340 ) / 2 / 10000;

  Serial.print("\nDistance : ");
  Serial.print(distance);

  if (distance < 20) {        //장애물 감지 (20cm 이내)
      analogWrite(Motor_A1, 0);
      digitalWrite(Motor_A2, 0);
      digitalWrite(Motor_B1, 0);
      digitalWrite(Motor_B2, 0);
      delay(300);
      digitalWrite(Motor_A1, 0);
      digitalWrite(Motor_A2, Lspeed);
      digitalWrite(Motor_B1, 0);
      digitalWrite(Motor_B2, Rspeed);  
      delay(300);
    
    int rnd = random(0, 2);  //장애물 감지시 좌/우회전 랜덤처리
    if (rnd == 0) {
      Serial.print("Left, ");
      analogWrite(Motor_A1, 0);
      analogWrite(Motor_A2, 0);
      analogWrite(Motor_B1, Rspeed);
      analogWrite(Motor_B2, 0);
      delay(400);
    }
    else {
      Serial.print("Right, ");
      analogWrite(Motor_A1, Lspeed);
      analogWrite(Motor_A2, 0);
      analogWrite(Motor_B1, 0);
      analogWrite(Motor_B2, 0);
      delay(400);
    }
  }
  else {        //장애물 없음
    Serial.println(" forward");
    analogWrite(Motor_A1, Lspeed);
    analogWrite(Motor_A2, 0);
    analogWrite(Motor_B1, Rspeed);
    analogWrite(Motor_B2, 0);
  }
}
