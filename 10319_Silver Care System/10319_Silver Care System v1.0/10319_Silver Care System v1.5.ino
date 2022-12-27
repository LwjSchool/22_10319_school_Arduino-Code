/***************************************************************************
  =======================================================================
  .......................................................................
  H/W
  -----------------------------------------------------------------------
   - 2022/8/8
   D1 : GPIO5 --> RED LED
   D0 : GPIO16 --> PIR SENDOR-->Blynk에서는 GPIO16을 지원못하기에 Virtual pin으로 변경예정?????????????
   D4 : GPIO2 --> BLUE LED
  -----------------------------------------------------------------------
  S/W  
   - 2022.12.5
   프로그램이름 : Blynk-IoT_Korea.kr_MomMoving_A_OK
   - 2022.12.6
    프로그램이름 : Blynk-IoT_Korea.kr_MomMoving_B_OK
    Serial.println("MomMoving_CareSystem"); 추가
   - 2022.12.7
    프로그램이름 : 221207_Korea.kr_CareSystem_B_OK
    날짜와 메일 그리고 이름을 부여하는 형태로 플 이름 변경함
   - 2022.12.21
    프로그램이름 : 221221_어르신캐어시스템배포용  
    다산중에 맞게 몇몇 부분들 변경하였움
  -----------------------------------------------------------------------
  =======================================================================

 ****************************************************************************/
#define BLYNK_FIRMWARE_VERSION "0.1.1"
// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings

#define BLYNK_TEMPLATE_ID "TMPLClHUT75q"
#define BLYNK_DEVICE_NAME "10319 Silver Care System"
#define BLYNK_AUTH_TOKEN "GW_DoCnVY_oYwnH0ISHlCBhLWdMZzUhw"

#define PIR_SEN D0 // for mom PIR sensor

#define BLYNK_PRINT Serial // BlynkDebug.h 파일에서 serial포트로 블링크 로고가 출력됨
#include <ESP8266WiFi.h>   // ESP8266 Core WiFi Library, wemos모듈 등록이 안되었다면 Go to www.wemos.cc
#include <BlynkSimpleEsp8266.h> // 블링크 라이브러리를 설치하세요--> 스케치-->라이브러리 매니저-->"blynk"입력,,,, 참조 :  www.blynk.io

#include <ESP8266WebServer.h> //Local WebServer used to serve the configuration portal
#include <WiFiManager.h> //스케치-->라이브러리 매니저-->"WiFiManager"입력(설치는 최신것으로할것),,,참조 -> https://github.com/tzapu/WiFiManager,내컴터저장위치-->C:\Users\mac\Documents\Arduino\libraries\WiFiManager

BlynkTimer timer; //SimpleTimer mbktimer 또는 BlynkTimer mbktimer; 로 대체해도 됨, BlynkTimer.h를 참조하세요

int OldState = LOW; // PIR_SEN의 초기값 
WidgetLED led(V0); // for led.on() & led.off()

char auth[] = BLYNK_AUTH_TOKEN;

void setup()
{
  // Debug console
  Serial.begin(115200); // 1초 당 115200비트의 전송 속도로 시리얼 모니터로 출력 됨.
  Serial.println("");//for new line
  Serial.println("for 나의 메일@naver.com(Blynk-IoT)");
  Serial.println("BLYNK_DEVICE_NAME '0808APCMBK'");
  Serial.println("다산중 귀염둥이들 Moving_CareSystem");
  WiFiManager wifiManager; // Initialize library
  wifiManager.autoConnect("AutoConnectAP");

  pinMode(PIR_SEN, INPUT_PULLUP); // PIR_SEN센서를 입력으로 설정 
  pinMode(LED_BUILTIN, OUTPUT); // LED_BUILTIN is D4. D4는 파란색 LED
  pinMode(D1, OUTPUT); // D1 is RED-LED
  digitalWrite(D4, 1); // 파란색 LED off
  //digitalWrite(D1, 1);//적색 LED off
  
  Blynk.config(auth);
  timer.setInterval(3000L, MovingCheck); // 3초마다 Call  
}

void loop()
{
  Blynk.run();
  timer.run();
}

void MovingCheck()
{
  int state = digitalRead(PIR_SEN); //PIR은 인체를 감지하면 3.3볼트가 출력됨
  if (state == LOW) led.off();//사람이 없으면 블링크화면에 있는 Moving LED가 off 
  else led.on(); //사람이 감지되면 Moving LED가 on
  if (state == HIGH && OldState == LOW) //사람이 없었다가 나타나면 "Moving OK"
  {
    digitalWrite(D4, 0); // 파란색 LED on
    Blynk.logEvent("moved", "Moving OK");
    delay(1000);
    digitalWrite(D4, 1); // 파란색 LED off
  }
  OldState = state;
}
