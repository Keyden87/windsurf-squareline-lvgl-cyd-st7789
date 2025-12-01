#include "ui_components.h"
#include <Arduino.h>

// Style definitions
lv_style_t style_main_cont;
lv_style_t style_header;
lv_style_t style_header_title;
lv_style_t style_speed_value;
lv_style_t style_speed_label;
lv_style_t style_card;
lv_style_t style_card_title;
lv_style_t style_card_value;
lv_style_t style_card_label;

// UI elements
static lv_obj_t* battery_bar = nullptr;
static lv_obj_t* battery_label = nullptr;
static lv_obj_t* speed_label = nullptr;
static lv_obj_t* time_label = nullptr;
static lv_obj_t* temp_label = nullptr;

// Font declarations
extern lv_font_t ui_font_Number;

// Image assets
LV_IMG_DECLARE(ui_img_icn_bike_png);
LV_IMG_DECLARE(ui_img_icn_charge_png);
LV_IMG_DECLARE(ui_img_icn_map_png);

void ui_components_init() {
    // Main container style
    lv_style_init(&style_main_cont);
    lv_style_set_bg_color(&style_main_cont, COLOR_BG);
    lv_style_set_pad_all(&style_main_cont, 0);
    lv_style_set_pad_gap(&style_main_cont, 0);

    // Header style
    lv_style_init(&style_header);
    lv_style_set_bg_color(&style_header, COLOR_PRIMARY);
    lv_style_set_pad_all(&style_header, 10);
    lv_style_set_radius(&style_header, 0);

    // Header title style
    lv_style_init(&style_header_title);
    lv_style_set_text_color(&style_header_title, lv_color_white());
    lv_style_set_text_font(&style_header_title, &lv_font_montserrat_20);

    // Speed value style
    lv_style_init(&style_speed_value);
    lv_style_set_text_color(&style_speed_value, COLOR_SECONDARY);
    lv_style_set_text_font(&style_speed_value, &ui_font_Number);

    // Speed label style
    lv_style_init(&style_speed_label);
    lv_style_set_text_color(&style_speed_label, COLOR_TEXT_GRAY);
    lv_style_set_text_font(&style_speed_label, &lv_font_montserrat_24);

    // Card style
    lv_style_init(&style_card);
    lv_style_set_bg_color(&style_card, COLOR_CARD_BG);
    lv_style_set_radius(&style_card, 10);
    lv_style_set_pad_all(&style_card, 15);
    lv_style_set_pad_gap(&style_card, 5);

    // Card title style
    lv_style_init(&style_card_title);
    lv_style_set_text_color(&style_card_title, COLOR_TEXT_GRAY);
    lv_style_set_text_font(&style_card_title, &lv_font_montserrat_16);

    // Card value style
    lv_style_init(&style_card_value);
    lv_style_set_text_color(&style_card_value, lv_color_white());
    lv_style_set_text_font(&style_card_value, &lv_font_montserrat_20);
}

