#include <iostream>
#include <memory>
#include <array>
#include <map>

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

/*
 * Задача 2
 * Написать функцию, которая считает количество слов каждой длины
 * работает только с ASCII
 */
std::map<int, int> exercise2(std::string &str) {
    int cntr = 0;
    std::map<int, int> res;

    for(unsigned int i = 0; i < str.length(); i++) {
        char c = str[i];
        if((c == ' ') || (i == (str.length() - 1))) {
            if(cntr != 0) {
                if(i == (str.length() - 1)) {
                    cntr++;
                }
                res[cntr]++;
                cntr = 0;
            }
        } else {
            cntr++;
        }
    }
    return res;
}


int main() {
    //Задача 1
    /*int N = 100;

    //вариант с функцией
    //массив для простых чисел
    int *prime = new int[(N + 1)];
    //получаю заполненный простыми числами массив
    auto prNumbsCnt = calculatePrimeNumbers(prime, 100);
    //вывожу на экран
    for(decltype(prNumbsCnt) i = 0; i < (prNumbsCnt); i++) {
        std::cout << prime[i] << std::endl;
    }*/

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

    //Задача 2
    std::cout << "Введите строку:" << std::endl;
    std::string msg;
    std::getline(std::cin, msg);

    std::map<int, int> res = exercise2(msg);

    for(auto v : res) {
        std::cout << v.first << " " << v.second << std::endl;
    }

    return 0;
}
