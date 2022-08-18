 WiFi 헤더파일
#include SPI.h
#include WiFiNINA.h  NANO 33 IoT에서 Wi-Fi 기능을 사용하기 위한 라이브러리 입니다.
#include PubSubClient.h

 아두이노 센서 Json 값으로 변경
#include ArduinoJson.h

 WiFi 및 MQTT 브로커 연결(라즈베리파이)
const char ssid = ;  Wi-Fi의 SSID(이름)를 입력합니다.
const char password = ;  Wi-Fi의 페스워드를 입력합니다.
const char mqtt_server = ;  MQTT 서버를 입력합니다.(라즈베리파이 연결된 IP 주소)

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
#define MSG_BUFFER_SIZE  (50)
char msg[50];
int value = 0;

 아두이노 센서 읽는 핀넘버
#define soil_pin A0
#define cds_pin A1
#define waterlv_pin A2
#define pump_pin 13

 cds
#define cRed_pin 13
#define cGreen_pin 12
#define cBlue_pin 11

soil
#define sRed_pin 10
#define sGreen_pin 9
#define sBlue_pin 8

waterLv
#define wRed_pin 7
#define wGreen_pin 6
#define wBlue_pin 5

String packet_cds,packet_soil,packet_water;


 핀 넘버 수정필요
int pump_AA = A5;  정방향 펌프 작동 핀
int pump_AB = A4;  역방향 펌프 작동 핀


int temp;


 아두이누 데이타 저장 공간
int soil;
int cds;
int waterlv;
int waterFlag;


void SetCdsLedColor();
void SetWaterLvLedColor();
void SetSoilLedColor();

void Water();

char msg_cds[50];cds
char msg_soil[50];soil
char msg_water[50];water

void setup_wifi() {

  delay(10);
   We start by connecting to a WiFi network
  Serial.println();
  Serial.print(Connecting to );
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);  앞서 설정한 ssid와 페스워드로 Wi-Fi에 연결합니다.
  
  while (WiFi.status() != WL_CONNECTED) {  연결될 때 까지 0.5초 마다 Wi-Fi 연결상태를 확인합니다.
    delay(500);
    Serial.print(.);
  }
  
  Serial.println();
  Serial.println(WiFi connected);
  Serial.println(IP address );
  Serial.println(WiFi.localIP());
  
  randomSeed(micros());  렌덤 문자를 위한 렌덤 시드를 설정합니다.
}

int Loop = 0;  LED의 토글을 위해 사용되는 변수입니다.

void callback(char topic, byte payload, unsigned int length) {
   Topic에 메시지가 도착하면 실행되는 콜백입니다.
   for (int i = 0; i  length; i++) {
   Serial.print((char)payload[i]); }
    
    String InString=;
    for (int i = 0; i  length; i++){
    InString += (char)payload[i];
  }
  
  Serial.println(InString);
  
  if(InString == waterOn)
  {
    Serial.println(실행);  
    digitalWrite(pump_AA,HIGH);
  }
  else if(InString == waterOff)
  {
    Serial.println(꺼짐);
    digitalWrite(pump_AA,LOW);
  }
}


 WiFi 연결 상태 확인
