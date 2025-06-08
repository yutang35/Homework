import matplotlib.pyplot as plt

# 定義參數
n = 200000  # 總記錄數
S = 2000    # 記憶體容量 (記錄數)
t_s = 0.08  # 尋道時間 (秒)
t_l = 0.02  # 延遲時間 (秒)
t_t = 0.001 # 每條記錄的傳輸時間 (秒/記錄)

# 計算 t_input 的函數
def calculate_t_input(k):
    return (n * (k + 1) / S) * (t_s + t_l) + n * t_t

# 生成 k 的值 (從 2 到 64)
k_values = [2, 10, 20, 30, 40, 50, 60, 64]
t_input_values = [calculate_t_input(k) for k in k_values]

# 繪製圖表
plt.figure(figsize=(10, 6))
plt.plot(k_values, t_input_values, marker='o', color='#4CAF50', label='總輸入時間 (秒)')
plt.fill_between(k_values, t_input_values, color='rgba(76, 175, 80, 0.2)')
plt.xlabel('k (合併路數)')
plt.ylabel('總輸入時間 (秒)')
plt.title('總輸入時間 t_input 對 k 的圖表')
plt.grid(True)
plt.legend()
plt.show()