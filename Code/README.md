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
### - begin()
### - Imu_getData()
### - AmbientLight_getData()
### - Mic_getData()
### - Eye(3-pattern)
- Eye(unsigned int num)
- Eye(int dX_point_u, int dY_point_u, int dX_size_u, int dY_size_u)
- Eye(int dX_point_u, int dY_point_u, int dX_size_u, int dY_size_u, unsigned int num)
### - Move() <- 予定
### - Motor(int motor_power_l, int motor_power_r)
### - Voice() <- 予定

> [!IMPORTANT]
> 〈第2.1世代〉ころボ のライブラリは，複数の既存ライブラリに依存しています．
> 事前に，それらのライブラリをインストールしてください[^1][^2][^3][^4]．
> また，各ライブラリには**異なるライセンス**が付与されています．
> これらのライブラリを独自に改変，または ころボ のライブラリへ組み込むといった場合は，十分にご確認ください．
[^1]: https://github.com/adafruit/Adafruit-GFX-Library
[^2]: https://github.com/adafruit/Adafruit_SSD1306
[^3]: https://github.com/adafruit/Adafruit_Sensor
[^4]: https://github.com/adafruit/Adafruit_BNO055
