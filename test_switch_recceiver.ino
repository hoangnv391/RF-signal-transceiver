
/*
 * https://maniacbug.github.io/RF24/classRF24.html
 * 
 * Sơ đồ chân mạch NRF24L01 + PA + LNA
 * 
 * VCC - 3.3v
 * GND - GND
 * CSN - 8
 * CE - 7
 * SCK - 13
 * MOSI - 11
 * MISO - 12
 */

/*
* Sơ đồ chân điều khiển loa và đèn (đấu nối vào relay)
* 
* đèn - 6 
* loa - 5
*/


/*
* Sơ đồ nối chân phát nhạc MP3 TF 16P
* VCC - 3.3V
* DAC_R - R (trên mạch khuếch đại - tín hiệu đầu vào)
* DAC_L - L (trên mạch khuếch đại - tín hiệu đầu vào)
* GND - GND (Arduino) - GND (trên mạch khuếch đại, tín hiệu đầu vào)
* IO_1 - (cơ chế: nối tắt vào chân GND - cách nối: IO_1 vào rơ le, chân còn lại của rơ le đấu vào chân GND)
*/

 

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// init led
int led = 6;

// init speaker
int speaker = 5;

RF24 radio(7, 8); // CE, CSN
const byte diachi[6] = "12345";

void setup() 
{
  Serial.begin(9600);
  
  if (!radio.begin()) 
  {
    Serial.println("Module không khởi động được...!!");
    while (1) {}
  } 

  //set up led
  pinMode(led, OUTPUT);   
  digitalWrite(led, HIGH);


  pinMode(speaker, OUTPUT);   
  digitalWrite(speaker, HIGH);
  
  radio.openReadingPipe(1, diachi);
  radio.setPALevel(RF24_PA_MIN);
  radio.setChannel(80);
  radio.setDataRate(RF24_250KBPS);
  radio.startListening();
  
  if (!radio.available())
  {
    Serial.println("Chưa kết nối được với TX...!!");
    Serial.println("CHỜ KẾT NỐI.......");
  } 
}

void loop() 
{
  
  if (radio.available()) 
  {
    char nhan = '0'; //30 là số kí tự trong mảng
    radio.read(&nhan, sizeof(nhan));

    //control led
    if (nhan=='1'){
      Serial.println("Den bat");
      digitalWrite(led, LOW);
    }
    if (nhan=='2'){
      Serial.println("Den tat");
      digitalWrite(led, HIGH);
    }

    // control speaker
    if (nhan=='3'){
      Serial.println("Loa bat");
      digitalWrite(speaker, LOW);
    }
    if (nhan=='4'){
      Serial.println("Loa tat");
      digitalWrite(speaker, HIGH);
    }
    
  }
}
