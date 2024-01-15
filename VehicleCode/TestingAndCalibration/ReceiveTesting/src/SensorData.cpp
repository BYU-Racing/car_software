#include "SensorData.h"
#include <Arduino.h>
#include <FlexCAN_T4.h>

FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can1;


/**
 * @brief Default constructor for SensorData class.
 * Initializes a SensorData object with default values.
 */
SensorData::SensorData() {
    id = 0;
    data = {0};
    timeStamp = 0;
    dataLength = 0;
}

/**
 * @brief Parameterized constructor for SensorData class.
 *
 * @param inId (int) The ID of the sensor data.
 * @param inData (int*) Pointer to the data array of arbitrary length.
 * @param dataLength (int) Length of the data array.
 * @param inTimeStamp (unsigned long) The timestamp of the sensor data.
 */
SensorData::SensorData(int inId, int* inData, int dataLength, unsigned long inTimeStamp) {
    id = inId;
    data = inData;
    dataLength = dataLength;
    timeStamp = inTimeStamp;
}

/**
 * @brief Constructor for SensorData class from CAN message.
 * @param canMessage (CAN_message_t) The CAN message to convert to SensorData.
 */
SensorData::SensorData(CAN_message_t canMessage) {
    id = canMessage.id;
    timeStamp = canMessage.timestamp;
    dataLength = canMessage.len;
    data = new int[dataLength];
    for (int i = 0; i < dataLength; i++) {
        data[i] = canMessage.buf[i];
    }
}

/**
 * @brief Destructor for SensorData class.
 * Deallocates memory for the data array.
 */
SensorData::~SensorData() {
    delete[] data;
}

/**
 * @brief Get the timestamp of the sensor data.
 * @return (int) The timestamp value.
 */
int SensorData::getTimeStamp() const {
    return timeStamp;
}

/**
 * @brief Get the ID of the sensor data.
 * @return (int) The ID value.
 */
int SensorData::getId() const {
    return id;
}

/**
 * @brief Get the pointer to the data array.
 * @return (int*) Pointer to the data array.
 */
int* SensorData::getData() const {
    return data;
}

/**
 * @brief Set the ID of the sensor data.
 * @param inId (int) The new ID value.
 */
void SensorData::setId(int inId) {
    id = inId;
}

/**
 * @brief Set the data array for the sensor data.
 * @param inData (int*) Pointer to the new data array.
 */
void SensorData::setData(int* inData) {
    data = inData;
}

/**
 * @brief Set the timestamp of the sensor data.
 * @param inTimeStamp (unsigned long) The new timestamp value.
 */
void SensorData::setTimeStamp(unsigned long inTimeStamp) {
    timeStamp = inTimeStamp;
}

/**
 * @brief Format SensorData as a CAN message.
 * @return (CAN_message_t) The formatted CAN message.
 */
CAN_message_t SensorData::formatCAN() const {
    CAN_message_t canMessage;
    canMessage.id = id;
    for (int i = 0; i < dataLength; i++) {
        canMessage.buf[i] = data[i];
    }
    canMessage.len = dataLength;
    canMessage.timestamp = timeStamp;
    return canMessage;
}