// ========================  La bàn TGC ========================  //
int compass() {
  Serial3.print('z');
  static int16_t value = 0;
  if(Serial3.available()){
    delay(5);
    uint8_t high_byte = Serial3.read();
    uint8_t low_byte = Serial3.read();
    value = (high_byte << 8) | (low_byte); 
  }
    return(value); 
}