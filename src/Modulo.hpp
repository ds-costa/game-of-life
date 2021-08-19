#ifndef MODULO_HPP
#define MODULO_HPP

class Modulo {

public:
    static inline int Add(int a, int b, int n) {
        return (a + b) % n;
    }

    static inline int Subtract(int a, int b, int n) {
        return (a % n - b % n + n) % n;
    }
};

#endif