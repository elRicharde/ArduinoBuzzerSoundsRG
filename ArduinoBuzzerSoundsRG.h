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

		// Definition of SoundTypes
		enum class SoundType {
			DbReadError,
			NoAuth,
			AuthOk,
			SOS,
			SMS,
			OK
		};

		// Constructor
		explicit BuzzerSoundsRgBase(int buzzerPin);

		// virtual destructor
		virtual ~BuzzerSoundsRgBase();

		// method to play a sound based on enum type
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
		// attributes
		int _buzzerPin;

		// methods
		void dit();
		void dah();

		void db_read_error_sound();
		void no_auth_sound();
		void auth_ok_sound();
		void sos_sound();
		void sms_sound();
		void ok_sound();
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
