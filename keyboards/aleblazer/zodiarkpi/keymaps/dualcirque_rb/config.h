/* Cirque Pointing Devices */
#ifdef POINTING_DEVICE_ENABLE
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
#endif

#define DYNAMIC_KEYMAP_LAYER_COUNT 5        //allow extra layers (total of 5 including the base)

//enable TT functions for keys to respond with two taps
#define TAP_CODE_DELAY 10
#define TAPPING_TOGGLE 2 //Tap TT twice to toggle layer
#define TAPPING_TERM 140 //Tapping duration in ms, normally using 140

// included line in rules.mk SPLIT_KEYBOARD = yes
#define SPLIT_LAYER_STATE_ENABLE        //sync layer state
#define SPLIT_LED_STATE_ENABLE          //sync LED state for caps lock, num lock
#define SPLIT_ACTIVITY_ENABLE           //sync activity or inactivity to both sides
#define SPLIT_TRANSPORT_MIRROR          //This mirrors the master side matrix to the slave side for features that react or require knowledge of master side key presses on the slave side.

#ifdef OLED_ENABLE
	#define OLED_DISPLAY_128X64             //Using 128x32 1.3" OLEDs
	#define OLED_TIMEOUT 0                  //80000 = 80secs, 120000 = 2mins in ms.
//	#define SPLIT_OLED_ENABLE		        //Sync on/off OLED state between halves (only use when you have two OLED)
    #define OLED_IC OLED_IC_SH1106          //driver for specific OLED screen
    #define OLED_BRIGHTNESS 255             //max 255
    #define OLED_UPDATE_INTERVAL 50         //Default 0. 50 for splits. Set the time interval for updating the OLED display in ms. This will improve the matrix scan rate.
//  #define OLED_FADE_OUT                   //seemed to interfere with off state
    #define OLED_COLUMN_OFFSET 2            //Shift output to the right this many pixels. Useful for 128x64 displays centered on a 132x64 SH1106 IC.
#endif

/* RGB Sleep Function*/
#define RGBLIGHT_SLEEP
#define RGB_MATRIX_SLEEP // turn off effects when suspended
#define RGBLIGHT_TIMEOUT 300000  // ms to wait until rgblight time out, 900K ms is 15min.
#define RGB_MATRIX_TIMEOUT 300000 // number of milliseconds to wait until rgb automatically turns off

/* Extra Effects RGB Matrix (still confirming why some are not being activate)*/
#define ENABLE_RGB_MATRIX_FLOWER_BLOOMING
#define ENABLE_RGB_MATRIX_STARLIGHT_DUAL_HUE
#define ENABLE_RGB_MATRIX_STARLIGHT_DUAL_SAT
#define ENABLE_RGB_MATRIX_RIVERFLOW
#define RGB_MATRIX_TYPING_HEATMAP_DECREASE_DELAY_MS 50
#define RGB_MATRIX_TYPING_HEATMAP_SPREAD 40
#define RGB_MATRIX_TYPING_HEATMAP_AREA_LIMIT 16
#define RGB_MATRIX_SOLID_REACTIVE_GRADIENT_MODE

