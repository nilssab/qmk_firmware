#include "preonic.h"
#include "action_layer.h"
#include "eeconfig.h"
#include "keyphrase.h"
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _GAME 1  // A game layer, keypad+F keys etc
#define _UTIL 2                                      
#define _LOWER 3
#define _RAISE 4
#define _ADJUST 16

enum preonic_keycodes {
  QWERTY = SAFE_RANGE,
  GAME,
  UTIL,
  LOWER,
  RAISE,
  BACKLIT
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |PrnScr|   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Esc  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |  `   |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |RShift|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |  GUI | Ctrl | RAlt |Lower |    Space    | Raise| Ctrl | LAlt |  GUI | Del  |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = {
  {KC_PSCR, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,  KC_8,    KC_9,    KC_0,    KC_ESC},
  {KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,  KC_I,    KC_O,    KC_P,    KC_BSPC},
  {KC_GRV,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,  KC_K,    KC_L,    KC_SCLN, KC_ENT},
  {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,  KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT},
  {KC_LCTL, KC_LGUI, KC_LCTL, KC_RALT, LOWER,   KC_SPC,  KC_SPC,  RAISE, KC_LCTL, KC_LALT, KC_LGUI, KC_DEL}
},

/* GAME mode
notes:
1. WASD moved to ESDF, to have hand on home row center position

 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   R  |   W  |   E  |   T  |      |      |  Up  |      |   ;  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |  Grv |   F  |   A  |   S  |   D  |   G  |      | left | down |right |   O  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |      |      |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |  Alt | Ctrl | RAlt |Lower |    Space    | Raise| Ctrl | LAlt |  GUI | Del  |
 * `-----------------------------------------------------------------------------------'
 */
[_GAME] = {
  {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC},
  {KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_DEL},
  {KC_ESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT},
  {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT},
  {KC_LCTL, KC_LGUI, KC_LCTL, KC_RALT, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LCTL, KC_LALT, KC_LGUI, KC_DEL}
},

/* UTIL layout
notes:
Utility layer
made for one handed input of numbers, cursor movement and copy and pasting easier etc.
(basically the lower layer but permanent)

/* UTIL layer
 * ,-----------------------------------------------------------------------------------.
 * |aPrtSc| Cut  | Copy | Paste|      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      | M-<  | PGUP |  UP  | PGDN | M->  |   ^  |   7  |   8  |  9   |   ,  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  | HOME | LEFT | DOWN |RIGHT | END  |   %  |   4  |   5  |  6   |   0  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  /   |   *  |   +  |  -   |  =   |   $  |   1  |   2  |  3   |   .  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */

[_UTIL] = {
  {KC_TILD, KC_EXLM,    KC_AT,   KC_HASH, KC_DLR,   KC_PERC, KC_CIRC,     KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC},
  {_______,LALT(S(KC_COMM)),KC_PGUP,KC_UP,KC_PGDN,LALT(S(KC_DOT)),KC_CIRC,KC_7,    KC_8,    KC_9,    KC_COMM, _______},
  {KC_ESC, KC_HOME,     KC_LEFT, KC_DOWN, KC_RIGHT, KC_END,  KC_PERC,     KC_4,    KC_5,    KC_6,    KC_0,    _______},
  {_______, KC_SLSH,    KC_ASTR, KC_PLUS, KC_MINS,  KC_EQL,  KC_DLR,      KC_1,    KC_2,    KC_3,    KC_DOT,  _______},
  {_______, _______,    _______, _______, _______,  _______, _______,     _______, _______, _______, _______, _______}
},


/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      | M-<  | PGUP |  UP  | PGDN | M->  |   ^  |   7  |   8  |  9   |   ,  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  | HOME | LEFT | DOWN |RIGHT | END  |   %  |   4  |   5  |  6   |   0  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  /   |   *  |   +  |  -   |  =   |   $  |   1  |   2  |  3   |   .  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = {
  {KC_TILD, KC_EXLM,    KC_AT,   KC_HASH, KC_DLR,   KC_PERC, KC_CIRC,     KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC},
  {_______,LALT(S(KC_COMM)),KC_PGUP,KC_UP,KC_PGDN,LALT(S(KC_DOT)),KC_CIRC,KC_7,    KC_8,    KC_9,    KC_COMM, _______},
  {KC_ESC, KC_HOME,     KC_LEFT, KC_DOWN, KC_RIGHT, KC_END,  KC_PERC,     KC_4,    KC_5,    KC_6,    KC_0,    _______},
  {_______, KC_SLSH,    KC_ASTR, KC_PLUS, KC_MINS,  KC_EQL,  KC_DLR,      KC_1,    KC_2,    KC_3,    KC_DOT,  _______},
  {_______, _______,    _______, _______, _______,  _______, _______,     _______, _______, _______, _______, _______}
},

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  | F10  | F11  | F12  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | sTAB |MWhUp |MWhLft| MUp  |MWhRgt|   !  |  \   |   [  |   ]  |  MB1 |  MB2 |  MB3 |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | CAPS |MWhDwn|MLeft |MDown |MRight|   &  |  '   |   (  |   )  |   {  |   }  |  MB4 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | BACK |PrScrn|  #   |  |   |   ~  |  "   |   @  |   ;  |   :  | FWD  |  MB5 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */

[_RAISE] = {
  {KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,    KC_F8,    KC_F9,   KC_F10,     KC_F11,    KC_F12},
  {S(KC_TAB),KC_WH_U,KC_WH_L, KC_MS_U, KC_WH_R, KC_EXLM, KC_BSLASH,KC_LBRC,  KC_RBRC, KC_BTN1,    KC_BTN2,   KC_BTN3},
  {KC_CAPS,  KC_WH_D, KC_MS_L,KC_MS_D, KC_MS_R, KC_AMPR, KC_QUOT,  KC_LPRN,  KC_RPRN, S(KC_LBRC), S(KC_RBRC),KC_BTN4},
  {_______, KC_WBAK, KC_PSCR, KC_HASH, KC_PIPE, KC_TILD, KC_DQUO,  KC_AT,    KC_SCLN, S(KC_SCLN), KC_WFWD,   KC_BTN5},
  {_______, _______, _______, _______, _______, _______, _______,  _______,  _______, _______,    _______,   _______}
},

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |Voice-|Voice+|Mus on|MusOff|  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Au OFF| Reset|      |BLight|      |      |      |  F9  |  F10 |  F11 |  F12 | Vol+ |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |Au ON |PASSW1|      |      |      |QWERTY|      |  F5  |  F6  |  F7  |  F8  | Vol- |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      | GAME |UTIL |  F1  |  F2  |  F3  |  F4  | Mute |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = {
  {MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12},
  {AU_OFF,  RESET,   _______, BACKLIT, _______, _______, _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_VOLU},
  {AU_ON,   PASS1,   _______, _______, _______, QWERTY,  _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_VOLD},
  {_______, _______, _______, _______, _______, GAME,    UTIL,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_MUTE},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
}
};

