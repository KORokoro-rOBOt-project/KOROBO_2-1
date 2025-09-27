# 〈第2.1世代〉ころボ / KOROBO (2.1 Gen)
> [!IMPORTANT]
> 組み立て説明を除き，他のデータは最低限完成しました！\
> 学生個人の活動であるため，ご了承ください．

<p align="center"><img src="/Document/Picture/image_korobo-2-1.jpg" width="75%"></p>

## 概要 / Overview
### ころボ？
“ころボ” は，カプセルに覆われた手のひらサイズのロボットです．
ただ，表情は四角い2つの瞳，動きはカプセル内で前後左右するも丸いカプセルに振り回され，言葉らしい言葉も話しません．
一見するとポンコツな子ですが，自身や周囲の状況に応じた繊細な反応，設計者の思惑を介さない不完全だからこそ引き出される解釈に，不思議と魅了されます．

玩具や機械ではなく，生き物っていうわけでもないけれど，どこか自分たちと同じ存在感を与える新たな存在になってほしいと考えています．
そして，周囲の人同士の関係を築いたり，誰かの不安や秘密を一緒に抱え込んでくれたり，孤独を埋めてくれたりする存在に... 

### 第2.1世代
〈第2.1世代〉ころボは，〈第2世代〉のオープンソース版として開発中の子です．

<details>
<summary>第1世代，第2世代 / 1st Gen, 2nd Gen</summary>
	
<table>
  <thead>
    <tr>
      <th align="center"><strong>第1世代 / 1st Gen</strong></th>
      <th align="center"><strong>第2世代 / 2nd Gen</strong></th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td valign="top">
        〈第1世代〉ころボは，高専の本科生で最後となる高専祭に向けて制作された球体ロボットです．<br><br>
        <strong>直径8</strong> [<strong>cm</strong>]の小さなロボットは，特定の行動パターンを持たず，ランダムに転がります．
        そして，球体という不安定な要素と合わさり，あなたに自由な解釈でロボットと触れ合える余地（
        <a href="https://magazine.serviceology.org/2021/12/20/1433/" target="_blank"><strong>解釈の余地</strong></a>）を与えます．
      </td>
      <td valign="top">
        〈第2世代〉ころボは，
        <a href="https://hacku.yahoo.co.jp/kosen2021/" target="_blank">Hack U KOSEN 2021</a>
        に出場した際に制作した球体ロボットです．
        <strong>直径10</strong> [<strong>cm</strong>]の手にすっぽりおさまるロボットは，周囲の環境（
        <a href="https://twitter.com/KORokororOBOt/status/1652417063770820609" target="_blank"><strong>音</strong></a>，
        明るさ）や自身の状態（
        <a href="https://twitter.com/KORokororOBOt/status/1652271276403347457" target="_blank"><strong>加速度，角速度</strong></a>）を取得します．<br><br>
        それらの情報を反映させたことで，玩具っぽさが軽減され，あなたと同じ世界に住む存在なのだと感じられます．
        また，球体という不安定な要素と合わさり，あなたに自由な解釈でロボットと触れ合える余地（
        <a href="https://magazine.serviceology.org/2021/12/20/1433/" target="_blank"><strong>解釈の余地</strong></a>）を与えます．
      </td>
    </tr>
    <tr>
      <td valign="top">
        &emsp;&emsp;<strong>The first generation</strong> is a spherical robot I created as a department student for the Kosen College Festival.<br><br>
        &emsp;&emsp;The tiny robot, <strong>8 [cm]</strong> in diameter, has no specific action pattern and rolls randomly.
        Combined with the unstable element of the sphere, it gives you room to interact with the robot in any way you like (
        <a href="https://magazine.serviceology.org/2021/12/20/1433/" target="_blank"><strong>Room for Interpretation</strong></a>).
      </td>
      <td valign="top">
        &emsp;&emsp;<strong>The second generation</strong> is a spherical robot created for 
        <a href="https://hacku.yahoo.co.jp/kosen2021/" target="_blank">Hack U KOSEN 2021</a>.
        The <strong>10 [cm]</strong> diameter robot fits snugly in your hand and gets information about its surroundings (
        <a href="https://twitter.com/KORokororOBOt/status/1652417063770820609" target="_blank"><strong>Sound</strong></a>, Luminance) and its state (
        <a href="https://twitter.com/KORokororOBOt/status/1652271276403347457" target="_blank"><strong>Acceleration, Angular Velocity</strong></a>).<br><br>
        &emsp;&emsp;The robot reflects this information, making it feel less like a toy and more like a being that lives in the same world as you.
        Combined with the unstable element of the sphere, it gives you room to interact with the robot in any way you like (
        <a href="https://magazine.serviceology.org/2021/12/20/1433/" target="_blank"><strong>Room for Interpretation</strong></a>).
      </td>
    </tr>
  </tbody>
