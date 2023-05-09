#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <ezButton.h>

ezButton toggleSwitchLed(5);
ezButton toggleSwitchSpeaker(6);

RF24 radio(7, 8); // CE, CSN
const byte diachi[6] = "12345"; //Mảng kí tự dạng chuỗi có 6 kí tự


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  //set up for switch
  toggleSwitchLed.setDebounceTime(50);
  toggleSwitchSpeaker.setDebounceTime(50);
  //set up for TX-RX
  if (!radio.begin()) 
  {
    Serial.println("Module không khởi động được...!!");
    while (1) {}
  } 
  
  radio.openWritingPipe(diachi);
  radio.setPALevel(RF24_PA_MIN); 
  radio.setChannel(80); 
  radio.setDataRate(RF24_250KBPS);
  radio.stopListening();
  if (!radio.available())
  {
    Serial.println("Chưa kết nối được với RX...!!");
    Serial.println("CHỜ KẾT NỐI.......");
  }  
}

void loop() {
  char text = '0'; 
  
  toggleSwitchLed.loop();
  toggleSwitchSpeaker.loop();
  
  if (toggleSwitchLed.isPressed()){
    Serial.println("Cong tac den: OFF -> ON");
    text = '1';
  }

  if (toggleSwitchLed.isReleased()){
    Serial.println("Cong tac den: ON -> OFF");
    text = '2';
  }

  if (toggleSwitchSpeaker.isPressed()){
    Serial.println("Cong tac loa: OFF -> ON");
    text = '3';
  }

  if (toggleSwitchSpeaker.isReleased()){
    Serial.println("Cong tac loa: ON -> OFF");
    text = '4';
  }
  
  
//  radio.write(&text, sizeof(text));
  if (text != '0'){
    radio.write(&text, sizeof(text));
    Serial.println(text);
  }
}
