#include "KoroboLib_2_1.h"

// I2C SDA:GP4, SCL:GP5
MbedI2C myi2c(p4, p5); 
// 9-axis sensor
Adafruit_BNO055 bno = Adafruit_BNO055(-1, 0x28, &myi2c);
// OLED
Adafruit_SSD1306 oled(128, 64, &myi2c, -1);

KoroboLib_2_1::KoroboLib_2_1() {

}

KoroboLib_2_1::~KoroboLib_2_1() {

}

void KoroboLib_2_1::begin(){
  bno.begin();
  delay(100);

  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  delay(100);
  oled.setTextColor(SSD1306_WHITE);
  oled.clearDisplay();
  oled.display();
  delay(100);
}

void KoroboLib_2_1::Imu_getData(){
  korobo_acc_temp = korobo_acc;
  korobo_gyro_temp = korobo_gyro;
  korobo_mag_temp = korobo_mag;
  korobo_acc = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
  korobo_gyro = bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
  korobo_mag = bno.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);
}

int KoroboLib_2_1::AmbientLight_getData(){
  return analogRead(AMBIENT_LIGHT_PIN);
}

int KoroboLib_2_1::Mic_getData(){
  return abs(analogRead(MIC_PIN));
}

int KoroboLib_2_1::SoundAmplitude(int data) {
  if (mic_val_temp != 0) {
    if (data - mic_val_temp >= 0) {
      if (mic_val_positive != true) {
        mic_val_min = mic_val_temp;
        mic_count++;
      }
      mic_val_positive = true;
    } 
    else {
      if (mic_val_positive != true) {
        mic_val_max = mic_val_temp;
        mic_count++;
      }
      mic_val_positive = false;
    }
    mic_val_temp = data;
  } else mic_val_temp = data;

  if (mic_count == 2) {
    mic_ans = mic_val_max - mic_val_min;
    mic_count = 0;
  }

  return mic_ans;
}

void KoroboLib_2_1::Eye_point_size_init(){
  dX_point = 0;
  dY_point = 0;
  dX_size = 0;
  dY_size = 0;
}

void KoroboLib_2_1::Eye_sound() {
  int eye_sound;
  int sound_amp = SoundAmplitude(Mic_getData());
  eye_sound = abs(sound_amp - sound_amp_temp);
  sound_amp_temp = sound_amp;

  float eye_sound_filter = 0.8;
  eye_sound = round((1.0 - eye_sound_filter) * (float)eye_sound + eye_sound_filter * (float)eye_sound_temp);
  eye_sound_temp = eye_sound;
  eye_sound -= 3;

  Serial.println(eye_sound);

  //目の横幅反映
  int eye_sound_x_limit = 12;
  if (eye_sound > eye_sound_x_limit) {
    dX_point -= eye_sound_x_limit / 2;
    dX_size += eye_sound_x_limit;
  } else {
    dX_point -= eye_sound / 2;
    dX_size += eye_sound;
  }
  //目の縦幅反映
  int eye_sound_y_limit = 24;
  eye_sound *= 2;
  if (EYE_HEIGHT + dY_size - eye_sound > 4 || EYE_HEIGHT + dY_size - eye_sound_y_limit > 4) {
    if (eye_sound > eye_sound_y_limit) {
      dY_point += eye_sound_y_limit / 2;
      dY_size -= eye_sound_y_limit;
    } else {
      dY_point += eye_sound / 2;
      dY_size -= eye_sound;
    }
  }
}

void KoroboLib_2_1::Eye_imu() {
  //加速度(acc_ary[0], acc_ary[2])＆角速度(gyro_ary[2], gyro_ary[0])を目の上下動作に反映
  int eye_agx, eye_agy;
  eye_agx = round((korobo_acc.x() - korobo_acc_temp.x()) * 100 + (korobo_gyro.z() - korobo_gyro_temp.z()) * 0.5);
  eye_agy = round((korobo_acc.z() - korobo_acc_temp.z()) * 100 + (korobo_gyro.x() - korobo_gyro_temp.x()) * 1);

  int eye_ag_filter = 0.8;
  eye_agx = (1 - eye_ag_filter) * eye_agx + eye_ag_filter * eye_agx_temp;
  eye_agy = (1 - eye_ag_filter) * eye_agy + eye_ag_filter * eye_agy_temp;
  eye_agx_temp = eye_agx;
  eye_agy_temp = eye_agy;

  ///*
  for (int n = 0; n < EYE_AG_FILTER - 1; n++) {
    Eye_agx_array[n] = Eye_agx_array[n + 1];
    Eye_agy_array[n] = Eye_agy_array[n + 1];
  }
  Eye_agx_array[EYE_AG_FILTER - 1] = eye_agx;
  Eye_agy_array[EYE_AG_FILTER - 1] = eye_agy;

  eye_agx = 0;
  eye_agy = 0;
  for (int n = 0; n < EYE_AG_FILTER; n++) {
    eye_agx += Eye_agx_array[n];
    eye_agy += Eye_agy_array[n];
  }
  eye_agx = eye_agx / EYE_AG_FILTER;
  eye_agy = eye_agy / EYE_AG_FILTER;
  //*/

  int eye_agx_limit = 10;
  if (eye_agx > eye_agx_limit) dX_point += eye_agx_limit;
  else if (eye_agx < -eye_agx_limit) dX_point += -eye_agx_limit;
  else dX_point += eye_agx;

  int eye_agy_limit = 5;
  if (eye_agy > eye_agy_limit) dY_point += eye_agy_limit;
  else if (eye_agy < -eye_agy_limit) dY_point += -eye_agy_limit;
  else dY_point += eye_agy;
}

