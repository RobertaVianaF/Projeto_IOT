#include <HTTPClient.h>
#include <WiFi.h>
#include <WiFiClient.h>




// Definição dos pinos para ESP32 
const int RED_LED_PIN = 14;   // GPIO12
const int GREEN_LED_PIN = 12;   // GPIO12
const int GAS_PIN = 2;   // GPIO14

// Configurações do WiFi
const char* ssid = "iPhone";
const char* password = "roberta1234";

// Configurações do CallMeBot
const String phoneNumber = "5516997431335";  // Formato: 5511999999999
const String apiKey = "7660349";

unsigned long previousMillis = 0;
const long interval = 500;  // Intervalo de verificação (500ms)
bool is_red_led_on = false;
bool red_pin_enabled = false;
bool green_pin_enabled = false;
bool alreadyNotified = false;

void setup() {
  Serial.begin(115200);
  
  // Configura os pinos
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(GAS_PIN, INPUT);
  
  // Desliga o red_led inicialmente
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, LOW);
  
  // Conecta ao WiFi
  WiFi.begin(ssid, password);
  Serial.print("Conectando ao WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado ao WiFi");
  Serial.println("IP: " + WiFi.localIP().toString());
  
  // Envia mensagem inicial
  sendWhatsAppMessage("Sistema de detecção de gás tóxico iniciado!");
}

void sendWhatsAppMessage(String message) {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;
    
    message.replace(" ", "%20");
    String url = "http://api.callmebot.com/whatsapp.php?phone=" + phoneNumber + "&apikey=" + apiKey + "&text=" + message;
    
    http.begin(client, url);
    int httpResponseCode = http.GET();
    
    if (httpResponseCode > 0) {
      Serial.printf("Mensagem WhatsApp enviada, código HTTP: %d\n", httpResponseCode);
    } else {
      Serial.printf("Erro ao enviar mensagem WhatsApp: %s\n", http.errorToString(httpResponseCode).c_str());
    }
    
    http.end();
  }
}

void red_led_on() {
  red_pin_enabled = true;
  green_pin_enabled = false;
}

void red_led_off() {
  red_pin_enabled = false;
  green_pin_enabled = true;
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, HIGH);
}

bool is_red_led_enable() {
  return red_pin_enabled;
}

void loop() {
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    
    bool danger_detected = false;
        
    // Verifica se detectou gás (LOW significa detecção)
    if (digitalRead(GAS_PIN) == HIGH) {
      Serial.println(digitalRead(GAS_PIN));
      danger_detected = true;
      Serial.println("Gás detectado!");
    }
    
    if (danger_detected) {
      if (!is_red_led_enable()) {
        red_led_on();
        if (!alreadyNotified) {
          sendWhatsAppMessage("Alerta! Detectamos emissão de gás tóxico! Verifique imediatamente.");
          alreadyNotified = true;
        }
      }
    } else {
      red_led_off();
      alreadyNotified = false;
    }
  }
  
  // Controle do red_led
  if (red_pin_enabled) {
    is_red_led_on = !is_red_led_on;
    digitalWrite(RED_LED_PIN, is_red_led_on ? HIGH : LOW);
    digitalWrite(GREEN_LED_PIN, is_red_led_on ? LOW : HIGH);
  }
}
