# AgroGuardian - Estação de Monitoramento Edge Computing 🌾🛰️

Este repositório contém o desenvolvimento da camada de **Edge Computing & Computer Systems** do projeto **AgroGuardian**, uma plataforma focada em transformar o manejo agrícola reativo em gestão preditiva. O protótipo foi inteiramente desenvolvido e validado de forma funcional utilizando o simulador **Tinkercad**.

---

## 📋 Descrição do Projeto
O **AgroGuardian Edge** é uma estação meteorológica e de monitoramento de solo automatizada projetada para operar diretamente nas extremidades (campo) da propriedade agrícola. Enquanto a plataforma central processa dados macro (como imagens orbitais e índices de vegetação NDVI), este dispositivo atua na coleta microclimática em tempo real. 

O sistema realiza o processamento local dos dados de temperatura e umidade da terra para tomar decisões autônomas imediatas (como ativação de alarmes e sinalizações de status), garantindo a segurança da lavoura mesmo em cenários de perda temporária de conexão com a internet.

---

## 🎯 Objetivo da Solução
* **Antecipação de Riscos:** Identificar preventivamente condições favoráveis a geadas, ondas de calor extremo e estresse hídrico (seca) antes que causem perdas produtivas.
* **Manejo Inteligente:** Fornecer dados locais precisos para otimizar os ciclos de irrigação, alinhando-se aos Objetivos de Desenvolvimento Sustentável da ONU (ODS 2 - Agricultura Sustentável e ODS 13 - Ação Contra a Mudança Global do Clima).
* **Autonomia Operacional:** Garantir que o produtor rural receba alertas visuais e sonoros instantâneos diretamente no campo, sem depender exclusivamente de telas de computadores.

---

## 🛠️ Componentes Utilizados
Abaixo estão listados os componentes eletrônicos configurados no simulador:

| Componente | Função no Projeto | Conexão no Arduino |
| :--- | :--- | :--- |
| **Arduino Uno R3** | Microcontrolador central responsável pela lógica do Edge Computing. | Placa Principal |
| **Display LCD 16x2** | Interface visual local para exibição das leituras em tempo real. | Pinos Digitais 12, 11, 5, 4, 3, 2 |
| **Sensor de Temperatura (TMP36)** | Monitora as oscilações térmicas do ar para prever riscos de geada. | Pino Analógico A1 |
| **Sensor de Umidade do Solo** | Mede o estresse hídrico diretamente na raiz da cultura monitorada. | Pino Analógico A0 |
| **LED Verde** | Indicador visual de status ideal/seguro para a plantação. | Pino Digital 8 |
| **LED Amarelo** | Indicador visual de atenção/estresse moderado. | Pino Digital 9 |
| **LED Vermelho** | Indicador de risco crítico iminente (Seca ou Geada). | Pino Digital 10 |
| **Buzzer (Piezo)** | Alarme sonoro intermitente ativado apenas em condições críticas. | Pino Digital 6 |
| **Placa de Ensaio e Resistores** | Linhas de distribuição elétrica e resistores de $220\ \Omega$ para os LEDs. | Barramentos VCC/GND |

---

## ⚙️ Explicação do Funcionamento
O algoritmo processa as informações coletadas na ponta e as categoriza em quatro estados lógicos baseado no cruzamento de dados exigidos pelo Dashboard do AgroGuardian:

1. **Risco Crítico de Seca (Estresse Hídrico):** Se a umidade do solo cair abaixo de **30%**, o sistema exibe `ALERTA: Solo Seco` no LCD, acende o **LED Vermelho** e dispara o **Buzzer** intermitente.
2.**Risco Crítico de Geada (Estresse Térmico):** Se a temperatura ambiente detectada pelo TMP36 for inferior a **5°C**, o sistema exibe `ALERTA: Geada!` no LCD, acende o **LED Vermelho** e aciona o **Buzzer**.
3. **Estado de Atenção:** Se a umidade do solo estiver estável porém em observação (entre **30% e 59%**), o sistema exibe `Status: Moderado` e acende apenas o **LED Amarelo**.
4. **Estado Ideal:** Se os indicadores estiverem em níveis perfeitos para a cultura (Umidade do solo $\ge$ **60%** e Temperatura $\ge$ **5°C**), o sistema exibe `Status: Solo OK` e acende o **LED Verde**.

> 🌐 **Integração com a Nuvem:** Além do controle local, o Arduino envia os dados formatados continuamente via protocolo Serial (`TEMP_C` e `UMID_SOLO`), simulando a alimentação em tempo real do banco de dados da plataforma AgroGuardian.

---

## 📐 Estrutura do Circuito
O circuito foi projetado visando escalabilidade e fidelidade técnica:
<img width="1321" height="549" alt="GS-AgroGuardian" src="https://github.com/user-attachments/assets/d2304b77-42bc-4446-bacd-1fa409da57c0" />
* As linhas de alimentação superiores e inferiores da *breadboard* foram interconectadas criando barramentos contínuos de $5\text{V}$ e GND.
* O display LCD foi configurado no modo de comunicação de 4 bits para liberar pinos analógicos e digitais.
* Todos os LEDs possuem resistores limitadores de corrente conectados aos seus respectivos cátodos para evitar queima de componentes em uma futura montagem física.

---

## 🚀 Instruções de Execução
Para testar o projeto no ambiente de simulação:
1. Acesse o circuito através do seu link de compartilhamento do **Tinkercad**. [Clique aqui para acessar a simulação no Tinkercad](https://www.tinkercad.com/things/48Wtwybpvh3-gs-agroguardian?sharecode=-1v9Ysc_ZNQbbsOX9PyOnBIFng804OAna5K_T8RTtNU)
2. Clique no botão **"Iniciar Simulação"**.
3. Clique em cima do componente **Sensor de Umidade do Solo** (placa vermelha) e movimente o controle deslizante para alterar os níveis de água no solo.
4. Clique em cima do sensor **TMP36** (componente preto) e mova o medidor de temperatura para simular calor extremo ou geadas.
5. Abra o painel **"Monitor Serial"** na parte inferior da tela de código para visualizar as strings de dados sendo transmitidas em tempo real.

---

## 👥 Integrantes do Grupo
* [cite_start]**Isabella Yogui Kohara** - RM569777 [cite: 3]
* [cite_start]**Júlia Santiago Mateini** - RM561315 [cite: 4]
* [cite_start]**Marcella Pinheiro Silva** - RM569457 [cite: 5]

---
*Global Solution 2026 - FIAP - 1ESPG* 
