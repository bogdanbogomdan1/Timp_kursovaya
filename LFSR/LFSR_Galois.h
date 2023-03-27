#pragma once
#include <iostream>
#include <random>
using namespace std;

/**
 * @class LFSR_Galois
 * @author bogdan
 * @date 09/15/21
 * @file LFSR_Galois.h
 * @brief Программа генерации псевдослучайно последовательности на базе регистра сдвига с линейной обратной связью с разрядностью 64 бит в конфигурации Галуа.
 */
class LFSR_Galois
{
private:
	uint64_t polinom_bits = 0xD800000000000000; ///< Полином, показывающий какие биты подвергаются операции XOR(64, 63, 61, 60)
	uint64_t first_bit = 0x0000000000000001; ///< Вспомогальная переменная, первый бит которой равен 1
	uint64_t last_bit = 0x8000000000000000; ///< Вспомогальная переменная, последний бит которой равен 1
	uint64_t start_bits = 0x0000000000000000; ///< Начальная позиция регистра
	const int num_bits = 64; ///< Длина регистра
	const int num_numbers = 64; ///< Количество сдвигов регистра

public:
	LFSR_Galois(); ///< Конструктор
	void print_bits(uint64_t bits); ///< Функция для вывода числа в битном представлении
	void set_start_bits(uint64_t bits); ///< Функция для установки начальной позиции
	uint64_t get_start_bits(); ///< Функция возвращает начальное значение
	uint64_t get_random_bits(); ///< Функция для генерации случайной начальной позиции
	uint64_t reverse_bits(uint64_t bits); ///< Функция для нахождения перевёрнутого числа
	uint64_t get_respond_bits(bool is_random_bits); ///< Функция для генерации псевдослучайного числа

};

/**
 * @brief Класс-исключение
 */
class GaloisError: public runtime_error
{
public:

	/**
	 * @brief Принимает си строку, поднимает исключение
	 * @param what_arg
	 */
	explicit GaloisError (const char* what_arg):
		runtime_error(what_arg) {}
};
