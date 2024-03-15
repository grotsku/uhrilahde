// pins
const int controlPin1 = 3;
const int controlPin2 = 5;
const int enablePin = 2;
const int trig = 4;
const int echo = 7;
const int btnPin = 12;
// ultra
int duration;
float distance;
float meter;
// motor
int motorState = LOW;
int motorSpeed = 0;
int btnState = 0;
int motorOnTime = 0;
// timing
unsigned long previousMillis = 0;
int interval = 0;

// Define thresholds for rapid distance changes
const float rapidIncreaseThreshold = 50.0; // Adjust as needed
const float rapidDecreaseThreshold = -50.0; // Adjust as needed

// Variables to track previous distance
float previousDistance = 0.0;

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
  // button
  pinMode(btnPin, INPUT);
  digitalWrite(btnPin, HIGH);

  Serial.println("---start program---");
}

void loop() {
  ultraSonic();
  // distanceChange();

  motorSpeed = random(25, 200);

  if (distance > 35) {
    if (distance >= 400) {
      interval = random(20000, 60000);
      motorSpeed = random(10, 80);
      motorOnTime = random(500, 1000);
    } else if (distance < 400 && distance >= 325) {
      interval = random(1000, 10000);
      motorSpeed = random(80, 140);
      motorOnTime = random(400, 1500);
    } else if (distance < 325 && distance >= 250) {
      interval = random(800, 4000);
      motorSpeed = random(100, 180);
      motorOnTime = random(400, 1800);
    } else if (distance < 250 && distance >= 150) {
      interval = random(500, 2500);
      motorSpeed = random(150, 190);
      motorOnTime = random(400, 2500);
    } else if (distance < 150 && distance >= 50) {
      interval = random(500, 1000);
      motorSpeed = random(180, 220);
      motorOnTime = random(1000, 5000);
    }
    motorProgram(interval, motorSpeed, motorOnTime);
  } else {
    digitalWrite(enablePin, HIGH);
    analogWrite(controlPin1, random(190, 255));
    Serial.println("too close!!!");
  }

  delay(50);
}

void motorProgram(int interval, int motorSpeed, int motorOnTime) {
  // check to see if it's time to run the motor
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    Serial.print("distance: ");
    Serial.println(distance);
    // save the last time the motor ran
    Serial.println("motor on");
    digitalWrite(enablePin, HIGH);
    analogWrite(controlPin1, motorSpeed);
    delay(motorOnTime);
    digitalWrite(enablePin, LOW);
    Serial.println("motor off");

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

void distanceChange() {
  // Check for rapid increase in distance
  if (distance - previousDistance > rapidIncreaseThreshold) {
    // Rapid increase detected, trigger behavior
    digitalWrite(enablePin, HIGH);
    analogWrite(controlPin1, random(190, 255));
    Serial.println("rapid increase!!!");
    delay(1000);
  }

  // Update previous distance for next iteration
  previousDistance = distance;
}
