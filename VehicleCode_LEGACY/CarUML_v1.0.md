# BYU Racing

## UML Diagram

by David Reinhardt and Dallin Stewart

```mermaid
classDiagram

    class Sensor
    Sensor : -int[] inputPins
    Sensor : -int waitTime
    Sensor : -int previousUpdateTime
    Sensor : -enum sensorID
    Sensor : -int dataLength
    Sensor : int readInputs()
    Sensor : bool readyToCheck()
    Sensor : int getId()
    Sensor : int getDataLength()
    Sensor : int rescale(int data)
    Sensor : int* buildData(int value)
    Sensor : int* buildError()


    UARTSensor --|> Sensor : Is
    note for UARTSensor "GPS\nAccelerometer"
    AnalogSensor --|> Sensor : Is
    note for AnalogSensor "Damper Pots\nThrottle Position\nWheatstone Bridges\nBrake Pressure\nCoolant Temp\nThrottle Sensor"
    DigitalSensor --|> Sensor : Is
    note for DigitalSensor "Buttons\nSwitches\nKey\nWheel Speed"

    class Actuator
    Actuator : -int* outputPins
    Actuator : +void updateValue(SensorData)
    Screen --|> Actuator : Is
    Screen : displayTime()
    Screen : displayLapTime(int inSeconds, int milliseconds)
    Screen : setMatrix(Adafruit_7segment myMatrix)
    note for Screen "Run Time\nLap number\nLap Time"
    LEDArray --|> Actuator : Is
    LEDArray : displayLEDsPerc()
    LEDArray : displayLEDsTemp()
    note for LEDArray "Battery Temp\nBattery Percentage"
    Horn --|> Actuator : Is
    note for Horn "Horn"

    class SensorData
    SensorData : -int id
    SensorData : -int dataLength
    SensorData : -int* data
    SensorData : -unsigned long timeStamp
    SensorData : +CAN_message_t formatCAN()
    SensorData : SensorData(CANMessage)
    SensorData : SensorData(id, priority, data, timeStamp)
    SensorData : SensorData()
    SensorData : int getTimeStamp()
    SensorData : int getId()
    SensorData : int getPriority()
    SensorData : int* getData()
    SensorData : int length()
    SensorData : void setId(int id)
    SensorData : void setTimeStamp(unsigned long timeStamp)

    class Dashboard
    Dashboard : -Actuator** display
    Dashboard : -int numActuators
    Dashboard : -unsigned long startTime
    Dashboard : FlexCAN_T4 can1
    Dashboard : int getSensorIndex(int id)
    Dashboard : void updateDisplay()
    Dashboard : void setCAN(FlexCAN_T4 canIN)
    Dashboard : void resetTimeZero(unsigned long startTime)


    class DataCollector
    DataCollector : -Sensor** sensors
    DataCollector : -int numSensors
    DataCollector : -unsigned long timeZero
    DataCollector : -FlexCAN_T4 can2
    DataCollector : +void checkSensors()
    DataCollector : -void sendSignal(SensorData*)
    DataCollector : -void readData(Sensor*)
    DataCollector : -void resetTimeZero(unsigned long startTime)
    DataCollector : -void setCAN(FlexCAN_T4 can2)

    class Car
    Car : -bool active
    Car : -bool key
    Car : -bool switchOn
    Car : -bool logState
    Car : -string fileName
    Car : -File dataFile
    Car : -FlexCAN_T4 can2
    Car : -int timeZero
    Car : -int throttlePosition
    Car : -int timeZero
    Car : -int saveDelay
    Car : -int buttonState
    Car : -int prevButtonState
    Car : -int scale
    Car : -int startThreshold
    Car : -int byteValue
    Car : -int maxNameLength
    Car : -unsigned long lastSave
    Car : void logData(SensorData*)
    Car : String updateFileName()
    Car : int getMaxNumber()
    Car : void writeNumber(int&)
    Car : String assembleName(int&)
    Car : int tempLength(int&)
    Car : void saveSD()
    Car : void startSD()
    Car : void writeHeader()
    Car : void shutdown()
    Car : void updateState()
    Car : void checkKey()
    Car : void checkButton()
    Car : void checkSwitch()
    Car : void checkToLog()
    Car : void buttonPushed()

    DataCollector <--> Car : CAN
    DataCollector <--> Dashboard : CAN

    Car ..> SensorData : Uses
    DataCollector ..> SensorData : Uses
    Dashboard ..> SensorData : Uses

    Sensor *-- DataCollector : Has
    Actuator *-- Dashboard : Has
```

| Revision History |                 |                 |              |
| :--------------- | :-------------- | :-------------- | :----------- |
| Revision         | Revised By      | Checked By      | Date         |
| 1.0              | David Reinhardt | Dallin Stewart  | 19 SEPT 2023 |
| 1.1              | Dallin Stewart  | David Reinhardt | 25 SEPT 2023 |
| 1.2              | Dallin Stewart  | David Reinhardt | 02 OCT 2023  |
| 1.3              | Dallin Stewart  | David Reinhardt | 17 OCT 2023  |
| 1.4              | Coleman Hardy   | David Reinhardt | 31 MAR 2024  |
