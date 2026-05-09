# Relatório - Parte 1: Edge Computing com ESP32

**Projeto:** CardioIA - Fase 3  
**Aluna:** Flávia Bocchino | RM: 564213  
**Link Wokwi:** https://wokwi.com/projects/463560222254129153

---

## O que foi desenvolvido

Um protótipo simulado de dispositivo vestível cardiológico usando ESP32 no Wokwi, com dois sensores:

- **DHT22**: lê temperatura e umidade do paciente
- **LDR (fotoresistor)**: sensor secundário que simula variação de sinal luminoso (analogia a oxímetro)

---

## Fluxo de funcionamento

1. O ESP32 lê os sensores a cada 3 segundos
2. Se Wi-Fi estiver **online**: envia os dados imediatamente para a nuvem (simulado via Serial)
3. Se Wi-Fi estiver **offline**: armazena os dados num buffer em memória (até 10 registros)
4. Quando o Wi-Fi reconecta: sincroniza automaticamente todos os dados do buffer antes de continuar

---

## Lógica de resiliência offline (Edge Computing)

O sistema alterna automaticamente entre online e offline a cada 5 ciclos de leitura, demonstrando que:

- Dados **nunca são perdidos** durante queda de conexão
- O buffer garante continuidade do monitoramento
- A sincronização é automática ao reconectar

> Nota: o recurso SPIFFS (armazenamento em arquivo no chip) não funciona no simulador Wokwi Web. A alternativa adotada foi o buffer em memória com saída pelo Monitor Serial, conforme orientado pelo enunciado.

---

## Alertas automáticos

O sistema emite alertas no Monitor Serial quando:

| Condição | Limite |
|---|---|
| Temperatura elevada | > 37,5 °C |
| Umidade baixa | < 30% |
| LDR crítico | < 200 |

---

## Relevância para o CardioIA

Esta etapa simula o comportamento de um wearable médico real: captura contínua de sinais vitais, processamento local no dispositivo (Edge) e transmissão segura para a nuvem — mesmo em ambientes com conectividade instável.
