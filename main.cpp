#include <iostream>
#include <memory>
#include <array>
#include <map>
#include <iterator>
#include <stack>

/*
 * Задача 1
 * Вычислить простые числа до N и
 * записать их в массив. Вернет количество простых чисел
 */
//для варианта с функцией
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

//для вызова задачи1 из main
void executeTask1() {
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
    int *prime2 = new int[(N + 1)];

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
    decltype(auto) prNumbsCnt2 = calcPrNumbs(prime2, 100);

    //вывожу на экран
    for(decltype(prNumbsCnt2) i = 0; i < (prNumbsCnt2); i++) {
        std::cout << prime2[i] << std::endl;
    }
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

//для вызова задачи 2 из main
void executeTask2() {
    std::cout << "Введите строку:" << std::endl;
    std::string msg;
    std::getline(std::cin, msg);

    std::map<int, int> res = exercise2(msg);

    for(auto v : res) {
        std::cout << v.first << " " << v.second << std::endl;
    }
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

//Для вызова задачи 3 из main
void executeTask3() {
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
        return;
    }

    //вывод результата
    ListNode<int> *curr = first;
    for(int i = 0; i < newSize; i++) {
        std::cout << curr->m_data << " ";
        curr = curr->m_next;
    }
    std::cout << std::endl;
}


/*
 * Задача 4.
 * Функция принимает 32 битное целое число без знака
 * и возвращает максимальное и минимальное 32-битные целые
 * числа, которые могут  быть получены с использованием
 * тех-же чисел битов, установленных в 1, что и во взятом
 * числе
 */
static const uint32_t CONST_BITS_IN_BYTE = 8;
std::pair<uint32_t, uint32_t> exercise4(uint32_t value) {
    //счетчики бит
    uint32_t fromYoung = 0;
    uint32_t fromOld   = CONST_BITS_IN_BYTE * sizeof(uint32_t) - 1;

    //выходные значения
    uint32_t maxVal = 0;
    uint32_t minVal = 0;
    for(uint32_t i = 0; i < (CONST_BITS_IN_BYTE * sizeof(uint32_t)); i++) {
        //подсчитываю биты и формирую min и max числа
        if((static_cast<bool>((1 << i) & value)) == true) {
            //пишу нужный бит в max мальное число
            maxVal |= (1 << fromOld);
            fromOld--;

            //пишу нужный бит в min мальное число
            minVal |= (1 << fromYoung);
            fromYoung++;
        }
    }

    //современный компилятор соптимизирует
    std::pair<uint32_t, uint32_t> res(maxVal, minVal);
    return res;
}

//Для вызова задачи 4 из main
void executeTask4() {
    std::pair<uint32_t, uint32_t> res = exercise4(255);

    std::cout << "Max: " << res.first << std::endl;
    std::cout << "Min: " << res.second << std::endl;
}

/*
 * Задача 5.
 * struct TreeNode {
 *     TreeNode *leftChild;
 *     TreeNode *rightChild;
 * };
 * Написать функцию, которая вычисляет глубину дерева.
 */

int maxLevel = 0;

struct TreeNode {
    std::string m_name;
    TreeNode *leftChild;
    TreeNode *rightChild;
};

//максимальная глубина
void maxDepth(TreeNode *root, int level) {
    if(root == nullptr) {
        return;
    }

    //спускаюсь в правое поддерево
    maxDepth(root->rightChild, (level + 1));

    for(auto i = 0; i < level; i++) {
        std::cout << "           ";
    }

    //вывожу данные, хранимые узлом
    std::cout << root->m_name << " " << level << std::endl;
    stackPath.push(root->m_name);

    //изменяю значения max глубины
    if(maxLevel < level) {
        maxLevel = level;
    }

    //спускаюсь в левое поддерево
    maxDepth(root->leftChild, (level + 1));
}

//функция создания нового узла
TreeNode *newNode(std::string name) {
    TreeNode *node = new TreeNode();
    node->m_name = name;
    node->leftChild = nullptr;
    node->rightChild = nullptr;
    return node;
}

//Для вызова задачи 5 из main
void executeTask5() {
    //построю дерево
    TreeNode *root = newNode("root");
    TreeNode *l1   = newNode("l1");
    TreeNode *r1   = newNode("r1");

    root->leftChild  = l1;
    root->rightChild = r1;

    TreeNode *l2   = newNode("l2");
    TreeNode *r2   = newNode("r2");
    l1->leftChild  = l2;
    l1->rightChild = r2;

    TreeNode *l22  = newNode("l22");
    TreeNode *r22  = newNode("r22");
    r1->leftChild  = l22;
    r1->rightChild = r22;

    TreeNode *l3 = newNode("l3");
    l22->leftChild = l3;

    maxDepth(root, 0);

    std::cout << "Максимальная глубина дерева = " << maxLevel << std::endl;
}

int main() {
    executeTask5();
    return 0;
}
