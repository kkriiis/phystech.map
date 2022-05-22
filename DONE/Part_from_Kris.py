import math

with open("input.txt", "r") as input:   #считываем данные из файла, разделяем всё по строкам
    data = input.read().split("\n")

names = { name: i for i, name in enumerate(data[0].split(" ")) }
len_names = len(names)

A = [[0 if i == j else math.inf
        for i in range(len_names)]
            for j in range(len_names)]

for i in range(1, len(data) - 1):
    x_name, y_name, edge_len = data[i].split(" ")
    x = names[x_name]
    y = names[y_name]
    A[x][y] = A[y][x] = int(edge_len)

dest = data[-1].split(" ")       #записываем начало и конец пути в переменные, зная, что в файле эта информация на последней строке

start = names[dest[0]]
end = names[dest[1]]

#функция для выбора следующего узла в наименьшим весом

def arg_min(Weight, Viewed):
    amin = -1
    amax = math.inf     #максимальное значение
    for i, t in enumerate(Weight):
        if(t < amax) and i not in Viewed:
            amax = t
            amin = i
    return amin

## Алгоритм Дейкстры ##

Weight = [math.inf]*len_names      #последняя строка таблицы

Viewed = {start}        #просмотренные вершины
Weight[start] = 0       #нулевой вес для стартовой вершины
Optimal = [0]*len_names        #оптимальные связи между вершинами

v = start
while v != -1:      #просматривавем все вершины
    for j, dw in enumerate(A[v]):       #перебираем все связанные вершины с вершиной v
        if j not in Viewed:     #если вершина ещё не просмотрена
            w = Weight[v] + dw
            if w < Weight[j]:
                Weight[j] = w
                Optimal[j] = v      #связываем вершину j с вершной v

    v = arg_min(Weight, Viewed)     #выбираем следующий узел с наименьшим весом
    if v >= 0:      #выбираем очередную вершину
        Viewed.add(v)       #добавляем новую вершину в рассмотренные

# формирование оптимального маршрута:
P = [end]
while end != start:
    end = Optimal[P[-1]]
    P.append(end)

print(P)
road = []
for i in range(len(P)-1, -1, -1):
    for key, value in names.items():
        if value == P[i]:
            road.append(key)

with open("output_from_Kris.txt", "w") as output:
    output.write(" ".join(road[i] for i in range(len(road))))