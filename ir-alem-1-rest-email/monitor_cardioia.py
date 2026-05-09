import requests
import smtplib
import json
import random
import time
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
from datetime import datetime

# ========== CONFIGURAÇÃO ==========
EMAIL_REMETENTE = "cardioia.alerta@gmail.com"
EMAIL_SENHA = "sua_senha_app_aqui"
EMAIL_DESTINATARIO = "rm564213@fiap.com.br"

API_URL = "https://jsonplaceholder.typicode.com/posts"  # API REST pública para simulação

# ========== LIMITES CLÍNICOS ==========
LIMITE_TEMP_MAX = 37.5
LIMITE_UMID_MIN = 30
LIMITE_BPM_MAX = 120
LIMITE_BPM_MIN = 40

# ========== SIMULA LEITURA DE SENSORES ==========
def gerar_sinais_vitais():
    return {
        "timestamp": datetime.now().strftime("%Y-%m-%d %H:%M:%S"),
        "temperatura": round(random.uniform(35.0, 39.5), 1),
        "umidade": round(random.uniform(20.0, 70.0), 1),
        "bpm": random.randint(35, 140),
        "paciente": "Simulado-CardioIA"
    }

# ========== ENVIA DADOS VIA API REST ==========
def enviar_para_api(dados):
    try:
        response = requests.post(API_URL, json=dados)
        if response.status_code == 201:
            print(f"[API] Dados enviados com sucesso. ID: {response.json().get('id')}")
        else:
            print(f"[API] Resposta: {response.status_code}")
    except Exception as e:
        print(f"[API] Erro: {e}")

# ========== VERIFICA RISCOS ==========
def verificar_riscos(dados):
    alertas = []
    if dados["temperatura"] > LIMITE_TEMP_MAX:
        alertas.append(f"Temperatura elevada: {dados['temperatura']} °C (limite: {LIMITE_TEMP_MAX} °C)")
    if dados["umidade"] < LIMITE_UMID_MIN:
        alertas.append(f"Umidade baixa: {dados['umidade']}% (limite: {LIMITE_UMID_MIN}%)")
    if dados["bpm"] > LIMITE_BPM_MAX:
        alertas.append(f"Taquicardia detectada: {dados['bpm']} BPM (limite: {LIMITE_BPM_MAX} BPM)")
    if dados["bpm"] < LIMITE_BPM_MIN:
        alertas.append(f"Bradicardia detectada: {dados['bpm']} BPM (mínimo: {LIMITE_BPM_MIN} BPM)")
    return alertas

# ========== ENVIA E-MAIL DE ALERTA ==========
def enviar_email(dados, alertas):
    try:
        msg = MIMEMultipart()
        msg["From"] = EMAIL_REMETENTE
        msg["To"] = EMAIL_DESTINATARIO
        msg["Subject"] = "🚨 CardioIA - Alerta de Sinal Vital"

        corpo = f"""
CardioIA - Sistema de Monitoramento Cardiológico
=================================================

ALERTA DETECTADO em {dados['timestamp']}

Paciente: {dados['paciente']}

Sinais Vitais:
- Temperatura: {dados['temperatura']} °C
- Umidade: {dados['umidade']} %
- BPM: {dados['bpm']}

Alertas identificados:
"""
        for a in alertas:
            corpo += f"  ⚠️ {a}\n"

        corpo += "\nEste é um alerta automático do sistema CardioIA."

        msg.attach(MIMEText(corpo, "plain"))

        with smtplib.SMTP_SSL("smtp.gmail.com", 465) as server:
            server.login(EMAIL_REMETENTE, EMAIL_SENHA)
            server.sendmail(EMAIL_REMETENTE, EMAIL_DESTINATARIO, msg.as_string())

        print(f"[EMAIL] Alerta enviado para {EMAIL_DESTINATARIO}")

    except Exception as e:
        print(f"[EMAIL] Erro ao enviar: {e}")

# ========== LOOP PRINCIPAL ==========
def main():
    print("=== CardioIA - Monitor REST + Alertas por E-mail ===")
    print("Monitorando sinais vitais a cada 5 segundos...\n")

    ciclos = 5  # para fins de simulação acadêmica
    for i in range(ciclos):
        print(f"--- Ciclo {i+1}/{ciclos} ---")
        dados = gerar_sinais_vitais()
        print(f"Sinais: Temp={dados['temperatura']}°C | Umid={dados['umidade']}% | BPM={dados['bpm']}")

        enviar_para_api(dados)

        alertas = verificar_riscos(dados)
        if alertas:
            print(f"[RISCO] {len(alertas)} alerta(s) detectado(s):")
            for a in alertas:
                print(f"  ⚠️ {a}")
            enviar_email(dados, alertas)
        else:
            print("[OK] Sinais dentro dos limites normais.")

        print()
        if i < ciclos - 1:
            time.sleep(5)

    print("=== Monitoramento encerrado ===")

if __name__ == "__main__":
    main()
