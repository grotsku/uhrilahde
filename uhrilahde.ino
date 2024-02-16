#include <Servo.h>
Servo myServo;
// pins
int trig = 4;
int echo = 2;
int servoPin = 9;
// ultra
int duration;
float distance;
float meter;
// servo
int angle;
// timing
unsigned long startTime = 0;
unsigned long timingDuration = 0;
bool timingStarted = false;

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
}

void loop() {
  ultraSonic();
  // check to start timing
  if (distance < 20 && !timingStarted) {
    startTime = millis();
    timingStarted = true;
    Serial.println("Clock started");
  }
  // end timing and execute program
  if (distance >= 20 && timingStarted) {
    timingDuration = millis() - startTime;
    timingStarted = false;
    Serial.println("Clock stopped");
    Serial.print("Duration: ");
    Serial.println(timingDuration);

    delay(timingDuration / 3);
    for (int i = 0; i <= timingDuration; i += 1000) {
      sayWord();
    }
  }

  delay(100);
}

void sayWord() {
  if (angle <= 90) {
    angle += random(5, 90);
    } else {
      angle -= random(5, 90);
    }
  if (angle < 0 || angle > 179) {
    angle = random (0, 179);
  }

  Serial.print("angle: ");
  Serial.println(angle);
  myServo.write(angle);

  delay(random(100, 1000));
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
