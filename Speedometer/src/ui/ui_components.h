#pragma once
#include <lvgl.h>

// Colors
#define COLOR_PRIMARY lv_color_hex(0x4CAF50)  // Green
#define COLOR_SECONDARY lv_color_hex(0xFF9800) // Orange
#define COLOR_BG lv_color_hex(0x1E1E1E)       // Dark background
#define COLOR_CARD_BG lv_color_hex(0x2D2D2D)  // Card background
#define COLOR_TEXT_WHITE lv_color_white()
#define COLOR_TEXT_GRAY lv_color_hex(0x9E9E9E)

// Style declarations
extern lv_style_t style_main_cont;
extern lv_style_t style_header;
extern lv_style_t style_header_title;
extern lv_style_t style_speed_value;
extern lv_style_t style_speed_label;
extern lv_style_t style_card;
extern lv_style_t style_card_title;
extern lv_style_t style_card_value;
extern lv_style_t style_card_label;

// Initialize all UI components and styles
void ui_components_init();

// Create a card with title and value
lv_obj_t* create_info_card(lv_obj_t* parent, const char* title, const char* value, const lv_img_dsc_t* icon = nullptr);

// Create a vertical progress bar (for battery)
lv_obj_t* create_vertical_bar(lv_obj_t* parent, int32_t min, int32_t max, int32_t val, const lv_color_t& color);

// Update a card's value
void update_card_value(lv_obj_t* card, const char* value);

// Set the battery level (0-100%)
void set_battery_level(int level);

// Set the speed value
void set_speed(int speed);

// Set the time display
void set_time(const char* time_str);

// Set the temperature display
void set_temperature(const char* temp_str);

// Set driving information
void set_driving_info(const char* odo, const char* trip, const char* max_speed, const char* avg_speed, const char* eta, const char* time);

// Create the main screen
lv_obj_t* create_main_screen();