void KoroboLib_2_1:: Eye_light() {

}

void KoroboLib_2_1:: Eye_wink() {

}

void KoroboLib_2_1::Eye(unsigned int num) {
  Eye_point_size_init();

  if (num % 2 == 0) Eye_sound();
  if (num % 3 == 0) Eye_imu();
  if (num % 5 == 0) Eye_light();
  if (num % 7 == 0) Eye_wink();

  oled.clearDisplay();

  oled.fillRect(X_EYE_L + dX_point, Y_EYE + dY_point, EYE_WIDTH + dX_size, EYE_HEIGHT + dY_size, WHITE);
  oled.fillRect(X_EYE_R + dX_point, Y_EYE + dY_point, EYE_WIDTH + dX_size, EYE_HEIGHT + dY_size, WHITE);

  oled.display();
}

void KoroboLib_2_1::Eye(int dX_point_u, int dY_point_u, int dX_size_u, int dY_size_u) {
  dX_point = dX_point_u;
  dY_point = dY_point_u;
  dX_size = dX_size_u;
  dY_size = dY_size_u;

  oled.clearDisplay();

  oled.fillRect(X_EYE_L + dX_point, Y_EYE + dY_point, EYE_WIDTH + dX_size, EYE_HEIGHT + dY_size, WHITE);
  oled.fillRect(X_EYE_R + dX_point, Y_EYE + dY_point, EYE_WIDTH + dX_size, EYE_HEIGHT + dY_size, WHITE);

  oled.display();
}

void KoroboLib_2_1::Eye(int dX_point_u, int dY_point_u, int dX_size_u, int dY_size_u, unsigned int num) {
  Eye_point_size_init();

  if (num % 2 == 0) Eye_sound();
  if (num % 3 == 0) Eye_imu();
  if (num % 5 == 0) Eye_light();
  if (num % 7 == 0) Eye_wink();

  dX_point += dX_point_u;
  dY_point += dY_point_u;
  dX_size += dX_size_u;
  dY_size += dY_size_u;

  oled.clearDisplay();

  oled.fillRect(X_EYE_L + dX_point, Y_EYE + dY_point, EYE_WIDTH + dX_size, EYE_HEIGHT + dY_size, WHITE);
  oled.fillRect(X_EYE_R + dX_point, Y_EYE + dY_point, EYE_WIDTH + dX_size, EYE_HEIGHT + dY_size, WHITE);

  oled.display();
}

void KoroboLib_2_1::Motor(int motor_power_l, int motor_power_r) {
  //left motor
  if (motor_power_l > MOTOR_POWER_MIN) {
    analogWrite(MOTOR_IN4_PIN, motor_power_l);
    analogWrite(MOTOR_IN3_PIN, 0);
  }
  else if (abs(motor_power_l) <= MOTOR_POWER_MIN) {
    analogWrite(MOTOR_IN4_PIN, 0);
    analogWrite(MOTOR_IN3_PIN, 0);
  }
  else {
    analogWrite(MOTOR_IN4_PIN, 0);
    analogWrite(MOTOR_IN3_PIN, -motor_power_l);
  }
  //right motor
  if (motor_power_r > MOTOR_POWER_MIN) {
    analogWrite(MOTOR_IN1_PIN, motor_power_r);
    analogWrite(MOTOR_IN2_PIN, 0);
  }
  else if (abs(motor_power_r) <= MOTOR_POWER_MIN) {
    analogWrite(MOTOR_IN1_PIN, 0);
    analogWrite(MOTOR_IN2_PIN, 0);
  }
  else {
    analogWrite(MOTOR_IN1_PIN, 0);
    analogWrite(MOTOR_IN2_PIN, -motor_power_r);
  }

  delay(10);
}
