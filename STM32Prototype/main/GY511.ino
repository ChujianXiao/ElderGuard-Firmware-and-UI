#include <LSM303.h>

LSM303 compass;
int heading = 0;
String direction;

void initGY511() {
  if (!compass.init()) {
    Serial.println("GY511 not found. Check wiring/power.");
    while (1);
  }
  compass.enableDefault();
}

void testCompass() {
    Serial.println("Testing compass.read...");
    compass.read();
    Serial.print("X: "); Serial.println(compass.m.x);
    Serial.print("Y: "); Serial.println(compass.m.y);
    Serial.print("Z: "); Serial.println(compass.m.z);

    if (compass.m.x == 0 && compass.m.y == 0 && compass.m.z == 0) {
        Serial.println("Magnetic field values are zero. Check sensor or wiring.");
    } else {
        Serial.println("Compass read successful.");
    }
}

void readGY511(lv_timer_t *timer) {
  compass.read();
  int16_t cal_x = compass.m.x;
  int16_t cal_y = compass.m.y;
  heading = atan2(cal_y, cal_x) * 180 / PI;
  if (heading < 0) heading += 360;

  if (heading >= 337.5 || heading < 22.5) direction = "N";
  else if (heading >= 22.5 && heading < 67.5) direction = "NE";
  else if (heading >= 67.5 && heading < 112.5) direction = "E";
  else if (heading >= 112.5 && heading < 157.5) direction = "SE";
  else if (heading >= 157.5 && heading < 202.5) direction = "S";
  else if (heading >= 202.5 && heading < 247.5) direction = "SW";
  else if (heading >= 247.5 && heading < 292.5) direction = "W";
  else if (heading >= 292.5 && heading < 337.5) direction = "NW";

  // Update the UI
  char buf[32];
  snprintf(buf, sizeof(buf), "Compass: %d° %s", heading, direction.c_str());
  lv_label_set_text(ui_Compass, buf); // ui_Compass is defined in ui.c

  Serial.print("Compass Heading: ");
  Serial.print(heading);
  Serial.print("° ");
  Serial.println(direction);
}