#ifdef AUDIO_ENABLE
float tone_startup[][2] = {
  {NOTE_B5, 20},
  {NOTE_B6, 8},
  {NOTE_DS6, 20},
  {NOTE_B6, 8}
};

float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);

float tone_goodbye[][2] = SONG(GOODBYE_SOUND);

float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);
#endif

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
        case QWERTY:
          if (record->event.pressed) {
            #ifdef AUDIO_ENABLE
              PLAY_NOTE_ARRAY(tone_qwerty, false, 0);
            #endif
            persistant_default_layer_set(1UL<<_QWERTY);
          }
          return false;
          break;
        case GAME:
          if (record->event.pressed) {
            #ifdef AUDIO_ENABLE
              PLAY_NOTE_ARRAY(tone_colemak, false, 0);
            #endif
            persistant_default_layer_set(1UL<<_GAME);
          }
          return false;
          break;
        case UTIL:
          if (record->event.pressed) {
            #ifdef AUDIO_ENABLE
              PLAY_NOTE_ARRAY(tone_dvorak, false, 0);
            #endif
            persistant_default_layer_set(1UL<<_UTIL);
          }
          return false;
          break;
        case LOWER:
          if (record->event.pressed) {
            layer_on(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
        case RAISE:
          if (record->event.pressed) {
            layer_on(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
        case BACKLIT:
          if (record->event.pressed) {
            register_code(KC_RSFT);
            #ifdef BACKLIGHT_ENABLE
              backlight_step();
            #endif
          } else {
            unregister_code(KC_RSFT);
          }
          return false;
          break;
      }
    return true;
};

void matrix_init_user(void) {
    #ifdef AUDIO_ENABLE
        startup_user();
    #endif
}

#ifdef AUDIO_ENABLE

void startup_user()
{
    _delay_ms(20); // gets rid of tick
    PLAY_NOTE_ARRAY(tone_startup, false, 0);
}

void shutdown_user()
{
    PLAY_NOTE_ARRAY(tone_goodbye, false, 0);
    _delay_ms(150);
    stop_all_notes();
}

void music_on_user(void)
{
    music_scale_user();
}

void music_scale_user(void)
{
    PLAY_NOTE_ARRAY(music_scale, false, 0);
}

#endif

/*
**OLD notes for Japanese input layer**
Main idea is to increase performace with japanese typing
1. Minimizes use of the 2 center columns 
    1a. non-alphabet characters moved to center
    1b. consonants not used in japan roman alphabet typing (qcvxjl) are moved to center (also see 2a)
    1c. "dfjk" columns are most preferred
2. Moves aiueo to one side, to greatly increase performance with Japanese typing
    (japanese written in the roman alphabet is almost always alternating consonants and vocals)
    2a. tries to move the non-used and least used consonants to the side with the aiueo keys
    2b. 
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |      |      |      |      |   ;  |   /  |   G  |   C  |   R  |   L  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   I  |   U  |   E  |      |      |      |   S  |   T  |   H  | Enter|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|      |      |   C  |   V  |   ,  |   .  |   G  |   Z  |   D  |   Z  | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrlx| Altx | GUIx | Raise|Lower |    Space    | Ctrl |  ALT | Left | Down |Right |
 * `-----------------------------------------------------------------------------------'
**OLD notes for Japanese input layer**
 */
