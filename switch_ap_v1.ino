#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

String form_p1 = "<form action='led'><input type='radio' name='state' value='1' ",
form_p2=">On<input type='radio' name='state' value='0'",
form_p3=">Off<input type='submit' value='Submit'></form>",
formnow="",chek00="",chek01="";
ESP8266WebServer server(80);

const int led = 13;
void handleRoot() {
  int state=digitalRead(led);
  chek00="";chek01="";
  if(state==0) chek00="checked"; else chek01="checked";
  formnow = form_p1+chek01+form_p2+chek00+form_p3;
  server.send(200, "text/html", formnow);
  //server.send(200, "text/html", "<h1>You are connected :)</h1>"+String(analogRead(resistor),DEC));
}
void handle_led() {
  int state = server.arg("state").toInt();
 //if(digitalRead(led)==state)
  digitalWrite(led, state);
  //server.send(200, "text/plain", String("LED is now ") + ((state)?"on":"off"));
  chek00="";chek01="";
  if(state==0) chek00="checked"; else chek01="checked";
formnow = formnow = form_p1+chek01+form_p2+chek00+form_p3;
  server.send(200, "text/html", formnow);}

void setup(void) {
  Serial.begin(74800);
  Serial.println("");
  pinMode(led, OUTPUT);

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
