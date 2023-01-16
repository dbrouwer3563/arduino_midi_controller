#ifndef KEYS_H
#define KEYS_H

enum key { NONE, AMAJOR, BMINOR };

//midi notes
#define A0	21
#define AS0	22
#define B0	23
#define C1	24
#define CS1	25
#define D1	26
#define DS1	27
#define E1	28
#define F1	29
#define FS1	30
#define G1	31
#define GS1	32
#define A1	33
#define AS1	34
#define B1	35
#define C2	36
#define CS2	37
#define D2	38
#define DS2	39
#define E2	40
#define F2	41
#define FS2	42
#define G2	43
#define GS2	44
#define A2	45
#define AS2	46
#define B2	47
#define C3	48
#define CS3	49
#define D3	50
#define DS3	51
#define E3	52
#define F3	53
#define FS3	54
#define G3	55
#define GS3	56
#define A3	57
#define AS3	58
#define B3	59
#define C4	60
#define CS4	61
#define D4	62
#define DS4	63
#define E4	64
#define F4	65
#define FS4	66
#define G4	67
#define GS4	68
#define A4	69
#define AS4	70
#define B4	71
#define C5	72
#define CS5	73
#define D5	74
#define DS5	75
#define E5	76
#define F5	77
#define FS5	78
#define G5	79
#define GS5	80
#define A5	81
#define AS5	82
#define B5	83
#define C6	84
#define CS6	85
#define D6	86
#define DS6	87
#define E6	88
#define F6	89
#define FS6	90
#define G6	91
#define GS6	92
#define A6	93
#define AS6	94
#define B6	95
#define C7	96
#define CS7	97
#define D7	98
#define DS7	99
#define E7	100
#define F7	101
#define FS7	102
#define G7	103
#define GS7	104
#define A7	105
#define AS7	106
#define B7	107
#define C8	108

const int AMAJOR_NOTES[] = { A0, CS1, E1, A1, CS2, E2, A2, CS3, E3, A3, CS4, E4, A4, CS5, E5, A5, CS6, E6, A6, CS7, E7, A7 };
const int BMINOR_NOTES[] = { B0, D1, FS1, B1, D2, FS2, B2, D3, FS3, B3, D4, FS4, B4, D5, FS5, B5, D6, FS6, B6, D7, FS7, B7 };

const int SIZE_AMAJOR = sizeof(AMAJOR_NOTES)/sizeof(int);
const int SIZE_BMINOR = sizeof(BMINOR_NOTES)/sizeof(int);

struct midi_note_str {
	int midi_note;
	const char *str;
};

midi_note_str definitions[] = {
	{ A0, "A  0" },
	{ AS0, "A# 0" },
	{ B0, "B  0" },
	{ C1, "C  1" },
	{ CS1, "C# 1" },
	{ D1, "D  1" },
	{ DS1, "D# 1" },
	{ E1, "E  1" },
	{ F1, "F  1" },
	{ FS1, "F# 1" },
	{ G1, "G  1" },
	{ GS1, "G# 1" },
	{ A1, "A  1" },
	{ AS1, "A# 1" },
	{ B1, "B  1" },
	{ C2, "C  2" },
	{ CS2, "C# 2" },
	{ D2, "D  2" },
	{ DS2, "D# 2" },
	{ E2, "E  2" },
	{ F2, "F  2" },
	{ FS2, "F# 2" },
	{ G2, "G  2" },
	{ GS2, "G# 2" },
	{ A2, "A  2" },
	{ AS2, "A# 2" },
	{ B2, "B  2" },
	{ C3, "C  3" },
	{ CS3, "C# 3" },
	{ D3, "D  3" },
	{ DS3, "D# 3" },
	{ E3, "E  3" },
	{ F3, "F  3" },
	{ FS3, "F# 3" },
	{ G3, "G  3" },
	{ GS3, "G# 3" },
	{ A3, "A  3" },
	{ AS3, "A# 3" },
	{ B3, "B  3" },
	{ C4, "C  4" },
	{ CS4, "C# 4" },
	{ D4, "D  4" },
	{ DS4, "D# 4" },
	{ E4, "E  4" },
	{ F4, "F  4" },
	{ FS4, "F# 4" },
	{ G4, "G  4" },
	{ GS4, "G# 4" },
	{ A4, "A  4" },
	{ AS4, "A# 4" },
	{ B4, "B  4" },
	{ C5, "C  5" },
	{ CS5, "C# 5" },
	{ D5, "D  5" },
	{ DS5, "D# 5" },
	{ E5, "E  5" },
	{ F5, "F  5" },
	{ FS5, "F# 5" },
	{ G5, "G  5" },
	{ GS5, "G# 5" },
	{ A5, "A  5" },
	{ AS5, "A# 5" },
	{ B5, "B  5" },
	{ C6, "C  6" },
	{ CS6, "C# 6" },
	{ D6, "D  6" },
	{ DS6, "D# 6" },
	{ E6, "E  6" },
	{ F6, "F  6" },
	{ FS6, "F# 6" },
	{ G6, "G  6" },
	{ GS6, "G# 6" },
	{ A6, "A  6" },
	{ AS6, "A# 6" },
	{ B6, "B  6" },
	{ C7, "C  7" },
	{ CS7, "C# 7" },
	{ D7, "D  7" },
	{ DS7, "D# 7" },
	{ E7, "E  7" },
	{ F7, "F  7" },
	{ FS7, "F# 7" },
	{ G7, "G  7" },
	{ GS7, "G# 7" },
	{ A7, "A  7" },
	{ AS7, "A# 7" },
	{ B7, "B  7" },
	{ C8, "C  8" },
	{ -1, "" }
};

#endif
