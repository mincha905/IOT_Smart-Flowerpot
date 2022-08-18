#define A0Pin 0
#define A1Pin 0
int waterSensorVal = 0; // 수위센서 핀을 A0으로 설정
int sensorVal = 0;  //토양수분센서 핀을 A1으로 설정
int pump = 13;  //펌프 핀을 13으로 설정
pinMode(7, INPUT); //7번 핀을 입력모드로 설정

void setup ( ) {
 Serial.begin(9600);

bool water(){
  if(int readvalue = digitalRead(7))  
    return true;   //입력핀의 값이 인지되면 급수
  else
    return false;
}
    
void loop ( ) { 
  int waterSensorVal = analogRead(A0);  
  Serial.print("Water Sensor : ");
  Serial.println(waterSensorVal);   //수위센서의 전류값을 읽고 출력한다
  delay(1000);  
  
  int sensorVal = analogRead(A1);    //토양센서 센서 값 읽어 저장
  delay(1000);
 
  // 습도 값에 따라 출력 처리를 다르게 해줌
  if ( sensorVal < 40) {
    changeColor != changeColor;  
    setcolor(255, 0, 0)     //습도가 40미만이면 red
  }
 else if ( 40 < sensorVal && sensorVal< 60){
   changeColor != changeColor;
    setcolor(0, 0, 255)     //습도가 40~60이면 blue
  }
 else {
    changeColor != changeColor;
    setcolor(0, 122, 122)  //습도가 60이상이면 yellow
  }

delay(3000);
Serial.write(sensorVal) //라즈베리파이에 데이터를 전송
}