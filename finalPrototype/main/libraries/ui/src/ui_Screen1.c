// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.5.0
// LVGL version: 8.3.11
// Project name: SquareLine_Project

#include "ui.h"

void ui_Screen1_screen_init(void)
{
    ui_Screen1 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Screen1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_Screen1, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_Screen1, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_HeartRateImage = lv_img_create(ui_Screen1);
    lv_img_set_src(ui_HeartRateImage, &ui_img_heartbeat_png);
    lv_obj_set_width(ui_HeartRateImage, LV_SIZE_CONTENT);   /// 32
    lv_obj_set_height(ui_HeartRateImage, LV_SIZE_CONTENT);    /// 32
    lv_obj_set_x(ui_HeartRateImage, -91);
    lv_obj_set_y(ui_HeartRateImage, -107);
    lv_obj_set_align(ui_HeartRateImage, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_HeartRateImage, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_HeartRateImage, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_HeartRate = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_HeartRate, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_HeartRate, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_HeartRate, -65);
    lv_obj_set_y(ui_HeartRate, -107);
    lv_obj_set_align(ui_HeartRate, LV_ALIGN_CENTER);
    lv_label_set_text(ui_HeartRate, "0");
    lv_obj_set_style_text_color(ui_HeartRate, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_HeartRate, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BloodOxygenImage = lv_img_create(ui_Screen1);
    lv_img_set_src(ui_BloodOxygenImage, &ui_img_drop_png);
    lv_obj_set_width(ui_BloodOxygenImage, LV_SIZE_CONTENT);   /// 32
    lv_obj_set_height(ui_BloodOxygenImage, LV_SIZE_CONTENT);    /// 32
    lv_obj_set_x(ui_BloodOxygenImage, -92);
    lv_obj_set_y(ui_BloodOxygenImage, -66);
    lv_obj_set_align(ui_BloodOxygenImage, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_BloodOxygenImage, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_BloodOxygenImage, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_BloodOxygen = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_BloodOxygen, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_BloodOxygen, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_BloodOxygen, -60);
    lv_obj_set_y(ui_BloodOxygen, -69);
    lv_obj_set_align(ui_BloodOxygen, LV_ALIGN_CENTER);
    lv_label_set_text(ui_BloodOxygen, "0%");
    lv_obj_set_style_text_color(ui_BloodOxygen, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_BloodOxygen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BodyTempImage = lv_img_create(ui_Screen1);
    lv_img_set_src(ui_BodyTempImage, &ui_img_thermometer_png);
    lv_obj_set_width(ui_BodyTempImage, LV_SIZE_CONTENT);   /// 32
    lv_obj_set_height(ui_BodyTempImage, LV_SIZE_CONTENT);    /// 32
    lv_obj_set_x(ui_BodyTempImage, -17);
    lv_obj_set_y(ui_BodyTempImage, -106);
    lv_obj_set_align(ui_BodyTempImage, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_BodyTempImage, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_BodyTempImage, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_BodyTemp = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_BodyTemp, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_BodyTemp, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_BodyTemp, 20);
    lv_obj_set_y(ui_BodyTemp, -108);
    lv_obj_set_align(ui_BodyTemp, LV_ALIGN_CENTER);
    lv_label_set_text(ui_BodyTemp, "0°");
    lv_obj_set_style_text_color(ui_BodyTemp, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_BodyTemp, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Time = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_Time, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Time, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Time, -29);
    lv_obj_set_y(ui_Time, 73);
    lv_obj_set_align(ui_Time, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Time, "12:00");
    lv_obj_set_style_text_font(ui_Time, &ui_font_RobotoBIG, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_TimeSeconds = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_TimeSeconds, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_TimeSeconds, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_TimeSeconds, 70);
    lv_obj_set_y(ui_TimeSeconds, 46);
    lv_obj_set_align(ui_TimeSeconds, LV_ALIGN_CENTER);
    lv_label_set_text(ui_TimeSeconds, "00");
    lv_obj_set_style_text_font(ui_TimeSeconds, &ui_font_RobotoMedium, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Bar1 = lv_bar_create(ui_Screen1);
    lv_bar_set_value(ui_Bar1, 25, LV_ANIM_OFF);
    lv_bar_set_start_value(ui_Bar1, 0, LV_ANIM_OFF);
    lv_obj_set_width(ui_Bar1, 24);
    lv_obj_set_height(ui_Bar1, 13);
    lv_obj_set_x(ui_Bar1, 95);
    lv_obj_set_y(ui_Bar1, -123);
    lv_obj_set_align(ui_Bar1, LV_ALIGN_CENTER);
    lv_obj_set_style_bg_color(ui_Bar1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Bar1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_Bar1, lv_color_hex(0xFF0000), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Bar1, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    ui_Power = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_Power, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Power, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Power, 96);
    lv_obj_set_y(ui_Power, -108);
    lv_obj_set_align(ui_Power, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Power, "100%");
    lv_obj_set_style_text_color(ui_Power, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Power, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Power, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ChargingImage = lv_img_create(ui_Screen1);
    lv_img_set_src(ui_ChargingImage, &ui_img_lightning_png);
    lv_obj_set_width(ui_ChargingImage, LV_SIZE_CONTENT);   /// 20
    lv_obj_set_height(ui_ChargingImage, LV_SIZE_CONTENT);    /// 20
    lv_obj_set_x(ui_ChargingImage, 75);
    lv_obj_set_y(ui_ChargingImage, -122);
    lv_obj_set_align(ui_ChargingImage, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ChargingImage, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_ChargingImage, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_zoom(ui_ChargingImage, 200);

    ui_UVRaysImage = lv_img_create(ui_Screen1);
    lv_img_set_src(ui_UVRaysImage, &ui_img_sunglasses_png);
    lv_obj_set_width(ui_UVRaysImage, LV_SIZE_CONTENT);   /// 32
    lv_obj_set_height(ui_UVRaysImage, LV_SIZE_CONTENT);    /// 32
    lv_obj_set_x(ui_UVRaysImage, -91);
    lv_obj_set_y(ui_UVRaysImage, -27);
    lv_obj_set_align(ui_UVRaysImage, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_UVRaysImage, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_UVRaysImage, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_WeatherPlaceholder = lv_img_create(ui_Screen1);
    lv_img_set_src(ui_WeatherPlaceholder, &ui_img_1407854121);
    lv_obj_set_width(ui_WeatherPlaceholder, LV_SIZE_CONTENT);   /// 48
    lv_obj_set_height(ui_WeatherPlaceholder, LV_SIZE_CONTENT);    /// 48
    lv_obj_set_x(ui_WeatherPlaceholder, 72);
    lv_obj_set_y(ui_WeatherPlaceholder, 93);
    lv_obj_set_align(ui_WeatherPlaceholder, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_WeatherPlaceholder, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_WeatherPlaceholder, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_UVRays = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_UVRays, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_UVRays, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_UVRays, -65);
    lv_obj_set_y(ui_UVRays, -28);
    lv_obj_set_align(ui_UVRays, LV_ALIGN_CENTER);
    lv_label_set_text(ui_UVRays, "0");
    lv_obj_set_style_text_color(ui_UVRays, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_UVRays, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_AtmosphereImage = lv_img_create(ui_Screen1);
    lv_img_set_src(ui_AtmosphereImage, &ui_img_2104800269);
    lv_obj_set_width(ui_AtmosphereImage, LV_SIZE_CONTENT);   /// 32
    lv_obj_set_height(ui_AtmosphereImage, LV_SIZE_CONTENT);    /// 32
    lv_obj_set_x(ui_AtmosphereImage, -20);
    lv_obj_set_y(ui_AtmosphereImage, -65);
    lv_obj_set_align(ui_AtmosphereImage, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_AtmosphereImage, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_AtmosphereImage, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Atmosphere = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_Atmosphere, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Atmosphere, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Atmosphere, 20);
    lv_obj_set_y(ui_Atmosphere, -66);
    lv_obj_set_align(ui_Atmosphere, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Atmosphere, "1 Pa");
    lv_obj_set_style_text_color(ui_Atmosphere, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Atmosphere, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Compass = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_Compass, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Compass, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Compass, -39);
    lv_obj_set_y(ui_Compass, 121);
    lv_obj_set_align(ui_Compass, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Compass, "Compass: 0° N");

    ui_DistanceImage = lv_img_create(ui_Screen1);
    lv_img_set_src(ui_DistanceImage, &ui_img_ruler_png);
    lv_obj_set_width(ui_DistanceImage, LV_SIZE_CONTENT);   /// 32
    lv_obj_set_height(ui_DistanceImage, LV_SIZE_CONTENT);    /// 32
    lv_obj_set_x(ui_DistanceImage, -91);
    lv_obj_set_y(ui_DistanceImage, 13);
    lv_obj_set_align(ui_DistanceImage, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_DistanceImage, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_DistanceImage, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_StepsImage = lv_img_create(ui_Screen1);
    lv_img_set_src(ui_StepsImage, &ui_img_960456026);
    lv_obj_set_width(ui_StepsImage, LV_SIZE_CONTENT);   /// 32
    lv_obj_set_height(ui_StepsImage, LV_SIZE_CONTENT);    /// 32
    lv_obj_set_x(ui_StepsImage, -20);
    lv_obj_set_y(ui_StepsImage, -27);
    lv_obj_set_align(ui_StepsImage, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_StepsImage, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_StepsImage, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Steps = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_Steps, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Steps, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Steps, 20);
    lv_obj_set_y(ui_Steps, -27);
    lv_obj_set_align(ui_Steps, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Steps, "0");
    lv_obj_set_style_text_color(ui_Steps, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Steps, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Distance = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_Distance, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Distance, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Distance, -65);
    lv_obj_set_y(ui_Distance, 10);
    lv_obj_set_align(ui_Distance, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Distance, "0");
    lv_obj_set_style_text_color(ui_Distance, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Distance, 255, LV_PART_MAIN | LV_STATE_DEFAULT);


}