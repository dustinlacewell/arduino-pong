#pragma once

// Function to convert a 0-1 float to a 16-bit greyscale RGB value
uint16_t floatToGreyscale16Bit(float value) {
  // Clamp the input value to the 0-1 range
  if (value < 0.0f) value = 0.0f;
  if (value > 1.0f) value = 1.0f;

  // Convert the 0-1 float to a 0-31 range integer for red and blue
  uint8_t greyValue5Bit = (uint8_t)(value * 31.0f);

  // Convert the 0-1 float to a 0-63 range integer for green
  uint8_t greyValue6Bit = (uint8_t)(value * 63.0f);

  // Combine the values into a single 16-bit RGB value
  uint16_t grey16Bit = (greyValue5Bit << 11) | (greyValue6Bit << 5) | greyValue5Bit;

  return grey16Bit;
}
