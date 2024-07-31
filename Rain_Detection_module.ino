int value;
int pins[3] = {8, 9, 10};

void setup(){
  pinMode(A0, INPUT);
  for(int i = 0; i < 3; i++) {
    pinMode(pins[i], OUTPUT);
  }
}

void loop(){
  value = analogRead(A0);
  setPins(value);
}

void setPins(int val) {
  if (val <= 200) {
    digitalWrite(pins[2], LOW);
    digitalWrite(pins[1], HIGH);
    digitalWrite(pins[0], LOW);
  } else if (val <= 550) {
    digitalWrite(pins[2], LOW);
    digitalWrite(pins[1], LOW);
    digitalWrite(pins[0], HIGH);
  } else {
    digitalWrite(pins[2], HIGH);
    digitalWrite(pins[1], LOW);
    digitalWrite(pins[0], LOW);
  }
}