# ESP32 呼吸灯制御システム

[中文](README.md) | [English](README_en.md)

## プロジェクト概要

これは ESP32 マイクロコントローラベースの LED 呼吸灯制御システムで、複数の LED モードをサポートしています。ボタンを使用して異なる LED 状態を循環させ、PWM を使用して明るさを制御します。

## 機能

- **4 つの LED 動作モード**:
  - OFF（消灯）
  - MID（中程度の明るさ - 50%）
  - MAX（最大明るさ - 100%）
  - BREATHE（呼吸効果）

- **スマートなデバウンス処理**: 50ms のデバウンス遅延で安定したボタン読み取りを実現

- **PWM 制御**: LED PWM コントローラを使用したスムーズな明るさ調整

- **シリアル フィードバック**: UART 経由でリアルタイムのステータスとボタン押下回数を出力

## ハードウェア要件

| コンポーネント | 仕様 | 数量 |
|-----------|------|------|
| ESP32 ボード | 任意の ESP32 開発ボード | 1 |
| LED | 任意の色（通常の LED 推奨） | 1 |
| ボタン | タッチまたはメカニカルボタン | 1 |
| 抵抗 | 220Ω～1kΩ（LED 限流用） | 1 |
| 配線 | デュポン線 | 複数 |

## 配線図

```
ESP32 GPIO12 ----[220Ω]---- LED 正極
ESP32 GND ---- LED 負極

ESP32 GPIO13 ---- ボタン
ボタンの他端 ---- GND
(GPIO13 は内部プルアップ抵抗を使用)
```

## ソフトウェア要件

- **開発環境**: PlatformIO
- **フレームワーク**: Arduino
- **ESP32 コア**: 最新バージョン

## クイックスタート

### 1. リポジトリをクローン
```bash
git clone https://github.com/yourusername/esp32-led-control.git
cd esp32-led-control
```

### 2. プロジェクトを開く
```bash
# VS Code + PlatformIO を使用
code .
```

### 3. コードをアップロード
- VS Code の PlatformIO サイドバーを開く
- ターゲット環境（ESP32）を選択
- 「Upload」をクリックしてボードにコードを書き込む

### 4. シリアル出力を監視
- PlatformIO → Project Tasks → ESP32 → Monitor
- または他のシリアル監視ツールを使用（ボーレート: 9600）

## 使用ガイド

### ボタン操作

ボタンを押すたびにモードが切り替わります：
- **1 回押下**: LED OFF（0%）
- **2 回押下**: LED MID（50%）
- **3 回押下**: LED MAX（100%）
- **4 回押下**: LED BREATHE（呼吸効果）
- **5 回以上押下**: OFF に戻る

### シリアル出力例
```
System Initialized - LED is OFF (0%)
Button pressed 1 times - LED is MID (50%)
Button pressed 2 times - LED is MAX (100%)
Button pressed 3 times - LED is BREATHE (Breathing...)
```

## コード構造

```
src/
├── main.cpp          # メインプログラムエントリ
├── ハードウェア設定  # GPIO ピン定義
├── ボタンハンドラ    # デバウンスアルゴリズム
└── LED 制御         # PWM と呼吸効果
```

### 主要関数

- `readButton()`: デバウンス付きボタン状態読み取り
- `updateLED()`: 現在のモードに基づいて LED 状態を更新
- `breatheLED()`: LED 呼吸効果を実装

## 技術的なハイライト

1. **デバウンスアルゴリズム**: タイムスタンプ比較を使用したソフトウェアデバウンス
2. **ステート管理**: enum 型を使用した LED モード管理
3. **PWM 制御**: LED コントローラによる正確な明るさ制御
4. **ノンブロッキング設計**: メインループで delay() を避け、迅速な応答を実現

## 設定パラメータ

`src/main.cpp` の以下のパラメータを編集してカスタマイズします：

```cpp
int pin = 12;                           // LED ピン
int pinButton = 13;                     // ボタンピン
const unsigned long debounceDelay = 50; // デバウンス遅延（ミリ秒）
const unsigned long breatheInterval = 10; // 呼吸間隔（ミリ秒）
```

## トラブルシューティング

| 問題 | 解決策 |
|------|-------|
| LED が点灯しない | GPIO 配線を確認し、接続を確認してください |
| ボタンが反応しない | GPIO13 のプルアップが有効であることを確認してください |
| LED がちらつく | デバウンス遅延の設定を調整してください |
| シリアル出力がない | USB 接続とボーレート（9600）を確認してください |

## ライセンス

MIT ライセンス - 詳細は [LICENSE](LICENSE) ファイルを参照してください

## 貢献

Issue と Pull Request は大歓迎です！

## 作成者

Created with ❤️ for ESP32 enthusiasts

---

**他の言語**: [中文](README.md) | [English](README_en.md)
