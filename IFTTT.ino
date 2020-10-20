#include<ESP8266WiFi.h>

int val1;
int val2;
int count1 = 1;
int count2 = 1;
int in;
int out;

// Your WiFi
char ssid[]= "HomeBroadband2"; //Your SSID
char pass[]= "0143226216";// Your Wifi Pass

//set IFTTT 
const char host[] = "maker.ifttt.com";
const char privteKey[] = "c41PHUGPOLBeHvqbmogauA";
const char event[] = "Counter1";
void setup() {
  Serial.begin(115200);
  
  WiFi.begin(ssid,pass);

  while(WiFi.status() !=WL_CONNECTED){
    delay(500);
    Serial.print(".");
    }

     Serial.println("WiFi connected");
     Serial.println(WiFi.localIP());

 //PINMOODE    
      pinMode(D6, INPUT);
      pinMode(D2, INPUT);

}

void loop() {
       int val= digitalRead(D6);
       int va2= digitalRead(D2);
  if(val == LOW ){
 in = count1++;
  Serial.print("in");
  Serial.println(in);
  delay(2000);
 } 
   if(va2 == LOW) {
 out = count2++;
  Serial.print("out");
  Serial.println(out);
  delay(2000);
        }

  
if(in==20||out==20 ){
 Serial.println(" connection to host ...");
 WiFiClient client;
 if(!client.connect(host,80)){Serial.println("connection Faild");
 return;}
//https://maker.ifttt.com/trigger/Counter1/with/key/c41PHUGPOLBeHvqbmogauA?value1=(in)&value2=(out)//
 String url = "/trigger/";
        url = url + event + "/with/key/" + privteKey + "?value1=" +  String(in) + "&value2=" + String(out);
 String http = "GET ";
        http = http + url + " HTTP/1.1\r\n";
        http = http + "Host: " + host +"\r\n";
        http = http + "connection: close\r\n\r\n";
       // send http
     client.print(http);
     client.stop();
     Serial.println("has been sent");
   delay(500);}
if(in==20||out==20 ){
 count1 = 1;
 count2 = 1;
  in= 1 ;
 out= 1 ;}
}
