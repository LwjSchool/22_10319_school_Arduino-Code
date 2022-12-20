/***************************************************************************
  =======================================================================
  .......................................................................
  H/W
  -----------------------------------------------------------------------
   - 2021/12/14
   D1 : GPIO5 --> RED LED
   D3 : GPIO0 --> tilt sw
   D4 : GPIO2 --> BLUE LED
  -----------------------------------------------------------------------
  S/W  
   - 2022.11.27
   프로그램이름 : Blynk-IoT_DasanGas_A_OK  
   - 2022.12.9
   프로그램이름 : 221209Blynk-IoT_DasanGas_B_OK  
   WidgetLED led(V0);// for led.on() & led.off() -->추가함
   led.on(); //WidgetLED led(V0);에서 제어하는 메소드로 스마트폰 화면에 LED를 표시해 줌 -->추가함
   led.off(); //WidgetLED led(V0);에서 제어하는 메소드로 스마트폰 화면에 LED 표시를 없애줌 -->추가함
   //TILT_SEN 모듈의 LED ON........추가 예정 -->삭제함
   설치라이브러리 버전 Blynk WiFiManager by khoi Hoang(버전1.6.2)WiFiManager by tzapu(버전2.0.11-beta)
   특히 버전2.0.11-bet가 아니면 스마트폰, wifi설정에서 SSID가 나타나지 않음
   - 2022.12.9
   프로그램이름 : 221209Blynk-IoT_DasanGas_배포용
  -----------------------------------------------------------------------
  TIP
   - 2022.11.27
    timer.setInterval(5000L, ValveCheck);에서 5000L, L을 사용하는 이유
    This tells the BlynkTimer library that we want to call the take_sensor_reading() function once every 5000 milliseconds (5 seconds).
    The L after the number 5000 forces the compiler to treat this as a Long Integer variable type. 
    This is important when you want to use larger numbers with 8-bit boards like the Arduino Uno, 
    as the maximum size of a regular Integer with an 8-bit board is 32,767 (or 32.767 seconds when used as a timer interval frequency).
  =======================================================================

 ****************************************************************************/
#define BLYNK_FIRMWARE_VERSION "0.1.1"// Blynk Air기능을 이용하여 플을 업데이트할때 버전 테크 때 필요
// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings

#define BLYNK_TEMPLATE_ID "TMPLh1s4NX6t"
#define BLYNK_DEVICE_NAME "Gas Alarm Program"
#define BLYNK_AUTH_TOKEN "6bczO_sgFtepVjvRIbWSLpW4Z182P_gL"

#define TILT_SW D3 // #define TILT_SW 0 라고 해도 됨

#define BLYNK_PRINT Serial // BlynkDebug.h 파일에서 serial포트로 블링크 로고가 출력됨
#include <ESP8266WiFi.h>   // ESP8266 Core WiFi Library, wemos모듈 등록이 안되었다면 Go to www.wemos.cc
#include <BlynkSimpleEsp8266.h> // 블링크 라이브러리를 설치하세요--> 스케치-->라이브러리 매니저-->"blynk"입력,,,, 참조 :  www.blynk.cc 또는 www.blynk.io

#include <ESP8266WebServer.h> //Local WebServer used to serve the configuration portal
#include <WiFiManager.h> //스케치-->라이브러리 매니저-->"WiFiManager"입력(설치버전은 2.0.11),,,참조 -> https://github.com/tzapu/WiFiManager, 내컴터저장위치-->C:\Users\mac\Documents\Arduino\libraries\WiFiManager

BlynkTimer timer; //SimpleTimer mbktimer 또는 BlynkTimer mbktimer; 로 대체해도 됨, BlynkTimer.h를 참조하세요

int OldState = HIGH; // TILT센서의 초기값 

WidgetLED led(V0);// for led.on() & led.off()

char auth[] = BLYNK_AUTH_TOKEN;

void setup()
{
  // Debug console
  Serial.begin(115200); // 1초 당 115200비트의 전송 속도로 시리얼 모니터로 출력 됨.
  Serial.println("");//for new line
  Serial.println("for dnil4@naver.com(Blynk-IoT)"); //자신의 이메일
  Serial.println("BLYNK_DEVICE_NAME '20211225A-TEST'"); // 자신의 DEVICE_NAME
  WiFiManager wifiManager; // Initialize library
  wifiManager.autoConnect("AutoConnectAP");

  pinMode(TILT_SW, INPUT_PULLUP); // TILT 센서를 입력으로 설정 
  pinMode(LED_BUILTIN, OUTPUT); // LED_BUILTIN is D4. D4는 파란색 LED
  pinMode(D1, OUTPUT); // D1 is RED-LED,,,,,,,,,,,,,,pinMode(5, OUTPUT)라고 해도 됨
  digitalWrite(D4, 1); // 파란색 LED off..... digitalWrite(2, 1)라고 해도 됨
    
  Blynk.config(auth);
  timer.setInterval(3000L, ValveCheck); // 3초마다 Call,,,,,3000L은 long int를 의미
}

void loop()
{
  Blynk.run();
  timer.run();
}

void ValveCheck()
{
  int state = digitalRead(TILT_SW); //TILT센서가 세워지면 0볼트가 출력됨, 즉 가스밸브를 열면 입력 값이 0, 닫으면 1
  if (state == LOW && OldState == HIGH) //꺼진 상태의 밸브를 켜면, 즉 GAS On이면
  {
    digitalWrite(D4, 0); // 파란색 LED on
    led.on(); //WidgetLED led(V0);에서 제어하는 메소드로 스마트폰 화면에 LED를 표시해 줌
    Blynk.logEvent("gas_on", "GAS On !!!!!");
    delay(1000);
    digitalWrite(D4, 1); // 파란색 LED off
  }
  if (state == HIGH && OldState == LOW) //켜 있었던 상태의 밸브를 끄면, 즉 GAS Off이면
  {
    digitalWrite(D4, 0); // 파란색 LED on
    led.off(); //WidgetLED led(V0);에서 제어하는 메소드로 스마트폰 화면에 LED 표시를 없애줌
    Blynk.logEvent("gas_off", "GAS Off !!!!!");
    delay(1000);
    digitalWrite(D4, 1); // 파란색 LED off   
  }
  OldState = state;
}


