#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

class IntArray {
private:
    int* data;      // Указатель на данные массива
    int size;       // Размер массива

public:
    // Конструктор, получающий размер массива
    IntArray(int arraySize) {
        if (arraySize <= 0) {
            size = 1; // Минимальный размер
        }
        else {
            size = arraySize;
        }

        data = new int[size];
        // Инициализация нулями
        for (int i = 0; i < size; i++) {
            data[i] = 0;
        }
        cout << "Создан массив размера " << size << endl;
    }

    // Конструктор копирования
    IntArray(const IntArray& other) {
        size = other.size;
        data = new int[size];

        // Копирование данных
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
        cout << "Создана копия массива размера " << size << endl;
    }

    // Деструктор
    ~IntArray() {
        delete[] data;
        cout << "Массив размера " << size << " удален" << endl;
    }

    // Функция вывода всех значений массива
    void print() const {
        cout << "Массив [размер: " << size << "]: ";
        for (int i = 0; i < size; i++) {
            cout << data[i];
            if (i < size - 1) {
                cout << ", ";
            }
        }
        cout << endl;
    }

    // Сеттер (установка значения по индексу)
    bool setValue(int index, int value) {
        // Проверка выхода за границы массива
        if (index < 0 || index >= size) {
            cout << "Ошибка: индекс " << index << " выходит за границы массива [0, " << size - 1 << "]!" << endl;
            return false;
        }

        // Проверка значения на принадлежность промежутку [-100, 100]
        if (value < -100 || value > 100) {
            cout << "Ошибка: значение " << value << " должно быть в диапазоне [-100, 100]!" << endl;
            return false;
        }

        data[index] = value;
        cout << "Установлено значение " << value << " по индексу " << index << endl;
        return true;
    }

    // Геттер (получение значения по индексу)
    bool getValue(int index, int& value) const {
        // Проверка выхода за границы массива
        if (index < 0 || index >= size) {
            cout << "Ошибка: индекс " << index << " выходит за границы массива [0, " << size - 1 << "]!" << endl;
            return false;
        }

        value = data[index];
        return true;
    }

    // Добавление значения в конец массива
    void append(int value) {
        // Проверка значения на принадлежность промежутку [-100, 100]
        if (value < -100 || value > 100) {
            cout << "Ошибка: значение " << value << " должно быть в диапазоне [-100, 100]!" << endl;
            return;
        }

        // Создаем новый массив на 1 элемент больше
        int newSize = size + 1;
        int* newData = new int[newSize];

        // Копируем старые данные
        for (int i = 0; i < size; i++) {
            newData[i] = data[i];
        }

        // Добавляем новое значение
        newData[size] = value;

        // Освобождаем старую память и обновляем указатель и размер
        delete[] data;
        data = newData;
        size = newSize;

        cout << "Значение " << value << " добавлено в конец массива. Новый размер: " << size << endl;
    }

    // Операция сложения массивов
    IntArray add(const IntArray& other) const {
        int maxSize = (size > other.size) ? size : other.size;
        IntArray result(maxSize);

        for (int i = 0; i < maxSize; i++) {
            int sum = 0;

            // Берем элемент из первого массива, если индекс в пределах
            if (i < size) {
                sum += data[i];
            }

            // Берем элемент из второго массива, если индекс в пределах
            if (i < other.size) {
                sum += other.data[i];
            }

            // Ограничиваем сумму диапазоном [-100, 100]
            if (sum < -100) sum = -100;
            if (sum > 100) sum = 100;

            result.data[i] = sum;
        }

        cout << "Выполнено сложение массивов" << endl;
        return result;
    }

    // Операция вычитания массивов
    IntArray subtract(const IntArray& other) const {
        int maxSize = (size > other.size) ? size : other.size;
        IntArray result(maxSize);

        for (int i = 0; i < maxSize; i++) {
            int diff = 0;

            // Берем элемент из первого массива, если индекс в пределах
            if (i < size) {
                diff += data[i];
            }

            // Вычитаем элемент из второго массива, если индекс в пределах
            if (i < other.size) {
                diff -= other.data[i];
            }

            // Ограничиваем разность диапазоном [-100, 100]
            if (diff < -100) diff = -100;
            if (diff > 100) diff = 100;

            result.data[i] = diff;
        }

        cout << "Выполнено вычитание массивов" << endl;
        return result;
    }

    // Получение размера массива
    int getSize() const { return size; }
};

// Наследник с дополнительными методами
class EnhancedIntArray : public IntArray {
public:
    // Конструкторы
    EnhancedIntArray(int arraySize) : IntArray(arraySize) {}
    EnhancedIntArray(const IntArray& other) : IntArray(other) {}

    // Новые методы
    double calculateAverage() const {
        if (getSize() == 0) {
            return 0.0;
        }

        int sum = 0;
        int size = getSize();

        for (int i = 0; i < size; i++) {
            int value;
            if (getValue(i, value)) {
                sum += value;
            }
        }

        return static_cast<double>(sum) / size;
    }

