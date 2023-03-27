#include "LFSR_Galois.h"

/**
 * @brief Конструктор по-умолчанию.
 * @file LFSR_Galois.cpp
 */
LFSR_Galois::LFSR_Galois()
{
}
/**
 * @brief Функция, принимающая на вход число. Выводит число по битам.
 * @param bits
 */
void LFSR_Galois::print_bits(uint64_t bits)
{
	int N(num_bits);
	for (int i = N-1; i>=0; i--) {
		if (bits & ((uint64_t)1<<i)) cout<<"1";
		else cout<<"0";
	}
	cout<<endl;
}
/**
 * @brief Функция, принимающая на вход число. Переворачивает число.
 * @param bits
 * @return Перевёрнутое число
 * @throw GaloisError, если число равно нулю
 */
uint64_t  LFSR_Galois::reverse_bits(uint64_t bits)
{
	if (bits==0) {
		throw GaloisError("Число не может быть равно нулю.");
	}
	uint64_t val_mirror = 0;
	for (int N(num_bits); N > 0; --N) {
		val_mirror <<= 1;
		val_mirror |= (bits & 1);
		bits >>= 1;
	}
	return val_mirror;
}
/**
 * @brief Функция генерирует случайное 64-х битное число.
 * @return Случайное число
 */
uint64_t  LFSR_Galois::get_random_bits()
{
	random_device rd;
	mt19937_64 rnd(rd());
	return rnd();
}
/**
 * @brief Функция принимает на вход число. Устанавливает начальный регистр.
 * @param bits
 * @throw GaloisError, если число равно нулю
 */
void LFSR_Galois::set_start_bits(uint64_t bits)
{
	start_bits = bits;
	if (start_bits == 0) {
		throw GaloisError("Начальное число не может быть равно нулю");
	}
}
/**
 * @brief Функция возвращает начальный регистр.
 * @return Начальный регистр
 */
uint64_t LFSR_Galois::get_start_bits()
{
	return start_bits;
}
/**
 * @brief Функция принимает на вход булеву переменную. Генерирует псевдослучайное число.
 * @param is_random_bits
 * @return Псевдослучайное число
 */
uint64_t LFSR_Galois::get_respond_bits(bool is_random_bits)
{
	uint64_t respond_bits = 0;
	if (is_random_bits == true) start_bits = get_random_bits();
	for (int i = 0 ; i<=num_numbers; i++) {
		if (start_bits & first_bit) {
			start_bits = ((start_bits^reverse_bits(polinom_bits)) >> (uint64_t)1) | last_bit;
			respond_bits |= first_bit;
			respond_bits <<= (uint64_t) 1;

		} else {
			respond_bits <<= (uint64_t) 1;
			start_bits>>=(uint64_t) 1;
		}
	}
	return respond_bits;
}
