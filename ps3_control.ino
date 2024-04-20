// ========================  PS 3 ========================  //
void ps3() {
  static uint32_t  combined_data = 0; 
  Serial1.print('p'); 
    uint8_t byte_[4] = {0x00,0x00,0x00,0x00};
    delay(2); 
   if(Serial1.available()){
      char haha = Serial1.read(); 
      if(haha == '}'){                // Kiem tra khoa 
      uint8_t byte_1 = Serial1.read(); 
      uint8_t byte_2 = Serial1.read(); 
      uint8_t byte_3 = Serial1.read(); 
      uint8_t byte_4 = Serial1.read();
        combined_data = ((uint32_t)byte_1 << 24) | ((uint32_t)byte_2 << 16) | ((uint32_t)byte_3 << 8) | byte_4;
      }      
    }
   bt_in = combined_data; 
}


