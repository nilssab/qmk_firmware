// This is my preferred layout, I'll give it a better name later..

#include "planck.h"
#include "action_layer.h"
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _COLEMAK 1
#define _DVORAK 2
#define _LOWER 3
#define _RAISE 4
#define _PLOVER 5
#define _ADJUST 6

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  PLOVER,
  LOWER,
  RAISE,
  BACKLIT,
  EXT_PLV,
  ADJUST_,
  LOWER__,
  RAISE__
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | sTab |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |  Tab |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |RShift|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |  GUI | Ctrl | RAlt |Lower |    Space    | Raise| Ctrl | LAlt |  GUI | Del  |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = {
  {S(KC_TAB), KC_Q,    KC_W,    KC_E,    KC_R,  KC_T,   KC_Y,   KC_U,  KC_I,    KC_O,    KC_P,    KC_BSPC},
  {KC_TAB,    KC_A,    KC_S,    KC_D,    KC_F,  KC_G,   KC_H,   KC_J,  KC_K,    KC_L,    KC_SCLN, KC_ENT},
  {KC_LSFT,   KC_Z,    KC_X,    KC_C,    KC_V,  KC_B,   KC_N,   KC_M,  KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT},
  {KC_LCTL,   KC_LGUI, KC_LCTL, KC_RALT, LOWER, KC_SPC, KC_SPC, RAISE, KC_LCTL, KC_LALT, KC_LGUI, KC_DEL}
},

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |      | M-<  | PGUP |  UP  | PGDN | M->  |   ^  |   7  |   8  |  9   |   ,  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  | HOME | LEFT | DOWN |RIGHT | END  |   %  |   4  |   5  |  6   |   0  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  /   |   *  |   +  |  -   |  =   |   $  |   1  |   2  |  3   |   .  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
/* LowerNew
 * ,-----------------------------------------------------------------------------------.
 * |      |   7  |   8  |   9  |   ,  |   ^  |  \   |  [   |  ]   |  <   |   >  |      |
 * |------+------+------+------+--------------------+------+------+------+------+------|
 * | Esc  |   4  |   5  |   6  |   0  |   %  |  '   |  (   |  )   |  {   |   }  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   1  |   2  |   3  |   .  |   $  |  =   |  -   |  +   |  *   |   /  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */




[_LOWER] = {
  {_______, LALT(S(KC_COMM)), KC_PGUP, KC_UP,   KC_PGDN, LALT(S(KC_DOT)), KC_CIRC, KC_7,    KC_8,    KC_9,    KC_COMM, _______},
  {KC_ESC,  KC_HOME,          KC_LEFT, KC_DOWN, KC_RIGHT,        KC_END,  KC_PERC, KC_4,    KC_5,    KC_6,    KC_0,    _______},
  {_______, KC_SLSH,          KC_ASTR, KC_PLUS, KC_MINS,         KC_EQL,  KC_DLR,  KC_1,    KC_2,    KC_3,    KC_DOT,  _______},
  {_______, _______,          _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______}
},

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * | sTAB |MWhUp |MWhLft| MUp  |MWhRgt|   #  |  \   |   [  |   ]  |  MB1 |  MB2 |  MB3 |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | CAPS |MWhDwn|MLeft |MDown |MRight|   &  |      |   (  |   )  |   {  |   }  |  MB4 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | BACK |PrScrn|  |   |   !  |   ~  |      |   @  |   '  |   "  | FWD  |  MB5 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
/* RaiseNew
 * ,-----------------------------------------------------------------------------------.
 * |      | M-<  | PGUP |  UP  | PGDN | M->  |      |MWhUp |MWhLft| MUp  |MWhRgt|  MB3 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | CAPS | HOME | LEFT | DOWN |RIGHT | END  |      |MWhDwn|MLeft |MDown |MRight|  MB4 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | BACK |PrScrn|      |      |      |      |      |      |      | FWD  |  MB5 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */


[_RAISE] = {
  {S(KC_TAB),KC_WH_U,KC_WH_L, KC_MS_U, KC_WH_R, KC_EXLM, KC_BSLASH,KC_LBRC,  KC_RBRC, KC_BTN1,    KC_BTN2,   KC_BTN3},
  {KC_CAPS,  KC_WH_D, KC_MS_L,KC_MS_D, KC_MS_R, KC_AMPR, KC_QUOT,  KC_LPRN,  KC_RPRN, S(KC_LBRC), S(KC_RBRC),KC_BTN4},
  {_______, KC_WBAK, KC_PSCR, KC_HASH, KC_PIPE, KC_TILD, KC_DQUO,  KC_AT,    KC_SCLN, S(KC_SCLN), KC_WFWD,   KC_BTN5},
  {_______, _______, _______, _______, _______, _______, _______,  _______,  _______, _______,    _______,   _______}
},

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |Au OFF| Reset|      |BLight|      |      |      |  F9  |  F10 |  F11 |  F12 | Vol+ |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |Au ON | LGUI |LSHIFT| LCTRL| LALT |QWERTY|Adjust|  F5  |  F6  |  F7  |  F8  | Vol- |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      | Lower|Raise |  F1  |  F2  |  F3  |  F4  | Mute |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = {
  {AU_OFF,  RESET,   _______, BACKLIT, _______, _______, _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_VOLU},
  {AU_ON,   KC_LGUI, KC_LSFT, KC_LCTL, KC_LALT, QWERTY,  ADJUST_, KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_VOLD},
  {_______, _______, _______, _______, _______, LOWER__, RAISE__, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_MUTE},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
}

};

#ifdef AUDIO_ENABLE

float tone_startup[][2]    = SONG(STARTUP_SOUND);
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
float tone_plover[][2]     = SONG(PLOVER_SOUND);
float tone_plover_gb[][2]  = SONG(PLOVER_GOODBYE_SOUND);
float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);

float tone_goodbye[][2] = SONG(GOODBYE_SOUND);
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
    case RAISE__:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_colemak, false, 0);
        #endif
        persistant_default_layer_set(1UL<<_RAISE);
      }
      return false;
      break;
    case LOWER__:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_dvorak, false, 0);
        #endif
        persistant_default_layer_set(1UL<<_LOWER);
      }
      return false;
      break;
    case ADJUST_:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_dvorak, false, 0);
        #endif
        persistant_default_layer_set(1UL<<_ADJUST);
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
    case PLOVER:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          stop_all_notes();
          PLAY_NOTE_ARRAY(tone_plover, false, 0);
        #endif
        layer_off(_RAISE);
        layer_off(_LOWER);
        layer_off(_ADJUST);
        layer_on(_PLOVER);
        if (!eeconfig_is_enabled()) {
            eeconfig_init();
        }
        keymap_config.raw = eeconfig_read_keymap();
        keymap_config.nkro = 1;
        eeconfig_update_keymap(keymap_config.raw);
      }
      return false;
      break;
    case EXT_PLV:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_plover_gb, false, 0);
        #endif
        layer_off(_PLOVER);
      }
      return false;
      break;
  }
  return true;
}

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
