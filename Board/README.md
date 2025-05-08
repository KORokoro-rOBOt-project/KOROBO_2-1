# Board
<img src="/Document/Picture/korobo_2-1_bno055_ver3-1_img1.jpg" width="75%">
<p>
  <img src="/Document/Picture/korobo_2-1_bno055_ver3-1_img2.jpg" width="37.5%"><img src="/Document/Picture/korobo_2-1_bno055_ver3-1_img3.jpg" width="37.5%">
</p>
<img src="/Document/Picture/schematic_korobo_2-1_bno055.jpg" width="75%">

## 概要 / Overview
〈第2.1世代〉ころボのプリント基板は，組み立てやすさとメンテナンス性に注力しています．

まず，プリント基板に設けられたスルーホールのピッチは，すべて2.54mmとなっています．
つまり，市販のユニバーサル基板との互換性があるため，プリント基板の調達が困難な方でも作成可能となっています．

そして，メインボードと各種モジュールは，ピンソケットとピンヘッダーによって接続されています．
そのため，簡単に取り外せて，故障時の対応やマイコンボードの載せ替えが柔軟に行えます．
## 部品リスト / Parts List
| ラベル | 仕様                         | 個数 | 補足                          |
|:------:|------------------------------|:----:|-------------------------------|
| C1     | 100uF                        | 1    | 電解コンデンサ                |
| C2     | 0.1uF                        | 1    | セラミックコンデンサ          |
| J1     | JST XH 2pin                 | 1    | 照度センサへ接続             |
| J2     | JST PH 2pin                 | 1    | バッテリへ接続               |
| J3     | JST XH 2pin                 | 1    | 右モータへ接続               |
| J4     | JST XH 2pin                 | 1    | 左モータへ接続               |
| J5     | PinSocket 2.54mm 20pin      | 1    | マイコンボードへ接続         |
| J6     | PinSocket 2.54mm 20pin      | 1    | マイコンボードへ接続         |
| R1     | 150k                        | 1    | 抵抗                          |
| U1     | PinSocket 2.54mm 6pin       | 1    | 充放電モジュールへ接続       |
| U2     | PinSocket 2.54mm 3pin       | 1    | マイクセンサへ接続           |
| U3     | PinSocket 2.54mm 4pin       | 2    | 9軸センサへ接続              |
| U4     | PinSocket 2.54mm 4pin       | 1    | D級アンプへ接続              |
| U5     | JST XH 4pin                 | 1    | OLEDへ接続                   |
| U6     | DIP-28 W7.62mm              | 1    | ボイスICへ接続               |
| U7     | PinSocket 2.54mm 8pin       | 2    | モータドライバへ接続         |

<img src="/Document/Picture/main-board_parts.jpg" width="75%">
