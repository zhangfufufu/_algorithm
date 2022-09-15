#include <iostream>
#include <mutex>
#include <thread>

std::mutex mtx;

// 高效版 线程安全 懒汉式
class Singleton {
public:
    ~Singleton();

    Singleton(const Singleton &) = delete;             // 禁用拷贝构造函数
    Singleton &operator=(const Singleton &) = delete;  // 禁用赋值运算符

    static Singleton *get_instance() {
        // if(_instance == nullptr)并不是原子操作,多线程会存在线程安全问题 需要加锁
        if (_instance == nullptr) {
            // lock_guard类通过在对象构造的时候对mutux进行加锁，当对象离开作用域时自动解锁
            std::lock_guard<std::mutex> lck(mtx);
            if (_instance == nullptr) {
                _instance = new Singleton;
            }
        }
        return _instance;  // 非空new一个对象,保证只有一个对象
    }

private:
    Singleton();                  // 构造私有
    static Singleton *_instance;  // 静态成员私有

private:
    class Del {  // 内部类 负责释放单例对象 解决_instance内存泄漏问题
    public:
        ~Del() {
            if (Singleton::_instance != nullptr) {
                delete Singleton::_instance;
                Singleton::_instance = nullptr;
            }
        }

        static Del d;  // 静态变量会在程序结束时候自动调用它的析构函数
    };
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
