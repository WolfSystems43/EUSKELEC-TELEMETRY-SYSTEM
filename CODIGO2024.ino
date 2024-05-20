/*
  Telemetría para Somoracers [CENTRO FORMACIÓN SOMORROSTRO]
  Autor: Luis Moricz Radu / Telemetry Manager 
  Contacto: luis.moricz.somorrostro@gmail.com 
  Github: https://github.com/WolfSystems43
  Descripción: Este código controla la telemetría de un vehículo para la competición EUSKELEC.
*/

#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>
#include <SPI.h>
#include <DHT.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <MPU6050.h>
#include <vector>


#define TFT_CS    D2     // TFT CS  
#define TFT_RST   D3     // TFT RST 
#define TFT_DC    D4     // TFT DC  
#define DHTPIN 3
#define DHTTYPE DHT22
#define rxPin 0
#define txPin 1

DHT dht(DHTPIN, DHTTYPE);
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
SoftwareSerial neogps(rxPin, txPin);
TinyGPSPlus gps;
MPU6050 sensor;

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

const char* ssid = "TKNIKA-2G";
const char* password = "mvpemqcv";
const char* mqtt_server = "broker.emqx.io";
const int mqttPort = 1883;
//const char* mqttUser = “mqtt username”;
//const char* mqttPassword = “mqtt password”;

float getTemp() {
  return dht.readTemperature();
}

void setup() {
  Serial.begin(9600);
  neogps.begin(9600);
  dht.begin();
  Wire.begin();
  sensor.initialize();
  setup_wifi();
  client.setServer(mqtt_server, mqttPort);
  client.setCallback(callback);
  tft.begin();
  tft.fillScreen(ILI9341_BLACK);
  tft.setRotation(1);
  layout();
}

void layout() {
  tft.setCursor(0, 10);
  tft.setTextColor(ILI9341_BLUE);
  tft.setTextSize(2);
  tft.println("        SOMORACERS");
  tft.setCursor(50, 30);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(1);
  tft.println("          C.F SOMORROSTRO");
  tft.setCursor(-100, 180);
  tft.setTextColor(ILI9341_ORANGE);
  tft.setTextSize(2);
  tft.println("          ULT. TIEMPO");
  tft.setCursor(5, 130);
  tft.setTextColor(ILI9341_RED);
  tft.setTextSize(3);
  tft.println("           KM/H");
  tft.setCursor(100, 180);
  tft.setTextColor(ILI9341_CYAN);
  tft.setTextSize(2);
  tft.println("        BATERIA");
  tft.setCursor(180, 10);
  tft.setTextColor(ILI9341_DARKCYAN);
  tft.setTextSize(2);
  tft.println("      PILOT");
  tft.setCursor(200, 50);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.println("     LUIS");
  tft.setCursor(200, 75);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.println("    MORICZ");
  tft.setCursor(200, 100);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.println("      76");
  tft.drawRect(-2, 171, 320, 172, ILI9341_WHITE);
  tft.drawRect(-2, 171, 160, 235, ILI9341_WHITE);
  tft.drawRect(240, 0, 320, 120, ILI9341_WHITE); // Posicion
  tft.drawRect(0, 0, 65, 71, ILI9341_WHITE); // Temperatura Cockpit
}

void loop() {
  temperatura();
  velocidad();
  tiempo();
  bateria();
  gpsloop();
  giroescopio();
}

void setup_wifi() {
  delay(10);
  Serial.println("Conectandose a: " + String(ssid)); 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("." + String('\n') + " ");
  }
  Serial.println("Wifi Conectado" + String('\n') + "IP:" );
  Serial.print(WiFi.localIP());
  delay(1000);
}

void callback(char* topic, uint8_t* payload, unsigned int length) {
  Serial.println("Mensaje recibido [ " + String(topic) + " ]");
  for (int i = 0; i < length; i++) {
    Serial.println((char)payload[i]);
  }

  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);
  } else 
      digitalWrite(BUILTIN_LED, HIGH);  
}

void reconnect() {
  Serial.println("Intentado reconectar MQTT...");
  if (client.connect("ESP8266Somorrostro")) {
    Serial.println("Conectado");
    delay (500);
  } else {
      Serial.print("Conexión fallida / Conexión perdida" + String('\n') + "Reintentando en 5 seg...");
      delay(5000);
    }
}

static void smartDelay(unsigned long ms) {
  unsigned long start = millis();
  do 
  {
    while (neogps.available()) 
      gps.encode(neogps.read());
  }
    while (millis() - start < ms);
}

void temperatura() {  
  float temp = getTemp();
  tft.setCursor(2, 10);
  tft.setTextColor(ILI9341_GREEN);
  tft.setTextSize(2);
  tft.println(" Temp");
  #define temperatura_cockpit "telemetria/DHT22/temperatura_cockpit"
  client.publish(temperatura_cockpit, String(temp).c_str(), true);
}

