import matplotlib.pyplot as plt
import numpy as np
from scipy import optimize

# 配置中文字体支持
plt.rcParams['font.sans-serif'] = ['SimHei']  # 指定默认字体为黑体
plt.rcParams['axes.unicode_minus'] = False  # 解决保存图像时负号'-'显示为方块的问题

# 数据点
data = [1.045804, 11.915978, 138.41495]
n_values = [1e3, 1e4, 1e5]  # 对应的数据规模

# 定义拟合函数 f(n) = k * n * log(n)
def func(n, k):
    return k * n * np.log(n)

# 使用scipy进行曲线拟合
params, params_covariance = optimize.curve_fit(func, n_values, data)
k = params[0]  # 获取拟合参数k

# 创建更密集的x值用于绘制平滑曲线
x_smooth = np.logspace(3, 5, 100)  # 在10^3到10^5之间取100个点
y_smooth = func(x_smooth, k)

# 创建图形和坐标轴
plt.figure(figsize=(10, 6))

# 绘制原始数据点
plt.scatter(n_values, data, color='red', s=80, label='实际数据')

# 绘制拟合曲线
plt.plot(x_smooth, y_smooth, 'b-', label=f'拟合曲线: {k:.8f} · n · log(n)')

# 添加标题和标签
plt.title('数据拟合与时间复杂度分析', fontsize=16)
plt.xlabel('数据规模 (n)', fontsize=14)
plt.ylabel('执行时间 (ms)', fontsize=14)

# 使用对数刻度使曲线更容易观察
plt.xscale('log')
plt.yscale('log')

# 添加网格线以提高可读性
plt.grid(True, linestyle='--', alpha=0.7)

# 添加数据标签
for i, (x, y) in enumerate(zip(n_values, data)):
    plt.text(x, y*1.1, f'{y:.2f}ms', ha='center')

# 添加图例
plt.legend(loc='best')

# 优化显示范围
plt.tight_layout()

# 保存和显示图表
plt.savefig('complexity_fit.png')
plt.show()

# 输出拟合参数
print(f"拟合结果: T(n) ≈ {k:.8f} · n · log(n)")