const int motorpin1 = 5;
const int motorpin2 = 6;


void setupMotor() {
  // put your setup code here, to run once:
  pinMode(motorpin1, OUTPUT);
  pinMode(motorpin2, OUTPUT);
}

void motorSpinLeft() {
  // put your main code here, to run repeatedly:
  digitalWrite(motorpin1, HIGH);
  digitalWrite(motorpin2, LOW);
}

void motorSpinRight(){
  digitalWrite(motorpin1,LOW);
  digitalWrite(motorpin2, HIGH);
}

void motorStop(){
  digitalWrite(motorpin1, LOW);
  digitalWrite(motorpin2, LOW);
}
