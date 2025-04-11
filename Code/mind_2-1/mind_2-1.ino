#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <string.h>

//Eye info
#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels
#define X_EYE_L 30
#define X_EYE_R 85
#define Y_EYE 10
#define EYE_WIDTH 13
#define EYE_HEIGHT 44
#define EYE_AG_FILTER 10
#define EYE_SOUND_FILTER 50

// Sketch Output Settings //
#define PRINT_SPEED 50  // 50ms毎にデータを出力

//motor
#define MOTOR_POWER 255
#define MOTOR_IN4_PIN 21
#define MOTOR_IN3_PIN 20
#define MOTOR_IN1_PIN 19
#define MOTOR_IN2_PIN 18
#define MOTOR_EN_PIN 22
//mic
#define MIC_PIN 26
#define MIC_PP_DATA_NUM 1000
//illuminance
#define ILLUMINANCE_PIN 27
//speaker
#define SPEAKER_EN_PIN 6

//[ms]
unsigned long time_now;
unsigned long time_temp_m = 0;  //motor
unsigned long time_temp_s = 0;  //sound
unsigned long time_temp_e = 0;  //eye
unsigned long time_temp_eye_wink = 0;
unsigned long time_temp_eye_wink2 = 0;
unsigned long time_temp_nade = 0;
unsigned long time_temp_e_nade = 0;
unsigned long time_temp_mic = 0;
unsigned long time_temp_sup_eye = 0;  //びっくり目の時間
unsigned long time_temp_sound = 0;
unsigned long time_temp_motor = 0;
unsigned long time_temp_tun = 0;
unsigned long time_temp_tun_move = 0;
unsigned long time_temp_tun_turn_1 = 0;
unsigned long time_temp_tun_turn_2 = 0;
//[μs]
unsigned long time_now_m;
unsigned long time_temp_imu;

unsigned int random_m = 0;  //motor
unsigned int random_m2 = 0;
unsigned int random_s = 1;  //sound
unsigned int random_s2 = 1;
unsigned int random_e1 = 0;  //eye
unsigned int random_e2 = 0;
unsigned int nade_state = 0;  //0:通常，1:上部に手あり，2:指定時間以上手あり

float mic_pp[MIC_PP_DATA_NUM] = { 0 };  //peak to peak data array

float Eye_wink_h = 28.0;                       //瞬き時の目の高さ※値が大きいほど下になる．
float Eye_wink_val = 1.0 + Eye_wink_h / 44.0;  //下瞼の挙動を再現するための係数．
float roll = 0, pitch = 0, yaw = 0;
float tuntun_yaw_temp = 0;
float tuntun_move_yaw_temp = 0;

int Eye_wink_spd = 7;  //瞬きの速さ．
int y = Eye_wink_spd;
int Eye_wink_time;
int random_time_eye_wink = 2000;
int nade_eye_width = 0;
int mic_val_max = 0;
int mic_val_min = 0;
int temp_mic_val = 0;
int mic_count = 0;
int mic_ans = 0;
int mic_temp = 0;
int eye_sound_temp = 0;
int eye_agx_temp = 0, eye_agy_temp = 0;

bool eye_wink_check = false;
bool motor_active = false;
bool sound_action = false;
bool mic_val_positive = false;
bool tuntun_check = false;
bool tuntun_move_check = false;
bool eye_sup = false;
bool tuntun_turn_1 = false;
bool tuntun_turn_2 = false;

static int Eye_agx_array[EYE_AG_FILTER] = { 0 };
static int Eye_agy_array[EYE_AG_FILTER] = { 0 };
static int Eye_sound_array[EYE_SOUND_FILTER] = { 0 };

uint16_t BNO055_SAMPLERATE_DELAY_MS = 100;
double acc_ary[3] = { 0 };
double gyro_ary[3] = { 0 };
double acc_ary_temp[3] = { 0 };
double gyro_ary_temp[3] = { 0 };

//MbedI2C myi2c(p20, p21);  // I2C SDA:GP20, SCL:GP21
MbedI2C myi2c(p4, p5);

Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28, &myi2c);
Adafruit_SSD1306 OLED(128, 64, &myi2c, -1);


