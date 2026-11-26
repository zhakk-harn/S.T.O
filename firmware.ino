uint8_t columns[] = { 13, 14, 15, 16, 17, 18, 19, 20, 21 };
uint8_t rows[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 12 };

unsigned int keys[12][9] = {
        //0                       1                       2                         3                 4                 5                         6               7               8                   
  /*0*/ { 0,                      KEY_ENTER,              KEY_SPACE,                0,                MODIFIERKEY_ALT,  MODIFIERKEY_GUI,          0,              0,              MODIFIERKEY_CTRL },                                                
  /*1*/ { KEY_COMMA,              KEY_M,                  KEY_N,                    KEY_B,            KEY_V,            KEY_C,                    KEY_X,          KEY_Z,          MODIFIERKEY_SHIFT },                                                               
  /*2*/ { KEY_K,                  KEY_J,                  KEY_H,                    KEY_G,            KEY_F,            KEY_D,                    KEY_S,          KEY_A,          KEY_CAPS_LOCK },                                                                       
  /*3*/ { KEY_I,                  KEY_U,                  KEY_Y,                    KEY_T,            KEY_R,            KEY_E,                    KEY_W,          KEY_Q,          KEY_TAB },                                                                             
  /*4*/ { KEY_L,                  KEY_SEMICOLON,          KEY_QUOTE,                KEY_BACKSLASH,    KEY_HOME,         KEY_END,                  KEYPAD_4,       KEYPAD_5,       KEYPAD_6 },                                                  
  /*5*/ { KEY_PERIOD,             KEY_SLASH,              KEY_PAGE_UP,              KEY_PAGE_DOWN,    KEY_UP,           MODIFIERKEY_RIGHT_SHIFT,  KEYPAD_1,       KEYPAD_2,       KEYPAD_3 },                            
  /*6*/ { MODIFIERKEY_RIGHT_ALT,  MODIFIERKEY_RIGHT_GUI,  MODIFIERKEY_RIGHT_CTRL,   KEY_LEFT,         KEY_DOWN,         KEY_RIGHT,                KEYPAD_0,       KEYPAD_PERIOD,  KEYPAD_ENTER },  
  /*7*/ { KEY_F9,                 KEY_F10,                KEY_F11,                  KEY_F12,          KEY_PRINTSCREEN,  KEY_NUM_LOCK,             0,            0,            0 },                                                             
  /*8*/ { KEY_F8,                 KEY_F7,                 KEY_F6,                   KEY_F5,           KEY_F4,           KEY_F3,                   KEY_F2,         KEY_F1,         KEY_ESC },                                                                     
  /*9*/ { KEY_8,                  KEY_7,                  KEY_6,                    KEY_5,            KEY_4,            KEY_3,                    KEY_2,          KEY_1,          KEY_TILDE },                                                                           
  /*10*/ { KEY_O,                 KEY_P,                  KEY_LEFT_BRACE,           KEY_RIGHT_BRACE,  KEY_INSERT,       KEY_DELETE,               KEYPAD_7,       KEYPAD_8,       KEYPAD_9 },                                        
  /*11*/ { KEY_9,                 KEY_0,                  KEY_MINUS,                KEY_EQUAL,        KEY_BACKSPACE,    KEYPAD_SLASH,             KEYPAD_ASTERIX, KEYPAD_MINUS,   KEYPAD_PLUS }                                  
};

bool active[12][9] = {
  {false,false,false,false,false,false,false,false,false,},
  {false,false,false,false,false,false,false,false,false,},
  {false,false,false,false,false,false,false,false,false,},
  {false,false,false,false,false,false,false,false,false,},
  {false,false,false,false,false,false,false,false,false,},
  {false,false,false,false,false,false,false,false,false,},
  {false,false,false,false,false,false,false,false,false,},
  {false,false,false,false,false,false,false,false,false,},
  {false,false,false,false,false,false,false,false,false,},
  {false,false,false,false,false,false,false,false,false,},
  {false,false,false,false,false,false,false,false,false,},
  {false,false,false,false,false,false,false,false,false,},
};

bool wasActive[12][9] = {
  {false,false,false,false,false,false,false,false,false,},
  {false,false,false,false,false,false,false,false,false,},
  {false,false,false,false,false,false,false,false,false,},
  {false,false,false,false,false,false,false,false,false,},
  {false,false,false,false,false,false,false,false,false,},
  {false,false,false,false,false,false,false,false,false,},
  {false,false,false,false,false,false,false,false,false,},
  {false,false,false,false,false,false,false,false,false,},
  {false,false,false,false,false,false,false,false,false,},
  {false,false,false,false,false,false,false,false,false,},
  {false,false,false,false,false,false,false,false,false,},
  {false,false,false,false,false,false,false,false,false,},
};

uint8_t led_num = 23;
uint8_t led_caps = 22;

void setup() {
  Serial.begin(115200);

  pinMode(led_num, OUTPUT);
  pinMode(led_caps, OUTPUT);

  digitalWrite(led_num, LOW);
  digitalWrite(led_caps, LOW);

  for (uint8_t c = 0; c < sizeof(columns) / sizeof(columns[0]); c++) {
    pinMode(columns[c], INPUT_PULLUP);
  }

  for (uint8_t r = 0; r < sizeof(rows) / sizeof(rows[0]); r++) {
    pinMode(rows[r], OUTPUT);
    digitalWrite(rows[r], LOW);
  }
}

void loop() {
  for (uint8_t c = 0; c < sizeof(columns) / sizeof(columns[0]); c++) {
    if (digitalRead(columns[c]) == 0) {
      for (uint8_t r = 0; r < sizeof(rows) / sizeof(rows[0]); r++) {
        digitalWrite(rows[r], HIGH);
      }

      for (uint8_t r = 0; r < sizeof(rows) / sizeof(rows[0]); r++) {
        digitalWrite(rows[r], LOW);

        if (digitalRead(columns[c]) == 0) {
          active[r][c] = true;
          Serial.print(c);
          Serial.print(":");
          Serial.print(r);
          Serial.print(":");
          Serial.print(keys[r][c]);
          Serial.print("\t");
        }else{
          active[r][c] = false;
        }

        // press
        if(active[r][c] && !wasActive[r][c]){
            Keyboard.press(keys[r][c]);
        }

        // release
        if(!active[r][c] && wasActive[r][c]){
        // if(!active[r][c]){
          Keyboard.release(keys[r][c]);
        }

        digitalWrite(rows[r], HIGH);
        wasActive[r][c] = active[r][c];
      }

      for (uint8_t r = 0; r < sizeof(rows) / sizeof(rows[0]); r++) {
        digitalWrite(rows[r], LOW);
      }
    }else{
      for (uint8_t r = 0; r < sizeof(rows) / sizeof(rows[0]); r++) {
        if(wasActive[r][c]){
          Keyboard.release(keys[r][c]);
        }
        wasActive[r][c] = false;
      }
    }
  }

  delay(15);
  Serial.println();  
}

bool isModifier(unsigned int key){
  switch(key){
    case MODIFIERKEY_CTRL:
    case MODIFIERKEY_RIGHT_CTRL:
    case MODIFIERKEY_SHIFT:
    case MODIFIERKEY_RIGHT_SHIFT:
    case MODIFIERKEY_ALT:
    case MODIFIERKEY_RIGHT_ALT:
    case MODIFIERKEY_GUI:
    case MODIFIERKEY_RIGHT_GUI:
      return true;
    default:
      return false;
  }
}
