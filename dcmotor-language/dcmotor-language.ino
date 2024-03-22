// pins
const int controlPin1 = 3;
const int controlPin2 = 5;
const int enablePin = 2;
const int trig = 4;
const int echo = 7;
// ultra
int duration;
float distance;
float meter;
// motor
int motorState = LOW;
int motorSpeed = 0;
int motorOnTime = 0;
int chosenMotorPin = 0;
// timing
unsigned long previousMillis = 0;
unsigned long interval = 0;
unsigned long previousDirectionMillis = 0;
unsigned long sentenceDuration = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(controlPin1, OUTPUT);
  pinMode(controlPin2, OUTPUT);
  pinMode(enablePin, OUTPUT);
  digitalWrite(enablePin, LOW);
  digitalWrite(controlPin1, HIGH);
  digitalWrite(controlPin2, LOW);
  pinMode(trig, OUTPUT);
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  pinMode(echo, INPUT);
  delay(6000);
  Serial.println("Distance:");

  Serial.println("---start program---");
}

void loop() {
  ultraSonic();
  getMotorDirection();
  getMotorSpeed();

  if (distance > 35) {
    if (distance >= 400) {
      interval = random(20000, 60000);
      motorOnTime = random(1000, 2000);
      sayWord(interval, motorSpeed, motorOnTime);
    } else if (distance < 400 && distance >= 325) {
      sentenceDuration = random(1000, 3000);
      for (int i = 0; i <= sentenceDuration; i += 1000) {
        interval = random(100, 1000);
        motorOnTime = random(100, 1000);
        sayWord(interval, motorSpeed, motorOnTime);   
      }
    } else if (distance < 325 && distance >= 250) {
      sentenceDuration = random(1000, 3000);
      for (int i = 0; i <= sentenceDuration; i += 1000) {
        interval = random(100, 1000);
        motorOnTime = random(100, 1000);
        sayWord(interval, motorSpeed, motorOnTime);   
      }
    } else if (distance < 250 && distance >= 150) {
      sentenceDuration = random(1000, 3000);
      for (int i = 0; i <= sentenceDuration; i += 1000) {
        interval = random(100, 1000);
        motorOnTime = random(100, 1000);
        sayWord(interval, motorSpeed, motorOnTime);   
      }
    } else if (distance < 150 && distance >= 100) {
      sentenceDuration = random(1000, 3000);
      for (int i = 0; i <= sentenceDuration; i += 1000) {
        interval = random(100, 1000);
        motorOnTime = random(100, 1000);
        sayWord(interval, motorSpeed, motorOnTime);   
      }
    } else if (distance < 100 && distance >= 30) {
      sentenceDuration = random(1000, 3000);
      for (int i = 0; i <= sentenceDuration; i += 1000) {
        interval = random(100, 1000);
        motorOnTime = random(100, 1000);
        sayWord(interval, motorSpeed, motorOnTime);   
      }
    }
  } else {
    digitalWrite(enablePin, HIGH);
    digitalWrite(controlPin2, LOW);
    analogWrite(controlPin1, random(220, 255));
    Serial.println("too close!!!");
  }

  delay(50);
}

void saySentence(int sentenceDuration) {

}

void sayWord(int interval, int motorSpeed, int motorOnTime) {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    digitalWrite(enablePin, HIGH);
    analogWrite(chosenMotorPin, motorSpeed);
    // save the last time the motor ran
    previousMillis = currentMillis;
    // set flag to indicate the motor is running
    motorState = HIGH;
  }

  // check to see if motor has been running for motorOnTime
  if (motorState == HIGH && currentMillis - previousMillis >= motorOnTime) {
    // turn motor off
    digitalWrite(enablePin, LOW);
    // reset motor state flag
    motorState = LOW;
  }
}

void getMotorSpeed() {
  int motorSpeedNoise = random(-5, 15);
  motorSpeed = 254 - map(distance, 1, 417, 10, 254) + motorSpeedNoise;
  if (motorSpeed <= 10) { motorSpeed = 10; }
  // Serial.print("mapped motor speed: ");
  // Serial.println(motorSpeed);
}

void getMotorDirection() {
    if (millis() - previousDirectionMillis >= 2000) {
        chosenMotorPin = (chosenMotorPin == controlPin1) ? controlPin2 : controlPin1;
        digitalWrite(controlPin1, chosenMotorPin == controlPin1 ? HIGH : LOW);
        digitalWrite(controlPin2, chosenMotorPin == controlPin2 ? HIGH : LOW);
        previousDirectionMillis = millis();
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
    // Serial.print(distance);
    // Serial.print("cm");
    meter = distance / 100;
    // Serial.print("\t");
    // Serial.print(meter);
    // Serial.println("m");
  }
}