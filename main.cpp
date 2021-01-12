#include <iostream>
#include <memory>
#include <array>

/*
 * Задача 1
 * Вычислить простые числа до N и
 * записать их в массив. Вернет количество простых чисел
 */
//вариант с функцией
int calculatePrimeNumbers(int *resArr, int n) {
    //выделяю память под решето Эратосфена
    int *arr = new int[(n + 1)];

    //заполняю решето
    for(auto i = 0; i <= n; i++) {
        arr[i] = i;
    }

    int primeNumbsCnt = 0;

    for(auto i = 2; i <= n; i++) {
        //если k простое
        if(arr[i] != 0) {
            resArr[primeNumbsCnt] = arr[i];
            primeNumbsCnt++;
            //вычеркиваю кратные n
            for(auto j = (i * i); j <= n; j +=i ) {
                arr[j] = 0;
            }
        }
    }

    return primeNumbsCnt;
}

int main() {
    int N = 100;


    //вариант с функцией
    //массив для простых чисел
    int *prime = new int[(N + 1)];
    //получаю заполненный простыми числами массив
    auto prNumbsCnt = calculatePrimeNumbers(prime, 100);
    //вывожу на экран
    for(decltype(prNumbsCnt) i = 0; i < (prNumbsCnt); i++) {
        std::cout << prime[i] << std::endl;
    }

    //вариант с лямбдой
    //массив для простых чисел
    /*int *prime = new int[(N + 1)];
    //получаю лямбду
    auto calcPrNumbs = [&](int *resArr, int n) {
        //выделяю память под решето Эратосфена
        int *arr = new int[(n + 1)];

        //заполняю решето
        for(auto i = 0; i <= n; i++) {
            arr[i] = i;
        }

        int primeNumbsCnt = 0;

        for(auto i = 2; i <= n; i++) {
            //если k простое
            if(arr[i] != 0) {
                resArr[primeNumbsCnt] = arr[i];
                primeNumbsCnt++;
                //вычеркиваю кратные n
                for(auto j = (i * i); j <= n; j +=i ) {
                    arr[j] = 0;
                }
            }
        }

        return primeNumbsCnt;
    };

    //получаю заполненный простыми числами массив
    decltype(auto) prNumbsCnt = calcPrNumbs(prime, 100);

    //вывожу на экран
    for(decltype(prNumbsCnt) i = 0; i < (prNumbsCnt); i++) {
        std::cout << prime[i] << std::endl;
    }*/

    return 0;
}
