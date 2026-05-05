#include "clock.h"

#include <stdio.h>
#include <string.h>

namespace {

constexpr uint8_t kMonthNames = 12;
constexpr char kBuildMonths[kMonthNames][4] = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

}  // namespace

bool ClockService::begin() {
  if (!initializeFromBuildTime()) {
    snapshot_ = ClockSnapshot{};
    snapshot_.year = 2026;
    snapshot_.month = 1;
    snapshot_.day = 1;
    snapshot_.valid = true;
    snapshot_.synchronized = false;
  }

  snapshot_.synchronized = false;
  lastTickMs_ = millis();
  initialized_ = true;
  return true;
}

bool ClockService::update() {
  if (!initialized_) {
    return false;
  }

  const uint32_t nowMs = millis();
  const uint32_t elapsedMs = nowMs - lastTickMs_;
  if (elapsedMs < 1000U) {
    return false;
  }

  uint32_t elapsedSeconds = elapsedMs / 1000U;
  lastTickMs_ += elapsedSeconds * 1000U;

  while (elapsedSeconds-- > 0U) {
    advanceOneSecond();
  }

  return true;
}

const ClockSnapshot& ClockService::snapshot() const {
  return snapshot_;
}

bool ClockService::setDateTime(uint16_t year, uint8_t month, uint8_t day,
                               uint8_t hour, uint8_t minute, uint8_t second) {
  if (!validateDateTime(year, month, day, hour, minute, second)) {
    return false;
  }

  snapshot_.year = year;
  snapshot_.month = month;
  snapshot_.day = day;
  snapshot_.hour = hour;
  snapshot_.minute = minute;
  snapshot_.second = second;
  snapshot_.valid = true;
  snapshot_.synchronized = true;
  lastTickMs_ = millis();
  return true;
}

bool ClockService::initializeFromBuildTime() {
  char monthText[4] = {};
  int day = 0;
  int year = 0;
  if (sscanf(__DATE__, "%3s %d %d", monthText, &day, &year) != 3) {
    return false;
  }

  int month = 0;
  for (int index = 0; index < kMonthNames; ++index) {
    if (strcmp(monthText, kBuildMonths[index]) == 0) {
      month = index + 1;
      break;
    }
  }

  int hour = 0;
  int minute = 0;
  int second = 0;
  if (month == 0 || sscanf(__TIME__, "%d:%d:%d", &hour, &minute, &second) != 3) {
    return false;
  }

  return setDateTime(static_cast<uint16_t>(year),
                     static_cast<uint8_t>(month),
                     static_cast<uint8_t>(day),
                     static_cast<uint8_t>(hour),
                     static_cast<uint8_t>(minute),
                     static_cast<uint8_t>(second));
}

void ClockService::advanceOneSecond() {
  if (!snapshot_.valid) {
    return;
  }

  ++snapshot_.second;
  if (snapshot_.second < 60U) {
    return;
  }

  snapshot_.second = 0;
  ++snapshot_.minute;
  if (snapshot_.minute < 60U) {
    return;
  }

  snapshot_.minute = 0;
  ++snapshot_.hour;
  if (snapshot_.hour < 24U) {
    return;
  }

  snapshot_.hour = 0;
  ++snapshot_.day;
  if (snapshot_.day <= daysInMonth(snapshot_.year, snapshot_.month)) {
    return;
  }

  snapshot_.day = 1;
  ++snapshot_.month;
  if (snapshot_.month <= 12U) {
    return;
  }

  snapshot_.month = 1;
  ++snapshot_.year;
}

bool ClockService::validateDateTime(uint16_t year, uint8_t month, uint8_t day,
                                    uint8_t hour, uint8_t minute, uint8_t second) const {
  return year >= 2000U && month >= 1U && month <= 12U &&
         day >= 1U && day <= daysInMonth(year, month) &&
         hour <= 23U && minute <= 59U && second <= 59U;
}

uint8_t ClockService::daysInMonth(uint16_t year, uint8_t month) const {
  static constexpr uint8_t kDaysPerMonth[12] = {
      31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  if (month == 2U) {
    const bool leapYear = ((year % 4U) == 0U && (year % 100U) != 0U) || ((year % 400U) == 0U);
    return leapYear ? 29U : 28U;
  }

  return kDaysPerMonth[month - 1U];
}
