#include <stdio.h>
#include <limits.h>
#include "ft_printf.h"  // Replace with the actual header file for your ft_printf


void test_char() {
    char chars[] = {'A', 'z', '\0', 127};
    for (int i = 0; i < 4; i++) {
        printf("Char Test %d\n", i+1);
        printf("printf:     |%c|\n", chars[i]);
        ft_printf("ft_printf:  |%c|\n\n", chars[i]);
    }
}

void test_string() {
    char *strings[] = {"Hello, World!", "", "A longer string with multiple words.", NULL};
    for (int i = 0; i < 4; i++) {
        printf("String Test %d\n", i+1);
        printf("printf:     |%s|\n", strings[i]);
        ft_printf("ft_printf:  |%s|\n\n", strings[i]);
    }
}

void test_pointer() {
    void *pointers[] = {(void*)0x123456789ABCDEF, NULL, (void*)42};
    for (int i = 0; i < 3; i++) {
        printf("Pointer Test %d\n", i+1);
        printf("printf:     |%p|\n", pointers[i]);
        ft_printf("ft_printf:  |%p|\n\n", pointers[i]);
    }
}

void test_decimal() {
    int decimals[] = {-42, 0, 123456, INT_MIN, INT_MAX};
    for (int i = 0; i < 5; i++) {
        printf("Decimal Test %d\n", i+1);
        printf("printf:     |%d|\n", decimals[i]);
        ft_printf("ft_printf:  |%d|\n\n", decimals[i]);
    }
}

void test_integer() {
    int integers[] = {42, 0, -98765, INT_MIN, INT_MAX};
    for (int i = 0; i < 5; i++) {
        printf("Integer Test %d\n", i+1);
        printf("printf:     |%i|\n", integers[i]);
        ft_printf("ft_printf:  |%i|\n\n", integers[i]);
    }
}

void test_unsigned() {
    unsigned int unsigneds[] = {42, 0, 98765, UINT_MAX};
    for (int i = 0; i < 4; i++) {
        printf("Unsigned Test %d\n", i+1);
        printf("printf:     |%u|\n", unsigneds[i]);
        ft_printf("ft_printf:  |%u|\n\n", unsigneds[i]);
    }
}

void test_hex_lower() {
    unsigned int hex_lower[] = {0xabcdef, 0, 0x12345678, UINT_MAX};
    for (int i = 0; i < 4; i++) {
        printf("Hex Lower Test %d\n", i+1);
        printf("printf:     |%x|\n", hex_lower[i]);
        ft_printf("ft_printf:  |%x|\n\n", hex_lower[i]);
    }
}

void test_hex_upper() {
    unsigned int hex_upper[] = {0xABCDEF, 0, 0x12345678, UINT_MAX};
    for (int i = 0; i < 4; i++) {
        printf("Hex Upper Test %d\n", i+1);
        printf("printf:     |%X|\n", hex_upper[i]);
        ft_printf("ft_printf:  |%X|\n\n", hex_upper[i]);
    }
}

void test_percent() {
    printf("Percent Test\n");
    printf("printf:     |%%|\n");
    ft_printf("ft_printf:  |%%|\n\n");
}


void test_random_pointer()
{
    int i = 42;
    printf("Pointer test: %p\n", &i);
    ft_printf("Pointer test: %p\n", &i);
}

int main() {
    test_char();
    test_string();
    test_pointer();
    test_decimal();
    test_integer();
    test_unsigned();
    test_hex_lower();
    test_hex_upper();
    test_percent();
    test_random_pointer();
    return 0;
}
