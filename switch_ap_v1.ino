#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

String form_p1 = "<form action='led'><input type='radio' name='state' value='1' ",
form_p2 = "<input type='radio' name='state2' value='1' ",
form_p3 = "<input type='radio' name='state3' value='1' ",
form_p10=">On<input type='radio' name='state' value='0'",
form_p12=">On<input type='radio' name='state2' value='0'",
form_p13=">On<input type='radio' name='state3' value='0'",
form_poff=">Off<BR>",
form_p33="<big><big><input type='submit' value='Submit'></big></big></form>",
formnow="",chek00="",chek01="",chek20="",chek21="",chek30="",chek31="";
ESP8266WebServer server(80);

const int led = 13;
const int led2 = 12;
const int led3 = 15;
void handleRoot() {
  int state=digitalRead(led);  
    int state2=digitalRead(led2);  
      int state3=digitalRead(led3);  
  chek00="";chek01="";chek20="";chek21="";chek30="";chek31="";
  if(state==1) chek00="checked"; else chek01="checked";
  if(state2==1) chek20="checked"; else chek21="checked";
  if(state3==1) chek30="checked"; else chek31="checked";
  formnow = form_p1+chek00+form_p10+chek01+form_poff+form_p2+chek20+form_p12+chek21+form_poff+form_p3+chek30+form_p13+chek31+form_poff+form_p33;
  server.send(200, "text/html", formnow);
  //server.send(200, "text/html", "<h1>You are connected :)</h1>"+String(analogRead(resistor),DEC));
}
void handle_led() {
  
  int state = server.arg("state").toInt();
  int state2 = server.arg("state2").toInt();
  int state3 = server.arg("state3").toInt();
  
 //if(digitalRead(led)==state)
  digitalWrite(led, state);
  digitalWrite(led2, state2);
  digitalWrite(led3, state3);
  //server.send(200, "text/plain", String("LED is now ") + ((state)?"on":"off"));
  //handleRoot;
  /*chek00="";chek01="";
  if(state==0) chek00="checked"; else chek01="checked";
formnow = formnow = form_p1+chek01+form_p2+chek00+form_p3;
  server.send(200, "text/html", formnow);
  */
  server.send(200, "text/html", "<html><head><meta http-equiv='refresh' content='0;URL=http://192.168.4.1/' /></head></html>");
  }

void setup(void) {
  Serial.begin(74800);
  Serial.println("");
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

 // WiFi.mode(WIFI_STA);
  //WiFi.disconnect();
  delay(100);
  WiFi.softAP("Switch","");
 IPAddress myIP = WiFi.softAPIP();
 Serial.print("AP IP address: ");
  Serial.println(myIP);
server.on("/", handleRoot);
   //server.on("/", [](){ server.send(200, "text/html", form);  });
server.on("/led", handle_led);
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
}
