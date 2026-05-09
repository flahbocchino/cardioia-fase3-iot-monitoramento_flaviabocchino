# CardioIA — Fase 3: Monitoramento Contínuo com IoT

**Aluna:** Flávia Bocchino | **RM:** 564213  
**Curso:** Inteligência Artificial — FIAP  
**Fase:** 3 — Além das Fronteiras Digitais: Chips Neuromórficos

---

## Links do projeto

| Item | Link |
|---|---|
| Repositório GitHub | https://github.com/flahbocchino/cardioia-fase3-iot-monitoramento_flaviabocchino |
| Simulação Wokwi (ESP32) | https://wokwi.com/projects/463560222254129153 |
| Dashboard Node-RED | https://funny-black-lark-8290.flowfuse.cloud/ui |
| Vídeo de apresentação (YouTube) | https://youtu.be/dlVCc2OgH2Y |

---

## Sobre este projeto

Nesta fase do CardioIA, desenvolvemos um sistema completo de monitoramento cardiológico com IoT, simulando o comportamento de um wearable médico real. O sistema cobre todo o ciclo de dados: captura de sinais vitais, armazenamento local com resiliência offline, transmissão para a nuvem via MQTT, visualização em dashboard em tempo real e análise com Inteligência Artificial.
├── parte1-edge-wokwi/
│   ├── sketch.ino               # Código ESP32 com DHT22 + LDR
│   └── relatorio-parte1.md      # Relatório Edge Computing
│
├── parte2-mqtt-dashboard/
│   ├── esp32-mqtt.ino           # Código MQTT do ESP32
│   ├── relatorio-parte2.md      # Relatório MQTT + Dashboard
│   └── prints/                  # Prints do dashboard Node-RED
│
├── ir-alem-1-rest-email/
│   ├── monitor_cardioia.py      # Sistema REST + alerta por e-mail
│   └── relatorio-ir-alem-1.md  # Relatório Ir Além 1
│
└── ir-alem-2-series-temporais/
├── cardioia_iralem2_series_temporais.ipynb  # Notebook comparativo
└── relatorio-ir-alem-2.md   # Relatório Ir Além 2
---

## Parte 1 — Edge Computing (Wokwi + ESP32)

Protótipo de wearable cardiológico simulado com dois sensores:
- **DHT22**: temperatura e umidade do paciente
- **LDR (fotoresistor)**: sensor secundário de variação de sinal luminoso

O sistema lê os sensores a cada 3 segundos e implementa resiliência offline com buffer em memória: quando a conexão cai, os dados ficam armazenados localmente e são sincronizados automaticamente ao reconectar. Alertas são emitidos quando temperatura ultrapassa 37,5°C, umidade cai abaixo de 30% ou o LDR atinge valor crítico.

> Nota: o recurso SPIFFS (armazenamento em arquivo no chip) não funciona no simulador Wokwi Web. A alternativa adotada foi buffer em memória com saída pelo Monitor Serial, conforme orientado pelo enunciado.

🔗 **Wokwi:** https://wokwi.com/projects/463560222254129153

---

## Parte 2 — MQTT + Dashboard Node-RED

Transmissão dos dados do ESP32 para a nuvem via protocolo MQTT usando o broker público HiveMQ (`broker.hivemq.com:1883`). O Node-RED assina os tópicos e exibe os dados em tempo real no dashboard:

- Gráfico de linha: temperatura em tempo real
- Gauge: umidade (0–100%)
- Gauge: LDR (0–4095)
- Indicador de alertas automáticos com lógica de detecção de risco

🔗 **Dashboard:** https://funny-black-lark-8290.flowfuse.cloud/ui

### Nota sobre os prints na pasta `prints/`

A pasta `prints/` contém tanto os prints reais do dashboard Node-RED rodando no FlowFuse quanto uma imagem ilustrativa gerada para documentação. O dashboard real está acessível pelo link acima e pode ser verificado diretamente pelo professor. A imagem ilustrativa foi incluída apenas para facilitar a visualização da proposta de layout no contexto do relatório.

---

## Ir Além 1 — REST + Alerta por E-mail

Sistema em Python que simula monitoramento contínuo via API REST. Gera leituras de sinais vitais, envia via HTTP POST, verifica limites clínicos e dispara e-mail automático de alerta quando detecta risco.

**Limites monitorados:**
| Sinal | Condição | Limite |
|---|---|---|
| Temperatura | Febre | > 37,5°C |
| Umidade | Desidratação | < 30% |
| BPM | Taquicardia | > 120 BPM |
| BPM | Bradicardia | < 40 BPM |

---

## Ir Além 2 — IA em Séries Temporais

Comparação entre Regressão Logística e Rede Neuromórfica (LIF — Leaky Integrate-and-Fire) para classificação de séries temporais de BPM.

| Modelo | Acurácia |
|---|---|
| Regressão Logística | 100% |
| Rede Neuromórfica (LIF) | 48% |

A Regressão Logística obteve acurácia perfeita nos dados simulados, que têm separação linear clara. O modelo LIF, por sua vez, é mais adequado para padrões temporais complexos e não-lineares — como ECGs reais — onde sua arquitetura inspirada em neurônios biológicos se destaca, especialmente em hardware de baixo consumo energético.

🎥 **Vídeo:** https://youtu.be/dlVCc2OgH2Y

---

## Tecnologias utilizadas

- ESP32 + DHT22 + LDR (Wokwi)
- C++ (Arduino IDE)
- MQTT (HiveMQ)
- Node-RED (FlowFuse)
- Python 3
- Scikit-learn
- Google Colab
- GitHub

---

## Estrutura do repositório
