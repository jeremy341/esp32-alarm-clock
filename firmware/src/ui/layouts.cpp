#include "../display/display.h"

#include <string.h>

LayoutGeometry buildLayoutGeometry(const ui::ResolvedPreset& preset, int16_t screenWidth, int16_t screenHeight) {
  LayoutGeometry geometry{};

  geometry.showHeader = false;
  geometry.showBorder = false;
  geometry.hasSecondaryPanel = false;

  if (strcmp(preset.layout->id, "retro_pixel") == 0) {
    geometry.showBorder = true;
  }

  // Big time in upper middle
  geometry.clock.x = 16;
  geometry.clock.y = 30;
  geometry.clock.width = screenWidth - 32;
  geometry.clock.height = 120;

  // Secondary hidden
  geometry.secondary.x = 16;
  geometry.secondary.y = 160;
  geometry.secondary.width = screenWidth - 32;
  geometry.secondary.height = 4;

  // Date and Alarm at the bottom
  geometry.date.x = 16;
  geometry.date.y = 174;
  geometry.date.width = screenWidth - 32;
  geometry.date.height = 40;

  return geometry;
}