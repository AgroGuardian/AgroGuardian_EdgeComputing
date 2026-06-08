#include <LiquidCrystal.h>

// Inicializa o LCD nos pinos padrão do Tinkercad
// RS, EN, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Definição dos Pinos
const int pinoSensorSolo = A0;  // Sensor de Umidade do Solo
const int pinoTMP36 = A1;       // Sensor de Temperatura TMP36
const int ledVerde = 8;
const int ledAmarelo = 9;
const int ledVermelho = 10;
const int buzzer = 6;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode(buzzer, OUTPUT);
  
  // Tela de Inicialização do AgroGuardian
  lcd.print("AgroGuardian");
  lcd.setCursor(0, 1);
  lcd.print("Iniciando...");
  delay(2000);
  lcd.clear();
}

void loop() {
  // --- LEITURA DA UMIDADE DO SOLO ---
  int leituraSolo = analogRead(pinoSensorSolo);
  // Mapeia a leitura analógica (0 a 875 no Tinkercad) para 0% a 100%
  int umidadeSolo = map(leituraSolo, 0, 875, 0, 100); 
  if(umidadeSolo > 100) umidadeSolo = 100;

  // --- LEITURA DA TEMPERATURA (TMP36) ---
  int leituraTMP = analogRead(pinoTMP36);
  float voltagem = leituraTMP * 5.0;
  voltagem /= 1024.0;
  // Converte a voltagem em graus Celsius baseado no datasheet do TMP36
  float temperaturaC = (voltagem - 0.5) * 100; 

  // --- EXIBIÇÃO DOS DADOS NO LCD ---
  lcd.setCursor(0, 0);
  lcd.print("T: ");
  lcd.print(temperaturaC, 1);
  lcd.print("C S: ");
  lcd.print(umidadeSolo);
  lcd.print("% ");

  // --- LÓGICA DE DECISÃO EDGE (ALERTAS LOCALIZADOS) ---
  lcd.setCursor(0, 1);
  
  // Cenário 1: Risco Crítico de Seca 
  if (umidadeSolo < 30) { 
    lcd.print("ALERTA: Solo Seco");
    digitalWrite(ledVermelho, HIGH);
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, LOW);
    
    // Alarme Sonoro Intermitente
    tone(buzzer, 1000);
    delay(200);
    noTone(buzzer);
  } 
  // Cenário 2: Risco de Geada (Temperatura muito baixa)
  else if (temperaturaC < 5.0) {
    lcd.print("ALERTA: Geada!  ");
    digitalWrite(ledVermelho, HIGH);
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, LOW);
    
    tone(buzzer, 1500);
    delay(200);
    noTone(buzzer);
  }
  // Cenário 3: Atenção/Monitoramento Moderado
  else if (umidadeSolo >= 30 && umidadeSolo < 60) {
    lcd.print("Status: Moderado");
    digitalWrite(ledAmarelo, HIGH);
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledVermelho, LOW);
    noTone(buzzer);
  } 
  // Cenário 4: Tudo sob controle0
  else {
    lcd.print("Status: Solo OK  ");
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVermelho, LOW);
    noTone(buzzer);
  }

  // Envio de logs para o Monitor Serial (Simulando a integração de dados para a nuvem)
  Serial.print("TEMP_C:"); Serial.print(temperaturaC);
  Serial.print(",UMID_SOLO:"); Serial.println(umidadeSolo);

  delay(1000); // Aguarda 1 segundo antes da próxima varredura
}