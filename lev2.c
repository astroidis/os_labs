#include <stdio.h>
#include <wctype.h>
#include <wchar.h>
#include <locale.h>

int main(){
    setlocale(LC_ALL, "ru_RU.UTF-8");
    wint_t a = L'\x440';

    putwchar(a);
    putwchar(towupper(a));
    putwchar('\n');

    return 0;
}
