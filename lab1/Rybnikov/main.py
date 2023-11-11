def generate_young_diagrams(n):
    # Функция для генерации разбиений числа n на m слагаемых
    def partition(n, m):
        # Базовые случаи:
        # Если n равно 0, возвращаем пустое разбиение
        if n == 0:
            return [[]]
        # Если m равно 0 или n меньше 0, возвращаем пустой список
        if m == 0 or n < 0:
            return []

        # Генерируем разбиения с m включенным в первое слагаемое
        with_m = [[m] + sub for sub in partition(n - m, m)]
        # Генерируем разбиения без m
        without_m = partition(n, m - 1)

        # Возвращаем объединение разбиений с m и без m
        return without_m + with_m

    # Функция для преобразования диаграммы Юнга в строку
    def young_diagram_to_string(young_diagram):
        return ' '.join(map(str, young_diagram))

    # Открываем файл для записи результатов
    with open('output.txt', 'w') as output_file:
        # Генерируем и записываем диаграммы для каждого уровня от 1 до n
        for level in range(1, n + 1):
            # Получаем диаграммы для текущего уровня
            diagrams = partition(level, level)
            # Записываем информацию о количестве диаграмм на текущем уровне
            output_file.write(f"Level {level}. Count: {len(diagrams)}\n")
            # Записываем сами диаграммы
            for diagram in diagrams:
                output_file.write(young_diagram_to_string(diagram) + '\n')


if __name__ == "__main__":
    N = int(input("N = "))  # Задайте значение N
    generate_young_diagrams(N)
