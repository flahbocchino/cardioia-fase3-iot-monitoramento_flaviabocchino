# Relatório - Parte 2: Transmissão MQTT e Dashboard

**Projeto:** CardioIA - Fase 3  
**Aluna:** Flávia Bocchino | RM: 564213

---

## O que foi desenvolvido

Um sistema completo de transmissão de dados do ESP32 para a nuvem via protocolo MQTT, integrando os sensores DHT22 e LDR com um broker público e dashboard de visualização em tempo real.

---

## Fluxo de comunicação
ESP32 (sensores) → Wi-Fi → Broker MQTT (HiveMQ) → Node-RED → Dashboard

1. O ESP32 lê temperatura, umidade e LDR a cada 3 segundos
2. Publica cada valor em um tópico MQTT separado:
   - `cardioia/temperatura`
   - `cardioia/umidade`
   - `cardioia/ldr`
   - `cardioia/alerta` (quando limites são ultrapassados)
3. O Node-RED assina esses tópicos e exibe os dados no dashboard

---

## Broker MQTT utilizado

- **Broker:** HiveMQ Public Broker (`broker.hivemq.com`)
- **Porta:** 1883
- **Autenticação:** sem autenticação (broker público para fins acadêmicos)

---

## Dashboard Node-RED

O dashboard foi configurado com três elementos visuais:

| Elemento | Dado exibido | Alerta |
|---|---|---|
| Gráfico de linha | Temperatura em tempo real | > 37,5 °C |
| Gauge (medidor) | Umidade do ar | < 30% |
| Indicador de texto | Alertas ativos | Qualquer alerta |

---

## Conceitos aplicados

- **Fog Computing:** processamento parcial no ESP32 antes de transmitir
- **Cloud Computing:** broker MQTT na nuvem recebe e distribui os dados
- **Pub/Sub:** padrão de comunicação assíncrona entre dispositivo e dashboard

---

## Relevância para o CardioIA

A transmissão MQTT permite monitoramento cardiológico contínuo e em tempo real, com alertas automáticos quando sinais vitais ultrapassam limites clínicos. O dashboard oferece visualização imediata para profissionais de saúde, sem necessidade de acesso físico ao dispositivo.
