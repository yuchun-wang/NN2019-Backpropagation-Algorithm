# NN2019-Backpropagation-Algorithm

Backpropagation Algorithm

向前傳遞先將資料丟進網路，得到結果後計算與目標間的誤差，再在藉由向後傳遞，依照誤差值去調整網路的權重，反覆訓練後將誤差修正到極小範圍。如果誤差值越來越大，代表學習的不好，需要繼續學習或程式有誤，直到參數與誤差值收斂才是完成學習。

藉由讀檔先將x1、x2和每組的目標值desire讀入設定好，接著設定權中初始值為亂數、誤差值為零。接著進行迴圈訓練，一個Iteration會做四組，(x1,x2)分別為(1,1)、(0,1)、(1,0)、(0,0)，經由計算之後會得到一個值S_y，經由計算其與desire之間的誤差值，得到四個error，藉由error值去修正權重，一個Iteration做完後平均四個error值，若是該值仍大於learningrate則繼續執行下一輪繼續修正，直到該值仍小於learningrate，程式才停止，而此時S_y值應該相當接近desire值。
