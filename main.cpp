#include <iostream>
#include <memory>
#include <array>
#include <map>
#include <iterator>

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

/*
 * Задача 3
 * Реализовать функцию, которая удаляет каждый пятый элемент
 * из списка.
 * Список:
 * struct List {
 *     struct List* next;
 *     SomeDataType payload;
 * };
 */
static const int CONST_ELEM_NUM = 5;
//Элемент списка
template<typename T>
struct ListNode {
    ListNode*  m_next;
    T          m_data;

    ListNode(ListNode* next, T data) : m_next(next), m_data(data) {}
};

template<typename T>
int removeEveryFifth(ListNode<T> *first, ListNode<T> *last, int size) {
    if(size < (CONST_ELEM_NUM - 1)) {
        return - 1;
    }

    int decimator   = 0;
    int sizeCounter = size;
    ListNode<T> *curr  = first;
    ListNode<T> *currM = nullptr;;
    while(true) {
        if(curr == last) {
            if(decimator == (CONST_ELEM_NUM - 1)) {
                last = currM;
                currM->m_next = nullptr;
                delete curr;
                sizeCounter--;
            }
            break;
        }

        if(decimator == (CONST_ELEM_NUM - 1)) {
            currM->m_next = curr->m_next;
            delete curr;
            curr = currM->m_next;
            sizeCounter--;
            decimator = 0;
            continue;
        }

        decimator++;
        currM = curr;
        curr  = curr->m_next;
    }
    return sizeCounter;
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
    /*std::cout << "Введите строку:" << std::endl;
    std::string msg;
    std::getline(std::cin, msg);

    std::map<int, int> res = exercise2(msg);

    for(auto v : res) {
        std::cout << v.first << " " << v.second << std::endl;
    }*/

    //Задача 3
    //инициализирую список
    ListNode<int> *first = nullptr;
    ListNode<int> *last  = nullptr;
    int            size  = 0;
    for(int i = 0; i < 10; i++) {
        ListNode<int> *ln = new ListNode<int>(nullptr, i);
        if(first == nullptr) {
            first = ln;
            last  = first;
        } else {
            last->m_next = ln;
            last = ln;
        }
        size++;
    }

    //удаление каждого пятого
    int newSize = removeEveryFifth(first, last, size);

    if(newSize < 0) {
        std::cout << "Элементов в списке слишком мало" << std::endl;
        return 0;
    }

    //вывод результата
    ListNode<int> *curr = first;
    for(int i = 0; i < newSize; i++) {
        std::cout << curr->m_data << " ";
        curr = curr->m_next;
    }
    std::cout << std::endl;

    return 0;
}
