import numpy as np
import math

## Создание матрицы и пунктов назначения ##

with open("input.txt", "r") as input:   #считываем данные из файла, разделяем всё по строкам
    data = input.read().split("\n")

names = []  #создаем список имен - названий вершин, знаем, что первая строка в файле их содержит
for i in data[0].split(" "):
    names.append(i)

A = np.full((len(names), len(names)), math.inf) #создаем матрицу из бесконечностей

for i in range(len(names)):     #начинаем заполнение матрицы весами ребер
    A[i][i] = 0     #присваиваем нули по диагоналям
    connection = data[i+1].split(" ")       #знаем, что каждая следующая строка, после первой, содержит в себе название соединённых вершин и длину соединяющего их ребра
    for x in range(len(names)):
        if (connection[0] == names[x]):     #ищем первую вершину, указанную в строчке
            for y in range(x, len(names), 1):       #ищем вторую вершину, указанную в строчке. Также знаем, что она гарантированно будет дальше по номеру, относительно первой вершины
                if (connection[1] == names[y]):     #если это не гарантированно, то range(len(names))
                    A[x][y] = connection[2]     #заполняем матрицу(получается симметричной)
                    A[y][x] = connection[2]

dest = data[len(data) - 1].split(" ")       #записываем начало и конец пути в переменные, зная, что в файле эта информация на последней строке

for i in range(len(names)):
    if(dest[0] == names[i]):
        start = i
    if (dest[1] == names[i]):
        end = i

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

Weight = [math.inf]*len(names)      #последняя строка таблицы

Viewed = {start}        #просмотренные вершины
Weight[start] = 0       #нулевой вес для стартовой вершины
Optimal = [0]*len(names)        #оптимальные связи между вершинами

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

#записываем полученный путь в файл

with open("output_from_Kris.txt", "w") as output:
    for i in range(len(P)-1, 0, -1):
        output.write(names[P[i]] + "\n")
    output.write(names[P[0]])
