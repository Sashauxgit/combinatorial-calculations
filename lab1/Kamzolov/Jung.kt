import java.lang.IllegalArgumentException

fun nextCell(curTable: List<Int>, levelCounters: Map<Int, Int>, curTableCounters: Map<Int, Int>) {
    if (levelCounters.values.all { it == 0 }) {
        // если обработали все клетки, то выводим результат
        println(curTable.joinToString(separator = " "))
        return
    }

    levelCounters.keys.forEach { level ->
        val curLevelCounter = curTableCounters[level] ?: 0
        val prevLevelCounter = curTableCounters[level - 1] ?: 0
        if (levelCounters[level]!! > 0 && curLevelCounter < prevLevelCounter
            || level == 0 && levelCounters[0] != 0
        ) {
            nextCell(
                curTable = curTable + listOf(level),
                levelCounters = buildMap {
                    putAll(levelCounters)
                    put(level, levelCounters[level]!! - 1)
                },
                curTableCounters = buildMap {
                    putAll(curTableCounters)
                    put(level, curLevelCounter + 1)
                }
            )
        }
    }
}

fun main(args: Array<String> = arrayOf("3 2 1")) {
    val heights = args.getOrNull(0) // Чтение данных
        ?.split(' ')
        ?.map { it.toInt() }
        ?: throw IllegalArgumentException("Specify heights of Jung table")

    val levelCounters = mutableMapOf<Int, Int>()
    heights.forEach { height -> // инициализация мапы с соответствием количества клеток на каждой строке диаграммы Юнга
        (0 until height).forEach { level ->
            levelCounters[level] = levelCounters.getOrDefault(level, 0) + 1
        }
    }
    levelCounters[0] = levelCounters[0]!! - 1
    nextCell(
        curTable = listOf(0),
        levelCounters = levelCounters,
        curTableCounters = mapOf(0 to 1) // эта мапа хранит то, сколько клеток на каждом уровне на текущий момент
    )
}