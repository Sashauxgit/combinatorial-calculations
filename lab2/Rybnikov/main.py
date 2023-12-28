def shift_and_put(row_list, column, new_value):
    new_row = []
    i = 0
    while i < len(row_list):
        if (i == column):
            new_row.append(new_value)
            i -= 1
            column = -1
        else:
            new_row.append(row_list[i])
        i += 1
    return new_row


def RSK_shift(table_p, new_value, column=0):
    row = 0
    while True:
        if len(table_p) == row:
            table_p.append([new_value])
            return row, column
        if len(table_p[row]) == column:
            table_p[row].append(new_value)
            return row, column
        if table_p[0][column] > new_value:
            table_p[0] = shift_and_put(table_p[0], column, new_value)
            return 0, len(table_p[0]) - 1
        if table_p[row][column] > new_value:
            temp_new_value = table_p[row][column]
            table_p[row][column] = new_value
            row, column = RSK_shift(table_p, temp_new_value, column + 1)
            return row, column
        row += 1




def fill_Q(table_q, row, column, step):
    if len(table_q) == row:
        table_q.append([step])
    elif len(table_q[row]) == column:
        table_q[row].append(step)


def RSK(permutation):
    table_p = []
    table_q = []
    for i in range(len(permutation)):
        row, column = RSK_shift(table_p, permutation[i])
        fill_Q(table_q, row, column, i + 1)
    return table_p, table_q


def knut(permutation1, permutation2):
    if len(permutation1) != len(permutation2):
        return
    p1, q1 = RSK(permutation1)
    p2, q2 = RSK(permutation2)
    flags = [0, 0]
    if p1 == p2:
        flags[0] = 1
    if q1 == q2:
        flags[1] = 1
    return flags


with open('input.txt', 'r') as f:
    permutation1 = list(map(int, f.readline().split(' ')))
    permutation2 = list(map(int, f.readline().split(' ')))
ans = knut(permutation1, permutation2)
if ans[0] == 1:
    print("Эквивалентные по Кнуту")
if ans[1] == 1:
    print("Двойственно эквивалентные по Кнуту")
if ans[0] == 0 and ans[1] == 0:
    print("Не принадлежат одному классу (двойственной) эквивалентности по Кнуту.")