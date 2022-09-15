// 工厂方法模式 在工厂模式中，工厂父类负责定义创建产品对象的公告接口，而工厂子类负责生成具体的产品对象。
// 目的是将产品的实例化操作延迟到工厂子类中完成，通过工厂子类来确定究竟应该实例化哪一个具体产品类。

// 工厂方法：多个工厂类，一个产品抽象类，利用多态创建不同的产品对象，避免了大量的if-else判断。
#include <iostream>

using namespace std;

class TV {  // 抽象电视工厂类
public:
    virtual void show() = 0;  // 指定show方法,让其子类实现
    virtual ~TV(){};          // 析构函数指定为虚函数,防止内存泄漏
};

class HairTV : public TV {  // hair 电视类
public:
    virtual void show() override {
        cout << "Hair" << endl;
    }
};

class HisenseTV : public TV {  // hisense 电视类
public:
    virtual void show() override {
        cout << "Hisense" << endl;
    }
};

class TVFactory {  // 抽象电视机工厂类
public:
    ~TVFactory(){};
    virtual TV *create_tv() = 0;
};

class HairTVFactory : public TVFactory {
public:
    virtual TV *create_tv() override {
        return new HairTV();
    }
};

class HisenseTVFactory : public TVFactory {
public:
    virtual TV *create_tv() {
        return new HisenseTV();
    }
};

int main(int argc, char const *argv[]) {
    // 创建hair工厂生产海尔电视
    TVFactory *hair_tv_factor = new HairTVFactory();
    TV *hair_tv = hair_tv_factor->create_tv();
    if (hair_tv) {
        hair_tv->show();
    }

    // 创建海信工厂生产海信电视
    TVFactory *hisense_tv_factory = new HisenseTVFactory();
    TV *hisense_tv = hisense_tv_factory->create_tv();
    if (hisense_tv) {
        hisense_tv->show();
    }

    delete hair_tv_factor;
    hair_tv_factor = nullptr;
    delete hair_tv;
    hair_tv = nullptr;

    delete hisense_tv_factory;
    hisense_tv_factory = nullptr;
    delete hisense_tv;
    hisense_tv = nullptr;

    return 0;
}
