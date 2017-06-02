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
#define _COLEMAK 1
#define _DVORAK 2
#define _LOWER 3
#define _RAISE 4
#define _ADJUST 16

enum preonic_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
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
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |  Up  | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrlx| Altx | GUIx | Raise|Lower |    Space    | Ctrl |  ALT | Left | Down |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = {
  {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,  KC_8,    KC_9,    KC_0,    KC_BSPC},
  {KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,  KC_I,    KC_O,    KC_P,    KC_BSPC},
  {KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,  KC_K,    KC_L,    KC_SLSH, KC_ENT},
  {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,  KC_COMM, KC_DOT,  KC_UP,   KC_DEL},
  {KC_LCTL, KC_LGUI, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE, KC_LCTRL,KC_LEFT, KC_DOWN, KC_RGHT}
},

/* Colemak
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrlx| Altx | GUIx | Raise|Lower |    Space    | Ctrl |  ALT | Left | Down |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_COLEMAK] = {
  {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC},
  {KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_DEL},
  {KC_ESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT},
  {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT},
  {KC_LCTL, KC_LGUI, KC_LALT, KC_LCTL, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LGUI, KC_LEFT, KC_DOWN, KC_RGHT}
},

/* Dvorak
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   '  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |  /   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrlx| Altx | GUIx | Raise|Lower |    Space    | Ctrl |  ALT | Left | Down |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_DVORAK] = {
  {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC},
  {KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_DEL},
  {KC_ESC,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_SLSH},
  {KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_ENT},
  {KC_LCTL, KC_LGUI, KC_LALT, KC_LCTL, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LGUI, KC_LEFT, KC_DOWN, KC_RGHT}
},

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      | M-<  | PGUP |  UP  | PGDN | M->  |  +   |   7  |   8  |  9   |   .  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |   `  | HOME | LEFT | DOWN |RIGHT | END  |  -   |   4  |   5  |  6   |   0  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  $   |   %  |   @  |  |   |  =   |  _   |   1  |   2  |  3   |   ,  | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      | PGDN | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = {
  {KC_TILD, KC_EXLM,    KC_AT,   KC_HASH, KC_DLR,   KC_PERC, KC_CIRC,     KC_AMPR, KC_ASTR,KC_LPRN, KC_RPRN, KC_BSPC},
  {_______,LALT(S(KC_COMM)),KC_PGUP,KC_UP,KC_PGDN,LALT(S(KC_DOT)),KC_PLUS,KC_7,    KC_8,   KC_9,    KC_DOT,  KC_BSPC},
  {KC_GRV,  KC_HOME,    KC_LEFT, KC_DOWN, KC_RIGHT, KC_END,  KC_MINS,     KC_4,    KC_5,   KC_6,    KC_0,    KC_ENTER},
  {_______, KC_DLR,     KC_PERC, KC_AT,   KC_PIPE,  KC_EQL,  KC_UNDS,     KC_1,    KC_2,   KC_3,    KC_COMM, KC_DEL},
  {_______, _______,    _______, _______, _______,  _______, _______,     _______, _______,KC_MPRV, KC_MNXT, KC_MPLY}
},

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  | F10  | F11  | F12  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |MWhUp |  MB4 | MUp  |  MB3 |   !  |  \   |   [  |   ]  | MB1  |  MB2 | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | CAPS |MWhDwn|MLeft |MDown |MRight|   &  |  '   |   (  |   )  |   {  |   }  | ENTR |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | MB5  |PrScrn|  ^   |  #   |   ~  |  *   |   "  |   ;  |   :  | Vol+ | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      | Vol- | Play |
 * `-----------------------------------------------------------------------------------'
 */

[_RAISE] = {
  {KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,    KC_F8,    KC_F9,   KC_F10,     KC_F11,    KC_F12},
  {_______, KC_WH_U, KC_BTN4, KC_MS_U, KC_BTN3, KC_EXLM, KC_BSLASH,KC_LBRC,  KC_RBRC, KC_BTN1,    KC_BTN2,   KC_BSPC},
  {KC_CAPS, KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, KC_AMPR, KC_QUOT,  KC_LPRN,  KC_RPRN, S(KC_LBRC), S(KC_RBRC),KC_ENTER},
  {_______, KC_BTN5, KC_PSCR, KC_CIRC, KC_HASH, KC_TILD, KC_ASTR,  KC_DQUO,  KC_SCLN, S(KC_SCLN), KC_VOLU,   KC_DEL},
  {_______, _______, _______, _______, _______, _______, _______,  _______,  _______, KC_MUTE,    KC_VOLD,   KC_MPLY}
},

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Reset|      |BLight|QWERTY|DVORAK|Colemk|  F9  |  F10 |  F11 |  F12 | Vol+ |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |PASSW1|      |Aud on|AudOff|AGnorm|AGswap|  F5  |  F6  |  F7  |  F8  | Vol- |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|MusOff|MidiOn|MidOff|  F1  |  F2  |  F3  |  F4  | Mute |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |  MA0 |  MA1 | MA2  |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = {
  {KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, KC_F12},
  {_______, RESET,   _______, BACKLIT, QWERTY,  DVORAK,  COLEMAK, KC_F9,   KC_F10,  KC_F11,  KC_F12, KC_VOLU},
  {_______, PASS1,   _______, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, KC_F5,   KC_F6,   KC_F7,   KC_F8,  KC_VOLD},
  {_______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  KC_F1,   KC_F2,   KC_F3,   KC_F4,  KC_MUTE},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, KC_ACL0, KC_ACL1,KC_ACL2}
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
        case COLEMAK:
          if (record->event.pressed) {
            #ifdef AUDIO_ENABLE
              PLAY_NOTE_ARRAY(tone_colemak, false, 0);
            #endif
            persistant_default_layer_set(1UL<<_COLEMAK);
          }
          return false;
          break;
        case DVORAK:
          if (record->event.pressed) {
            #ifdef AUDIO_ENABLE
              PLAY_NOTE_ARRAY(tone_dvorak, false, 0);
            #endif
            persistant_default_layer_set(1UL<<_DVORAK);
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
