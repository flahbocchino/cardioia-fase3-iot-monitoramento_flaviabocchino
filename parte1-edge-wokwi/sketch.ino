#include <DHT.h>

#define DHTPIN 15
#define DHTTYPE DHT22
#define LDR_PIN 34

DHT dht(DHTPIN, DHTTYPE);

bool wifiConectado = true;

struct Leitura {
  float temperatura;
  float umidade;
  int ldr;
  unsigned long timestamp;
};

const int MAX_BUFFER = 10;
Leitura bufferOffline[MAX_BUFFER];
int totalBufferizado = 0;

unsigned long ultimaLeitura = 0;
const unsigned long INTERVALO = 3000;
int ciclo = 0;

void setup() {
  Serial.begin(115200);
  dht.begin();
  Serial.println("=== CardioIA - Fase 3: Monitoramento IoT ===");
  Serial.println("Sensores: DHT22 + LDR");
  Serial.println("Resiliencia offline ativa (buffer em memoria)");
  Serial.println("=============================================");
}

void enviarParaNuvem(Leitura l) {
  Serial.println("  [NUVEM] Enviando dados...");
  Serial.print("  Temperatura: "); Serial.print(l.temperatura); Serial.println(" C");
  Serial.print("  Umidade: "); Serial.print(l.umidade); Serial.println(" %");
  Serial.print("  LDR: "); Serial.println(l.ldr);
  Serial.println("  [NUVEM] Transmitido com sucesso.");
}

void sincronizarBuffer() {
  if (totalBufferizado == 0) return;
  Serial.println(">>> Wi-Fi reconectado. Sincronizando dados offline...");
  for (int i = 0; i < totalBufferizado; i++) {
    enviarParaNuvem(bufferOffline[i]);
  }
  totalBufferizado = 0;
  Serial.println(">>> Sincronizacao concluida.");
}

void verificarAlertas(float temp, float umidade, int ldr) {
  if (temp > 37.5) Serial.println("  *** ALERTA: Temperatura elevada! ***");
  if (umidade < 30) Serial.println("  *** ALERTA: Umidade baixa! ***");
  if (ldr < 200)   Serial.println("  *** ALERTA: LDR em valor critico! ***");
}

void loop() {
  unsigned long agora = millis();

  if (ciclo > 0 && ciclo % 5 == 0) {
    wifiConectado = !wifiConectado;
    Serial.print("\n[SISTEMA] Wi-Fi ");
    Serial.println(wifiConectado ? "CONECTADO" : "DESCONECTADO");
  }

  if (agora - ultimaLeitura >= INTERVALO) {
    ultimaLeitura = agora;
    ciclo++;

    float temp = dht.readTemperature();
    float umid = dht.readHumidity();
    int ldr = analogRead(LDR_PIN);

    if (isnan(temp) || isnan(umid)) {
      Serial.println("[ERRO] Falha na leitura do DHT22.");
      return;
    }

    Serial.println("\n--- Leitura #" + String(ciclo) + " ---");
    Serial.print("Temperatura: "); Serial.print(temp); Serial.println(" C");
    Serial.print("Umidade: "); Serial.print(umid); Serial.println(" %");
    Serial.print("LDR: "); Serial.println(ldr);
    Serial.print("Wi-Fi: "); Serial.println(wifiConectado ? "ONLINE" : "OFFLINE");

    verificarAlertas(temp, umid, ldr);

    Leitura lAtual = {temp, umid, ldr, agora};

    if (wifiConectado) {
      sincronizarBuffer();
      enviarParaNuvem(lAtual);
    } else {
      if (totalBufferizado < MAX_BUFFER) {
        bufferOffline[totalBufferizado++] = lAtual;
        Serial.print("[OFFLINE] Bufferizado. Total: ");
        Serial.println(totalBufferizado);
      } else {
        Serial.println("[OFFLINE] Buffer cheio.");
      }
    }
  }
}
