## Расчет выработки органов регулирования поглощающих стержней средств управления и защиты.

## Описание:

Настоящий проект позволяет рассчитать выработку каждого поглощающего стержня в активной зоне реактора с использованием архивных данных за все кампании с учетом  их перестановок при переходе из одной кампании в другую.

## Инструкция по развертыванию:

В корневом каталоге программы должны находиться следующие папки:
- answer — в данной папке по результату работы программы формируется отчетная информация, определяющая состояние датчиков;
- input_data — содержит архивные данные с положением поглощающих стержней в течении кампаний;
- input_names — содержит условные номера поглощающих стержней, а также информацию об их перестановках.

## Использовано:
- Стандарт языка С++17;
- Библиотека STL контейнеров;
- Алгоритмы.

## Последовательность действий для запуска программы:
1) В папку input_data расположить архивы с положением поглощающих стержней в течении нескольких кампаний.
2) В папку  input_names расположить информацию о перестановках поглощающих стержней и массив соответствия координат ячейки номерам ячеек.
3) После запуска исполняемого файла необходимо ввести номер блока — шаг архивных данных (HOUR, Minutes), количество кампаний подлежащих анализу.
4) По окончанию работы программы в папке  answer  формируется отчетная информация, о наработке поглощающих стержней. В отчетном документе answer/Teff_SUZ_total.csv появляется информация о наработке поглощающих стержней.

## Программа является моей разработкой
