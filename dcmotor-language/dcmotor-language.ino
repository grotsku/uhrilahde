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
  // getMotorDirection();
  getMotorSpeed();

  if (distance > 35) {
    if (distance >= 400) {
      interval = random(20000, 60000);
      motorOnTime = random(1000, 2000);
      sayWord(interval, motorSpeed, motorOnTime);
// distance between 400 & 325 cm
    } else if (distance < 400 && distance >= 325) {
      sentenceDuration = random(500, 1500);
      for (int i = 0; i <= sentenceDuration; i += 500) {
        interval = random(100, 1500);
        motorOnTime = random(100, 300);
        sayWord(interval, motorSpeed, motorOnTime);   
        waitBetweenWords(interval);
      }
      delay(2000);
// distance between 325 & 250 cm
    } else if (distance < 325 && distance >= 250) {
      sentenceDuration = random(500, 1750);
      for (int i = 0; i <= sentenceDuration; i += 500) {
        interval = random(100, 1200);
        motorOnTime = random(100, 500);
        sayWord(interval, motorSpeed, motorOnTime);   
        waitBetweenWords(interval);
      }
      delay(2000);
// distance between 250 & 150 cm
   } else if (distance < 250 && distance >= 150) {
      sentenceDuration = random(500, 2000);
      for (int i = 0; i <= sentenceDuration; i += 500) {
        interval = random(100, 1000);
        motorOnTime = random(100, 1000);
        sayWord(interval, motorSpeed, motorOnTime);   
        waitBetweenWords(interval);
      }
      delay(2000);
// distance between 150 & 100 cm
   } else if (distance < 150 && distance >= 100) {
      sentenceDuration = random(500, 2000);
      for (int i = 0; i <= sentenceDuration; i += 500) {
        interval = random(100, 1250);
        motorOnTime = random(200, 1000);
        sayWord(interval, motorSpeed, motorOnTime);   
        waitBetweenWords(interval);
      }
      delay(2000);
// distance between 100 & 30 cm
   } else if (distance < 100 && distance >= 30) {
      sentenceDuration = random(1000, 3000);
      for (int i = 0; i <= sentenceDuration; i += 500) {
        interval = random(100, 1000);
        motorOnTime = random(100, 1500);
        sayWord(interval, motorSpeed, motorOnTime);   
        waitBetweenWords(interval);
      }
      delay(2000);
    }
// distance under 30 cm
  } else {
    digitalWrite(enablePin, HIGH);
    digitalWrite(controlPin2, LOW);
    analogWrite(controlPin1, random(220, 255));
    Serial.println("too close!!!");
  }

  delay(50);
}

void sayWord(int interval, int motorSpeed, int motorOnTime) {
  // get motor direction
  int motorRandom = random(1, 10);
  if (motorRandom <= 5) {
    chosenMotorPin = controlPin1;
    digitalWrite(controlPin1, HIGH);
    digitalWrite(controlPin2, LOW);
    Serial.print("MOTOR ON! motor spinning clockwise: ");
    Serial.println(motorSpeed);
  } else {
    chosenMotorPin = controlPin2;
    digitalWrite(controlPin1, LOW);
    digitalWrite(controlPin2, HIGH);
    Serial.print("MOTOR ON! motor spinning counter clockwise: ");
    Serial.println(motorSpeed);
  }

  digitalWrite(enablePin, HIGH);
  analogWrite(chosenMotorPin, motorSpeed);
  delay(random(100, 1000));
  digitalWrite(enablePin, LOW);
  Serial.println("MOTOR OFF!");

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

void waitBetweenWords(unsigned long interval) {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    Serial.println("waiting");
    previousMillis = currentMillis;
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