    double calculateMedian() const {
        int size = getSize();

        if (size == 0) {
            return 0.0;
        }

        vector<int> sortedData;
        for (int i = 0; i < size; i++) {
            int value;
            if (getValue(i, value)) {
                sortedData.push_back(value);
            }
        }

        sort(sortedData.begin(), sortedData.end());

        if (size % 2 == 1) {
            return sortedData[size / 2];
        }
        else {
            return (sortedData[size / 2 - 1] + sortedData[size / 2]) / 2.0;
        }
    }

    int findMin() const {
        if (getSize() == 0) {
            return 0;
        }

        int minVal;
        getValue(0, minVal);

        for (int i = 1; i < getSize(); i++) {
            int current;
            if (getValue(i, current)) {
                if (current < minVal) {
                    minVal = current;
                }
            }
        }

        return minVal;
    }

    int findMax() const {
        if (getSize() == 0) {
            return 0;
        }

        int maxVal;
        getValue(0, maxVal);

        for (int i = 1; i < getSize(); i++) {
            int current;
            if (getValue(i, current)) {
                if (current > maxVal) {
                    maxVal = current;
                }
            }
        }

        return maxVal;
    }
};

int main() {
    setlocale(LC_ALL, "RU");
    cout << "=== Тестирование класса IntArray ===" << endl;

    // Задание 1: Создание массива
    cout << "\n1. Создание массива размера 3:" << endl;
    EnhancedIntArray arr1(3);
    arr1.print();

    // Тестирование сеттера и геттера
    cout << "\n2. Установка значений:" << endl;
    arr1.setValue(0, 10);
    arr1.setValue(1, 50);
    arr1.setValue(2, -30);
    arr1.print();

    // Проверка ошибок
    cout << "\n3. Проверка обработки ошибок:" << endl;
    arr1.setValue(5, 20);  // Неверный индекс
    arr1.setValue(1, 150); // Неверное значение

    // Тестирование геттера
    cout << "\n4. Тестирование геттера:" << endl;
    int value;
    if (arr1.getValue(1, value)) {
        cout << "Значение по индексу 1: " << value << endl;
    }

    // Задание 2: Конструктор копирования
    cout << "\n5. Тестирование конструктора копирования:" << endl;
    EnhancedIntArray arr2 = arr1;
    cout << "Оригинал: ";
    arr1.print();
    cout << "Копия: ";
    arr2.print();

    // Задание 3: Добавление в конец
    cout << "\n6. Добавление значений в конец:" << endl;
    arr1.append(80);
    arr1.append(-90);
    arr1.print();

    // Попытка добавить неверное значение
    arr1.append(150);

    // Задание 4: Операции с массивами
    cout << "\n7. Операции с массивами:" << endl;

    EnhancedIntArray arrA(3);
    arrA.setValue(0, 10);
    arrA.setValue(1, 20);
    arrA.setValue(2, 30);

    EnhancedIntArray arrB(2);
    arrB.setValue(0, 5);
    arrB.setValue(1, 15);

    cout << "Массив A: ";
    arrA.print();
    cout << "Массив B: ";
    arrB.print();

    // Сложение
    EnhancedIntArray sum = arrA.add(arrB);
    cout << "A + B: ";
    sum.print();

    // Вычитание
    EnhancedIntArray diff = arrA.subtract(arrB);
    cout << "A - B: ";
    diff.print();

    // Тестирование с массивами разной длины
    cout << "\n8. Тестирование с массивами разной длины:" << endl;

    EnhancedIntArray arrShort(2);
    arrShort.setValue(0, 40);
    arrShort.setValue(1, 60);

    EnhancedIntArray arrLong(4);
    arrLong.setValue(0, 1);
    arrLong.setValue(1, 2);
    arrLong.setValue(2, 3);
    arrLong.setValue(3, 4);

    cout << "Короткий массив: ";
    arrShort.print();
    cout << "Длинный массив: ";
    arrLong.print();

    EnhancedIntArray sum2 = arrShort.add(arrLong);
    cout << "Короткий + Длинный: ";
    sum2.print();

    // доп методы для наследуемого
    cout << "\nТестирование дополнительных методов" << endl;

    cout << "\n9. Статистические методы для массива A:" << endl;
    cout << "Массив A: ";
    arrA.print();
    cout << "Среднее значение: " << arrA.calculateAverage() << endl;
    cout << "Медианное значение: " << arrA.calculateMedian() << endl;
    cout << "Наименьший элемент: " << arrA.findMin() << endl;
    cout << "Наибольший элемент: " << arrA.findMax() << endl;

    cout << "\n10. Статистические методы для массива arr1:" << endl;
    cout << "Массив arr1: ";
    arr1.print();
    cout << "Среднее значение: " << arr1.calculateAverage() << endl;
    cout << "Медианное значение: " << arr1.calculateMedian() << endl;
    cout << "Наименьший элемент: " << arr1.findMin() << endl;
    cout << "Наибольший элемент: " << arr1.findMax() << endl;

    cout << "\n=== Программа завершена ===" << endl;

    return 0;
}