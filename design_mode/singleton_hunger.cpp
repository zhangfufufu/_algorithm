#include <iostream>

// 饿汉式 本身线程安全 不需要加锁

// 即无论是否调用该类的实例，在程序开始时就会产生一个该类的实例，并在以后仅返回此实例。
// 由静态初始化实例保证其线程安全性，WHY？因为静态实例初始化在程序开始时进入主函数之前就由主线程以单线程方式
// 完成了初始化，不必担心多线程问题。
// 故在性能需求较高时，应使用这种模式，避免频繁的锁争夺。

// 饿汉式的特点：代码简单，不会出现内存泄露，是线程安全的。
class Singleton {
public:
    ~Singleton();

    Singleton(const Singleton &) = delete;             // 禁用拷贝构造函数
    Singleton &operator=(const Singleton &) = delete;  // 禁用赋值运算符

    static Singleton *get_instance() {
        return _instance;
    }

private:
    Singleton();                  // 构造私有
    static Singleton *_instance;  // 静态成员私有
};

Singleton *Singleton::_instance = new Singleton;  // 饿汉 类外实例化,类内直接使用

Singleton::Singleton() {
    std::cout << "Singleton Constructor" << std::endl;
}

Singleton::~Singleton() {
    std::cout << "Singleton Destructor" << std::endl;
}

int main(int argc, char const *argv[]) {
    // 测试
    Singleton *s1 = Singleton::get_instance();
    Singleton *s2 = Singleton::get_instance();

    if (s1 == s2) {
        std::cout << "==" << std::endl;
    }

    delete s1;
    delete s2;

    return 0;
}
