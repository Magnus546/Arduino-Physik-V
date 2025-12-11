// ---------------------------------------------------------------------------
// PIN- UND HARDWARE-DEFINITIONEN
// ---------------------------------------------------------------------------

// A0 misst die Spannung am Shunt-Widerstand (98,8 Ohm)
// Dieser Shunt sitzt zwischen A0 und GND
const int shuntPin = A0;

// Der reale Messwiderstand, durch den der gesamte Laststrom fließt
const float Rshunt = 98.8;      // Ohm -> sehr wichtig für genaue Strommessung

// Referenzspannung des Arduino ADC
// Die meisten Arduino Boards benutzen 5V als Referenz (0–1023 entspricht 0–5V)
const float Vref = 5.0;


// ---------------------------------------------------------------------------
// SETUP: Wird einmal beim Start ausgeführt
// ---------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);      // Serielle Ausgabe starten (Monitor öffnen!)
  pinMode(9, OUTPUT);      // Pin 9 als PWM-Ausgang definieren
}


// ---------------------------------------------------------------------------
// PWM-WERTE (DIE ERZEUGTEN SPANNUNGSSTUFEN)
// ---------------------------------------------------------------------------
// Diese Werte erzeugen verschiedene PWM-Stufen zwischen 0 und 5V.
// Beispiel: PWM 255 = 5V, PWM 127 ≈ 2.5V usw.

int einhalb = 25;
int eins = 51;
int eineinhalb = 76;
int zwei = 102;
int zweieinhalb = 127;
int drei = 153;
int dreieinhalb = 178;
int vier = 204;
int viereinhalb = 229;
int funf = 255;


// ---------------------------------------------------------------------------
// FUNKTION: Strom über den Shunt-Widerstand messen
// ---------------------------------------------------------------------------
//
// So funktioniert's:
// Der Shunt sitzt zwischen A0 und GND.
// A0 misst die Spannung, die direkt über dem Widerstand abfällt.
// Formel:
//      U_shunt = (ADC-Wert / 1023) * Vref
//
// und Strom I:
//      I = U_shunt / Rshunt
//
// Da der Shunt klein ist: Strom fällt nur wenig Spannung ab.
// ---------------------------------------------------------------------------

float readCurrent() {

  // Rohwert des ADC lesen (0–1023)
  int raw = analogRead(shuntPin);

  // ADC-Wert in echte Spannung umwandeln
  float Ushunt = (raw / 1023.0) * Vref;

  // Strom berechnen: I = U / R
  float I = Ushunt / Rshunt;

  return I;    // Ergebnis in Ampere
}


// ---------------------------------------------------------------------------
// FUNKTION: PWM AUSGEBEN UND WERTE MESSEN + ANZEIGEN
// ---------------------------------------------------------------------------
//
// Diese Funktion:
// 1. setzt eine PWM-Spannung am Pin 9
// 2. lässt kurz Zeit zur Stabilisierung
// 3. misst die Spannung am Shunt
// 4. berechnet den Strom
// 5. gibt alles im Serial Monitor aus
// ---------------------------------------------------------------------------

void writeAndPrint(int pwmValue, const char* label) {

  // PWM-Wert ausgeben
  analogWrite(9, pwmValue);

  // Berechnete Ausgangsspannung (für Info)
  float Uout = (pwmValue / 255.0) * 5.0;

  delay(100);   // kleine Wartezeit für stabile Messung

  // Tatsächlich gemessener Strom über den Shunt
  float I = readCurrent();

  // Spannung *über* dem Shunt (zur Kontrolle)
  float Ushunt = I * Rshunt;


  // -------------------------------------------------------------------------
  // AUSGABE IM SERIAL MONITOR
  // -------------------------------------------------------------------------

  Serial.print(label);              // "0.5" "1.0" "1.5" usw.
  Serial.print(" -> PWM: ");
  Serial.print(pwmValue);

  Serial.print(" | Ausgangsspannung: ");
  Serial.print(Uout, 2);
  Serial.print(" V");

  Serial.print(" | Shuntspannung: ");
  Serial.print(Ushunt, 4);
  Serial.print(" V");

  Serial.print(" | Strom: ");
  Serial.print(I * 1000, 2);        // Umwandlung in mA für bessere Lesbarkeit
  Serial.println(" mA");

  delay(5000);  // 5 Sekunden warten, bevor die nächste Stufe aktiviert wird
}


// ---------------------------------------------------------------------------
// LOOP: Alle PWM-Stufen nacheinander durchlaufen
// ---------------------------------------------------------------------------
void loop() {

  writeAndPrint(einhalb, "0.5");
  writeAndPrint(eins, "1.0");
  writeAndPrint(eineinhalb, "1.5");
  writeAndPrint(zwei, "2.0");
  writeAndPrint(zweieinhalb, "2.5");
  writeAndPrint(drei, "3.0");
  writeAndPrint(dreieinhalb, "3.5");
  writeAndPrint(vier, "4.0");
  writeAndPrint(viereinhalb, "4.5");
  writeAndPrint(funf, "5.0");
}
