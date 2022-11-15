int motor_L = 12;
int motor_R = 13;

void setup() {
  Serial.begin(9600);
  pinMode(motor_L, OUTPUT);
  pinMode(motor_R, OUTPUT);
}

void loop() {
  Sequence1();
}

void MoveForward() {
  digitalWrite(motor_L, HIGH);
  digitalWrite(motor_R, HIGH);
}

void StopMotors() {
  digitalWrite(motor_L, LOW);
  digitalWrite(motor_R, LOW);
}

void MoveLeft() {
  digitalWrite(motor_L, LOW);
  digitalWrite(motor_R, HIGH);
  delay(2000);
  StopMotors();
}

void MoveRight() {
  digitalWrite(motor_L, HIGH);
  digitalWrite(motor_R, LOW);
  delay(2000);
  StopMotors();
}

void Sequence1() {
  
  MoveForward();
  delay(8000);

  MoveRight();
  MoveForward();
  delay(8000);

  MoveRight();
  MoveForward();
  delay(8000);

  MoveRight();
  MoveForward();
  delay(8000);

  StopMotors();
  delay(5000);

}
