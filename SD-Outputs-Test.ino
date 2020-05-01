// LED + Button Test
// Author: Néstor Daza - nestor@extensa.io
// http://gosocialdistancer.com/

// Outputs
const int greenLedPin = 2; // inverted logic
const int yellowLedPin = 16;
const int redLedPin = 4;
const int vibrationPin = 15;
const int piezoPin = 5;
const int stayOnPin = 14;

// Inputs
const int buttonPin = 12; // 12
int reading;
int previous = LOW;

// Debounce
unsigned long lastDebounce = 0;
unsigned long debounceDelay = 20;

const int analogWriteFrequency = 100;
const int maxAnalogDutyCycle = 512;

byte activeOutput = -1;

void setup() {

    pinMode(redLedPin, OUTPUT);
    pinMode(yellowLedPin, OUTPUT);
    pinMode(greenLedPin, OUTPUT);
    pinMode(vibrationPin, OUTPUT);
    pinMode(piezoPin, OUTPUT);

    pinMode(stayOnPin, OUTPUT);
    digitalWrite(stayOnPin, HIGH);

    pinMode(buttonPin, INPUT_PULLUP);

    analogWriteFreq(analogWriteFrequency); //should give 1Khz

    Serial.begin(115200);

    ClearFeedback();
}

void loop() {
    unsigned long currentMillis = millis();

    reading = digitalRead(buttonPin);

    if (reading != previous) {
        lastDebounce = millis();
    }

    if ((currentMillis - lastDebounce) > debounceDelay) {
        if (reading == HIGH && previous == LOW) {
            previous = HIGH;
            ClearFeedback();
            CheckButton();
        }
        else if (reading == LOW && previous == HIGH) {
            previous = LOW;
        }
    }
}

void ClearFeedback() {
    analogWrite(redLedPin, 0);
    analogWrite(yellowLedPin, 0);
    analogWrite(greenLedPin, 1023); // inverted logic GPIO02

    analogWrite(piezoPin, 0);

    digitalWrite(vibrationPin, LOW);
}

void CheckButton() {
    activeOutput++;
    Serial.printf("output: %d\n", activeOutput);
    switch(activeOutput) {
        case 1:
            analogWrite(greenLedPin, maxAnalogDutyCycle);
            break;
        case 2:
            analogWrite(yellowLedPin, maxAnalogDutyCycle);
            break;
        case 3:
            analogWrite(redLedPin, maxAnalogDutyCycle);
            break;
        case 4:
            analogWrite(piezoPin, 1000);
            break;
        case 5:
            digitalWrite(vibrationPin, HIGH);
            break;
        default:
            activeOutput = 0;
            break;
    }
}
