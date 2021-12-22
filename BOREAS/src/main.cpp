#include<Arduino.h>
int sensor_not_connected(){
digitalWrite(2,LOW);
Serial.println("Se detecto que el sensor no esta bien conectado, puede se devido a que el dispositivo esta en corto");
Serial.println("con tierra o simplemente no esta conectado, reinicie el dispositivo o espere 30 segundos para el reinicio");
Serial.println("Y  no olvide de aseguar la coneccion del sensor");
for(int q = 0; q < 30;q++)
{
  Serial.print("#");
  delay(1000);
}
esp_restart();
}
float analogic;
int time_trigger = 0;
float euler_number = 2.71828182;
float euler_number_negative = 0.36787944117;
TaskHandle_t Task2, Task3;
int w;
int ready = 0;
float CO2 = 0;
float mg = 0;
long Rs = 0;
long Ro = 0;
long a = 5.5973021420;
long b =  -0.365425824;
long  ppm = 0;
float Rs_media = 0;
float conatdor = 0;
float co2_outdoor = 0;
float co2_peack = 0;
float co2_diference = 0;
float Decay63_percentage = 0;
float time63_percentage = 0;
float ventilation_rate = 0;
int  minute_max_peack = 61 ;
int minute_decay = 60;
int Ventilation_Rate = 0 ;
float probability = 0;
float quanta_inhaled_per_person = 0;
float average_quanta_concentration = 0;
float Breathing_rate = 0.318; //el numero debe de ser cambiado si se sabe lo que se hace, el valor es valido para alumnos de 16-21 
float Mask_eficiency = 30;//si se conoce la eficiencia de la masacara y se establece que todos tengan la misma, se pude cambiar
float Net_emission_Rate = 0;
float Total_order_loss_rate = 0;
float volume = 200;//se debe de cambiar dependiendo del salon, debe de ser m3
float Quanta_Exalation_rate_of_posible_infected = 2.0;//debe de cambiarse dependiendo del la actividad que se este realizando,pero la probabilidad es que todos estaen callados escuchando 
//al profesor porlo que por pura probabilidad el contagiado debe de ser un alumno, asi que tomamos en cuenta que el alumno solo esta respirando escuchando la clase
//control de perifericos------------------------------------------------------------------------------------------------------------
void loop1(void *parameter){
 /* for(;;){
if (ready == 1){
if (ppm > 900){ digitalWrite(2,HIGH); }
else{ digitalWrite(2,LOW); }
delay(1);}
vTaskDelay(10);*/}
//Setup-----------------------------------------------------------------------------------------------------------------------------
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
pinMode(34,INPUT);
pinMode(2,OUTPUT);
Serial.println("########################");
Serial.println("#                      #");
Serial.println("#      CALIBRANDO!     #");
Serial.println("#                      #");
Serial.println("########################");

for(int i = 0;i < 300; i++){
analogic = analogRead(34);
if(analogic < 1){
sensor_not_connected();
}else{
Rs = 1024*(20000/analogic)-20000;
conatdor = conatdor + Rs;
delay(1000);
}
}
ready = 1;
Ro = conatdor/(5.56 * 400);
 Rs = 1024 * (20000/analogRead(34)) - 20000;
  ppm = 142.48*(Rs / Ro);
  co2_outdoor = ppm;
}

//LOOP-------------------------------------------------------------------------------------------------------
void loop() {
for(int w = 1;w < 61;w++){
Ro = conatdor/(5.56 * 400);
 if(analogRead(34) == 0){
sensor_not_connected();
}
  Rs = 1024 * (20000/analogRead(34)) - 20000;
  ppm = 142.48*(Rs / Ro);
  if(ppm > co2_peack){
    co2_peack = ppm;
    minute_max_peack = w;
  }
Serial.print(ppm);
Serial.print(" ppm\n");

mg = ppm * 0.0409 * 44.01;
Serial.print(mg);
Serial.print(" mg/m3\n");
if (Decay63_percentage-ppm <= 1 && Decay63_percentage - ppm >= -1)
{
  minute_decay = w;
}
Serial.println(w);
delay(1000);
  }
co2_diference = co2_peack - co2_outdoor;
Serial.println("co2_diference past");
Decay63_percentage = co2_outdoor + (euler_number_negative * co2_diference);
Serial.println("Decay past");
ventilation_rate = 60;
Serial.println("ventilation past");
Total_order_loss_rate = ventilation_rate + 0.62 + 0.3;
Serial.println("total_los_ order past");
Net_emission_Rate = Quanta_Exalation_rate_of_posible_infected *(1-Mask_eficiency*100)*1;
Serial.println("emision rate past");
average_quanta_concentration = Net_emission_Rate/Total_order_loss_rate/volume*(1-(1-Total_order_loss_rate/1)*(1-pow(euler_number,Total_order_loss_rate)));
Serial.println("quanta concentration past");
quanta_inhaled_per_person = average_quanta_concentration * Breathing_rate * 1 * (1 - Mask_eficiency * 100);
Serial.println("quanta per person past");
probability = (1-(pow(euler_number,(quanta_inhaled_per_person))));
Serial.println("you done it past");
Serial.println("#############################################");
Serial.println("#         Probabilidad de contagio          #");
Serial.println("#############################################");
Serial.print("=>\t");
Serial.print(probability);
Serial.println("");
if (probability < 1){
Serial.println("[#         ]");
}else if (probability > 1 && probability <= 2)
{
Serial.println("[##        ]");  
}else if (probability > 2 && probability <= 3)
{
Serial.println("[###       ]");  
}else if (probability > 3 && probability <= 4)
{
Serial.println("[####      ]");  
}else if (probability > 4 && probability <= 5)
{
Serial.println("[#####     ]");  
}else if (probability > 5 && probability <= 6)
{
Serial.println("[######    ]");  
}else if (probability > 6 && probability <= 7)
{
Serial.println("[#######   ]");  
}else if (probability > 7 && probability <= 8)
{
Serial.println("[########  ]");  
}else if (probability > 8 && probability <= 9)
{
Serial.println("[######### ]");  
}else if (probability > 9 && probability <= 10)
{
Serial.println("[##########] How did we get here?");  
}

}
