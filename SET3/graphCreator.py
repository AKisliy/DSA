import pandas as pd
import matplotlib.pyplot as plt

# загрузим данные с github
data = pd.read_csv("https://raw.githubusercontent.com/AKisliy/DSA/main/SET3/data/sort_results.csv")

# какие сортировки и массивы вообще есть
sort_names = data['Sort Name'].unique()
array_names = data['Array Name'].unique()

# сделаем два общих графика - для времени и сравнений
fig, ax = plt.subplots(2, 1, figsize=(12, 12))

for sort_name in sort_names:
    for array_name in array_names:
        subset = data[(data['Sort Name'] == sort_name) & (data['Array Name'] == array_name)]

        ax[0].plot(subset[' Array Size'], subset[' Time'], marker='o', label=f"{sort_name} - {array_name}")

        ax[1].plot(subset[' Array Size'], subset[' Comparisons'], marker='o', label=f"{sort_name} - {array_name}")

ax[0].set_title('Sorting Time vs Array Size')
ax[0].set_xlabel('Array Size')
ax[0].set_ylabel('Time (ms)')
ax[0].legend()
ax[0].grid(True)

ax[1].set_title('Comparisons vs Array Size')
ax[1].set_xlabel('Array Size')
ax[1].set_ylabel('Comparisons')
ax[1].legend()
ax[1].grid(True)

plt.tight_layout()
plt.show()

# создание графиков для каждой сортировки
for sort_name in sort_names:
    fig, ax = plt.subplots(2, 1, figsize=(10, 10))  # Две оси на одной фигуре для каждой сортировки

    sort_data = data[data['Sort Name'] == sort_name]

    array_names = sort_data['Array Name'].unique()

    for array_name in array_names:
        subset = sort_data[sort_data['Array Name'] == array_name]
        ax[0].plot(subset[' Array Size'], subset[' Time'], marker='o', label=f"{array_name}")
        ax[1].plot(subset[' Array Size'], subset[' Comparisons'], marker='o', label=f"{array_name}")

    ax[0].set_title(f'Time vs Array Size for {sort_name}')
    ax[0].set_xlabel('Array Size')
    ax[0].set_ylabel('Time (ms)')
    ax[0].legend()
    ax[0].grid(True)

    ax[1].set_title(f'Comparisons vs Array Size for {sort_name}')
    ax[1].set_xlabel('Array Size')
    ax[1].set_ylabel('Comparisons')
    ax[1].legend()
    ax[1].grid(True)

    plt.tight_layout()
    plt.show()
