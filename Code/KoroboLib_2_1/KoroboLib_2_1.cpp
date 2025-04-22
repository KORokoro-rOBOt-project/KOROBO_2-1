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
  //RC-Filter
  eye_sound = round((1 - RC_FILTER) * eye_sound + RC_FILTER * eye_sound_temp);
  eye_sound_temp = eye_sound;
  eye_sound -= 3;

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
  Imu_getData();
  int eye_agx, eye_agy;
  eye_agx = round((korobo_acc.x() - korobo_acc_temp.x()) * 100 + (korobo_gyro.z() - korobo_gyro_temp.z()) * 0.5);
  eye_agy = round((korobo_acc.z() - korobo_acc_temp.z()) * 100 + (korobo_gyro.x() - korobo_gyro_temp.x()) * 1);
  //RC-Filter
  eye_agx = round((1 - RC_FILTER) * eye_agx + RC_FILTER * eye_agx_temp);
  eye_agy = round((1 - RC_FILTER) * eye_agy + RC_FILTER * eye_agy_temp);
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
  int eye_al_val = AmbientLight_getData();
  int eye_al_val_ave = 0;
  int eye_al_dx, eye_al_dy;
  //RC-Filter
  eye_al_val = (1 - RC_FILTER) * eye_al_val + RC_FILTER * eye_al_val_temp;
  //Average-Filter
  for (int i = FILTER_SAMPLE - 1; i > 0; i--) Eye_al_array[i] = Eye_al_array[i - 1];
  Eye_al_array[0] = eye_al_val;
  for (int i = 0; i < FILTER_SAMPLE; i++) eye_al_val_ave += Eye_al_array[i];
  eye_al_val_ave /= FILTER_SAMPLE;

  eye_al_dx = abs(round((eye_al_val - eye_al_val_ave) * 0.03));
  eye_al_dy = abs(round((eye_al_val_ave - eye_al_val) * 0.05));

  dX_size += eye_al_dx;
  dX_point -= eye_al_dx / 2;
  dY_size -= eye_al_dy;
  dY_point += eye_al_dy / 2;

  eye_al_val_temp = eye_al_val;
}

/*
void KoroboLib_2_1:: Eye_wink_hoge() {

}
*/

void KoroboLib_2_1::Eye(unsigned int num) {
  Eye_point_size_init();

  if (num % 2 == 0) Eye_sound();
  if (num % 3 == 0) Eye_imu();
  if (num % 5 == 0) Eye_light();
  //if (num % 7 == 0) Eye_wink_hoge();

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
  //if (num % 7 == 0) Eye_wink_hoge();

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

void KoroboLib_2_1::Move(){

}

void KoroboLib_2_1::Voice(){
  int voice_mic, voice_imu, voice_light;
  voice_mic = Mic_getData();
  Imu_getData();
  voice_imu = round((abs(korobo_acc.x()) + abs(korobo_acc.y()) + abs(korobo_acc.z())) / 3 + (abs(korobo_gyro.x()) + abs(korobo_gyro.y()) + abs(korobo_gyro.z())) / 3);
  voice_light = AmbientLight_getData();

  int voice_mic_d, voice_imu_d, voice_light_d, voice_d_sum, voice_d_sum_temp;
  voice_mic_d = abs(voice_mic - voice_mic_temp);
  voice_light_d = abs(voice_light - voice_light_temp);
  voice_d_sum = voice_mic_d + voice_imu + voice_light_d;
  voice_d_sum = round((1 - RC_FILTER) * voice_d_sum + RC_FILTER * voice_d_sum_temp);
  voice_d_sum *= 10;

  /*10(DEC) -> 2(BIN)*/
  
  String voice_code, voice = "";
  voice_code = String(voice_d_sum, BIN);

  int voice_code_len = voice_code.length();
  if (voice_code_len <= 16){
    for (int i = 0; i < 16 - voice_code_len; i++)  voice_code.concat("0");
  }
  else  voice_code = voice_code.substring(0, 16);

  //00:n, 01:ko, 10:ro, 11:bo
  for (int i = 2; i < voice_code.length() / 2; i++){
    String voice_code_2words = voice_code.substring(i * 2, (i * 2) + 2);
    if (voice.length() > 0 && voice_code_2words == "00"){
      voice.concat("n");
      break;
    }
    else if (voice_code_2words == "01") voice.concat("ko");
    else if (voice_code_2words == "10") voice.concat("ro");
    else if (voice_code_2words == "11") voice.concat("bo");
  }

  voice_mic_temp = voice_mic;
  voice_light_temp = voice_light;
  voice_d_sum_temp = voice_d_sum;

  if (voice.length() > 4){
    //*
    Serial.print(voice);Serial.print(", \t\t");
    Serial.print(voice_code);Serial.print(", \t");
    Serial.println(voice_d_sum);
    //*/
  }
}