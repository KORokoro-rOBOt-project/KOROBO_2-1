# Code
> [!NOTE]
> **Arduino IDE**を用いて，書き込みます．ボードマネージャーは，[**arduino-pico**](https://github.com/earlephilhower/arduino-pico)を利用します．

<details>
<summary>書き込み手順（準備中）</summary>
準備中．
</details>

## mind_2-1
〈第2.1世代〉ころボ の基本プログラム

<details>
<summary>プログラム全体</summary>
  
```cpp
#include "KoroboLib_2_1.h"

KoroboLib_2_1 korobo;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  korobo.begin();
  delay(10);
}

void loop() {
  // put your main code here, to run repeatedly:
  korobo.init();
  if (korobo.Sleep(ALL)) {
    korobo.Eye(ALL);
    korobo.Voice(ALL);
    korobo.Move();
  }
}
```

</details>

1. **ライブラリの読み込み**\
    `KoroboLib_2_1 korobo;`の`korobo`の部分は，任意の単語を指定可能．
   ただし，それ以降の`korobo.begin()`のような関数呼び出し時は，指定した単語に変更する必要がある．
    ```cpp
    #include "KoroboLib_2_1.h"
    
    KoroboLib_2_1 korobo;
    ```  
2. **初回処理**\
    <a name="begin"></a>
    `korobo.begin()`は，必須．
    ```cpp
    void setup() {
      // put your setup code here, to run once:
      Serial.begin(9600);
      korobo.begin();
      delay(10);
    }
    ```
3. **ループ処理**\
    <a name="init"></a>
    `korobo.init()`を一番上に記述．
    ```cpp
    void loop() {
      // put your main code here, to run repeatedly:
      korobo.init();
      if (korobo.Sleep(ALL)) {
        korobo.Eye(ALL);
        korobo.Voice(ALL);
        korobo.Move();
      }
    }
    ```

## KoroboLib_2_1
〈第2.1世代〉ころボ を動作させるにあたって必要となるライブラリ
- **`void begin()`** : 
各モジュールのセットアップ処理関数（[**mind_2-1** / 2. 初回処理](#begin)を参照）．
- **`void init()`** : 
ループ処理毎の初期化処理関数（[**mind_2-1** / 3. ループ処理](#init)を参照）．
- **`void Imu_getData()`** : 
記述した時点の9軸センサ（加速度・角速度・磁気）の値を取得できる．
  > 1回のループ処理中に複数実行しても，初めに実行した際の値が出力される．
  <table>
    <thead>
      <tr>
        <th align="center"><strong>変数</strong></th>
        <th align="center"><strong>内容</strong></th>
      </tr>
    </thead>
    <tbody>
      <tr>
        <td><code>korobo_acc.x()</code></td>
        <td>加速度（x軸）</td>
      </tr>
      <tr>
        <td><code>korobo_acc.y()</code></td>
        <td>加速度（y軸）</td>
      </tr>
      <tr>
        <td><code>korobo_acc.z()</code></td>
        <td>加速度（z軸）</td>
      </tr>
      <tr>
        <td><code>korobo_gyro.x()</code></td>
        <td>角速度（x軸）</td>
      </tr>
      <tr>
        <td><code>korobo_gyro.y()</code></td>
        <td>角速度（y軸）</td>
      </tr>
      <tr>
        <td><code>korobo_gyro.z()</code></td>
        <td>角速度（z軸）</td>
      </tr>
      <tr>
        <td><code>korobo_mag.x()</code></td>
        <td>磁気（x軸）</td>
      </tr>
      <tr>
        <td><code>korobo_mag.y()</code></td>
        <td>磁気（y軸）</td>
      </tr>
      <tr>
        <td><code>korobo_mag.z()</code></td>
        <td>磁気（z軸）</td>
      </tr>
    </tbody>
  </table>

    <details>
    <summary>使用例</summary>

    ```cpp
    void loop() {
      // put your main code here, to run repeatedly:
      korobo.init();

      float acc_x, acc_y, acc_z;
      korobo.Imu_getData();
      acc_x = korobo.korobo_acc.x();
      acc_y = korobo.korobo_acc.y();
      acc_z = korobo.korobo_acc.z();
    }
    ```
    </details>

- **`int AmbientLight_getData()`** :
上部光センサの値（0~1023）を取得できる．
- **`int Mic_getData()`** :
マイクセンサの値（0~1023）を取得できる．
- **`void Eye(3-pattern)`**
    ```C++
    void Eye(unsigned int num)
    ```
  > 瞳の表示および，瞳が表現する情報を選択できる．
  <table>
    <thead>
      <tr>
        <th align="center">unsigned int num = </th>
        <th align="center">内容</th>
      </tr>
    </thead>
    <tbody>
      <tr>
        <td align="center"><code>SOUND</code></td>
        <td>音情報を利用する (= 2)</td>
      </tr>
      <tr>
        <td align="center"><code>IMU</code></td>
        <td>加速度・角速度情報を利用する (= 3)</td>
      </tr>
      <tr>
        <td align="center"><code>LIGHT</code></td>
        <td>光情報を利用する (= 5)</td>
      </tr>
      <tr>
        <td align="center"><code>ALL</code></td>
        <td>すべての情報を利用する (= 30) <b>※推奨</b></td>
      </tr>
    </tbody>
  </table>
  
    ```C++
    void Eye(int dX_point_u, int dY_point_u, int dX_size_u, int dY_size_u)
    ```
  > 瞳の表示および，瞳の各種パラメータのデフォルト値へ任意の操作を加えられる．
  <table>
    <thead>
      <tr>
        <th align="center">変数名</th>
        <th align="center">内容</th>
        <th align="center">値の範囲</th>
      </tr>
    </thead>
    <tbody>
      <tr>
        <td align="center"><code>int dX_point_u</code></td>
        <td>瞳のX座標</td>
        <td align="center">?~?</td>
      </tr>
      <tr>
        <td align="center"><code>int dY_point_u</code></td>
        <td>瞳のY座標</td>
        <td align="center">?~?</td>
      </tr>
      <tr>
        <td align="center"><code>int dX_size_u</code></td>
        <td>瞳の幅</td>
        <td align="center">?~?</td>
      </tr>
      <tr>
        <td align="center"><code>int dY_size_u</code></td>
        <td>瞳の高さ</td>
        <td align="center">?~?</td>
      </tr>
    </tbody>
  </table>

    ```C++
    void Eye(int dX_point_u, int dY_point_u, int dX_size_u, int dY_size_u, unsigned int num)
    ```
  > 上記，2項目の組み合わせ．

> [!NOTE]
> 現状，左右の瞳の間隔や左右個別の操作は行えません．
- **`void Motor(int motor_power_l, int motor_power_r)`** :
左右のモータに任意の操作量を加えられる．
  <table>
    <thead>
      <tr>
        <th align="center">変数</th>
        <th align="center">内容</th>
        <th align="center">値の範囲</th>
      </tr>
    </thead>
    <tbody>
      <tr>
        <td align="center"><code>int motor_power_l</code></td>
        <td>左モータの操作量</td>
        <td align="center">0 ~ 255</td>
      </tr>
      <tr>
        <td align="center"><code>int motor_power_r</code></td>
        <td>右モータの操作量</td>
        <td align="center">0 ~ 255</td>
      </tr>
    </tbody>
  </table>

- **`void Move()`** : 
デフォルトの行動関数．
x, y軸の加速度を利用し，姿勢を水平な状態へ維持するようタイヤが動く．
  > この挙動とユーザーによる任意の操作を，同時行えるようにする予定．
- **`boolean Voice_state()`** : 
ころボが発話可能な状態か確認できる．
- **`void Voice_send(char Talk[20])`** : 
任意の文字列を発話できる．
文字列の文法は，[AquesTalk pico LSI](https://www.a-quest.com/products/aquestalkpicolsi.html)のデータシートを参照．
  > <code>Voice_state()</code>を内部に組み込んでいる．
- **`void Voice(unsigned int num)`** : 
デフォルトの発話関数．
発話が表現する情報を選択できる．
  <table>
    <thead>
      <tr>
        <th align="center">unsigned int num = </th>
        <th align="center">内容</th>
      </tr>
    </thead>
    <tbody>
      <tr>
        <td align="center"><code>SOUND</code></td>
        <td>音情報を利用する (= 2)</td>
      </tr>
      <tr>
        <td align="center"><code>IMU</code></td>
        <td>加速度・角速度情報を利用する (= 3)</td>
      </tr>
      <tr>
        <td align="center"><code>LIGHT</code></td>
        <td>光情報を利用する (= 5)</td>
      </tr>
      <tr>
        <td align="center"><code>ALL</code></td>
        <td>すべての情報を利用する (= 30) <b>※推奨</b></td>
      </tr>
    </tbody>
  </table>

- **`boolean Sleep(unsigned int num)`** :
スリープ機能関数．
スリープへ移行する条件の情報を選択できる．
  <table>
    <thead>
      <tr>
        <th align="center">unsigned int num = </th>
        <th align="center">内容</th>
      </tr>
    </thead>
    <tbody>
      <tr>
        <td align="center"><code>SOUND</code></td>
        <td>音情報を利用する (= 2)</td>
      </tr>
      <tr>
        <td align="center"><code>IMU</code></td>
        <td>加速度・角速度情報を利用する (= 3)</td>
      </tr>
      <tr>
        <td align="center"><code>LIGHT</code></td>
        <td>光情報を利用する (= 5)</td>
      </tr>
      <tr>
        <td align="center"><code>ALL</code></td>
        <td>すべての情報を利用する (= 30) <b>※推奨</b></td>
      </tr>
    </tbody>
  </table>
  
    <details>
    <summary>使用例</summary>

    ```cpp
    void loop() {
      // put your main code here, to run repeatedly:
      korobo.init();
      if (korobo.Sleep(ALL)) {
        //スリープ中に行わない処理...
      }
      //スリープ中にも行う処理...
    }
    ```
    </details>

> [!IMPORTANT]
> <b>KoroboLib_2_1</b>は，複数の既存ライブラリに依存しています．
> 事前に，それらのライブラリをインストールしてください[^1][^2][^3][^4]．
> また，各ライブラリには**異なるライセンス**が付与されています．
> これらのライブラリを独自に改変，または ころボ のライブラリへ組み込むといった場合は，十分にご確認ください．
[^1]: https://github.com/adafruit/Adafruit-GFX-Library
[^2]: https://github.com/adafruit/Adafruit_SSD1306
[^3]: https://github.com/adafruit/Adafruit_Sensor
[^4]: https://github.com/adafruit/Adafruit_BNO055
