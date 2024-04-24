#include "Horn.h"


/**
 * @brief Default constructor for Horn class
*/
Horn::Horn() {
  hornState = false;
}

/**
 * @brief Constructor for Horn class
 * @param outPin (const int) The pin used for sending sound signal to horn mosfet.
*/
Horn::Horn(const int outPin) {
  hornState = false;
  SOUNDPIN = outPin;
}

/**
 * @brief Destructor for Horn object
*/
Horn::~Horn() {
  hornState = NULL;
}

/**
 * @brief DO NOT USE!! This function is required because Horn.h is a child of the Actuator.h 
 * virtual class but will not be useful for this object.
 *    if used: will return nothing
*/
void Horn::updateValue(const SensorData& data) {
  return;
}

/**
 * @brief Turn ON horn/Ready to Drive Sound
*/
void Horn::Honk() {
  digitalWrite(SOUNDPIN, HIGH);
  hornState = true;
}

/**
 * @brief Turn OFF horn/Ready to Drive Sound
*/
void Horn::hornOFF() {
  digitalWrite(SOUNDPIN,LOW);
  hornState = false;
}

/**
 * @brief Get Horn/Ready to Drive Sound State
 *    True = Horn is ON
 *    False = Horn is Off
*/
void Horn::getHornState() {
  return hornState;
}
