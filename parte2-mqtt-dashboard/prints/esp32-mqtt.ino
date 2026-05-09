#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

// ========== CONFIGURAÇÃO ==========
#define DHTPIN 15
#define DHTTYPE DHT22
#define LDR_PIN 34

const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;
const char* mqtt_topic_temp = "cardioia/temperatura";
const char* mqtt_topic_umid = "cardioia/umidade";
const char* mqtt_topic_ldr  = "cardioia/ldr";
const char* mqtt_topic_alerta = "cardioia/alerta";

DHT dht(DHTPIN, DHTTYPE);
WiFiClient espClient;
PubSubClient client(espClient);

unsigned long ultimaLeitura = 0;
const unsigned long INTERVALO = 3000;

void conectarWifi() {
  Serial.print("Conectando ao Wi-Fi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi conectado!");
}

void conectarMQTT() {
  while (!client.connected()) {
    Serial.print("Conectando ao broker MQTT...");
    if (client.connect("CardioIA-ESP32")) {
      Serial.println("Conectado!");
    } else {
      Serial.print("Falhou. Tentando novamente em 3s...");
      delay(3000);
    }
  }
}

void verificarAlertas(float temp, float umid, int ldr) {
  String alerta = "";
  if (temp > 37.5) alerta += "FEBRE;";
  if (umid < 30)   alerta += "UMIDADE_BAIXA;";
  if (ldr < 200)   alerta += "LDR_CRITICO;";
  if (alerta != "") {
    client.publish(mqtt_topic_alerta, alerta.c_str());
    Serial.println("ALERTA enviado: " + alerta);
  }
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  conectarWifi();
  client.setServer(mqtt_server, mqtt_port);
  Serial.println("=== CardioIA - Fase 3: MQTT ativo ===");
}

void loop() {
  if (!client.connected()) conectarMQTT();
  client.loop();

  unsigned long agora = millis();
  if (agora - ultimaLeitura >= INTERVALO) {
    ultimaLeitura = agora;

    float temp = dht.readTemperature();
    float umid = dht.readHumidity();
    int ldr = analogRead(LDR_PIN);

    if (isnan(temp) || isnan(umid)) {
      Serial.println("[ERRO] Falha na leitura.");
      return;
    }

    char buf[10];

    dtostrf(temp, 4, 2, buf);
    client.publish(mqtt_topic_temp, buf);

    dtostrf(umid, 4, 2, buf);
    client.publish(mqtt_topic_umid, buf);

    itoa(ldr, buf, 10);
    client.publish(mqtt_topic_ldr, buf);

    Serial.print("Publicado — Temp: "); Serial.print(temp);
    Serial.print(" | Umid: "); Serial.print(umid);
    Serial.print(" | LDR: "); Serial.println(ldr);

    verificarAlertas(temp, umid, ldr);
  }
}
