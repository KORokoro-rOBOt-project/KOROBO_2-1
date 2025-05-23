# 〈第2.1世代〉ころボ / KOROBO (2-1 gen)
> [!CAUTION]
> 現在，オープンソースとしての環境を構築中です．\
> 学生個人の活動であるため，ご了承ください．\
> 組み立て説明を除き，他のデータ・ドキュメントは最低限完成しました！

<!-- ![〈第2.1世代〉ころボ / KOROBO (2-1 gen)](/Document/image_korobo-2-1.jpg) -->
<img src="/Document/Picture/image_korobo-2-1.jpg" width="75%">

## 概要 / Overview
### ころボ？
“ころボ” は，カプセルに覆われた手のひらサイズのロボットです．
ただ，表情は四角い2つの瞳，動きはカプセル内で前後左右するも丸いカプセルに振り回され，言葉らしい言葉も話しません．
一見するとポンコツな子ですが，自身や周囲の状況に応じた繊細な反応，設計者の思惑を介さない不完全だからこそ引き出される解釈に，不思議と魅了されます．

玩具や機械ではなく，生き物っていうわけでもないけれど，どこか自分たちと同じ存在感を与える新たな存在になってほしいと考えています．
そして，周囲の人同士の関係を築いたり，誰かの不安や秘密を一緒に抱え込んでくれたり，孤独を埋めてくれたりする存在に... 
### 第2.1世代
〈第2.1世代〉ころボは，〈第2世代〉のオープンソース版として開発中の子です．

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
- [**Document**](Document): 購入リスト，画像など
- [**Model**](Model): STEPファイルおよびSTLファイル
## 組み立て / How to Set Up
<details open>
<summary><strong>目次</strong></summary>

