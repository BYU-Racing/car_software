# BYU Racing #
### UML Diagram ###
by David Reinhardt and Dallin Stewart

|Revision History|             |                      |              |
|   :---   |       :---        |         :---         |     :---     |
| Revision |    Revised By     |    Checked By        |     Date     |
|    1.0   |  David Reinhardt  |   Dallin Stewart     | 19 SEPT 2023 |
|    1.1   |  Dallin Stewart   |   TBD                | 25 SEPT 2023 |

```mermaid
classDiagram

    class Sensor
    Sensor : -int[] inputPins
    Sensor : -int readFrequency
    Sensor : -int previousUpdateTime
    Sensor : -enum sensorID 
    Sensor : -int priority
    Sensor : int readInputs()
    Sensor : bool readyToCheck()
    UARTSensor --|> Sensor : Is
    note for UARTSensor "GPS\nAccelerometer"
    AnalogSensor --|> Sensor : Is
    note for AnalogSensor "Damper Pots\nThrottle Position\nWheel Speed\nWheatstone Bridges\nBrake Pressure\nCoolant Temp"
    DigitalSensor --|> Sensor : Is
    note for DigitalSensor "Buttons\nSwitches\nKey"

    class Actuator
    Actuator : -int[] outputPins
    Actuator : -int value
    Actuator : -void writeToDisplay()
    Actuator : +void updateValue(SensorData)
    Screen --|> Actuator : Is
    note for Screen "Time\nLap number"
    LEDArray --|> Actuator : Is
    note for LEDArray "Battery Temperature\mBattery Draw\nBattery Life"
    Servo --|> Actuator : Is
    note for Servo "Speed"
    Horn --|> Actuator : Is
    note for Horn "Horn"

    class SensorData
    SensorData : -int id
    SensorData : -int priority
    SensorData : -double data
    SensorData : -int timeStamp
    SensorData : +int[] formatCAN()
    SensorData : SensorData(CANMessage)

    class Dashboard
    Dashboard : -Actuator[] display
    Dashboard : -int timeZero
    Dashboard : void readCANBus()
    Dashboard : void updateDisplay()

    class DataCollector
    DataCollector : -Sensor[] sensors
    DataCollector : -int timeZero
    DataCollector : +void checkSensors()
    DataCollector : -void sendSignals
    DataCollector : -SensorData createSensorData()

    class Car
    Car : -bool active
    Car : -bool key
    Car : -bool pushToStart
    Car : -file fileName
    Car : -int throttlePosition
    Car : -int timeZero
    Car : +void logData(SensorData)
    Car : +void updateState()
    Car : +void shutdown()
    Car : +void emergencyShutdown()
    Car : +void updateMotor()
    Car : +bool checkActive()
    Car : +void readSensors()

    DataCollector --> Car : CAN
    DataCollector --> Dashboard : CAN

    Car ..> SensorData : Uses
    DataCollector ..> SensorData : Uses
    Dashboard ..> SensorData : Uses

    Sensor *-- DataCollector : Has
    Actuator *-- Dashboard : Has
```