#include <Servo.h>
Servo myServo;
// pins
const int trig = 4;
const int echo = 2;
const int servoPin = 9;
const int btnPin = 12;
// ultra
int duration;
float distance;
float meter;
// servo
int angle;
// btn
int btnState = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  pinMode(echo, INPUT);
  delay(6000);
  Serial.println("Distance:");
  // servo
  myServo.attach(servoPin);
  angle = 0;
 // button
  pinMode(btnPin, INPUT);
  digitalWrite(btnPin, HIGH);
}

void loop() {
  ultraSonic();

  test();

  delay(100);
}

void test() {
  btnState = digitalRead(btnPin);

  if (btnState == LOW) {
    angle = random(20, 90);
    myServo.write(angle);
    delay(random(10,100));
    myServo.write(0);
    Serial.print("Angle: ")
    Serial.println(angle)
  }
}

void ultraSonic() {

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);

  if (duration >= 38000) {
    Serial.print("Out range");
  } else {
    distance = duration / 58;
    Serial.print(distance);
    Serial.print("cm");
    meter = distance / 100;
    Serial.print("\t");
    Serial.print(meter);
    Serial.println("m");
  }
}
