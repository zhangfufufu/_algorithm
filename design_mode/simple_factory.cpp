// 简单工厂：唯一工厂类，一个产品抽象类，工厂类的创建方法依据入参判断并创建具体产品对象。

#include <iostream>

using namespace std;

typedef enum ProductType {  // 产品类型使用枚举定义
    Hair,
    Hisense,
} ProType;

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

class TVFactory {  // 电视机工厂类
public:
    TV *create_tv(ProType type) {
        switch (type) {
            case Hair:
                return new HairTV();
            case Hisense:
                return new HisenseTV();
            default:
                return nullptr;
        }
    }
};

int main(int argc, char const *argv[]) {
    // 创建工厂类对象
    TVFactory *tv_factory = new TVFactory();
    TV *hair_tv = tv_factory->create_tv(Hair);
    if (hair_tv) {
        hair_tv->show();
    }

    TV *hisense_tv = tv_factory->create_tv(Hisense);
    if (hisense_tv) {
        hisense_tv->show();
    }

    delete tv_factory;
    tv_factory = nullptr;
    delete hair_tv;
    hair_tv = nullptr;
    delete hisense_tv;
    hisense_tv = nullptr;

    return 0;
}
