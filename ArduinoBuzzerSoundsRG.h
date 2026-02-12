#ifndef ARDUINO_BUZZER_SOUNDS_RG_H
#define ARDUINO_BUZZER_SOUNDS_RG_H

#include <Arduino.h> // will not hurt, as it contains guards against multiple definition


/* ###############  BuzzerSoundsRgBase ############### */
class BuzzerSoundsRgBase {  // Class Declaration
	public:

		// Definition of Morse Code timings and sound-types
		enum class MorseCodeTiming {
			// International Morse code is composed of five elements:
			//   short mark, dot or dit ( . ): "dit duration" is one time unit long
			//   long mark, dash or dah ( _ ): three time units long
			//   inter-element gap between the dits and dahs within a character: one dot duration or one unit long
			//   short gap (between letters): three time units long
			//   medium gap (between words): seven time units long

			DitLength = 100,     // short signal
			DitPause = 100,      // break between signals/signs
			DahLength = 300,     // long signal = Dah = 3xDit
			DahPause = 300,      // break between characters in a word
			WordPause = 700      // break between words
		};

		// Preset sound patterns.
		// Each sound uses Morse code elements (dit/dah) to create distinct, recognizable patterns.
		enum class SoundType {
			DbReadError,  // Morse "U" (..-) — short alert for data/read errors
			NoAuth,       // Custom (.....-) — insistent rapid beeps + long tone for access denied
			AuthOk,       // Morse "A" (.-) — short confirmation beep for successful authentication
			SOS,          // Morse "SOS" (...---...) — universal distress signal for critical errors
			SMS,          // Morse "SMS" (...--...) — classic notification pattern for incoming messages
			OK            // Morse "OK" (-----.-) — acknowledgment pattern for successful operations
		};

		// Constructor — initializes the buzzer pin as OUTPUT
		explicit BuzzerSoundsRgBase(int buzzerPin);

		// Virtual destructor — ensures buzzer pin is set LOW on destruction
		virtual ~BuzzerSoundsRgBase();

		// Plays a preset sound pattern selected by SoundType enum
		void playSound(SoundType sound);

	protected:
		// methods
		virtual void pause(BuzzerSoundsRgBase::MorseCodeTiming pause) = 0; // Pure virtual method
		// This abstract method needs to be redefined depending on the usage with or without RTOS:
		//
		// For RTOS, derive in your specific program to avoid dependency on RTOS in the library:
		//
		//   class BuzzerSoundsRgRtos : public BuzzerSoundsRgBase {
		//   public:
		//       explicit BuzzerSoundsRgRtos(int buzzerPin) : BuzzerSoundsRgBase(buzzerPin) {}
		//
		//       void pause(BuzzerSoundsRgBase::MorseCodeTiming pause) override {
		//           vTaskDelay(pdMS_TO_TICKS(static_cast<int>(pause))); // RTOS delay
		//       }
		//   };

	private:
		int _buzzerPin;  // Digital output pin connected to the buzzer

		// Morse code building blocks
		void dit();  // Short beep (1 time unit)
		void dah();  // Long beep (3 time units)

		// Preset sound implementations
		void db_read_error_sound();  // ..-   (Morse U)
		void no_auth_sound();        // .....-(Custom)
		void auth_ok_sound();        // .-    (Morse A)
		void sos_sound();            // ...---... (Morse SOS)
		void sms_sound();            // ...--...  (Morse SMS)
		void ok_sound();             // -----.-   (Morse OK)
};

/* ###############  BuzzerSoundsRgRtos ############### */
// Should be derived in specific programs to avoid dependency on RTOS in the library.
// See comment in base class for an example implementation.

/* ###############  BuzzerSoundsRgNonRtos ############### */
class BuzzerSoundsRgNonRtos : public BuzzerSoundsRgBase {
	public:
		// derived class constructor calls base class constructor
		explicit BuzzerSoundsRgNonRtos(int buzzerPin) : BuzzerSoundsRgBase(buzzerPin) {}

	protected:
		// redefine abstract method into concrete implementation for use without RTOS
		void pause(BuzzerSoundsRgBase::MorseCodeTiming pause) override; // Standard Arduino delay
};

#endif // ARDUINO_BUZZER_SOUNDS_RG_H
