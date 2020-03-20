void lightsensor(){
  
  uint16_t lux = lightMeter.readLightLevel();
  delay(500);
  if(lux <7){
    digitalWrite(led,LOW);
    lcd.setCursor ( 0, 3 ); 
    lcd.print("           ");
    lcd.setCursor ( 0, 3 ); 
    lcd.print("LED is ON "); 
  }else{
    digitalWrite(led,HIGH );
    lcd.setCursor ( 0, 3 ); 
    lcd.print("          ");
    lcd.setCursor ( 0, 3 ); 
    lcd.print("LED is OFF"); 
  }
}
