# Relatório - Ir Além 2: IA em Séries Temporais de Saúde

**Projeto:** CardioIA - Fase 3  
**Aluna:** Flávia Bocchino | RM: 564213

---

## Objetivo

Comparar um classificador tradicional (Regressão Logística) com uma rede neuromórfica simples (modelo LIF — Leaky Integrate-and-Fire) para classificação de séries temporais de sinais vitais cardíacos.

---

## Dados utilizados

Série temporal simulada de BPM (batimentos por minuto) com duas classes:

- **Normal**: 70 BPM médio, variação senoidal suave
- **Risco**: 110 BPM médio, variação mais intensa

Total: 1000 amostras (500 por classe). Features extraídas: valor atual de BPM, média móvel de 5 pontos e variação entre leituras.

---

## Modelos comparados

### Modelo 1: Regressão Logística
Classificador linear supervisionado. Aprende um limite de decisão entre as classes com base nas features numéricas.

### Modelo 2: Rede Neuromórfica (LIF — Leaky Integrate-and-Fire)
Modelo inspirado no funcionamento biológico dos neurônios. O neurônio acumula potencial elétrico ao receber sinais de entrada. Quando esse potencial ultrapassa um limiar, dispara um "spike" e zera. A classificação é feita com base na taxa de spikes gerada por cada amostra.

---

## Resultados

| Modelo | Acurácia |
|---|---|
| Regressão Logística | 100% |
| Rede Neuromórfica (LIF) | 48% |

---

## Análise comparativa

A Regressão Logística obteve acurácia perfeita porque os dados simulados têm separação linear clara entre as classes — exatamente o cenário em que esse modelo é mais eficiente.

O modelo LIF obteve 48% — próximo ao acaso — porque sua lógica de classificação por taxa de spikes não captura bem a separação linear dos dados. O LIF é mais adequado para padrões temporais complexos e não-lineares, como detecção de arritmias em ECGs reais, onde a dinâmica dos spikes tem vantagem sobre modelos convencionais.

---

## Vantagens e limitações

**Regressão Logística**
- Vantagens: rápida, interpretável, eficiente em dados linearmente separáveis
- Limitações: não captura padrões temporais complexos ou não-lineares

**Rede Neuromórfica (LIF)**
- Vantagens: baixo consumo energético, processamento em tempo real, adequada para hardware especializado (chips neuromórficos como Intel Loihi)
- Limitações: difícil de treinar, sensível à escolha de hiperparâmetros, menos eficiente em dados simples

---

## Conclusão

Para dados clínicos simples e bem estruturados, a Regressão Logística é superior. Redes neuromórficas mostram seu potencial em cenários de baixa energia e padrões temporais complexos — o que as torna relevantes para wearables médicos de próxima geração, como o que o CardioIA propõe simular.
