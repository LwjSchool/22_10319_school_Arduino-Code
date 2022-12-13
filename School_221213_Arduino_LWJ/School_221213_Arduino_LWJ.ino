void setup() {
  /* LED */
  pinMode(D1, OUTPUT);  // RED - R
  pinMode(D2, OUTPUT);  // ORANGE - O
  pinMode(D3, OUTPUT);  // YELLOW - Y
}

void loop() {
  digitalWrite(D1, LOW);  // R
  delay(100);
  digitalWrite(D1, HIGH);
  delay(100);

  digitalWrite(D2, LOW);  // O
  delay(100);
  digitalWrite(D2, HIGH);
  delay(100);
  
  digitalWrite(D3, LOW);  // Y
  delay(100);
  digitalWrite(D3, HIGH);
  delay(100);
}