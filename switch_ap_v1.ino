#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

String  golova="<html><big><big><div align='center'><form action='led'><table style='font-size: 500%;' ><tr><td><label ",
form_p1 = ">blue<input type='radio' name='state' value='1'  onClick='this.form.submit();'",
form_p2 = ">green<input type='radio' name='state2' value='1' onClick='this.form.submit();'",
form_p3 = ">red<input type='radio' name='state3' value='1' onClick='this.form.submit();'",
form_p10=">On</label><label><input type='radio' name='state' value='0' onClick='this.form.submit();'",
form_p12=">On</label><label><input type='radio' name='state2' value='0' onClick='this.form.submit();'",
form_p13=">On</label><label><input type='radio' name='state3' value='0' onClick='this.form.submit();'",
form_poff=">Off</label><BR><label ",
form_p33="</td></tr></table></form></div></big></big></html>",
lab_st1=" style='background:blue; color:white;'",
lab_st2=" style='background:green; color:white;'",
lab_st3=" style='background:red; color:white;'",
 formnow="";
IPAddress ip(10,10,2,1);
IPAddress gateway(10, 10, 2, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress dns(10, 10, 2, 1);

ESP8266WebServer server(ip,80);

const int led = 13;
const int led2 = 12;
const int led3 = 15;
void handleRoot() {
  int state=digitalRead(led);  
    int state2=digitalRead(led2);  
      int state3=digitalRead(led3);  
  String chek00="",chek01="",chek20="",chek21="",chek30="",chek31="",lab_st00="",lab_st20="",lab_st30="";
  if(state==1) {chek00="checked";lab_st00=lab_st1;} else chek01="checked";
  if(state2==1) {chek20="checked";lab_st20=lab_st2;} else chek21="checked";
  if(state3==1) {chek30="checked";lab_st30=lab_st3;} else chek31="checked";
  formnow = golova+lab_st00+form_p1+chek00+form_p10+chek01+form_poff+lab_st20+form_p2+chek20+form_p12+chek21+form_poff+lab_st30+form_p3+chek30+form_p13+chek31+form_poff+form_p33;
  server.send(200, "text/html", formnow);
  
}
void handle_led() {
  
  int state = server.arg("state").toInt();
  int state2 = server.arg("state2").toInt();
  int state3 = server.arg("state3").toInt();
  digitalWrite(led, state);
  digitalWrite(led2, state2);
  digitalWrite(led3, state3);
  server.send(200, "text/html", "<html><head><meta http-equiv='refresh' content='0;URL=http://10.10.2.1/' /></head></html>");
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
  WiFi.softAPConfig(ip, gateway, subnet);
  WiFi.softAP("switch-10.10.2.1","");
 IPAddress myIP = WiFi.softAPIP();
 Serial.print("AP IP address: ");
  Serial.println(myIP);
server.on("/", handleRoot);
server.on("/led", handle_led);
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
}