static void create_header(lv_obj_t* parent) {
    lv_obj_t* header = lv_obj_create(parent);
    lv_obj_set_size(header, LV_PCT(100), 50);
    lv_obj_add_style(header, &style_header, 0);
    lv_obj_set_flex_flow(header, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(header, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    // Title
    lv_obj_t* title = lv_label_create(header);
    lv_label_set_text(title, "Home");
    lv_obj_add_style(title, &style_header_title, 0);
    lv_obj_set_flex_grow(title, 1);
    lv_obj_set_style_text_align(title, LV_TEXT_ALIGN_CENTER, 0);

    // Settings button
    lv_obj_t* settings_btn = lv_btn_create(header);
    lv_obj_set_size(settings_btn, 40, 40);
    lv_obj_t* settings_icon = lv_label_create(settings_btn);
    lv_label_set_text(settings_icon, LV_SYMBOL_SETTINGS);
    lv_obj_center(settings_icon);
}

static lv_obj_t* create_battery_indicator(lv_obj_t* parent) {
    lv_obj_t* cont = lv_obj_create(parent);
    lv_obj_remove_style_all(cont);
    lv_obj_set_size(cont, 40, 150);
    lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(cont, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_pad_gap(cont, 5, 0);

    // Battery bar
    battery_bar = lv_bar_create(cont);
    lv_obj_set_size(battery_bar, 20, 120);
    lv_bar_set_range(battery_bar, 0, 100);
    lv_bar_set_value(battery_bar, 50, LV_ANIM_OFF);
    lv_obj_set_style_bg_color(battery_bar, lv_color_hex(0x4CAF50), LV_PART_INDICATOR);

    // Battery percentage with icon
    lv_obj_t* battery_cont = lv_obj_create(cont);
    lv_obj_remove_style_all(battery_cont);
    lv_obj_set_size(battery_cont, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_flex_flow(battery_cont, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(battery_cont, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    
    lv_obj_t* icon = lv_label_create(battery_cont);
    lv_label_set_text(icon, LV_SYMBOL_CHARGE);
    lv_obj_set_style_text_color(icon, lv_color_hex(0x4CAF50), 0);
    
    battery_label = lv_label_create(battery_cont);
    lv_label_set_text(battery_label, "50%");
    lv_obj_add_style(battery_label, &style_card_value, 0);

    return cont;
}

static lv_obj_t* create_speed_display(lv_obj_t* parent) {
    lv_obj_t* cont = lv_obj_create(parent);
    lv_obj_remove_style_all(cont);
    lv_obj_set_size(cont, LV_PCT(50), 200);
    lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(cont, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    // Speed label
    lv_obj_t* label = lv_label_create(cont);
    lv_label_set_text(label, "Speed");
    lv_obj_add_style(label, &style_speed_label, 0);

    // Speed value
    speed_label = lv_label_create(cont);
    lv_label_set_text(speed_label, "32");
    lv_obj_add_style(speed_label, &style_speed_value, 0);

    // Unit
    lv_obj_t* unit = lv_label_create(cont);
    lv_label_set_text(unit, "km/h");
    lv_obj_add_style(unit, &style_speed_label, 0);

    return cont;
}

static lv_obj_t* create_driving_info_card(lv_obj_t* parent) {
    lv_obj_t* cont = lv_obj_create(parent);
    lv_obj_add_style(cont, &style_card, 0);
    lv_obj_set_size(cont, LV_PCT(100), LV_SIZE_CONTENT);
    lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_pad_all(cont, 15, 0);

    // Title
    lv_obj_t* title = lv_label_create(cont);
    lv_label_set_text(title, "Driving Information");
    lv_obj_add_style(title, &style_card_title, 0);
    lv_obj_set_style_pad_bottom(title, 10, 0);

    // Info grid
    static lv_coord_t grid_col_dsc[] = {LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
    static lv_coord_t grid_row_dsc[] = {LV_GRID_CONTENT, LV_GRID_CONTENT, LV_GRID_CONTENT, LV_GRID_TEMPLATE_LAST};
    
    lv_obj_t* grid = lv_obj_create(cont);
    lv_obj_remove_style_all(grid);
    lv_obj_set_size(grid, LV_PCT(100), LV_SIZE_CONTENT);
    lv_obj_set_grid_dsc_array(grid, grid_col_dsc, grid_row_dsc);
    lv_obj_set_style_pad_row(grid, 8, 0);
    lv_obj_set_style_pad_column(grid, 10, 0);

    // ODO
    lv_obj_t* odo_label = lv_label_create(grid);
    lv_label_set_text(odo_label, "ODO:");
    lv_obj_add_style(odo_label, &style_card_title, 0);
    lv_obj_set_grid_cell(odo_label, LV_GRID_ALIGN_START, 0, 1, LV_GRID_ALIGN_CENTER, 0, 1);
    
    lv_obj_t* odo_value = lv_label_create(grid);
    lv_label_set_text(odo_value, "287.7 km");
    lv_obj_add_style(odo_value, &style_card_value, 0);
    lv_obj_set_grid_cell(odo_value, LV_GRID_ALIGN_END, 1, 1, LV_GRID_ALIGN_CENTER, 0, 1);

    // Add other driving info items (TRIP, MAX SPEED, AVG SPEED, ETA, TIME) in a similar way
    // ... (implementation omitted for brevity)

    return cont;
}

lv_obj_t* create_main_screen() {
    lv_obj_t* scr = lv_obj_create(NULL);
    lv_obj_add_style(scr, &style_main_cont, 0);
    lv_obj_set_flex_flow(scr, LV_FLEX_FLOW_COLUMN);

    // Header
    create_header(scr);

    // Main content
    lv_obj_t* content = lv_obj_create(scr);
    lv_obj_remove_style_all(content);
    lv_obj_set_size(content, LV_PCT(100), LV_PCT(100));
    lv_obj_set_flex_flow(content, LV_FLEX_FLOW_ROW);
    lv_obj_set_style_pad_all(content, 10, 0);
    lv_obj_set_style_pad_gap(content, 10, 0);

    // Left side - Battery
    create_battery_indicator(content);

    // Center - Speed
    create_speed_display(content);

    // Right side - Driving info
    create_driving_info_card(content);

    // Footer
    lv_obj_t* footer = lv_obj_create(scr);
    lv_obj_set_size(footer, LV_PCT(100), 50);
    lv_obj_set_flex_flow(footer, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(footer, LV_FLEX_ALIGN_SPACE_AROUND, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_bg_color(footer, lv_color_hex(0x2D2D2D), 0);
    lv_obj_set_style_radius(footer, 0, 0);

    // Footer icons
    lv_obj_t* bike_btn = lv_imgbtn_create(footer);
    lv_imgbtn_set_src(bike_btn, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_icn_bike_png, NULL);
    lv_obj_set_size(bike_btn, 32, 32);
    
    lv_obj_t* charge_btn = lv_imgbtn_create(footer);
    lv_imgbtn_set_src(charge_btn, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_icn_charge_png, NULL);
    lv_obj_set_size(charge_btn, 32, 32);
    
    lv_obj_t* location_btn = lv_imgbtn_create(footer);
    lv_imgbtn_set_src(location_btn, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_icn_map_png, NULL);
    lv_obj_set_size(location_btn, 32, 32);

    return scr;
}

// Update functions
void set_battery_level(int level) {
    if (battery_bar) {
        lv_bar_set_value(battery_bar, level, LV_ANIM_ON);
    }
    if (battery_label) {
        lv_label_set_text_fmt(battery_label, "%d%%", level);
    }
}

void set_speed(int speed) {
    if (speed_label) {
        lv_label_set_text_fmt(speed_label, "%d", speed);
    }
}

void set_time(const char* time_str) {
    if (time_label) {
        lv_label_set_text(time_label, time_str);
    }
}

void set_temperature(const char* temp_str) {
    if (temp_label) {
        lv_label_set_text(temp_label, temp_str);
    }
}
