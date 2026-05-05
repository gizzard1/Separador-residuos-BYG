// Descripción: Un dispositivo ESP32 escucha activamente un websocket P2P y envía la señal a 4 actuadores (leds) conectados a los pines GPIO 2, 4, 5 y 18. 
// El dispositivo también se conecta a una red Wi-Fi para facilitar la comunicación y el control remoto de los actuadores a través de una aplicación móvil o una interfaz web.
#include <WiFi.h>
#include <WebSocketsServer.h>
#include <base64.h>

#define WEBSOCKET_PORT 81
#define PIN_PUERTA_ACTUADOR 15
#define GREEN_LED 2
#define BLUE_LED 4
#define WHITE_LED 5
#define RED_LED 18

WebSocketsServer webSocket = WebSocketsServer(WEBSOCKET_PORT);

const String SECRET_PASSWORD_B64 = "bXljb250cmFzZW5h"; // "mycontrasena" en Base64
bool puertaAbierta = false; // Estado de la puerta

void apagarTodosLosLeds() {
  digitalWrite(2, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(18, LOW);
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  switch(type) {
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Desconectado!\n", num);
      break;
    case WStype_CONNECTED:
      {
        IPAddress ip = webSocket.remoteIP(num);
        Serial.printf("[%u] Conectado desde %d.%d.%d.%d\n", num, ip[0], ip[1], ip[2], ip[3]);
      }
      break;
    case WStype_TEXT:
      {
        String message = String((char*)(payload));
        // Separamos el mensaje esperando el formato "CONTRASEÑA_B64:COMANDO"
        int separatorIndex = message.indexOf(':');
        if (separatorIndex != -1) {
          String receivedB64 = message.substring(0, separatorIndex);
          String command = message.substring(separatorIndex + 1);

          if (receivedB64 == SECRET_PASSWORD_B64) {
             Serial.printf("[%u] Autenticado. Comando: %s\n", num, command.c_str());

             // Control de la puerta (Ejemplo: "P1" es abierta, "P0" es cerrada)
             if (command == "P1") {
               puertaAbierta = true;
               digitalWrite(PIN_PUERTA_ACTUADOR, HIGH); // Activar actuador de puerta abierta
               apagarTodosLosLeds();
               Serial.println("Puerta ABIERTA: Leds desactivados y bloqueados.");
               return;
             } else if (command == "P0") {
               puertaAbierta = false;
               digitalWrite(PIN_PUERTA_ACTUADOR, LOW); // Desactivar actuador de puerta
               Serial.println("Puerta CERRADA: Leds desbloqueados.");
               return;
             }

             // Si la puerta está abierta, no permitir encender ningún led
             if (puertaAbierta) {
               Serial.println("Comando rechazado: La puerta está abierta.");
               digitalWrite(18, HIGH); // Encender led rojo de aviso/error
               return;
             }
             
             // Lógica de exclusión mutua: si se va a encender uno nuevo, apagar todos primero
             if (command.endsWith("1")) {
               apagarTodosLosLeds();
             }

             if(command[0] == '2') digitalWrite(2, command[1] == '1' ? HIGH : LOW);
             if(command[0] == '4') digitalWrite(4, command[1] == '1' ? HIGH : LOW);
             if(command[0] == '5') digitalWrite(5, command[1] == '1' ? HIGH : LOW);
             if(command[0] == '1' && command[1] == '8') digitalWrite(18, command[2] == '1' ? HIGH : LOW);
          } else {
             Serial.printf("[%u] Error: Contraseña incorrecta\n", num);
             digitalWrite(18, HIGH); // Activar LED rojo por error de seguridad
          }
        } else {
          Serial.printf("[%u] Error: Formato de mensaje inválido\n", num);
          digitalWrite(18, HIGH); // Activar LED rojo por error de formato
        }
      }
      break;
  }
}

void setup() {
  Serial.begin(115200);
  // Configuración de los pines GPIO para los actuadores (leds)
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(WHITE_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(PIN_PUERTA_ACTUADOR, OUTPUT);

  // Conexión a la red Wi-Fi
  const char* ssid = "SSID";
  const char* password = "PASS";
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }
  
  Serial.println("Conectado a WiFi");

  // Imprimir la dirección IP del ESP32
  Serial.println("Dirección IP: ");
  Serial.println(WiFi.localIP());
  
  // Configuración del servidor WebSocket P2P
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

void loop() {
  // El servidor WebSocket se ejecuta en el loop principal
  webSocket.loop();
}