</table>

<p align="center"><img src="/Document/Picture/korobo-1--2_pop.png" width="75%"></p>

</details>

<p align="center"><img src="/Document/Picture/korobo-2-1_pop.png" width="75%"></p>

<p align="center"><img src="/Document/Movie/korobo_2-1_3d-movie_small.gif" width="75%"></p>

- ころボ 開発当初から大切にしてきた**シンプルな構造**と，**はめ込みによる組み立て方式**[^1]はそのままに，**耐久性**や**拡張性**が向上しました！
    > 机から落ちても，間違えて蹴っ飛ばしても致命傷になることはありません．\
    > マイコンボードとアクセス可能なスペースがあり，思い思いに進化させられます．
[^1]: 既製品のギヤボックスキットは除く．

- マイコンボードに，Raspberry Pi Foundationが提供する[**Raspberry Pi Pico（ラズベリーパイピコ）**](https://www.raspberrypi.com/products/raspberry-pi-pico/)を採用しています！
    > 安価で入手性に優れ，様々な制作事例が存在します．\
    > 多くの互換ボードが存在し，USB端子や用途に合わせて自由に選べます．\
    > <a href="https://www.raspberrypi.com/products/raspberry-pi-pico-2/" >Raspberry Pi Pico 2</a>のように，世代が上がっても互換性があります．
 
## フォルダ構成 / Directory Layout
- [**Board**](Board): 基板発注に必要なガーバーデータ
- [**Code**](Code): ソースコード，ライブラリ
- [**Document**](Document): 調達リスト，画像など
- [**Model**](Model): STEPファイルおよびSTLファイル
## 組み立て / How to Set Up
<details open>
<summary><strong>目次</strong></summary>

0. [部品調達](#01-調達)
1. [駆動ユニット](#10-準備)
2. [配線](#20-準備)
3. [基板](#30-準備)
4. [はめ込み](#40-準備)
5. [ソースコード](#50-準備)
</details>

---
### 0. 部品調達（0/[1](#10-準備)/[2](#20-準備)/[3](#30-準備)/[4](#40-準備)/[5](#50-準備)）
#### 0.1 調達 
[Document](Document)に記載されている各種材料を，添付されているURLの通販サイトや実店舗などにて，調達してください．
> [!NOTE]
> 電子工作経験者の場合，調達前に手持ちの部品を確認することで，不要な調達を避けられるかもしれません．（例：ピンソケット、ピンヘッダ、抵抗、コンデンサなど）

#### 0.2 印刷
> [!TIP]
> KORokoro.rOBOt projectの[BOOTH](https://korokoro-robot.booth.pm/items/6812764)にて，**3Dプリンタ製部品**を調達された方は，"[0.3 基板発注 or 作成](#03-基板発注-or-作成)" へ進んでください．
<details open>
<summary>手順</summary>

##### 0.20 準備
##### 0.21 PLA
<p align="center"><img src="/Document/Picture/pla-parts_2.jpg" width="75%"></p>
<p align="center">
<img src="/Document/Picture/pla-parts_support-remove_1.jpg" width="37.5%"><img src="/Document/Picture/pla-parts_support-remove_2.jpg" width="37.5%">
</p>
<p align="center">
<img src="/Document/Picture/pla-parts_support-remove_3.jpg" width="37.5%"><img src="/Document/Picture/pla-parts_support-remove_4.jpg" width="37.5%">
</p>
<p align="center"><img src="/Document/Picture/pla-parts_support-remove_5.jpg" width="75%"></p>

##### 0.22 TPU
<p align="center">
<img src="/Document/Picture/tpu-parts_support-remove_1.jpg" width="37.5%"><img src="/Document/Picture/tpu-parts_support-remove_2.jpg" width="37.5%">
</p>
<p align="center">
<img src="/Document/Picture/tpu-parts_support-remove_3.jpg" width="37.5%"><img src="/Document/Picture/tpu-parts_support-remove_4.jpg" width="37.5%">
</p>
<p align="center">
<img src="/Document/Picture/tpu-parts_support-remove_5.jpg" width="37.5%"><img src="/Document/Picture/tpu-parts_support-remove_6.jpg" width="37.5%">
</p>
</details>

#### 0.3 基板発注 or 作成
> [!TIP]
> KORokoro.rOBOt projectの[BOOTH](https://korokoro-robot.booth.pm/items/6807081)にて，**メインボード**を調達された方は，"[1. 駆動ユニット](#10-準備)" へ進んでください．
<details open>
<summary>業者に発注される方</summary>

> [**Board**](Board)の中にあるzipファイルをPCBサイトへアップロードしてください．
</details>
<details>
<summary>ユニバーサル基板から作成される方（準備中）</summary>

準備中...
</details>

---
### 1. 駆動ユニット（[0](#01-調達)/1/[2](#20-準備)/[3](#30-準備)/[4](#40-準備)/[5](#50-準備)）
#### 1.0 準備
次の表に示す，工具・部品を準備してください．
<table>
  <thead>
    <tr>
      <th>項目</th>
      <th>名称</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td rowspan="4">工具</td>
      <td>ニッパー</td>
    </tr>
    <tr>
      <td>カッターナイフ or デザインナイフ</td>
    </tr>
    <tr>
      <td>ピンセット</td>
    </tr>
    <tr>
      <td>プラスドライバー</td>
    </tr>
    <tr>
      <td rowspan="4">部品</td>
      <td>タミヤ ミニモーター低速ギヤボックス（4速）</td>
    </tr>
    <tr>
      <td>タミヤ 3mm六角シャフトセット</td>
    </tr>
    <tr>
      <td>メインタイヤ（3Dプリンタ製）</td>
    </tr>
    <tr>
      <td>ギヤボックスカバー（3Dプリンタ製）</td>
    </tr>
  </tbody>
</table>

#### 1.1 ギヤボックス
ミニモーター低速ギヤボックス（4速）を，付属の組み立て説明書に従って，組み立てます．

> [!NOTE]
> ギヤ比は，"<b>149.9:1</b>" を使用します．\
> 六角シャフトは，3mm六角シャフトセットに付属する "<b>38 [mm]</b>" を使用します．

#### 1.2 タイヤ
1.1で組み立てたギヤボックスのシャフトを，0.22で印刷したメインタイヤへ圧入します．
> [!NOTE]
> 最後，カプセルに入れる際，圧入度合いの微調整をする必要があります．

#### 1.3 ギヤボックスカバー
1.2のギヤボックスを，0.22で印刷したギヤボックスカバーへ組み込みます．\
軽く，ギヤボックスカバーにギヤボックスを押し込めば入ります．

---
### 2. 配線（[0](#01-調達)/[1](#10-準備)/2/[3](#30-準備)/[4](#40-準備)/[5](#50-準備)）
> [!TIP]
> KORokoro.rOBOt projectの[BOOTH](https://korokoro-robot.booth.pm/)にて，**配線類**を調達された方は，"[3. 基板](#30-準備)" へ進んでください．（※現在，準備中）
<p align="center"><img src="/Document/Picture/wire_parts.JPG" width="75%"></p>
<details open>
<summary>手順</summary>

#### 2.0 準備
準備中...

<table>
	<thead>
		<tr>
			<th>項目</th>
			<th>名称</th>
		</tr>
	</thead>
	<tbody>
		<tr>
			<td rowspan="2">工具</td>
			<td>圧着工具</td>
		</tr>
		<tr>
			<td>グルーガン（+ グルースティック）</td>
		</tr>
	</tbody>
</table>

#### 2.1 ピンヘッダー
準備中...

#### 2.2 JST-XH
準備中...

#### 2.3 JST-PH
準備中...

#### 2.4 PicoBlade
準備中...

</details>

---
### 3. 基板（[0](#01-調達)/[1](#10-準備)/[2](#20-準備)/3/[4](#40-準備)/[5](#50-準備)）
#### 3.0 準備
次の表・画像に示す，工具・部品を準備してください．

<table>
  <thead>
    <tr>
      <th>項目</th>
      <th>名称</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td rowspan="5">工具</td>
      <td>半田こて</td>
    </tr>
    <tr>
      <td>半田</td>
    </tr>
    <tr>
      <td>ニッパー</td>
    </tr>
    <tr>
      <td>机を保護できるマット</td>
    </tr>
    <tr>
      <td>基板や部品を固定できるモノ</td>
    </tr>
  </tbody>
</table>

<p align="center"><img src="/Document/Picture/main-board_parts.jpg" width="75%"></p>

#### 3.2 半田付け
準備中...

---
### 4. はめ込み（[0](#01-調達)/[1](#10-準備)/[2](#20-準備)/[3](#30-準備)/4/[5](#50-準備)）
#### 4.0 準備
準備中...
#### 4.1 基板 << 配線
準備中...
#### 4.2 メインフレーム << 基板（＋配線）
準備中...
#### 4.3 メインフレーム << バッテリ
準備中...
#### 4.4 メインフレーム << 駆動ユニット
準備中...
#### 4.5 メインフレーム << その他モジュール
<details open>
<summary>一覧（順不同）</summary>

- **OLED**
    1. 準備中...
    2. 準備中...
- **照度センサ**
    1. 準備中...
    2. 準備中...
- **スピーカ**
    1. 準備中...
    2. 準備中...
</details>

#### 4.6 上部滑車
<p align="center">
<img src="/Document/Picture/top-wheel_1.jpg" width="37.5%"><img src="/Document/Picture/top-wheel_2.jpg" width="37.5%">
</p>
<p align="center">
<img src="/Document/Picture/top-wheel_3.jpg" width="37.5%"><img src="/Document/Picture/top-wheel_4.jpg" width="37.5%">
</p>
<p align="center">
<img src="/Document/Picture/top-wheel_set_1.jpg" width="37.5%"><img src="/Document/Picture/top-wheel_set_2.jpg" width="37.5%">
</p>
<p align="center">
<img src="/Document/Picture/top-wheel_set_3.jpg" width="37.5%"><img src="/Document/Picture/top-wheel_set_4.jpg" width="37.5%">
</p>

#### 4.7 カバー
準備中...
#### 4.8 カプセル
準備中...

---
### 5. ソースコード（[0](#01-調達)/[1](#10-準備)/[2](#20-準備)/[3](#30-準備)/[4](#40-準備)/5）
#### 5.0 準備
準備中...
#### 5.1 配線
準備中...
#### 5.2 書き込み
準備中...
## ころボとの生活 / Life with KOROBO
#### ごはん
準備中...
#### 拡張性
準備中...
#### その他
> [!CAUTION]
> カプセルの仕様上，**完全防水ではありません**．

> [!CAUTION]
> **リチウムイオン電池**を用いています．取り扱いにはご注意ください．

<a name="license"></a>
<p xmlns:cc="http://creativecommons.org/ns#" xmlns:dct="http://purl.org/dc/terms/"><a property="dct:title" rel="cc:attributionURL" href="https://github.com/KORokoro-rOBOt-project/KOROBO_2-1">〈第2.1世代〉ころボ</a> by <a rel="cc:attributionURL dct:creator" property="cc:attributionName" href="https://community.camp-fire.jp/projects/view/764851">KORokoro.rOBOt project</a> is licensed under <a href="https://creativecommons.org/licenses/by-sa/4.0/?ref=chooser-v1" target="_blank" rel="license noopener noreferrer" style="display:inline-block;">Creative Commons Attribution-ShareAlike 4.0 International<img style="height:22px!important;margin-left:3px;vertical-align:text-bottom;" src="https://mirrors.creativecommons.org/presskit/icons/cc.svg?ref=chooser-v1" alt=""><img style="height:22px!important;margin-left:3px;vertical-align:text-bottom;" src="https://mirrors.creativecommons.org/presskit/icons/by.svg?ref=chooser-v1" alt=""><img style="height:22px!important;margin-left:3px;vertical-align:text-bottom;" src="https://mirrors.creativecommons.org/presskit/icons/sa.svg?ref=chooser-v1" alt=""></a></p>
