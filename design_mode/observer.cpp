// 观察者模式 应用于MVC架构

// 定义对象间的一种一对多的依赖关系，当一个对象的状态发生改变时，所有依赖于它的对象都得到通知并被自动更新。
// 当一个对象发生了变化，关注它的对象就会得到通知；这种交互也称为发布-订阅(publish-subscribe)。
// 目标是通知的发布者，它发出通知时并不需要知道谁是它的观察者。

#include <algorithm>
#include <iostream>
#include <list>

using namespace std;

class AbsObserver {  // 观察者抽象类
public:
    virtual void update() = 0;
    ~AbsObserver(){};
};

class Observer1 : public AbsObserver {  // 具体的观察者1
public:
    virtual void update() override {
        cout << "Observer1 update..." << endl;
    }
};

class Observer2 : public AbsObserver {  // 具体的观察者2
public:
    virtual void update() override {
        cout << "Observer2 update..." << endl;
    }
};

class AbsPublisher {  // 抽象发布者
public:
    virtual void attach(AbsObserver *observer) = 0;  // 添加一个观察者
    virtual void detach(AbsObserver *observer) = 0;  // 删除一个观察者
    virtual void notify() = 0;                       // 通知所有观察者
    ~AbsPublisher(){};

protected:
    list<AbsObserver *> observer_list;  // 观察者列表
};

class Publisher : public AbsPublisher {  // 具体发布者
public:
    virtual void attach(AbsObserver *observer) override {
        if (observer != nullptr) {
            observer_list.push_back(observer);
        }
    }

    virtual void detach(AbsObserver *observer) override {
        // 删除
        auto obs = find(observer_list.begin(), observer_list.end(), observer);

        if (obs != observer_list.end()) {
            observer_list.erase(obs);
            cout << "erase observer success" << endl;
        } else {
            cout << "can not find observer" << endl;
        }
    }

    virtual void notify() override {
        // 通知
        for (auto obs = observer_list.begin(); obs != observer_list.end(); obs++) {
            (*obs)->update();
        }
    }
};

int main(int argc, char const *argv[]) {
    AbsObserver *observer1 = new Observer1;
    AbsObserver *observer2 = new Observer2;

    AbsPublisher *publish = new Publisher;
    //添加被观察者
    publish->attach(observer1);
    publish->attach(observer2);

    publish->notify();

    return 0;
}
