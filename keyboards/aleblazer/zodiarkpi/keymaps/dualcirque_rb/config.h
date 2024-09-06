#define SPLIT_POINTING_ENABLE
#define CIRQUE_PINNACLE_POSITION_MODE CIRQUE_PINNACLE_ABSOLUTE_MODE
#define CIRQUE_PINNACLE_DIAMETER_MM 40
#define CIRQUE_PINNACLE_CURVED_OVERLAY
#define POINTING_DEVICE_CS_PIN GP11
#define CIRQUE_PINNACLE_TAP_ENABLE
#define CIRQUE_PINNACLE_TAPPING_TERM 100
#define POINTING_DEVICE_TASK_THROTTLE_MS 5
#define POINTING_DEVICE_GESTURES_CURSOR_GLIDE_ENABLE //motion of cursor continues when flicked

#define POINTING_DEVICE_COMBINED            // two pointing devices
#define POINTING_DEVICE_ROTATION_180        // for cirque on the left
#define POINTING_DEVICE_AUTO_MOUSE_ENABLE
#define AUTO_MOUSE_DEFAULT_LAYER 2

//enable TT functions for keys
#define TAP_CODE_DELAY 10
#define TAPPING_TOGGLE 2 //Tap TT twice to toggle layer
#define TAPPING_TERM 100 //Tapping duration in ms, normally using 140

//data sync issues for OLED i2c screen https://docs.qmk.fm/features/split_keyboard#data-sync-options
//also have included line in rules.mk SPLIT_KEYBOARD = yes
#define SPLIT_LAYER_STATE_ENABLE        //sync layer state
#define SPLIT_LED_STATE_ENABLE          //sync LED state for caps lock, num lock
#define SPLIT_ACTIVITY_ENABLE           //sync activity or inactivity to both sides
#define SPLIT_TRANSPORT_MIRROR          //This mirrors the master side matrix to the slave side for features that react or require knowledge of master side key presses on the slave side.

#ifdef OLED_ENABLE
	#define OLED_DISPLAY_128X64             //Using 128x32 1.3" OLEDs
	#define OLED_TIMEOUT 0                  //80000 = 80secs, 120000 = 2mins in ms.
//	#define SPLIT_OLED_ENABLE		        //Sync on/off OLED state between halves
    #define OLED_IC OLED_IC_SH1106          //driver for specific OLED screen
    #define OLED_BRIGHTNESS 255             //max 255
    #define OLED_UPDATE_INTERVAL 50         //Default 0. 50 for splits. Set the time interval for updating the OLED display in ms. This will improve the matrix scan rate.
//    #define OLED_FADE_OUT
    #define OLED_COLUMN_OFFSET 2           //Shift output to the right this many pixels. Useful for 128x64 displays centered on a 132x64 SH1106 IC.
#endif
