#define LmotorCW 5
#define LmotorCCW 6

#define RmotorCW 9
#define RmotorCCW 10

#define IRL 7
#define IRR 8

int speed = 200; //모터 속도
int ECHO_pin = 3;
int TRIG_pin = 2;
unsigned long distance;

void Sonic() {
  digitalWrite(TRIG_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_pin, LOW);
  distance = 0;
  distance = pulseIn(ECHO_pin, HIGH);
  distance = distance / 58;

  Serial.println(distance);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(LmotorCW,OUTPUT);
  pinMode(LmotorCCW,OUTPUT);
  pinMode(RmotorCW,OUTPUT);
  pinMode(RmotorCCW,OUTPUT);

  pinMode(IRL,INPUT);
  pinMode(IRR,INPUT);

  Serial.begin(9600);
  pinMode(ECHO_pin, INPUT);
  pinMode(TRIG_pin, OUTPUT);
  distance = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  //모터 장착 방향, 배선이 따라 코드를 수정 해서 사용

  Sonic();
  if(distance <= 6) {
    analogWrite(LmotorCW, 0);
    analogWrite(LmotorCCW, 0);
    analogWrite(RmotorCW, 0);
    analogWrite(RmotorCCW, 0);
  }
  else {
  //양쪽 IR 센서가 모두 검은색 라인 감지시 양 바퀴 전부 전진
    if(digitalRead(IRL)==HIGH && digitalRead(IRR)==HIGH){
      analogWrite(LmotorCW,0);
      analogWrite(LmotorCCW,speed);

      analogWrite(RmotorCW,speed);
      analogWrite(RmotorCCW,0);
    }
    //  검은색 선을 왼쪽 IR센서는 감지 오른쪽 IR센서는 미감지
    else if(digitalRead(IRL)==LOW && digitalRead(IRR)==HIGH){
      analogWrite(LmotorCW,0);
      analogWrite(LmotorCCW,speed);

      analogWrite(RmotorCW,0);
      analogWrite(RmotorCCW,speed);
    }
    // 검은색 선을 왼쪽 IR센서는 미감지 오른쪽 IR센서는 감지
    else if(digitalRead(IRL)==HIGH && digitalRead(IRR)==LOW){
      analogWrite(LmotorCW,speed);
      analogWrite(LmotorCCW,0);

      analogWrite(RmotorCW,speed);
      analogWrite(RmotorCCW,0);
    }
    //모두 미감지시 정지
    else if(digitalRead(IRL)==LOW && digitalRead(IRR)==LOW){
      analogWrite(LmotorCW,0);
      analogWrite(LmotorCCW,0);
      
      analogWrite(RmotorCW,0);
      analogWrite(RmotorCCW,0);
    }
  }
}

/* 
초음파: Trig - 2번 핀, Echo - 3번 핀, GND - 우노보드 GND 핀, VCC - 빵판
모터드라이버: A-1A - 5번 핀, A-1B - 6번 핀, B-1A - 9번 핀, B-2A - 10번 핀, GND, VCC - 빵판 / Motor A - 왼쪽 모터, Motor B - 오른쪽 모터
적외선 센서 왼쪽: out - 7번 핀, GND, VCC - 빵판 /오른쪽: out - 8번 핀, GND, VCC - 빵판
빵판: 우노보드 5V, GND 연결

*/