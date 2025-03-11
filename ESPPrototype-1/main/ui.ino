/*Change to your screen resolution*/
static const uint16_t screenWidth  = 240;
static const uint16_t screenHeight = 280;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[ screenWidth * screenHeight / 10 ];

TFT_eSPI tft = TFT_eSPI(screenWidth, screenHeight); /* TFT instance */

#if LV_USE_LOG != 0
/* Serial debugging */
void my_print(const char * buf)
{
    Serial.printf(buf);
    Serial.flush();
}
#endif

/* Display flushing */
void my_disp_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p )
{
    uint32_t w = ( area->x2 - area->x1 + 1 );
    uint32_t h = ( area->y2 - area->y1 + 1 );

    tft.startWrite();
    tft.setAddrWindow( area->x1, area->y1, w, h );
    tft.pushColors( ( uint16_t * )&color_p->full, w * h, true );
    tft.endWrite();

    lv_disp_flush_ready( disp );
}

/*Read the touchpad*/
void my_touchpad_read( lv_indev_drv_t * indev_driver, lv_indev_data_t * data )
{
    uint16_t touchX = 0, touchY = 0;

    bool touched = false;//tft.getTouch( &touchX, &touchY, 600 );

    if( !touched )
    {
        data->state = LV_INDEV_STATE_REL;
    }
    else
    {
        data->state = LV_INDEV_STATE_PR;

        /*Set the coordinates*/
        data->point.x = touchX;
        data->point.y = touchY;

        Serial.print( "Data x " );
        Serial.println( touchX );

        Serial.print( "Data y " );
        Serial.println( touchY );
    }
}

void initUI()
{
    String LVGL_Arduino = "Hello Arduino! ";
    LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();

    Serial.println( LVGL_Arduino );
    Serial.println( "I am LVGL_Arduino" );

    lv_init();

#if LV_USE_LOG != 0
    lv_log_register_print_cb( my_print ); /* register print function for debugging */
#endif

    tft.begin();          /* TFT init */
    tft.setRotation( 0 ); /* Landscape orientation, flipped */

    lv_disp_draw_buf_init( &draw_buf, buf, NULL, screenWidth * screenHeight / 10 );

    /*Initialize the display*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init( &disp_drv );
    /*Change the following line to your display resolution*/
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register( &disp_drv );

    /*Initialize the (dummy) input device driver*/
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init( &indev_drv );
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    //indev_drv.read_cb = my_touchpad_read;
    lv_indev_drv_register( &indev_drv );


    ui_init();

    //Turn off backlight
    //pinMode(TFT_BL, OUTPUT);
    //digitalWrite(TFT_BL, LOW); 

    //You can adjust how often the UI is updated here
    //Default is 
    lv_timer_create(updateUI, 1000, NULL); 

    Serial.println( "Setup done" );
}

//To be done -- split updateUI into dynamic and static UI, updating each at different rates to save power
void updateUI(lv_timer_t *timer) 
{
  //Initialize all data to 0.
  int uvIndex = 0;
  float temperature = 0.0;
  int altitude = 0;
  int steps = 0;
  int distance = 0;
  float heading = 0.0;
  String direction = "N";
  int heartRate = 0;
  int spo2 = 0;

  //Fetch the latest sensor data
  if (xSemaphoreTake(dataMutex, portMAX_DELAY)) {
      uvIndex = (int)latestSensorData.uvData[1]; // latestSensorData intialized in main.ino
      temperature = latestSensorData.bmp280Data[0];
      altitude = (int)latestSensorData.bmp280Data[1];
      steps = latestSensorData.mpu6050Data[0];
      distance = latestSensorData.mpu6050Data[1];
      heading = latestSensorData.gy511Data; 
      heartRate = latestSensorData.max3010Data[0]; // latestSensorData intialized in main.ino
      spo2 = latestSensorData.max3010Data[1];

      xSemaphoreGive(dataMutex);  // Release the mutex
  }

  if (heading < 0) heading += 360;
  
  if (heading >= 337.5 || heading < 22.5) direction = "N";
  else if (heading >= 22.5 && heading < 67.5) direction = "NE";
  else if (heading >= 67.5 && heading < 112.5) direction = "E";
  else if (heading >= 112.5 && heading < 157.5) direction = "SE";
  else if (heading >= 157.5 && heading < 202.5) direction = "S";
  else if (heading >= 202.5 && heading < 247.5) direction = "SW";
  else if (heading >= 247.5 && heading < 292.5) direction = "W";
  else if (heading >= 292.5 && heading < 337.5) direction = "NW";

  //Update the UI
  char buf[64];

  //UV level update
  snprintf(buf, sizeof(buf), "lvl %d", uvIndex);
  lv_label_set_text(ui_UVRays, buf); //ui_UVRays is defined in ui.c

  //Temperature update
  snprintf(buf, sizeof(buf), "%.1f°C", temperature);
  lv_label_set_text(ui_BodyTemp, buf); // ui_BodyTemp is defined in ui.c

  //Altitude update
  snprintf(buf, sizeof(buf), "%d m", altitude);
  lv_label_set_text(ui_Atmosphere, buf); // Didn't change UI element to altitude yet, placeholder

  //Distance update
  snprintf(buf, sizeof(buf), "%d m", distance);
  lv_label_set_text(ui_Distance, buf); // ui_Distance is defined in ui.c

  //Step count update
  snprintf(buf, sizeof(buf), "%d steps", steps);
  lv_label_set_text(ui_Steps, buf); // ui_Steps is defined in ui.c

  //Compass update
  snprintf(buf, sizeof(buf), "Compass: %d° %s", (int)(heading+0.5), direction.c_str());
  lv_label_set_text(ui_Compass, buf); // ui_Compass is defined in ui.c

  //Heart Rate update
  if(heartRate > 0){
    snprintf(buf, sizeof(buf), "%d", heartRate);
  }else{
    snprintf(buf, sizeof(buf), "N/A");
  }
  lv_label_set_text(ui_HeartRate, buf); // ui_HeartRate is defined in ui.c

  //SPO2 update
  if(spo2 > 0){
    snprintf(buf, sizeof(buf), "%d%%", spo2);
  }else{
    snprintf(buf, sizeof(buf), "N/A");
  }
  lv_label_set_text(ui_BloodOxygen, buf); // ui_BloodOxygen is defined in ui.c
}

