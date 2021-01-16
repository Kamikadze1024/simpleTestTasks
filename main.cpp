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
//Элемент списка
template<typename T>
struct ListNode {
    ListNode*  m_next;
    T          m_data;

    ListNode(ListNode* next, T data) : m_next(next), m_data(data) {}
};

//сам список
template<typename A>
class SimpleList {
private:
    ListNode<A> *m_first;
    ListNode<A> *m_last;
    int          m_size;

public:
    SimpleList() : m_first(nullptr), m_last(nullptr), m_size(0) {}
    ~SimpleList();

    //итератор
    template<typename T>
    class Iterator {
        //указатель на текущий узел
        ListNode<T>      *m_node;
        //указатель на список
        const SimpleList *m_list;

    public:
        Iterator(const SimpleList* list, ListNode<T>* node):
            m_node(node), m_list(list) {}

        //возвращает данные ноды при *it
        T& operator*() { return m_node->m_data; }

        //проверка итераторов на неравенство
        bool operator!=(const Iterator &lhs) const {
            return ((this->m_list != lhs.m_list)
                    || (this->m_node != lhs.m_node));
        }

        //проверка итераторов на равенство
        bool operator==(const Iterator &lhs) const {
            return ((this->m_list == lhs.m_list)
                    && (this->m_node == lhs.m_node));
        }

        //получить итератор на следующий элемени
        Iterator next() const {
            if(m_node != nullptr) {
                return Iterator(m_list, m_node->m_next);
            }
            return *this;
        }

        //инкремент итератора
        Iterator& operator++() {
            if(m_node != nullptr) {
                m_node = m_node->m_next;
            }
            return *this;
        }
    };

    //вернуть итератор на первый элемент
    Iterator<A> begin() {
        return Iterator<A>(this, m_first);
    }

    //вернуть итератор на последний элемент
    Iterator<A> end() {
        return Iterator<A>(this, m_last);
    }

    void push_back(A &value) {
        ListNode<A> *newNode = new ListNode<A>(nullptr, value);
        if(m_first == nullptr) {
            m_first = newNode;
            m_last  = newNode;
            return;
        }
        m_last->m_next = newNode;
        m_last = newNode;
    }

    //размер списка
    int size() const noexcept {
        return m_size;
    }
};



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
    SimpleList<int> sl;
    for(int i = 0; i < 13; i++) {
        sl.push_back(i);
    }

    SimpleList<int>::Iterator it = sl.begin();
    for(; it != sl.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}
