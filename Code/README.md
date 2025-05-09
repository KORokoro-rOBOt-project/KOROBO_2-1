# Code
## mind_2-1
〈第2.1世代〉ころボ の基本プログラム
> [!NOTE]
> **Arduino IDE**を用いて，書き込みます．
<details>
<summary>書き込み手順</summary>
準備中．
</details>

## KoroboLib_2_1
〈第2.1世代〉ころボ を動作させるにあたって必要となるライブラリ．
### - void begin()
### - void init()
### - void Imu_getData()
### - int AmbientLight_getData()
### - int Mic_getData()
### - void Eye(3-pattern)
- **Eye(unsigned int num) :**
  - `unsigned int num` = "SOUND", "IMU", "LIGHT" or "ALL"
    > SOUND(=2): 音情報を瞳の挙動に利用する．<br>
    > IMU(=3): 加速度・角速度情報を瞳の挙動に利用する．<br>
    > LIGHT(=5): 光情報を瞳の挙動に利用する．<br>
    > ALL(=30): すべての情報を瞳の挙動に利用する．
- **Eye(int dX_point_u, int dY_point_u, int dX_size_u, int dY_size_u) :**
    <table>
    <thead>
      <tr>
        <th align="center">変数名</th>
        <th align="center">説明</th>
        <th align="center">値の範囲</th>
      </tr>
    </thead>
    <tbody>
      <tr>
        <td><code>int dX_point_u</code></td>
        <td>瞳のX座標</td>
        <td align="center">?~?</td>
      </tr>
      <tr>
        <td><code>int dY_point_u</code></td>
        <td>瞳のY座標</td>
        <td align="center">?~?</td>
      </tr>
      <tr>
        <td><code>int dX_size_u</code></td>
        <td>瞳の幅</td>
        <td align="center">?~?</td>
      </tr>
      <tr>
        <td><code>int dY_size_u</code></td>
        <td>瞳の高さ</td>
        <td align="center">?~?</td>
      </tr>
    </tbody>
  </table>

- **Eye(int dX_point_u, int dY_point_u, int dX_size_u, int dY_size_u, unsigned int num) :** 上2つの組み合わせ版．
> [!NOTE]
> 現状，左右の瞳の間隔や左右個別の操作は，行えません．
### - void Motor(int motor_power_l, int motor_power_r)
### - void Move()
### - boolean Voice_state()
### - void Voice_send(char Talk[100])
### - void Voice(unsigned int num)
### - boolean Sleep(unsigned int num)

> [!IMPORTANT]
> 〈第2.1世代〉ころボ のライブラリは，複数の既存ライブラリに依存しています．
> 事前に，それらのライブラリをインストールしてください[^1][^2][^3][^4]．
> また，各ライブラリには**異なるライセンス**が付与されています．
> これらのライブラリを独自に改変，または ころボ のライブラリへ組み込むといった場合は，十分にご確認ください．
[^1]: https://github.com/adafruit/Adafruit-GFX-Library
[^2]: https://github.com/adafruit/Adafruit_SSD1306
[^3]: https://github.com/adafruit/Adafruit_Sensor
[^4]: https://github.com/adafruit/Adafruit_BNO055
