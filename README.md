# ArduinoBuzzerSoundsRG

An Arduino library for creating recognizable sound patterns through a digital output connected to a simple buzzer. All patterns are based on Morse code timing for distinct, universally recognizable signals.

## Features

- 6 preset sound patterns for common application events
- Based on international Morse code timing standards
- Supports both standard Arduino and RTOS (FreeRTOS) environments
- Clean OOP design with abstract base class for easy platform adaptation

## Hardware Setup

Connect a passive buzzer between a digital pin and GND:

```
Arduino Pin (e.g. D4) ---[Buzzer]--- GND
```

## Installation

1. Download or clone this repository
2. Copy the folder into your Arduino `libraries/` directory
3. Restart the Arduino IDE
4. Include the library: `#include <ArduinoBuzzerSoundsRG.h>`

## Quick Start

```cpp
#include <ArduinoBuzzerSoundsRG.h>

BuzzerSoundsRgNonRtos buzzer(4); // Buzzer on pin 4

void setup() {
    buzzer.playSound(BuzzerSoundsRgBase::SoundType::OK);
}

void loop() {}
```

## Preset Sound Patterns

| SoundType     | Morse Pattern    | Sound            | Recommended Use Case                          |
|---------------|------------------|------------------|-----------------------------------------------|
| `DbReadError` | `U` (..-  )      | dit-dit-dah      | Data/read errors — noticeable but not alarming |
| `NoAuth`      | Custom (.....- ) | 5x dit + dah     | Access denied — insistent rapid beeping        |
| `AuthOk`      | `A` (.- )        | dit-dah          | Authentication successful — quick confirmation |
| `SOS`         | `SOS` (...---...)| dit-dit-dit dah-dah-dah dit-dit-dit | Critical errors / emergencies |
| `SMS`         | `SMS` (...--...) | dit-dit-dit dah-dah dit-dit-dit     | Notifications / incoming messages |
| `OK`          | `OK` (-----.- )  | dah-dah-dah dah-dit-dah             | Successful operation / system ready |

## Morse Code Timing

All timings follow the international Morse code standard with a base unit of 100ms:

| Timing      | Duration | Description                              |
|-------------|----------|------------------------------------------|
| `DitLength` | 100ms    | Short signal (1 unit)                    |
| `DahLength` | 300ms    | Long signal (3 units)                    |
| `DitPause`  | 100ms    | Pause between elements within a letter   |
| `DahPause`  | 300ms    | Pause between letters                    |
| `WordPause` | 700ms    | Pause between words (available for custom use) |

## API Reference

### Classes

**`BuzzerSoundsRgBase`** — Abstract base class. Cannot be instantiated directly.

- `BuzzerSoundsRgBase(int buzzerPin)` — Constructor, sets the pin as OUTPUT.
- `~BuzzerSoundsRgBase()` — Virtual destructor, sets pin LOW.
- `void playSound(SoundType sound)` — Plays one of the preset sound patterns.

**`BuzzerSoundsRgNonRtos`** — Concrete implementation for standard Arduino (uses `delay()`).

- `BuzzerSoundsRgNonRtos(int buzzerPin)` — Constructor.

### Enums

- `BuzzerSoundsRgBase::SoundType` — Selects the sound pattern (see table above).
- `BuzzerSoundsRgBase::MorseCodeTiming` — Timing constants for Morse code elements.

## RTOS Usage

The library avoids any RTOS dependency. To use it with FreeRTOS, derive your own class and override the `pause()` method:

```cpp
#include <ArduinoBuzzerSoundsRG.h>

class BuzzerSoundsRgRtos : public BuzzerSoundsRgBase {
public:
    explicit BuzzerSoundsRgRtos(int buzzerPin) : BuzzerSoundsRgBase(buzzerPin) {}

protected:
    void pause(BuzzerSoundsRgBase::MorseCodeTiming pause) override {
        vTaskDelay(pdMS_TO_TICKS(static_cast<int>(pause)));
    }
};
```

## License

MIT License — see [LICENSE](LICENSE) for details.
