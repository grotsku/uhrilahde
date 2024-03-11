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
int motorEnabled = 0;
int motorSpeed = 0;
int btnState = 0;

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
}

void loop() {
  ultraSonic();

  test();
  // motorProgram();

  delay(100);
}

void motorProgram() {
  if (distance < 200 && distance >= 100) {
    analogWrite(enablePin, 100);
    delay(random(100, 2000));
    analogWrite(enablePin, 0);
    delay(random(100, 3000));
  } else {
    analogWrite(enablePin, 0);
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

void test() {
  btnState = digitalRead(btnPin);

  if (btnState == LOW) {
    digitalWrite(enablePin, HIGH);
    analogWrite(controlPin1, 100);
    Serial.println("motor on");
  } else {
    digitalWrite(enablePin, LOW);
    Serial.println("motor off");
  }
}
