int W = 0; 
int X = 0;
int Y = 0;
int Z = 0;  // Nueva variable para el cuarto botón
int A = 0;
int B = 0;

void setup() {
  pinMode(2, INPUT);    // W
  pinMode(3, INPUT);    // X
  pinMode(4, INPUT);    // Y
  pinMode(5, INPUT);    // Z (nuevo pin)
  pinMode(6, INPUT);    // A
  pinMode(7, INPUT);    // B
  pinMode(8, OUTPUT);   // Sum/Result
  pinMode(9, OUTPUT);   // Carry/Additional
  pinMode(10, OUTPUT);  // Infinito
  pinMode(11, OUTPUT);  // Indefinido
  pinMode(12, OUTPUT);  // Extra output
}

void loop() {
  // Reinicio de pines de salida antes de evaluar condiciones
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);

  // Lectura de entradas (ahora con Z)
  W = digitalRead(2);
  X = digitalRead(3);
  Y = digitalRead(4);
  Z = digitalRead(5);  // Lectura del nuevo botón Z
  A = digitalRead(6);
  B = digitalRead(7);

  // Operaciones lógicas y aritméticas
  // Suma (W=0, X=0, Y=1, Z=0)
  if (!W && !X && Y && !Z) {
    if (A && B) { 
      digitalWrite(8, HIGH); 
      digitalWrite(9, HIGH); 
    } else if (A ^ B) { 
      digitalWrite(8, HIGH); 
    }
  }

  // Resta (W=0, X=1, Y=1, Z=0)
  if (!W && X && Y && !Z) {
    if (A && !B) {
      // 1 - 0 = 1
      digitalWrite(8, HIGH);
    }
    if (!A && B) {
      // 0 - 1 = underflow → 11 en binario
      digitalWrite(8, HIGH);
      digitalWrite(9, HIGH);
    }
  }

  // Multiplicación (W=0, X=1, Y=0, Z=0)
  if (!W && X && !Y && !Z) {
    if (A && B) { 
      digitalWrite(8, HIGH);
    }
  }

  // División (W=1, X=0, Y=0, Z=0)
  if (W && !X && !Y && !Z) {  
    if (!A && !B) {
      digitalWrite(10, HIGH);  // Indefinido (0/0)
    } else if (A && !B) {
      digitalWrite(11, HIGH);  // Infinito (1/0)
    } else if (!A && B) {
      digitalWrite(12, HIGH);  // 0/1 → 0
    } else if (A && B) {
      digitalWrite(8, HIGH);  // 1/1 → 1
    }
  }

  // AND (W=1, X=0, Y=1, Z=0)
  if (W && !X && Y && !Z) {
    digitalWrite(8, A && B);
  }

  // OR (W=1, X=1, Y=0, Z=0)
  if (W && X && !Y && !Z) {
    digitalWrite(8, A || B);
  }

  // XOR (W=1, X=1, Y=1, Z=0)
  if (W && X && Y && !Z) {
    digitalWrite(8, A ^ B);
  }

  // NAND (W=1, X=0, Y=1, Z=1) - Nueva operación
  if (W && !X && Y && Z) {
    digitalWrite(8, !(A && B));  // NAND es el NOT de AND
  }
}