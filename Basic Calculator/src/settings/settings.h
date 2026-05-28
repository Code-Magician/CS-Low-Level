#ifndef SETTINGS_H
#define SETTINGS_H

typedef struct
{
    float glowIntensity;

    float particleMultiplier;

    float chromaticStrength;

    int crtEnabled;

} AppSettings;

extern AppSettings settings;

void InitializeSettings();

#endif