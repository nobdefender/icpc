// //Поиск простых чисел от 2 до N за O(N)
// //Поиск наименьших делителей
// //Если N до 2,5 млн., то достаточно uchar (1 байт), иначе short (2 байта)
// #include<vector>
// #include<cmath>
// #include<algorithm>

// template<class T>
// class prime {
// private:
//     std::vector<unsigned>pr;
//     std::vector<T>lp;//хранить индексы на pr, в которых находится наименьший делитель >1, или 0 - если число простое
// public:
//     prime() {};

//     //Находит наименьшие делители для чисел от 0 до limit включительно
//     prime(unsigned limit) {
//         lp.resize(++limit, 0);
//         pr.clear();
//         pr.push_back(1);
//         for (unsigned i = 2;i < limit;++i) {
//             register unsigned max_index = lp[i];
//             if (max_index == 0) {
//                 max_index = pr.size();
//                 pr.push_back(i);
//             }
//             register unsigned d;
//             for (unsigned j = 1;j <= max_index && (d = i * pr[j]) < limit;++j)
//                 lp[d] = j;
//         }
//     }

//     //Возвращает true, если число простое
//     //И false, если нет, или неизвесно
//     bool is_prime(unsigned number) {
//         return number < lp.size() && !lp[number];
//     }

//     //Возвращает порядковый номер простого числа за O( ln(pr.size()) )
//     //0 - если число не простое, или неизвестно
//     unsigned sequence_number(unsigned prime_number) {
//         if (!is_prime(prime_number))
//             return 0;
//         return std::lower_bound(pr.begin(), pr.end(), prime_number) - pr.begin();
//     }

//     //Возвращает простое число по его порядковому номеру,
//     //0 - если такого простого числа нет в pr
//     unsigned return_prime(unsigned sequence_number) {
//         if (sequence_number && sequence_number < pr.size())
//             return pr[sequence_number];
//         return 0;
//     }

//     //Возвращает наименьший делитель, 0 - если неизвесно
//     unsigned least_divisor(unsigned number) {
//         if (number >= lp.size())
//             return 0;
//         if (is_prime(number))
//             return number;
//         return pr[lp[number]];
//     }

//     //Возвращает наибольшее число, для которого известен наименьший делитель
//     unsigned limit() {
//         return lp.size() - 1;
//     }

//     //Возвращает факторизацию числа
//     std::vector<unsigned> factorize(unsigned number) {
//         std::vector<unsigned> v;
//         if (number < lp.size()) {
//             while (!is_prime(number)) {
//                 v.push_back(pr[lp[number]]);
//                 number /= pr[lp[number]];
//             }
//             v.push_back(number);
//         }
//         return v;
//     }
// };

// #include<iostream>
// #include<ctime>

// int main() {//Пример использования

//     clock_t t_start = clock();
//     prime<short>p(1e8);//249 (максимальный индекс)
//     clock_t t_finish = clock();

//     std::cout << "work_time = " << t_finish - t_start << "\n";

//     unsigned cnt_prime = 0;
//     for (unsigned i = 2; i <= 1e8; ++i)
//         if (p.is_prime(i))
//             cnt_prime++;
//     std::cout << "cnt_prime (1 to 1e8) = " << cnt_prime << std::endl;

//     std::cout << "number_prime (13) = " << p.sequence_number(13) << std::endl;

//     std::vector<unsigned> v = p.factorize(16);
//     unsigned mult = 1;
//     for (unsigned i = 0;i < v.size();++i) {
//         std::cout << v[i] << " *"[i + 1 < v.size()];
//         mult *= v[i];
//     }
//     std::cout << "= " << mult << std::endl;

//     return 0;
// }

// #include <bits/stdc++.h> // за O(NloglogN)
// #define inf 1e9+7
// #define int long long
// #define double long double
// #define nl "\n"
// #define fast ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0)
// using namespace std;
// int gcd(int a, int b) { if (a == 0) return b; else return gcd(b % a, a); }

// signed main()
// {
//     fast;
//     int t = 1;
//     cin >> t;
//     int n = 1e7;
//     vector<int>p(1e7 + 1, 0);
//     vector<int>mass;
//     for (int i = 2; i * i <= n; i++) {
//         if (p[i] == 1) continue;
//         if (i * i <= n) {
//             for (int j = i * i; j <= n; j += i) {
//                 p[j] = 1;
//             }
//         }
//     }

//     for (int i = 2; i <= 1e7; ++i) {
//         if (p[i] == 0) { // если 0 - число простое
//             mass.push_back(i);
//         }
//     }

//     while (t--)
//     {
//         int l = 0, r = 0;
//         cin >> l >> r;
//         int lx = lower_bound(mass.begin(), mass.end(), l) - mass.begin();
//         int rx = lower_bound(mass.begin(), mass.end(), r + 1) - mass.begin();
//         cout << rx - lx << endl;
//     }
// }

#include <iostream> // блочный (аккуратно выбирать константу SQRT_MAXN и S), лучшеее время при S от 1e4 до 1e5
// памяти - O(sqrt(n) + S)
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstring>
#define inf 1e9+7
#define int long long
#define double long double
#define nl "\n"
#define fast ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0)
using namespace std;
int gcd(int a, int b) { if (a == 0) return b; else return gcd(b % a, a); }

const int SQRT_MAXN = 10000; // корень из максимального значения N
const int S = 1e7+1;
bool nprime[SQRT_MAXN], bl[S];
int primes[SQRT_MAXN], cnt;

signed main() {

    int t = 1;
    cin >> t;
    int n = 1e7 + 1;
    int nsqrt = (int)sqrt(n + .0);
    for (int i = 2; i <= nsqrt; ++i)
        if (!nprime[i]) {
            primes[cnt++] = i;
            if (i * 1ll * i <= nsqrt)
                for (int j = i * i; j <= nsqrt; j += i)
                    nprime[j] = true;
        }

    int result = 0;
    vector<int> mass;
    for (int k = 0, maxk = n / S; k <= maxk; ++k) {
        memset(bl, 0, sizeof bl);
        int start = k * S;
        for (int i = 0; i < cnt; ++i) {
            int start_idx = (start + primes[i] - 1) / primes[i];
            int j = max(start_idx, (long long)2) * primes[i] - start;
            for (; j < S; j += primes[i])
                bl[j] = true;
        }
        if (k == 0)
            bl[0] = bl[1] = true;
        for (int i = 0; i < S && start + i <= n; ++i)
            if (!bl[i])
                mass.push_back(i);
    }

    while (t--) {
        int l = 0, r = 0;
        cin >> l >> r;
        int lx = lower_bound(mass.begin(), mass.end(), l) - mass.begin();
        int rx = lower_bound(mass.begin(), mass.end(), r + 1) - mass.begin();
        cout << rx - lx << endl;
    }
}