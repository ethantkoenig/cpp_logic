#ifndef __EITHER_H__
#define __EITHER_H__


template<class T, class U>
class Either {
public:
    static Either<T, U>* Left(T t);
    static Either<T, U>* Right(U u);
    bool getLeft(T& t); // true if successful
    bool getRight(U& u); // true if successful
private:
    Either();
    bool isLeft;
    union {
        T left;
        U right;
    };
};

template<class T, class U>
Either<T, U>::Either() {
    // no-op, will be initialized in static factory methods
}

template<class T, class U>
Either<T, U>* Either<T, U>::Left(T t) {
    Either<T, U>* e = new Either<T, U>();
    e -> isLeft = true;
    e -> left = t;
    return e;
}

template<class T, class U>
Either<T, U>* Either<T, U>::Right(U u) {
    Either<T, U>* e = new Either<T, U>();
    e -> isLeft = false;
    e -> right = u;
    return e;
}

template<class T, class U>
bool Either<T, U>::getLeft(T& t) {
    if (isLeft) {   
        t = this -> left;
        return true;
    }
    return false;
}

template<class T, class U>
bool Either<T, U>::getRight(U& u) {
    if (!isLeft) {   
        u = this -> right;
        return true;
    }
    return false;
}


#endif