0. [部品調達](#01-購入)
1. [駆動ユニット](#10-準備)
2. [配線](#20-準備)
3. [基板](#30-準備)
4. [はめ込み](#40-準備)
5. [ソースコード](#50-準備)
</details>

---
### 0. 部品調達（0/[1](#10-準備)/[2](#20-準備)/[3](#30-準備)/[4](#40-準備)/[5](#50-準備)）
#### 0.1 購入 
[Document](Document)の "[Parts-List_KOROBO_2-1.pdf](/Document/Parts-List_KOROBO_2-1.pdf)" に記載されている各種材料を，添付されているURLの通販サイトや実店舗などにて，購入してください．
> [!NOTE]
> 必要な部品の中には，購入時の**最低個数**が指定されている場合や，1つの商品あたりに**複数個の同じ部品**を含む場合があります．電子工作をされている方なら，一度ご自身が現在所持している部品を確認することで，必要以上の買い物を避けられるかもしれません．（例：ピンソケット，ピンヘッダ，抵抗，コンデンサなど）
#### 0.2 印刷
> [!TIP]
> KORokoro.rOBOt projectの[BOOTH](https://korokoro-robot.booth.pm/items/6812764)にて，**3Dプリンタ製部品**を購入された方は，"[1. 駆動ユニット](#10-準備)" へ進んでください．
<details open>
<summary>手順</summary>

##### 0.20 準備
##### 0.21 PLAフィラメント印刷
<img src="/Document/Picture/pla-parts_2.jpg" width="75%">
<p>
<img src="/Document/Picture/pla-parts_support-remove_1.jpg" width="37.5%"><img src="/Document/Picture/pla-parts_support-remove_2.jpg" width="37.5%">
</p>
<p>
<img src="/Document/Picture/pla-parts_support-remove_3.jpg" width="37.5%"><img src="/Document/Picture/pla-parts_support-remove_4.jpg" width="37.5%">
</p>
<img src="/Document/Picture/pla-parts_support-remove_5.jpg" width="75%">

##### 0.22 TPUフィラメント印刷
<p>
<img src="/Document/Picture/tpu-parts_support-remove_1.jpg" width="37.5%"><img src="/Document/Picture/tpu-parts_support-remove_2.jpg" width="37.5%">
</p>
<p>
<img src="/Document/Picture/tpu-parts_support-remove_3.jpg" width="37.5%"><img src="/Document/Picture/tpu-parts_support-remove_4.jpg" width="37.5%">
</p>
<p>
<img src="/Document/Picture/tpu-parts_support-remove_5.jpg" width="37.5%"><img src="/Document/Picture/tpu-parts_support-remove_6.jpg" width="37.5%">
</p>
</details>

---
### 1. 駆動ユニット（[0](#01-購入)/1/[2](#20-準備)/[3](#30-準備)/[4](#40-準備)/[5](#50-準備)）
#### 1.0 準備
準備中...
#### 1.1 TAMIYA製ギアボックス
メーカーの組み立て説明書に従って，組み立てます．
ギア比は，"_**149.9:1**_" を使用します． 
#### 1.2 タイヤ
準備中...
#### 1.3 ギアボックスカバー
準備中...

---
### 2. 配線（[0](#01-購入)/[1](#10-準備)/2/[3](#30-準備)/[4](#40-準備)/[5](#50-準備)）
> [!TIP]
> KORokoro.rOBOt projectの[BOOTH](https://korokoro-robot.booth.pm/)にて，**配線類**を購入された方は，"[3. 基板](#30-準備)" へ進んでください．
<img src="/Document/Picture/wire_parts.JPG" width="75%">
<details open>
<summary>手順</summary>

#### 2.0 準備
準備中...
#### 2.1 ピンヘッダー
準備中...
#### 2.2 JST-XH
準備中...
#### 2.3 JST-PH
準備中...
#### 2.4 PicoBlade
準備中...
</details>

***
### 3. 基板（[0](#01-購入)/[1](#10-準備)/[2](#20-準備)/3/[4](#40-準備)/[5](#50-準備)）
#### 3.0 準備
準備中...
#### 3.1 発注 or 作成
> [!TIP]
> KORokoro.rOBOt projectの[BOOTH](https://korokoro-robot.booth.pm/items/6807081)にて，**メインボード**を購入された方は，"[3.2 半田付け](#12-半田付け)" へ進んでください．
<details>
<summary>業者に発注される方</summary>

準備中...
</details>
<details>
<summary>ユニバーサル基板から作成される方</summary>

準備中...
</details>

#### 3.2 半田付け
<img src="/Document/Picture/main-board_parts.jpg" width="75%">
準備中...

---
### 4. はめ込み（[0](#01-購入)/[1](#10-準備)/[2](#20-準備)/[3](#30-準備)/4/[5](#50-準備)）
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
<p>
<img src="/Document/Picture/top-wheel_1.jpg" width="37.5%"><img src="/Document/Picture/top-wheel_2.jpg" width="37.5%">
</p>
<p>
<img src="/Document/Picture/top-wheel_3.jpg" width="37.5%"><img src="/Document/Picture/top-wheel_4.jpg" width="37.5%">
</p>
<p>
<img src="/Document/Picture/top-wheel_set_1.jpg" width="37.5%"><img src="/Document/Picture/top-wheel_set_2.jpg" width="37.5%">
</p>
<p>
<img src="/Document/Picture/top-wheel_set_3.jpg" width="37.5%"><img src="/Document/Picture/top-wheel_set_4.jpg" width="37.5%">
</p>

#### 4.7 カバー
準備中...
#### 4.8 カプセル
準備中...

---
### 5. ソースコード（[0](#01-購入)/[1](#10-準備)/[2](#20-準備)/[3](#30-準備)/[4](#40-準備)/5）
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
> [!WARNING]
> 定期的に，本体カバーを取り外して**バッテリ**の様子を見てください．もし，バッテリが膨らんでいたり，異常な発熱が生じていたりしたら，直ちにメインボード（基板）から取り外してください．**火災**につながる恐れがあります．

> [!CAUTION]
> カプセルの仕様上，**完全防水ではありません**．軽い雨や粉塵に対しての耐性はありますが，清掃は必要です．最悪の場合，故障する可能性もあるため，思いやりをもって共に過ごしましょう．

> [!CAUTION]
> 極端に**気温**が高かったり低かったりする環境では，バッテリや各種モジュールに負荷を与えるため，注意が必要です．

<a name="license"></a>
<p xmlns:cc="http://creativecommons.org/ns#" xmlns:dct="http://purl.org/dc/terms/"><a property="dct:title" rel="cc:attributionURL" href="https://github.com/KORokoro-rOBOt-project/KOROBO_2-1">〈第2.1世代〉ころボ</a> by <a rel="cc:attributionURL dct:creator" property="cc:attributionName" href="https://community.camp-fire.jp/projects/view/764851">KORokoro.rOBOt project</a> is licensed under <a href="https://creativecommons.org/licenses/by-sa/4.0/?ref=chooser-v1" target="_blank" rel="license noopener noreferrer" style="display:inline-block;">Creative Commons Attribution-ShareAlike 4.0 International<img style="height:22px!important;margin-left:3px;vertical-align:text-bottom;" src="https://mirrors.creativecommons.org/presskit/icons/cc.svg?ref=chooser-v1" alt=""><img style="height:22px!important;margin-left:3px;vertical-align:text-bottom;" src="https://mirrors.creativecommons.org/presskit/icons/by.svg?ref=chooser-v1" alt=""><img style="height:22px!important;margin-left:3px;vertical-align:text-bottom;" src="https://mirrors.creativecommons.org/presskit/icons/sa.svg?ref=chooser-v1" alt=""></a></p>
