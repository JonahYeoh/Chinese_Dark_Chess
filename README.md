# Chinese_Dark_Chess

這是一個懂得下暗棋的智慧玩家，棋力非常一般。
面對隨機性玩家可以達到高達6成的勝算。

人工智慧課的老師讓我們寫暗棋對弈的智慧Agent。寫了好幾周總算完成了雛形，以下是這支程式的一些説明：
做到了:
1. Alpha-Beta Pruning （5步）
沒做到：
1. 沒有對子節點做優先排序加强Alpha-Beta Pruning的效益
2. 完全不考量關閉的棋子 （ 非不得已不走 ）

## Usage

```bash
make all    # build
make clean  # clean all compile link file
```

Bug:
程式會反復在小區内移動，沒有對重複動作這件事做防呆。

注：
權重方面參考 =》 https://github.com/kuruwa2/Dark-Chess-AI/tree/master/code
產生節點的方法原本很複雜，今天下午被 黃嘉佑 學長提了一提，便直接參考原程式的expand function。

補充：
有同學反映編譯時沒問題但是執行起來卻無法動彈。
方法：
目前我都是用C++17在編譯，建議安裝mingw6.3或以上。
這裏提供好心的學長Jerry Yang整理好的安裝方法 -> https://blog.yangjerry.tw/2019/11/30/devcplusplus-gplusplus-8/?fbclid=IwAR0USywCQVmIE_vGCJe7HDiihDNvYCAGebEBydBsyMUauRt9A9cLBBextIw
淺顯易懂的教學！

## Enhancement
1. 對之前的程式做了些改良，參考老師的建議把原本的Alpha-Beta Pruning改成Negascout。
2. 爲了加深搜尋深度，才有了Progressive deepening的方法（以時限和層數控制）
3. 配分方面多加了深度和盤面上剩餘的所有棋子個數為計算參數

## 展望
1. 可以落實endgame的方法，讓敵方剩最後一顆棋子時有目標的去進攻。目前由於層數限制，常常落入horizon effect的窘境把充滿優勢的盤面白白斷送。