void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  bno.begin();
  delay(100);

  OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // 内部チャージ回路をON
  delay(100);
  OLED.setTextColor(SSD1306_WHITE);        //set text to white
  OLED.clearDisplay();
  OLED.display();
  delay(100);

  digitalWrite(MOTOR_EN_PIN, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  time_now = millis();
  eye_sup = false;

  sensors_event_t angVelocityData, accelerometerData;
  bno.getEvent(&angVelocityData, Adafruit_BNO055::VECTOR_GYROSCOPE);
  bno.getEvent(&accelerometerData, Adafruit_BNO055::VECTOR_ACCELEROMETER);

  inputEvent(&angVelocityData);
  inputEvent(&accelerometerData);

  Serial.print(acc_ary[0]); Serial.print(","); Serial.print(acc_ary[1]); Serial.print(","); Serial.println(acc_ary[2]);
  Serial.print(gyro_ary[0]); Serial.print(","); Serial.print(gyro_ary[1]); Serial.print(","); Serial.println(gyro_ary[2]);

  //EYE
  switch (Nade()) {
    case 0:
      //RandomMove();
      //tuntun_move(tuntun(roll, pitch));

      if (nade_eye_width > 0) {
        if (millis() - time_temp_e_nade > 2000) {
          nade_eye_width -= 4;
          if (nade_eye_width >= 0) Eye(-nade_eye_width / 2, 26, nade_eye_width, -40);
          else nade_eye_width = 0;
        }
      } else if (Mic() == true && (motor_active != true && sound_action != true)) {
        eye_sup = true;
        Eye(-10, 5, 20, -10);
        //RandomSound();
      } else {
        Eye_wink();
        //if (Huru() == true && motor_active != true) RandomSound();
      }
      break;
    case 1:
      Eye(-nade_eye_width / 2, 26, nade_eye_width, -40);
      if (nade_eye_width < 20) nade_eye_width++;
      //RandomSound();
      time_temp_e_nade = millis();
      break;
    case 2:
      OLED.clearDisplay();
      OLED.display();
      nade_eye_width = 0;
      break;
    default:
      Serial.println("Nadenade() function error!");
      break;
  }

  if (sound_action == true) {
    if (time_now - time_temp_sound >= 2000) sound_action = false;
  } else time_temp_sound = time_now;

  if (motor_active == true) {
    if (time_now - time_temp_motor >= 5000) motor_active = false;
  } else time_temp_motor = time_now;

  delay(10);
}

int Amplitude(int data) {
  if (temp_mic_val != 0) {
    if (data - temp_mic_val >= 0) {
      if (mic_val_positive != true) {
        mic_val_min = temp_mic_val;
        mic_count++;
      }
      mic_val_positive = true;
    } else {
      if (mic_val_positive != true && sound_action != true) {
        mic_val_max = temp_mic_val;
        mic_count++;
      }
      mic_val_positive = false;
    }
    temp_mic_val = data;
  } else temp_mic_val = data;

  if (mic_count == 2) {
    mic_ans = mic_val_max - mic_val_min;
    mic_count = 0;
  }

  return mic_ans;
}

bool Mic() {
  float ans;
  float sum = 0;

  for (int i = MIC_PP_DATA_NUM - 2; i >= 0; i--) {
    mic_pp[i + 1] = mic_pp[i];
    sum += mic_pp[i];
  }

  mic_temp = mic_pp[0];
  mic_pp[0] = Amplitude(analogRead(MIC_PIN));
  sum += mic_pp[0];

  ans = sum / MIC_PP_DATA_NUM;

  if (motor_active == true || sound_action == true) mic_pp[0] = ans;
  /*
    Serial.print(mic_pp[0]); Serial.print(",");
    Serial.println(ans * 10);
    //*/
  if (mic_pp[0] > ans * 10 && random(100) < 30) {
    time_temp_mic = millis();
    return true;
  } else {
    if (time_now - time_temp_mic >= time_temp_sup_eye) {
      time_temp_sup_eye = random(8, 16) * 100;
      return false;
    } else return true;
  }
}

bool Huru() {
  bool huru = false;
  int sum_a = 0;
  int sum_g = 0;

  sum_a = abs(acc_ary[0]) + abs(acc_ary[1]) + abs(acc_ary[2]);
  sum_g = abs(gyro_ary[0]) + abs(gyro_ary[1]) + abs(gyro_ary[2]);
  if (sum_a >= 20 || sum_g >= 5) huru = true;

  //Serial.print("sum_a: ");Serial.println(sum_a);
  //Serial.print("sum_g: ");Serial.println(sum_g);
  return huru;
}

int Nade() {
  if (analogRead(ILLUMINANCE_PIN) <= 300) {  //基本的に，センサ上に手をのせたら0になるけど．．．なぜか暗いはずの鞄の中で起きちゃうので要調整
    if (millis() - time_temp_nade > 7000) nade_state = 2;
    else nade_state = 1;
    Serial.println(millis() - time_temp_nade);

    if (Huru() && nade_state != 2) time_temp_nade = millis();  //nade_state != 2は一時的な処理．持ち運び時に目が覚めてもね．．．
  } else {
    time_temp_nade = millis();
    nade_state = 0;
  }
  Serial.println(nade_state);
  return nade_state;
}

