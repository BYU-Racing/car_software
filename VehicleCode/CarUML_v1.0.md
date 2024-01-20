# BYU Racing #
### UML Diagram ###
by David Reinhardt and Dallin Stewart

|Revision History|             |                      |              |
|   :---   |       :---        |         :---         |     :---     |
| Revision |    Revised By     |    Checked By        |     Date     |
|    1.0   |  David Reinhardt  |   Dallin Stewart     | 19 SEPT 2023 |
|    1.1   |  Dallin Stewart   |   David Reinhardt    | 25 SEPT 2023 |
|    1.2   |  Dallin Stewart   |   TBD                | 02 OCT  2023 |
|    1.3   |  Dallin Stewart   |   TBD                | 17 OCT  2023 |
|    1.4   |  Dallin Stewart   |   TBD                | 20 JAN  2024 |

```mermaid
classDiagram

    class Sensor
    Sensor : -int[] inputPins
    Sensor : -int waitTime
    Sensor : -int previousUpdateTime
    Sensor : -enum sensorID 
    Sensor : -int priority
    Sensor : int[] readInputs()
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
    note for LEDArray "Battery Temp\mBattery Draw\nBattery Life"
    Horn --|> Actuator : Is
    note for Horn "Horn"

    class SensorData
    SensorData : -int id
    SensorData : -int priority
    SensorData : -int data
    SensorData : -unsigned long timeStamp
    SensorData : +CAN_message_t formatCAN()
    SensorData : SensorData(CANMessage)
    SensorData : SensorData(id, priority, data, timeStamp)
    SensorData : SensorData()

    class Error
    Error : -string sensorName
    Error : -int errorType
    Error : -string errorMessage
    Error : -bool shutDown
    Error --|> SensorData : Is

    class Dashboard
    Dashboard : -Actuator[] display
    Dashboard : -int timeZero
    Dashboard : void readCANBus()
    Dashboard : void updateDisplay()

    class DataCollector
    DataCollector : -Sensor[] sensors
    DataCollector : -int numSensors
    DataCollector : -unsigned long timeZero
    DataCollector : +void checkSensors()
    DataCollector : -void sendSignal(SensorData*)
    DataCollector : -void readData(Sensor*)

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
