#include <SPI.h>

#define MCP2515_CS 10
#define MCP2515_READ 0x03
#define MCP2515_CANSTAT 0x0E

void setup() {
  Serial.begin(9600);
  SPI.begin();
  pinMode(MCP2515_CS, OUTPUT);
  digitalWrite(MCP2515_CS, HIGH);

  delay(1000);
  Serial.println("Starting MCP2515 SPI Test...");

  byte canstat = readMCP2515Register(MCP2515_CANSTAT);
  Serial.print("CANSTAT Register: 0x");
  Serial.println(canstat, HEX);
  
  if (canstat == 0x80 || canstat == 0x90 || canstat == 0xA0) {
    Serial.println("MCP2515 seems responsive over SPI.");
  } else {
    Serial.println("Unexpected response. Check wiring and power.");
  }
}

void loop() {
  // Do nothing
}

byte readMCP2515Register(byte address) {
  digitalWrite(MCP2515_CS, LOW);
  SPI.transfer(MCP2515_READ);
  SPI.transfer(address);
  byte result = SPI.transfer(0x00);
  digitalWrite(MCP2515_CS, HIGH);
  return result;
}
