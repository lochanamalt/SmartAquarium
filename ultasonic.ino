void ultrasonic_read(){
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  

  unsigned long duration= pulseIn(ECHO_PIN, HIGH);
 distance= duration/29/2;
}