bool isNear(double lat1, double lng1, double lat2, double lng2, double radius = 10.0) {
  const double R = 6371000;
  double dLat = radians(lat2 - lat1);
  double dLng = radians(lng2 - lng1);
  double a = sin(dLat / 2) * sin(dLat / 2) +
            cos(radians(lat1)) * cos(radians(lat2)) *
            sin(dLng / 2) * sin(dLng / 2);
  double c = 2 * atan2(sqrt(a), sqrt(1 - a));
  double distance = R * c;
  return distance <= radius;
}

void tiempo() {
  tft.setCursor(40, 220);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  
  unsigned long startTime = 0;
  unsigned long lastLapTime = 0;
  int lapCount = 0;
  std::vector<unsigned long> lapTimes;

  double referenceLat = 42.846476; // Latitud del punto de meta VITORIA
  double referenceLng = -2.673633; // Longitud del punto de meta VITORIA

  while (neogps.available() > 0) {
    gps.encode(neogps.read());
    if (gps.location.isUpdated()) {
      double currentLat = gps.location.lat();
      double currentLng = gps.location.lng();

      if (isNear(currentLat, currentLng, referenceLat, referenceLng)) {
        if (startTime == 0) {
          startTime = millis();
          Serial.println("Cronómetro iniciado.");
        } else {
          unsigned long currentTime = millis();
          unsigned long lapTime = currentTime - startTime;
          startTime = currentTime;

          lastLapTime = lapTime; 
          lapTimes.push_back(lapTime);

          lapCount++;

          unsigned long minutes = lapTime / 60000;
          unsigned long seconds = (lapTime / 1000) % 60;
          unsigned long milliseconds = lapTime % 1000;
          
          char lapTimeBuffer[12]; // Buffer para el tiempo de vuelta
          snprintf(lapTimeBuffer, sizeof(lapTimeBuffer), "%02d:%02d:%03d", minutes, seconds, milliseconds);

          Serial.print("Vuelta ");
          Serial.print(lapCount);
          Serial.print(", Tiempo: ");
          Serial.println(lapTimeBuffer);

          tft.println(lapTimeBuffer);

          // Publicar el tiempo de vuelta
          #define lapTimeTopic "telemetria/tiempo/lapTime"
          client.publish(lapTimeTopic, lapTimeBuffer, true);
        }
      }
    }
  }
  #define lapsTopic "telemetria/tiempo/laps"
  client.publish(lapsTopic, String(lapCount).c_str(), true);
}

void velocidad() {
  tft.setCursor(10, 125);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(4);
  tft.println(gps.speed.kmph());
  #define speed_coche "telemetria/GPS/speed_coche"
  client.publish(speed_coche, String(gps.speed.kmph()).c_str(), true);
}

void bateria() {
  #define SIGNALPIN1 A0
  int porcentaje = analogRead(SIGNALPIN1);
  tft.setCursor(200, 210);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(3);
  tft.println("%");

  const float V_BAT_MAX = 5.0;  
  const float V_BAT_MIN = 3.3;  
  float voltaje = (porcentaje / 1023.0) * V_BAT_MAX;
  float mappedporcentaje = ((voltaje - V_BAT_MIN) / (V_BAT_MAX - V_BAT_MIN)) * 100.0;
  mappedporcentaje = constrain(porcentaje, 0, 100);

  #define porcentaje_bateria "telemetria/bateria/pocentaje_bateria"
  client.publish(porcentaje_bateria, String(mappedporcentaje).c_str(), true);
}

void gpsloop() {
 boolean newData = false;
 for (unsigned long start = millis(); millis() - start < 1000;) {
    while (neogps.available()) {
      if (gps.encode(neogps.read()))
        newData = true;
    }
  }
 if (newData) {
    newData = false;
    velocidad();
 }
}


void reset() {
  #define reset 4
  while (digitalRead(reset) == HIGH) {
    digitalWrite(TFT_RST, HIGH);
    delay(10);
    digitalWrite(TFT_RST, LOW);
    break;
  }
}

void giroescopio() {
  int16_t gx, gy, gz;
  unsigned long tiempo_prev = 0;
  float girosc_ang_y;
  float girosc_ang_y_prev;
  float dt;
  sensor.getRotation(&gx, &gy, &gz);
  
  unsigned long current_time = millis();
  dt = current_time - tiempo_prev;
  tiempo_prev = current_time;
    
  girosc_ang_y = (gy/131.0)*dt/1000.0 + girosc_ang_y_prev;
  girosc_ang_y_prev=girosc_ang_y;

  Serial.println("\tRotacion Voltante: " + String(girosc_ang_y));
  delay(2000);

  #define girosc_ang_y "telemetria/volante/girosc_ang_y"
  client.publish(girosc_ang_y, String(girosc_ang_y).c_str(), true);
}