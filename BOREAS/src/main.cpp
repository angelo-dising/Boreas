#include <WiFi.h>
#include <WebServer.h>
TaskHandle_t Task2, Task3;
float CO2 = 0;
float mg = 0;
long Rs = 0;
long Ro = 0;
long a = 5.5973021420;
long b =  -0.365425824;
long  ppm = 0;
int ppm_sus =  ppm;
float Rs_media = 0;
float conatdor = 0;
const char* ssid = "ESP-WIFI_1";  
const char* password = "ESP-PASSWORD"; 
IPAddress ip(192,168,4,22);        
IPAddress gateway(192,168,4,9);     
IPAddress subnet(255,255,255,0);    
WebServer server(80); 
 String primera_parte = "<!DOCTYPE html> \
<html lang=\"en\">\
  <head>\
    <meta charset=\"UTF-8\" />\
    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\" />\\
    <title>REPORT</title>\
    <link rel=\"preconnect\" href=\"https://fonts.gstatic.com\" />\
  </head>\
<body>\
    <main style=\" font-family: 'Poppins', sans-serif;\
    min-height: 110vh;\
    background-image: linear-gradient(to left top, #c3463f, #ce4e6c, #cc6096, #bd76bb, #a68dd5, #929fe7, #7caff2, #69bff8, #52cffe, #41dfff, #46eefa, #5ffbf1);\
    display: flex;\
    align-items: center;\
    justify-content: center;\">\
      <section style=\"background: white;\
      min-height: 70vh;\
      width: 90%;\
      background: linear-gradient(\
        to left bottom,\
        rgba(196, 247, 231, 0),\
        rgba(255, 255, 255, 1)\
      );\
      border-radius: 2rem;\
  z-index: 2;\
  backdrop-filter: blur(2rem);\
  display: flex;\">\
        <div style = \"flex: 0.3;\
        filter: blur();\
        border-radius: 35px;\
        display: flex;\
        flex-direction: column;\
        align-items: center;\
        justify-content: space-evenly;\
        text-align: center;\
        background: linear-gradient(\
          to right bottom,\
          white,\
          rgba(240, 255, 255, 0.2)\
          )\"> \
          <div style=\"color: green; text-align: center;\">\
          </div>\
          <div style=\"color: black; text-align: center; font-size: large;\">\
            <div style=\"color:black; text-align: center; font-size: large;\">\
              \
              <h2>CPU SPEED: </h2> <!--modificar! para variables-->\
            </div>\
            <div style=\"color: black;text-align: center;\">\
              \
              <h2>MEMORY:</h2><!--modificar uso de variables-->\
            </div>\
            <div style=\"text-align: center;\">\
              <h2>CPU TEMPERATURE: </h2><!--modificar! para vairbables-->\
            </div>\
            <div style=\"text-align: center;\">\
              <h2>CURRENT STATE</h2><!--modificar para variables-->\
            </div>\
          </div>\
          <div style=\" background: linear-gradient(to right bottom ,rgb(89, 86, 86),rgb(72, 66, 66));\
          border-radius: 2rem;\
          color: white;\
          padding: 1rem;\
          position: relative;\
          opacity: 0.5;\">\
            <h2>Model: esp32 wroom </h2><!--VARIABLE A MODIFICAR-->\
          </div>\
        </div>\
        <div style=\"flex: 1;\">\
          <div style=\"font-size: large;\">\
            <h1>SENSOR READ</h1>\
            \
          </div>\
          <div>\
            <div style=\" display: flex;\
            position: relative;\
            border-radius: 2rem;\
            background: linear-gradient(\
              to left top,\
              rgba(255, 255, 255, 0.8),\
              rgba(255, 255, 255, 0.5)\
            ); margin-left: 10px;\
  margin-right: 10px;\
  margin-bottom: 20px;\">\
              <div style=\"display: flex;flex-direction: column;justify-content: space-between;\"><!--targeta 3-->\
                <h2>";

String segunda_parte = "</h2>\
                <div></div>\
              </div>\
            </div>\
            <div  style = \"display: flex;\
            position: relative;\
            border-radius: 2rem;\
            background: linear-gradient(\
              to left top,\
              rgba(255, 255, 255, 0.8),\
              rgba(255, 255, 255, 0.5)\
            ); margin-left: 10px;\
  margin-right: 10px;\
  margin-bottom: 20px;\">\
              <div style=\"display: flex;flex-direction: column;justify-content: space-between;position: absolute; bottom: 30px;\"><!--targeta 2-->\
                <h2></h2>\
                <p></p>\
                <div> </div>\
              </div>\
              <h2>";

            String tercera_Parte = "</h2>\
            </div>\
            <div style=\" display: flex;\
            position: relative;\
            border-radius: 2rem;\
            background: linear-gradient(\
              to left top,\
              rgba(255, 255, 255, 0.8),\
              rgba(255, 255, 255, 0.5)\
            ); margin-left: 10px;\
  margin-right: 10px;\
  margin-bottom: 20px;\">\
              <div><!--targeta 1-->\
                <h2>";

                String cuarta_parte = "</h2>\
                <div></div>\
              </div>\
              <h2> </h2>\
            </div>\
            <div id=\"back\"></div>\
          </div>\
        </div>\
      </section>\
    </main>\
  </body>\
</html>";

void loop1(void *parameter){
  for(;;){
    Serial.println("desde loop 3 -> "); 
  
  
    delay(5000);

  }
  vTaskDelay(10);
}
 


void handleConnectionRoot() {
  String final_1 = primera_parte + String(ppm) + segunda_parte + String(Rs_media) + tercera_Parte + String(Rs) + cuarta_parte;
  server.send(200, "text/html", final_1);
}


void setup() {
  Serial.begin(115200);
  xTaskCreatePinnedToCore(
      loop1,
      "Task_3",
      1000,
      NULL,
      0,
      &Task3,
      0);
   WiFi.softAP(ssid, password); 
  WiFi.softAPConfig(ip, gateway, subnet);
  Serial.print("Nombre de mi red esp32: ");
  Serial.println(ssid);
  server.on("/", handleConnectionRoot);
  server.begin();
  Serial.println("Servidor HTTP iniciado");
  delay(150);
pinMode(34,INPUT);
pinMode(2,OUTPUT);
Serial.println("########################");
Serial.println("#                      #");
Serial.println("#      CALIBRANDO!     #");
Serial.println("#                      #");
Serial.println("########################");
Serial.println(analogRead(34));
for(int i = 0;i < 300; i++){
Serial.println(analogRead(34));
Rs = 1024*(20000/analogRead(34))-20000;
Serial.println(Rs);
conatdor = conatdor + Rs;
Serial.println(conatdor);
delay(10);
}
Serial.println(conatdor);

delay(1000);

}
 
void loop() {
  server.handleClient();
  Ro = conatdor/(5.56 * 400);
  Rs = 1024 * (20000/analogRead(34 )) - 20000;
  ppm = 142.48*(Rs / Ro);

Serial.print(ppm);
Serial.print(" ppm\n");
mg = ppm * 0.0409 * 44.01;
Serial.print(mg);
Serial.print(" mg/m3\n");
if (ppm > 800){
digitalWrite(2,HIGH);
}else{
digitalWrite(2,LOW);
}
delay(100);
}
