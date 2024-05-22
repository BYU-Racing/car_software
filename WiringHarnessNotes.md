# Wiring Harness

## Wiring

### Standards

#### Plugs

- CAN wires
  - CANL(Green) goes to pin 1
  - CANH(White or Yellow) goes to pin 2

#### Colors

- Red = Power
- Black = Ground
- Yellow = Can High
- Green = Can Low
- Green/white twisted pair
  - Green = Can Low
  - White = Can High
- Blue = Analog
- White = Digital
- I2C
  - Blue = SCL
  - White = SDA

## 24-Pin Plugs

### Teensy 1 - Rear Data Collector

#### Output Pins

- 3.3V Output
  - Only goes to the 2 Damper Pots
  - A 1 pin plug spiced into the power for the 2 of them is my reccommended method
  - Alternatively, we could do a bus bar
- 5V in
  - Single pin plug required
- Ground pin
  - No plug necessary, gets bolted straight to chassis
- Pins 40 & 41
  - Inputs for damper pots
  - Along with power to each will need 2 plug connectors

#### Necessary Plugs

| | 1- Pin |  2- Pin |
| --- | --- | --- |
| | 5V in | CAN Line|
| | 3.3V out | Right Damper Pot |
| | - | Left Damper Pot |
| Totals| 2 | 3 |

### Teensy 2 - Front Data Collector

#### Output Pins

- 3.3V Output
  - Goes to the 2 Damper Pots, Throttle Pots, and I2C breakout board
  - Will use bus bar, wire from plug goes straight to the bus
- 5V in
  - Single pin plug required
  - Also needs to power brake line pressure sensor
- Ground pin
  - No plug necessary, gets bolted straight to chassis
- Pins 39 & 40
  - Inputs for Throttle pots
  - Both will get seperate single wire plugs to make them easy to monitor
- Pins 22 & 23
  - Inputs for damper pots
  - Along with power each will need 2 pin plug
- Pin 38
  - Will be used for the dash board switch
- Pin 3
  - has a voltage divider to be used with the brake line pressure sensor

#### Necessary Plugs

| | 1- Pin |  2- Pin | 3-Pin |
| --- | --- | --- | --- |
| | 5V in | CAN Line| I2C Breakout |
| | Throttle Pot 1 | Right Damper Pot | - |
| | Throttle Pot 2 | Left Damper Pot | - |
| | Dash Switch | Brake Line Pressure | - |
| Totals| 4 | 4 | 1 |

### Teensy 3 & 4 - Dashboard and ECU

#### Output Pins

- 3.3V Output
  - Is only needed to power the switches, a bullet connector should be sufficient
- 5V in
  - Single pin plug required
  - Will need to be spliced to the screen
- Ground pin
  - No plug necessary, gets bolted straight to chassis
- SDA & SCL
  - Along with 5V, goes to 7 segment display
- Pins 14-19
  - Pins to control RGBs
- Need to add output digital pin for the horn

#### Necessary Plugs

| | 1- Pin |  2- Pin | 3-Pin |
| --- | --- | --- | --- |
| | 5V in | CAN Line | Screen |
| | - | - | RGB LED 1 |
| | - | - | RGB LED 1 |
| Totals| 1 | 1 | 3 |
