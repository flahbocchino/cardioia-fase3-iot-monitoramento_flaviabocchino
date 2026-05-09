# Relatório - Ir Além 1: Comunicação REST e Alertas por E-mail

**Projeto:** CardioIA - Fase 3  
**Aluna:** Flávia Bocchino | RM: 564213

---

## O que foi desenvolvido

Um sistema em Python que simula o monitoramento contínuo de sinais vitais via API REST, com detecção automática de risco e disparo de e-mail de alerta quando os limites clínicos são ultrapassados.

---

## Fluxo do sistema
Geração de sinais vitais → Envio via API REST → Verificação de risco → Alerta por e-mail
1. O sistema gera leituras simuladas de temperatura, umidade e BPM
2. Envia os dados para uma API REST via HTTP POST
3. Verifica se algum valor ultrapassa os limites clínicos definidos
4. Se houver risco, dispara automaticamente um e-mail de alerta

---

## Limites clínicos monitorados

| Sinal Vital | Condição | Limite |
|---|---|---|
| Temperatura | Febre | > 37,5 °C |
| Umidade | Desidratação | < 30% |
| BPM | Taquicardia | > 120 BPM |
| BPM | Bradicardia | < 40 BPM |

---

## Tecnologias utilizadas

- **Python 3**: linguagem principal
- **requests**: envio de dados via HTTP POST
- **smtplib + MIME**: envio de e-mail automatizado
- **API REST pública (JSONPlaceholder)**: simula endpoint de recebimento de dados

---

## Conceitos aplicados

- **REST API**: comunicação padronizada entre o monitor e o servidor
- **RPA (Robotic Process Automation)**: disparo automático de e-mail sem intervenção humana
- **Detecção de risco clínico**: lógica baseada em limites médicos reais

---

## Relevância para o CardioIA

Este módulo representa a camada de comunicação e alerta do CardioIA: dados captados pelo ESP32 podem ser processados por este sistema Python, que decide automaticamente quando acionar a equipe médica — sem depender de monitoramento humano constante.
