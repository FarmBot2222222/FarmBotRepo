int motor_L = 12;
int motor_R = 13;

void setup() {
    pinMode(motor_L, OUTPUT);
    pinMode(motor_R, OUTPUT);
}

void loop() {

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
    delay(500);
    StopMotors();
}

void MoveRight() {
    digitalWrite(motor_L, HIGH);
    digitalWrite(motor_R, LOW);
    delay(500);
    StopMotors();
}

void Sequence1() {
    
    MoveForward();
    delay(2000);

    MoveLeft();
    MoveForward();
    delay(2000);

    MoveLeft();
    MoveForward();
    delay(2000);

    MoveLeft();
    MoveForward();
    delay(2000);
}