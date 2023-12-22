#pragma once

#include <Adafruit_Arcada.h>

class ButtonService {
private:
  uint32_t lastButtonState;
  uint32_t currentButtonState;
  Adafruit_Arcada arcada;

public:
  ButtonService() : lastButtonState(0), currentButtonState(0) {

  }

  void update() {
    // Save the last state
    lastButtonState = currentButtonState;
    // Read the new state
    currentButtonState = arcada.readButtons();
  }

  bool pressed(uint32_t buttonMask) {
    // Check if all specified buttons are pressed this frame and weren't pressed the last frame
    return (currentButtonState & buttonMask) == buttonMask && (lastButtonState & buttonMask) != buttonMask;
  }

  bool held(uint32_t buttonMask) {
    // Check if all specified buttons are pressed this frame and were also pressed the last frame
    return (currentButtonState & buttonMask) == buttonMask && (lastButtonState & buttonMask) == buttonMask;
  }

  bool released(uint32_t buttonMask) {
    // Check if all specified buttons were pressed last frame but not this frame
    return (currentButtonState & buttonMask) != buttonMask && (lastButtonState & buttonMask) == buttonMask;
  }
};

ButtonService buttons = ButtonService();