void Eye(int dX_point, int dY_point, int dX_size, int dY_size) {
  //加速度(acc_ary[0], acc_ary[2])＆角速度(gyro_ary[2], gyro_ary[0])を目の上下動作に反映
  int eye_agx, eye_agy;
  eye_agx = round((acc_ary[0] - acc_ary_temp[0]) * 100 + (gyro_ary[2] - gyro_ary_temp[2]) * 0.5);
  eye_agy = round((acc_ary[2] - acc_ary_temp[2]) * 100 + (gyro_ary[0] - gyro_ary_temp[0]) * 1);

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

  //音を目の幅に反映
  int eye_sound;
  eye_sound = round((float)(abs(mic_pp[0] - mic_temp)) / 1);
  /*
    for (int n = 0; n < EYE_SOUND_FILTER - 1; n++) Eye_sound_array[n] = Eye_sound_array[n + 1];
    Eye_sound_array[EYE_SOUND_FILTER - 1] = eye_sound;

    eye_sound = 0;
    for (int n = 0; n < EYE_SOUND_FILTER; n++) eye_sound += Eye_sound_array[n];
    eye_sound = eye_sound / EYE_SOUND_FILTER;
    //*/
  ///*
  float eye_sound_filter = 0.8;
  eye_sound = round((1.0 - eye_sound_filter) * (float)eye_sound + eye_sound_filter * (float)eye_sound_temp);
  eye_sound_temp = eye_sound;
  eye_sound -= 2;  //0にならないので，無理矢理補正
  //*/

  if (eye_sup != true) {
    eye_sound *= 2;

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

  OLED.clearDisplay();

  OLED.fillRect(X_EYE_L + dX_point, Y_EYE + dY_point, EYE_WIDTH + dX_size, EYE_HEIGHT + dY_size, WHITE);
  OLED.fillRect(X_EYE_R + dX_point, Y_EYE + dY_point, EYE_WIDTH + dX_size, EYE_HEIGHT + dY_size, WHITE);

  OLED.display();
}

void Eye_wink() {
  if (time_now - time_temp_eye_wink >= random_time_eye_wink) {
    if (y <= Eye_wink_h && eye_wink_check != true) {
      Eye(0, y, 0, -y * Eye_wink_val);
      y += Eye_wink_spd;
    } else if (eye_wink_check != true) {
      eye_wink_check = true;
      y = Eye_wink_h;

      int n = random(100);
      Eye_wink_time = 0;
      //瞬きの閉じた状態が長時間続くなんて，中々ないよね？ってやつ．
      if (n > 95) Eye_wink_time = 5000;
      else if (n > 80) Eye_wink_time = 1500;
      time_temp_eye_wink2 = millis();
    }

    if (time_now - time_temp_eye_wink2 >= Eye_wink_time && eye_wink_check != false) {
      if (y >= 0) {
        Eye(0, y, 0, -y * Eye_wink_val);
        y -= Eye_wink_spd;
      } else {
        y = Eye_wink_spd;
        eye_wink_check = false;
        time_temp_eye_wink = millis();
        random_time_eye_wink = random(10) * 1000;
      }
    } else if (eye_wink_check != false) {
      Eye(0, Eye_wink_h - 2, 0, -40);
    }
  } else Eye(0, 0, 0, 0);  //目を開いた状態（デフォルト時）
}

void Move(){
  int motor_power_l, motor_power_r;
  /*
  motor_power_l = ;
  motor_power_r = ;
  */
  Motor(motor_power_l, motor_power_r);
  
}

void Motor(int motor_power_l, int motor_power_r) {
  unsigned int motor_power_min = 50;
  //left motor
  if (motor_power_l > motor_power_min) {
    analogWrite(MOTOR_IN4_PIN, motor_power_l);
    analogWrite(MOTOR_IN3_PIN, 0);
  }
  else if (abs(motor_power_l) <= motor_power_min) {
    analogWrite(MOTOR_IN4_PIN, 0);
    analogWrite(MOTOR_IN3_PIN, 0);
  }
  else {
    analogWrite(MOTOR_IN4_PIN, 0);
    analogWrite(MOTOR_IN3_PIN, -motor_power_l);
  }
  //right motor
  if (motor_power_r > motor_power_min) {
    analogWrite(MOTOR_IN1_PIN, motor_power_r);
    analogWrite(MOTOR_IN2_PIN, 0);
  }
  else if (abs(motor_power_r) <= motor_power_min) {
    analogWrite(MOTOR_IN1_PIN, 0);
    analogWrite(MOTOR_IN2_PIN, 0);
  }
  else {
    analogWrite(MOTOR_IN1_PIN, 0);
    analogWrite(MOTOR_IN2_PIN, -motor_power_r);
  }

  delay(10);
}

void inputEvent(sensors_event_t* event) {
  double x = -1000000, y = -1000000, z = -1000000;  //dumb values, easy to spot problem
  if (event->type == SENSOR_TYPE_ACCELEROMETER) {
    memcpy(acc_ary_temp, acc_ary, sizeof(double) * 3);
    acc_ary[0] = event->acceleration.x;
    acc_ary[1] = event->acceleration.y;
    acc_ary[2] = event->acceleration.z;
  } else if (event->type == SENSOR_TYPE_GYROSCOPE) {
    memcpy(gyro_ary_temp, gyro_ary, sizeof(double) * 3);
    gyro_ary[0] = event->gyro.x;
    gyro_ary[1] = event->gyro.y;
    gyro_ary[2] = event->gyro.z;
  } else {
    //Serial.print("Unk:");
  }
}
