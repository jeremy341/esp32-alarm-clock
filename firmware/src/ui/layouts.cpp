#include "../display/display.h"

#include <string.h>

LayoutGeometry buildLayoutGeometry(const ui::ResolvedPreset& preset, int16_t screenWidth, int16_t screenHeight) {
  LayoutGeometry geometry{};

  if (strcmp(preset.layout->id, "minimal") == 0) {
    geometry.clock.x = 24;
    geometry.clock.y = 54;
    geometry.clock.width = screenWidth - 48;
    geometry.clock.height = 90;

    geometry.secondary.x = 40;
    geometry.secondary.y = 152;
    geometry.secondary.width = screenWidth - 80;
    geometry.secondary.height = 20;

    geometry.date.x = 36;
    geometry.date.y = 182;
    geometry.date.width = screenWidth - 72;
    geometry.date.height = 32;

    return geometry;
  }

  if (strcmp(preset.layout->id, "retro_pixel") == 0) {
    geometry.showHeader = true;
    geometry.showBorder = true;

    geometry.header.x = 26;
    geometry.header.y = 22;
    geometry.header.width = screenWidth - 52;
    geometry.header.height = 28;

    geometry.clock.x = 28;
    geometry.clock.y = 70;
    geometry.clock.width = screenWidth - 56;
    geometry.clock.height = 74;

    geometry.secondary.x = 28;
    geometry.secondary.y = 154;
    geometry.secondary.width = screenWidth - 56;
    geometry.secondary.height = 20;

    geometry.date.x = 28;
    geometry.date.y = 184;
    geometry.date.width = screenWidth - 56;
    geometry.date.height = 28;

    return geometry;
  }

  geometry.showHeader = true;
  geometry.hasSecondaryPanel = true;

  geometry.header.x = 20;
  geometry.header.y = 18;
  geometry.header.width = screenWidth - 40;
  geometry.header.height = 28;

  geometry.clock.x = 20;
  geometry.clock.y = 64;
  geometry.clock.width = 190;
  geometry.clock.height = 98;

  geometry.secondary.x = 220;
  geometry.secondary.y = 64;
  geometry.secondary.width = 80;
  geometry.secondary.height = 98;

  geometry.date.x = 20;
  geometry.date.y = 180;
  geometry.date.width = screenWidth - 40;
  geometry.date.height = 32;

  return geometry;
}