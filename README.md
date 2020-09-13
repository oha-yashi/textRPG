# テキストRPG <!-- omit in toc --> <!-- 目次から消すコマンド -->

terminal風にコマンド入力するRPGプログラム

- [アイデア](#アイデア)
- [ステータス](#ステータス)
  - [共通](#共通)
  - [プレイヤー](#プレイヤー)
  - [敵](#敵)
- [装備について](#装備について)
  - [部位](#部位)
- [表示するもの/`command`](#表示するものcommand)
  - [常時可能](#常時可能)
    - [`help`](#help)
  - [メニュー](#メニュー)
    - [`info` - 自分の情報](#info---自分の情報)
    - [`equip` - 武器メニュー](#equip---武器メニュー)
    - [`battle` - バトル](#battle---バトル)
    - [`shop` - 武器とか買える *`10n+1`階層で使える*](#shop---武器とか買える-10n1階層で使える)
    - [`save` - セーブ](#save---セーブ)
    - [`exit` - 終了 ~~（セーブを自動呼び出し）~~](#exit---終了-sセーブを自動呼び出しs)
- [バトルの流れ](#バトルの流れ)
  - [開始時](#開始時)
  - [毎ターン](#毎ターン)
- [データの形式](#データの形式)
  - [player.md](#playermd)
  - [weapon.md](#weaponmd)
  - [special.md](#specialmd)

# アイデア

- ncursesは使わない
- [ ] 戦闘は自動で
  - [ ] コンマ数秒ずつ送る
- [ ] 敵をある程度自動生成したい
- [ ] 武器カスタマイズ要素あり
- [ ] 戦闘中回復判定可能
- [ ] ~~ 階層に用意される敵は固定数（無限湧きはしない） ~~
  - [ ] ~~ ボス込みのキューで配置（初期配置ボス含めランダム（早くにボスに遭遇しても後回しにできる）） ~~
  - [ ] ~~ 先頭3つから選択、残りは後ろに回る ~~
  - [ ] ~~ 敵の数がなくなったら上の階層に戻る選択肢を出す ~~
- [ ] ランダムで敵が出現。ステージ進捗％で管理
- [ ] helpファイルを作って適宜呼び出せるようにする

# ステータス
## 共通

- 名前
- HP
- ATK - 攻撃
- DEF - 防御
- SPD - 攻撃の先後, 回避可能性
- EXP - 経験値
  - プレイヤーは持ってる全経験値
  - 敵はドロップする経験値
- GLD - 金
  - プレイヤーは持ってる金（ゴールド）
  - 敵はドロップする金
- SPE - 特殊効果<br>
  それぞれ補正効果により確率で発動する<br>
  ビットで保持。後ろの方が強い<br>
  - [ ] ***バトル関数の中でもつ***
  - 先制攻撃
  - 100%回避（被弾時）
  - 100%命中（攻撃時）
  - 起死回生（1回のみ）

## プレイヤー

- LVL - レベル
- STG - 現在のステージ
- 武器番号
  - 名前
  - 各補正量
    - dHP
    - dATK
    - dDEF
    - dSPD
- 特殊効果 バトル開始時に処理<br>
  種類と発動割合を設定する
- 敵キュー

## 敵

- 特殊効果<br>
  敵は独自にもっていたりする

# 装備について
## 部位

- head - 頭装備
- body - 体装備
- weapon - 攻撃装備
- shield - 防御装備
- leg - 足装備
- special - その他装備

<!-- 改ページ 
<div style="page-break-before:always"></div>
-->

# 表示するもの/`command`

## 常時可能

### `help`
その時々に応じたヘルプ（単にコマンド一覧）が出る
  
## メニュー

通常時は

```
name 1F$ hoge
```

### `info` - 自分の情報
  - [x] 名前
  - [x] HP/MAX
  - [x] ATK
  - [x] DEF
  - [x] SPD
  - [x] LVL
  - [x] EXP/NEXT
  - [x] 階層
  - [ ] 装備
### `equip` - 武器メニュー
装備変更
### `battle` - バトル
### `shop` - 武器とか買える *`10n+1`階層で使える*
### `save` - セーブ
### `exit` - 終了 ~~（セーブを自動呼び出し）~~

# バトルの流れ
```
name 1F$ battle [Enter]
1. name
2. name / back 1 floor
3. name
battle $ 1 [Enter]
:
:
```

## 開始時

- [ ] 双方の特殊効果の設定
- [ ] weaponのデータを作って補正値をそこにまとめる
- [ ] tempのデータを作って補正値はそこに毎ターン足す

## 毎ターン

- [ ] 攻撃力に毎回±10%の変化あり

# データの形式

markdownで保存
  
読み出し方法は、`|`を空白に変換してストリームから読み込む

## player.md
新規データ

```md
## 基本データ
| name | LVL | EXP | GLD | STG | PROG |
| ---- | --- | --- | --- | --- | ---- |
| ohys | 1   | 0   | 100 | 1   | 0    |

## 戦闘データ
| HP  | MAX_HP | ATK | DEF | SPD |
| --- | ------ | --- | --- | --- |
| 100 | 100    | 10  | 5   | 100 |

## 武器データ
| head | body | weapon | shield | leg | spe |
| ---- | ---- | ------ | ------ | --- | --- |
| 7    | 2    | 3      | 4      | 5   | 0   |
```

## weapon.md

武器一覧

表形式で一覧に。

- タイプ {頭, 体, 武器, 盾, 脚, 特殊} = {0,1,2,3,4,5}
- 名前
- 各補正量
  - dHP
  - dATK
  - dDEF
  - dSPD
- 特殊効果
  - タイプ
  - 発動確率

## special.md

特殊効果。番号の小さい方から適用される

- [ ] 戦闘開始時に武器から読み取り`vector<pair>`に入れる。sortする

0. なし
1. 先制攻撃
2. 100%回避
3. 100%命中（100%回避より強い）
4. 起死回生（死亡するダメ時を負った時確率でHP1で残る）