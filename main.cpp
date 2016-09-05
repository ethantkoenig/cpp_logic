#include <functional>
#include <iostream>

#include "either.hpp"
#include "void.h"

using namespace std; // provides function, cout

/* An implementation of the polymorphic type
 * -- [('a | ~'a) * ~('a * 'b)] -> [(~'a) | (~'b)]
 * in C++
 */


template<class T>
Void second_void(T t, Void impossible) {
    return impossible;
}

template<class T, class U>
Either<std::function<Void(T)>*, std::function<Void(U)>*>* tautology(
        Either<T, std::function<Void(T)>*>* excluded_middle,
        std::function<Void(T, U)>* not_and) {
    T value;
    if (excluded_middle->getLeft(value)) {
        auto lambda = new std::function<Void(U)>(
            [value, not_and] (U right) { return (*not_and)(value, right); });
        return Either<std::function<Void(T)>*, std::function<Void(U)>*>::Right(lambda);
    }
    std::function<Void(T)>* function;
    if (excluded_middle->getRight(function)) {
        return Either<std::function<Void(T)>*, std::function<Void(U)>*>::Left(function); 
    }
    throw; // cannot be reached
}


int main() {
    // int | (int -> void)
    Either<int, std::function<Void(int)>*>* either = 
            Either<int, std::function<Void(int)>*>::Left(4860);
    
    // (int * void) -> void
    std::function<Void(int, Void)> not_and(second_void<int>);

    // (int -> void) | (void -> void)
    Either<std::function<Void(int)>*, std::function<Void(Void)>*>* either_function =
            tautology(either, &not_and);

    // we expect to have gotten a (void -> void), not a (int -> void)
    std::function<Void(int)>* impossible_func;
    std::function<Void(Void)>* possible_func;
    if (either_function->getLeft(impossible_func)) {
        cout << "Impossible!\n";
        delete impossible_func;
    } else if (either_function->getRight(possible_func)) {
        cout << "It works!\n";
        delete possible_func;
    } else {
        // should never reach here
        cout << "I only have two hands...\n";
        throw;
    }
    delete either;
    delete either_function;
}
