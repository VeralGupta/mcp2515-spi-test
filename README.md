# mcp2515-spi-test
Minimal Arduino sketch to verify SPI communication with the MCP2515 CAN controller by reading the CANSTAT register.
# MCP2515 SPI Communication Test

This Arduino sketch helps verify **SPI communication** with the **MCP2515** CAN controller by reading the `CANSTAT` register over SPI. It’s a minimal, no-library test that confirms your wiring, power, and SPI interface are working **before** diving into full CAN bus implementation.

---

## 🔧 What It Does

- Initializes SPI on Arduino.
- Reads the MCP2515's `CANSTAT` register (`0x0E`) via raw SPI.
- Prints the result to the Serial Monitor.
- Interprets valid responses (e.g., configuration, loopback, listen-only modes).

---

## 🧪 Why Use This?

When using MCP2515 for CAN projects, SPI communication issues are common and can be hard to debug. This test sketch helps ensure:

- The MCP2515 is **powered and wired correctly**.
- The SPI connection is **functioning as expected**.
- You're getting valid, expected responses from the controller.

It’s perfect for quick validation before using more complex CAN libraries like `mcp_can`.

---

## 📦 Hardware Connections

| MCP2515 Pin | Arduino UNO Pin |
|-------------|------------------|
| VCC         | 5V               |
| GND         | GND              |
| CS          | D10              |
| SCK         | D13              |
| SI (MOSI)   | D11              |
| SO (MISO)   | D12              |

> ℹ️ Make sure the MCP2515 is powered at 5V and shares a common ground with the Arduino.

---

## 📈 Example Output

Starting MCP2515 SPI Test...  
CANSTAT Register: 0x80  
MCP2515 seems responsive over SPI.


Expected values for `CANSTAT`:

| Value | Mode          |
|-------|---------------|
| 0x80  | Configuration |
| 0x90  | Listen-only   |
| 0xA0  | Loopback      |

Unexpected values like `0xFF` or `0x00` may indicate:
- Incorrect wiring
- MCP2515 not powered
- SPI not initialized correctly

---

## 🧾 Code Snippet

```cpp
#define MCP2515_CS 10
#define MCP2515_READ 0x03
#define MCP2515_CANSTAT 0x0E

byte readMCP2515Register(byte address) {
  digitalWrite(MCP2515_CS, LOW);
  SPI.transfer(MCP2515_READ);
  SPI.transfer(address);
  byte result = SPI.transfer(0x00);
  digitalWrite(MCP2515_CS, HIGH);
  return result;
}

