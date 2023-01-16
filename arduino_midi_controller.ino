/* 
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2023 Deb Brouwer
 * Computer Science 444: Embedded/ Robotic Programming
 */
#include <MIDI.h>
#include <LiquidCrystal.h>
#include "keys.h"

enum note_delay { FAST = 60, NORMAL = 120 }; //in milliseconds

/* Distance Sensor */
const int SWITCH_PIN = 2;
const int TRIGGER_PIN = 12;
const int ECHO_PIN = 13;

/* LED Screen */
const int REGISTER_SELECT = 6;
const int ENABLE = 7;
const int DATA_LINE_7 = 11;
const int DATA_LINE_6 = 10;
const int DATA_LINE_5 = 9;
const int DATA_LINE_4 = 8;

const int GREEN_BUTTON = 5;
const int BLUE_BUTTON = 4;
const int YELLOW_BUTTON = 3;

const double MAX_DISTANCE = 45; //cm
const double DISTANCE_SENSITIVITY = 1; //cm
const double VELOCITY = 62;

double distance = 0; //cm
double previous_distance = 0; //cm

int midi_note = 0;
int previous_midi_note = 0;

key current_key = AMAJOR;
int delay_between_notes = NORMAL;

MIDI_CREATE_DEFAULT_INSTANCE();
LiquidCrystal lcd(REGISTER_SELECT, ENABLE, DATA_LINE_4, DATA_LINE_5, DATA_LINE_6, DATA_LINE_7);

void print_key()
{
	lcd.setCursor(0, 0);
	switch (current_key) {
	case AMAJOR:
		lcd.print("Key: A+");
		break;
	case BMINOR:
		lcd.print("Key: B-");
		break;
	break;
	}
}

void print_delay()
{
	lcd.setCursor(10, 0);
	if (delay_between_notes == FAST)
		lcd.print("FAST  ");
	if (delay_between_notes == NORMAL)
		lcd.print("NORMAL");
}

void print_midi_note()
{
	lcd.setCursor(0, 1);
	struct midi_note_str *def = &definitions[0];
	while ((def->midi_note != -1) && (def->midi_note != midi_note))
		def++;
	if (def->midi_note == midi_note)
		lcd.print(def->str);
}

void set_key()
{
	if (digitalRead(GREEN_BUTTON) == LOW) {
		current_key = AMAJOR;
	}
	if (digitalRead(BLUE_BUTTON) == LOW) {
		current_key = BMINOR;
	}
}

void set_delay()
{
	if (digitalRead(YELLOW_BUTTON) == LOW) {
		if (delay_between_notes == FAST) {
			delay_between_notes = NORMAL;
		} else if (delay_between_notes == NORMAL) {
			delay_between_notes = FAST;
		}
		delay(200); //don't spam button
	}
}

void set_distance()
{
	/*
	 * Send out the ultrasonic pulse for 10us.
	 * Since the speed of sound in air is 343m/s or 0.343mm per us,
	 * the front edge of the the ultrasonic pulse will only have travelled 3 mm
	 * by the time it is turned off.
	 */
	digitalWrite(TRIGGER_PIN, HIGH);
	delayMicroseconds(10);
	digitalWrite(TRIGGER_PIN, LOW);

	/* High means that the counting stops when the pin goes LOW. Returns time in microseconds us. */
	double echo_time = pulseIn(ECHO_PIN, HIGH);

	distance = echo_time / 2; //take half the bounce time
	distance = distance * 0.0343; //multiply it by the number of cm travelled in 1 us
}

void convert_distance_into_midi_note()
{
	/*
	 * An interval size (cm) is calculated by dividing the physical space that could be sensed by
	 * the sensor (i.e. the MAX_DISTANCE) by the number of notes in the key array.  For example,
	 * if the MAX_DISTANCE is set to 45 cm and there are 22 notes in AMAJOR, then the interval
	 * is about 2cm. interval = MAX_DISTANCE / SIZE_AMAJOR. Each physical interval represents an
	 * index into the key array.
	 * Next, divide the current distance sensed by the interval, to figure out which index in the key
	 * array that distance represents. index = (int) (distance / interval);
	 * The midi note at that index corresponds to the physical distance sensed by the sensor.
	 */

	double interval;
	int index;
	switch (current_key) {
	case AMAJOR:
		interval = (MAX_DISTANCE / SIZE_AMAJOR);
		index = (int) (distance / interval);
		midi_note = AMAJOR_NOTES[index];
		return;
	case BMINOR:
		interval = (MAX_DISTANCE / SIZE_BMINOR);
		index = (int) (distance / interval);
		midi_note = BMINOR_NOTES[index];
		return;
	}
}

void setup()
{
	Serial.begin(31250);
	pinMode(SWITCH_PIN, INPUT_PULLUP);
	pinMode(TRIGGER_PIN, OUTPUT);
	pinMode(ECHO_PIN, INPUT);

	pinMode(GREEN_BUTTON, INPUT_PULLUP);
	pinMode(BLUE_BUTTON, INPUT_PULLUP);
	pinMode(YELLOW_BUTTON, INPUT_PULLUP);

	lcd.begin(16, 2);

	MIDI.begin(MIDI_CHANNEL_OFF);
}

void loop()
{
	/* check status of ON/OFF switch ever 200 ms */
	while (digitalRead(SWITCH_PIN) == HIGH) {
		lcd.clear();
		delay(200);
	}
	set_key();
	print_key();
	set_delay();
	print_delay();
	set_distance();

	/* Wait for an object to come within range of the distance sensor. */
	while (distance > MAX_DISTANCE) {
		set_key();
		print_key();
		set_delay();
		print_delay();
		set_distance();
		previous_distance = MAX_DISTANCE + 1;
	}

	convert_distance_into_midi_note();
	if (abs(previous_distance - distance) > DISTANCE_SENSITIVITY) {
		/* Allow for reverb by turning off the previous note only before playing the next one. */
		MIDI.sendNoteOff(previous_midi_note, 0, 1);
		delay(delay_between_notes);
		MIDI.sendNoteOn(midi_note, VELOCITY, 1);
		print_midi_note();
		previous_midi_note = midi_note;
		previous_distance = distance;
	}
}