void reconnect() {
   Loop until we're reconnected
  while (!client.connected()) {
    Serial.print(Attempting MQTT connection...);
     Attempt to connect  
    if (client.connect(ESP8266Client)) {  앞서 설정한 클라이언트 ID로 연결합니다.
      Serial.println(connected);
       Once connected, publish an announcement...
      client.publish(outTopic, hello world);
       ... and resubscribe
      client.subscribe(inTopic);  inTopic 토픽을 듣습니다.
    } else {
      Serial.print(failed, rc=);
      Serial.print(client.state());
      Serial.println( try again in 5 seconds);
       Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  
  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, 1883);  MQTT 서버에 연결합니다. 기존30400
  client.setCallback(callback);

    waterFlag =0;  0 일시 워터 펌프 꺼짐
 
  pinMode(pump_pin,OUTPUT);  물 펌프 작동

  pinMode(pump_AA,OUTPUT);
  pinMode(pump_AB,OUTPUT);


  digitalWrite(pump_AA,LOW);
  digitalWrite(pump_AB,LOW);
  digitalWrite(pump_pin,LOW);
  
  
  pinMode(cRed_pin,OUTPUT); 광센서 작동
  pinMode(cGreen_pin,OUTPUT);
  pinMode(cBlue_pin,OUTPUT);

  pinMode(sRed_pin,OUTPUT); soil 작동
  pinMode(sGreen_pin,OUTPUT);
  pinMode(sBlue_pin,OUTPUT);


  pinMode(wRed_pin,OUTPUT); water 작동
  pinMode(wGreen_pin,OUTPUT);
  pinMode(wBlue_pin,OUTPUT);

}

void SetCdsLedColor()
{
  if(200cds&&cds=500)  max 
  {
     Serial.println(cds max);
     digitalWrite(cBlue_pin,HIGH);
     digitalWrite(cGreen_pin,LOW);
     digitalWrite(cRed_pin,LOW);
  }else if(40cds&&cds=200)  middle
  {
    digitalWrite(cBlue_pin,LOW);
    digitalWrite(cGreen_pin,HIGH);
    digitalWrite(cRed_pin,LOW);
    
     Serial.println(cds middle);
  }else if(cds=40)min
  {

    digitalWrite(cBlue_pin,LOW);
    digitalWrite(cGreen_pin,LOW);
    digitalWrite(cRed_pin,HIGH);
     Serial.println(cds min);
  }
}

void SetSoilLedColor()
{
  if(soil=400)  max 
  {
     Serial.println(soil max);
     digitalWrite(sBlue_pin,HIGH);
     digitalWrite(sGreen_pin,LOW);
     digitalWrite(sRed_pin,LOW);
     
  }else if(400soil&&soil=800)  middle
  {
    digitalWrite(sBlue_pin,LOW);
    digitalWrite(sGreen_pin,HIGH);
    digitalWrite(sRed_pin,LOW);
    
     Serial.println(soil middle);
  }else if(800soil&&soil=1023)min
  {

    digitalWrite(sBlue_pin,LOW);
    digitalWrite(sGreen_pin,LOW);
    digitalWrite(sRed_pin,HIGH);
     Serial.println(soil min);
  }
}

void SetWaterLvLedColor()
{
  if(500waterlv&&waterlv=700)  max 
  {
     Serial.println(waterlv max);
     digitalWrite(wBlue_pin,HIGH);
     digitalWrite(wGreen_pin,LOW);
     digitalWrite(wRed_pin,LOW);
     
  }else if(200waterlv&&waterlv=500)  middle
  {
    digitalWrite(wBlue_pin,LOW);
    digitalWrite(wGreen_pin,HIGH);
    digitalWrite(wRed_pin,LOW);
    
     Serial.println(waterlv middle);
     
  }else if(waterlv=200)min
  {
    digitalWrite(wBlue_pin,LOW);
    digitalWrite(wGreen_pin,LOW);
    digitalWrite(wRed_pin,HIGH);
     Serial.println(waterlv min);
  }
}


void water()
{
   client 에서 받은 메세지를 구분 가능하게 만들거나 node red 에서 제어가 가능하게 만들어야함 
  String temp = Serial.readStringUntil(client.subscribe(ActiveWater));
  Serial.print(temp);
  Serial.println(temp);
  if(temp == 1)
  {
    Serial.println(실행);  
  }
  else if(temp == 0)
  {
    Serial.println(꺼짐);
  }

  if(Serial.available()) inTopic 토픽을 듣습니다.
  {
    
     String data = Serial.readStringUntil(0x0d);

     {msgpump,cmd0} 펌프를 OFF
     {msgpump,cmd1} 펌프를 ON
     {msgauto1,cmd0} 물부족 펌프 멈춤 기능 비활성화
     {msgauto1,cmd1} 물부족 펌프 멈춤 기능 활성화
     {msgflow,cmd0}

    String inString = Serial.readStringUntil(msg);

    Serial.println(inString);
    StaticJsonDocument48 doc2;
    deserializeJson(doc2, data);

    
    String msg = doc2[msg];

    Serial.println(msg);

    Serial.println(play);

      digitalWrite(pump_AA,HIGH);
      delay(5000);
      waterFlag =0;
      digitalWrite(pump_AA,LOW);
      
    if(msg == water)
    {
      Serial.println(water Pump in);
      
      waterFlag =1;
      digitalWrite(pump_AA,HIGH);
      delay(5000);
      waterFlag =0;
      digitalWrite(pump_AA,LOW);
      msg =  ;
    }
  }
}

void callback(char topic, byte payload, unsigned int length) {
   Topic에 메시지가 도착하면 실행되는 콜백입니다.
  Serial.print(Message arrived [);
  Serial.print(topic);
  Serial.print(] );

  String Msg = ;
  int i=0;
  while (ilength) Msg += (char)payload[i++];
  Serial.println(Msg);
  if (Msg == waterOn)
     digitalWrite(pump_AA,HIGH);
  if (Msg == waterOff){
   digitalWrite(pump_AA,LOW);
  }
}


void mqttPubData(int cds, int soil,int water){
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

    packet_cds = String(cds); 
    packet_cds.toCharArray(msg_cds, 50); 
    packet_soil = String(soil); 
    packet_soil.toCharArray(msg_soil, 50); 
    packet_water = String(water); 
    packet_water.toCharArray(msg_water, 50); 

    mqtt publishing이 char형으로만 보낼 수 있기때문에 toCharArray로 변환한다.
    Serial.print(Publish cds msg );
    Serial.println(msg_cds);
    client.publish(smartPotcds, msg_cds);
    
    Serial.print(Publish soil msg );
    Serial.println(msg_soil);
    client.publish(smartPotsoil, msg_soil);

     Serial.print(Publish water msg );
    Serial.println(msg_water);
    client.publish(smartPotwater, msg_water);

  
    delay(200); 5초 단위로 Publishing (조정가능)
}


void loop() 
{
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  long now = millis();
  if (now - lastMsg  2000) 
  {
    lastMsg = now;
    ++value;
    snprintf (msg, MSG_BUFFER_SIZE, hello world #%ld, value);
    Serial.print(Publish message ); 
    Serial.println(msg);
    client.publish(outTopic, msg);


   soil = analogRead(soil_pin);
   cds = analogRead(cds_pin);
   waterlv = analogRead(waterlv_pin);


  
   {soil123,cds456,waterlv789}
  String output;  Json 값으로 보내기
  StaticJsonDocument24 doc;

  doc[soil] = soil;
  doc[cds] = cds;
  doc[waterlv] = waterlv;

  serializeJson(doc, output);
  Serial.println(output);


  SetCdsLedColor();
  SetSoilLedColor();
  SetWaterLvLedColor();



  water();
    mqttPubData(cds,soil,waterlv);
 여기 위치를 바꿔야함. 안그럼 바로 모든 값이 '0'으로 떨어짐
  Serial.println(waterFlag);
  if(waterFlag ==0)
  {
      Serial.println(waterPump Down);
      digitalWrite(pump_AA,LOW);
      digitalWrite(pump_AB,LOW);
  }
  else
  {
     하나만 HIGH 로 설정
      digitalWrite(pump_AA,HIGH);
      digitalWrite(pump_AB,LOW);
  }
  
  센서값 프린트
  Serial.print(soil);
  Serial.print(t);
  Serial.print(cds);
  Serial.print(t);
  Serial.println(waterlv);

  }
}
