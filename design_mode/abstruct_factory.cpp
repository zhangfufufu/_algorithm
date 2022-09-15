#include <iostream>
using namespace std;

// 抽象产品类类 Television(电视机类)
class Television {
public:
    virtual void Show() = 0;
    virtual ~Television(){};  //析构函数声明为虚函数，防止内存泄漏
};

//具体产品类 HaierTelevision（海尔电视机类）
class HaierTelevision : public Television {
public:
    void Show() {
        cout << "I'm HaierTelevision" << endl;
    }
};
//具体产品类 TCLTelevision（TCL电视机类）
class TCLTelevision : public Television {
public:
    void Show() {
        cout << "I'm TCLTelevision" << endl;
    }
};

// 抽象产品类  AirCondition（空调类）
class AirCondition {
public:
    virtual void Show() = 0;
    virtual ~AirCondition(){};  //析构函数声明为虚函数，防止内存泄漏
};
//具体产品类 HairAirCondition(海尔空调类)
class HairAirCondition : public AirCondition {
public:
    void Show() {
        cout << "I'm HairAirCondition" << endl;
    }
};
//具体产品类 TCLAirCondition(TCL空调类)
class TCLAirCondition : public AirCondition {
public:
    void Show() {
        cout << "I'm TCLAirCondition" << endl;
    }
};

// 抽象工厂类 EFactory(电器工厂类)
class EFactory {
public:
    virtual Television *CreateTelevision() = 0;
    virtual AirCondition *CreateAirCondition() = 0;
    virtual ~EFactory(){};  //析构函数声明为虚函数，防止内存泄漏
};
//具体工厂类 HairFactory(海尔工厂类)
class HairFactory : public EFactory {
public:
    Television *CreateTelevision() {
        return new HaierTelevision();
    }

    AirCondition *CreateAirCondition() {
        return new HairAirCondition();
    }
};
//具体工厂类 TCLFactory(TCL工厂类)
class TCLFactory : public EFactory {
public:
    Television *CreateTelevision() {
        return new TCLTelevision();
    }

    AirCondition *CreateAirCondition() {
        return new TCLAirCondition();
    }
};

int main(int argc, char *argv[]) {
    EFactory *hairFactory = new HairFactory();                     /*实例化工厂抽象类*/
    Television *haierTelevision = hairFactory->CreateTelevision(); /*实例化产品抽象类*/
    AirCondition *haierAirCondition = hairFactory->CreateAirCondition();

    haierTelevision->Show();
    haierAirCondition->Show();

    EFactory *tCLFactory = new TCLFactory();
    Television *tCLTelevision = tCLFactory->CreateTelevision();
    AirCondition *tCLAirCondition = tCLFactory->CreateAirCondition();

    tCLTelevision->Show();
    tCLAirCondition->Show();

    if (hairFactory != NULL) {
        delete hairFactory;
        hairFactory = NULL;
    }

    if (haierTelevision != NULL) {
        delete haierTelevision;
        haierTelevision = NULL;
    }

    if (tCLAirCondition != NULL) {
        delete tCLAirCondition;
        tCLAirCondition = NULL;
    }

    if (tCLFactory != NULL) {
        delete tCLFactory;
        tCLFactory = NULL;
    }

    if (tCLTelevision != NULL) {
        delete tCLTelevision;
        tCLTelevision = NULL;
    }

    if (tCLAirCondition != NULL) {
        delete tCLAirCondition;
        tCLAirCondition = NULL;
    }
}