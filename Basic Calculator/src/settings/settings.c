#include "settings.h"

AppSettings settings;

void InitializeSettings()
{
    settings.glowIntensity = 1.0f;

    settings.particleMultiplier = 1.0f;

    settings.chromaticStrength = 1.0f;

    settings.crtEnabled = 1;
}