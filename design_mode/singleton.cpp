#include <iostream>

// c++11 之后 线程安全
// 使用类的私有静态指针变量指向类的唯一实例，并用一个公有的静态方法获取该实例。
class Singleton {
public:
    ~Singleton();

    Singleton(const Singleton &) = delete;             // 禁用拷贝构造函数
    Singleton &operator=(const Singleton &) = delete;  // 禁用赋值运算符

    static Singleton *get_instance() {
        if (_instance == nullptr) {
            _instance = new Singleton;
        }
        return _instance;
    }

private:
    Singleton();                  // 构造私有
    static Singleton *_instance;  // 静态成员私有
};

// 类的静态变量需要类外初始化
Singleton *Singleton::_instance = nullptr;

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
