#pragma once

#include <stddef.h>

namespace alarm_clock_format {

static constexpr size_t kIdBufferSize = 24;

static constexpr char kFieldLayout[] = "layout";
static constexpr char kFieldTheme[] = "theme";
static constexpr char kFieldClockStyle[] = "clockStyle";
static constexpr char kFieldVersion[] = "version";
static constexpr char kFieldYear[] = "year";
static constexpr char kFieldMonth[] = "month";
static constexpr char kFieldDay[] = "day";
static constexpr char kFieldHour[] = "hour";
static constexpr char kFieldMinute[] = "minute";
static constexpr char kFieldSecond[] = "second";

}  // namespace alarm_clock_format
