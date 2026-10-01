# CyberPocket 6-Button Keypad

An ultra-portable, wireless 6-button chorded keypad and touch-navigation controller designed for mobile devices. Built as a hardware engineering project for Hack Club Half-Life.

## Project Layout & Chord Design Master Plan
![CyberPocket Written Plan](./20261001_190915.jpg)

## How It Works
The device features a compact 3x2 grid of mechanical keys. It uses a custom chorded firmware layout so that users can tap specific combinations of buttons simultaneously to output all 26 letters of the English alphabet, system commands, and spacebar actions without a bulky physical layout.

# 6-Button Mobile Chording Macropad

## Hour 1
- Created repository and mapped out full key chord layout on paper.

## Hour 2
- Implemented complete C++ firmware using `BleCombo` library.
- Mapped all single keypresses (A–F), double chords (G–S), triple chords (T–Z), navigation/mouse controls, and automation shortcuts.
- Verified input detection logic using Wokwi ESP32 simulator.
