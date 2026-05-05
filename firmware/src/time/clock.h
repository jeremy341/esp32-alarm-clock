#pragma once

#include <Arduino.h>

struct ClockSnapshot {
  uint16_t year = 0;
  uint8_t month = 0;
  uint8_t day = 0;
  uint8_t hour = 0;
  uint8_t minute = 0;
  uint8_t second = 0;
  bool valid = false;
  bool synchronized = false;
};

class ClockService {
public:
  bool begin();
  bool update();
  const ClockSnapshot& snapshot() const;
  bool setDateTime(uint16_t year, uint8_t month, uint8_t day,
                   uint8_t hour, uint8_t minute, uint8_t second);

private:
  bool initializeFromBuildTime();
  void advanceOneSecond();
  bool validateDateTime(uint16_t year, uint8_t month, uint8_t day,
                        uint8_t hour, uint8_t minute, uint8_t second) const;
  uint8_t daysInMonth(uint16_t year, uint8_t month) const;

  ClockSnapshot snapshot_;
  bool initialized_ = false;
  uint32_t lastTickMs_ = 0;
};
