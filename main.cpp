#include <BleCombo.h> // Bluetooth Keyboard + Mouse Library

// Button GPIO Pins (Matches ESP32 default wiring)
const int BTN1 = 13;
const int BTN2 = 12;
const int BTN3 = 14;
const int BTN4 = 27;
const int BTN5 = 26;
const int BTN6 = 25;

const int BUTTON_PINS[6] = {BTN1, BTN2, BTN3, BTN4, BTN5, BTN6};
const int CHORD_DELAY = 40; // 40ms window to register multi-key chords
bool mouseMode = false;     // Toggles between Typing and Cursor mode

void setup() {
  Serial.begin(115200);

  // Set pins as input with internal pull-up resistors
  for (int i = 0; i < 6; i++) {
    pinMode(BUTTON_PINS[i], INPUT_PULLUP);
  }

  // Start Bluetooth Services
  Keyboard.begin();
  Mouse.begin();
}

void loop() {
  // Wait until paired with phone/PC
  if (!Keyboard.isConnected()) return;

  // Read button states (LOW = Pressed)
  bool k1 = (digitalRead(BTN1) == LOW);
  bool k2 = (digitalRead(BTN2) == LOW);
  bool k3 = (digitalRead(BTN3) == LOW);
  bool k4 = (digitalRead(BTN4) == LOW);
  bool k5 = (digitalRead(BTN5) == LOW);
  bool k6 = (digitalRead(BTN6) == LOW);

  // Check if any button is pressed
  if (k1 || k2 || k3 || k4 || k5 || k6) {
    
    // Wait brief window to capture all fingers in a chord
    delay(CHORD_DELAY);

    // Re-read keys to confirm full active chord
    k1 = (digitalRead(BTN1) == LOW);
    k2 = (digitalRead(BTN2) == LOW);
    k3 = (digitalRead(BTN3) == LOW);
    k4 = (digitalRead(BTN4) == LOW);
    k5 = (digitalRead(BTN5) == LOW);
    k6 = (digitalRead(BTN6) == LOW);

    // --- MODE TOGGLE: Hold 1 + 3 ---
    if (k1 && k3 && !k2 && !k4 && !k5 && !k6) {
      mouseMode = !mouseMode; 
      delay(300); // Prevent accidental rapid toggling
    }
    
    // --- MOUSE MODE CONTROLS ---
    else if (mouseMode) {
      if (k1 && !k2 && !k3 && !k4 && !k5 && !k6) Mouse.move(0, -10); // Button 1: Up
      if (k2 && !k1 && !k3 && !k4 && !k5 && !k6) Mouse.move(0, 10);  // Button 2: Down
      if (k4 && !k1 && !k2 && !k3 && !k5 && !k6) Mouse.move(-10, 0); // Button 4: Left
      if (k5 && !k1 && !k2 && !k3 && !k4 && !k6) Mouse.move(10, 0);  // Button 5: Right
      if (k3 && !k1 && !k2 && !k4 && !k5 && !k6) Mouse.click(MOUSE_LEFT);  // Button 3: Left Click
      if (k6 && !k1 && !k2 && !k3 && !k4 && !k5) Mouse.click(MOUSE_RIGHT); // Button 6: Right Click
    }

    // --- KEYBOARD MODE CHORDS ---
    else {
      // 1. Voice to Text System Shortcut (1+2+3+4+5+6)
      if (k1 && k2 && k3 && k4 && k5 && k6) {
        Keyboard.press(KEY_LEFT_GUI);
        Keyboard.press('h');
        delay(100);
        Keyboard.releaseAll();
      }

      // 2. Automation Layout
      else if (k4 && k5 && k6 && !k1 && !k2 && !k3) Keyboard.write(KEY_RETURN);    // 4+5+6 = Enter
      else if (k1 && k6 && !k2 && !k3 && !k4 && !k5) Keyboard.print(' ');           // 1+6 = Spacebar
      else if (k3 && k4 && !k1 && !k2 && !k5 && !k6) Keyboard.write(KEY_BACKSPACE); // 3+4 = Backspace

      // 3. Triple Chords
      else if (k1 && k2 && k3 && !k4 && !k5 && !k6) Keyboard.print('t'); // 1+2+3 = T
      else if (k1 && k2 && k4 && !k3 && !k5 && !k6) Keyboard.print('u'); // 1+2+4 = U
      else if (k1 && k4 && k2 && !k3 && !k5 && !k6) Keyboard.print('v'); // 1+4+2 = V
      else if (k2 && k5 && k3 && !k1 && !k4 && !k6) Keyboard.print('w'); // 2+5+3 = W
      else if (k1 && k4 && k5 && !k2 && !k3 && !k6) Keyboard.print('x'); // 1+4+5 = X
      else if (k2 && k5 && k6 && !k1 && !k3 && !k4) Keyboard.print('y'); // 2+5+6 = Y
      else if (k3 && k6 && k5 && !k1 && !k2 && !k4) Keyboard.print('z'); // 3+6+5 = Z

      // 4. Double Chords
      else if (k1 && k2 && !k3 && !k4 && !k5 && !k6) Keyboard.print('g'); // 1+2 = G
      else if (k2 && k3 && !k1 && !k4 && !k5 && !k6) Keyboard.print('h'); // 2+3 = H
      else if (k4 && k5 && !k1 && !k2 && !k3 && !k6) Keyboard.print('i'); // 4+5 = I
      else if (k5 && k6 && !k1 && !k2 && !k3 && !k4) Keyboard.print('j'); // 5+6 = J
      else if (k1 && k3 && !k2 && !k4 && !k5 && !k6) Keyboard.print('k'); // 1+3 = K
      else if (k4 && k6 && !k1 && !k2 && !k3 && !k5) Keyboard.print('l'); // 4+6 = L
      else if (k1 && k4 && !k2 && !k3 && !k5 && !k6) Keyboard.print('m'); // 1+4 = M
      else if (k2 && k5 && !k1 && !k3 && !k4 && !k6) Keyboard.print('n'); // 2+5 = N
      else if (k3 && k6 && !k1 && !k2 && !k4 && !k5) Keyboard.print('o'); // 3+6 = O
      else if (k1 && k5 && !k2 && !k3 && !k4 && !k6) Keyboard.print('p'); // 1+5 = P
      else if (k2 && k4 && !k1 && !k3 && !k5 && !k6) Keyboard.print('q'); // 2+4 = Q
      else if (k2 && k6 && !k1 && !k3 && !k4 && !k5) Keyboard.print('r'); // 2+6 = R
      else if (k3 && k5 && !k1 && !k2 && !k4 && !k6) Keyboard.print('s'); // 3+5 = S

      // 5. Single Taps
      else if (k1 && !k2 && !k3 && !k4 && !k5 && !k6) Keyboard.print('a'); // Tap 1 = A
      else if (k2 && !k1 && !k3 && !k4 && !k5 && !k6) Keyboard.print('b'); // Tap 2 = B
      else if (k3 && !k1 && !k2 && !k4 && !k5 && !k6) Keyboard.print('c'); // Tap 3 = C
      else if (k4 && !k1 && !k2 && !k3 && !k5 && !k6) Keyboard.print('d'); // Tap 4 = D
      else if (k5 && !k1 && !k2 && !k3 && !k4 && !k6) Keyboard.print('e'); // Tap 5 = E
      else if (k6 && !k1 && !k2 && !k3 && !k4 && !k5) Keyboard.print('f'); // Tap 6 = F
    }

    // Debounce: Wait until all buttons are released before reading next stroke
    while (digitalRead(BTN1) == LOW || digitalRead(BTN2) == LOW || 
           digitalRead(BTN3) == LOW || digitalRead(BTN4) == LOW || 
           digitalRead(BTN5) == LOW || digitalRead(BTN6) == LOW) {
      delay(10);
    }
  }
}
