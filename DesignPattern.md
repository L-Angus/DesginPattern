## Design Pattern

### 1. SOLID Principles

#### 1.1 单一职责原则（SRP）

单一职责原则（Single Responsibility Principle）是指一个类应该只负责一个职责，一个类应该只有一个引起它变化的原因。

**正例：**
```c++
// 一个类只负责一个职责, Employee只负责员工的基本信息
class Employee {
     private:
          string name;
          int age;
          int salary;
     public:
     void setName(string name) {
          this->name = name;
     }
     std::string getName() {
          return this->name;
     }
     void setAge(int age) {
          this->age = age;
     }
     int getAge() {
          return this->age;
     }
     void setSalary(double salary) {
          this->salary = salary;
     }
     double getSalary() {
          return this->salary;
     }
};

// 而员工的工作职责应该单独放在一个类中
class EmployeeWork {
     private:
          Employee employee;
          std::string jobTitle;
          bool isWorking;
     public:
     void setEmployee(const Employee& employee) {
          this->employee = employee;
     }
     Employee getEmployee() {
          return this->employee;
     }
     void setJobTitle(std::string jobTitle) {
          this->jobTitle = jobTitle;
     }
     std::string getJobTitle() {
          return this->jobTitle;
     }
     void setIsWorking(bool isWorking) {
          this->isWorking = isWorking;
     }
     bool getIsWorking() {
          return this->isWorking;
     }

};
```
**反例：**
```c++
// 违反单一职责原则, Employee类既负责员工的基本信息, 又负责员工的工作职责
// 反例：一个类承担了过多职责，如员工类还负责管理员工的工作状态
class EmployeeBadSRP
{
private:
    string name;
    int id;
    double salary;
    string jobTitle;
    bool isWorking;

public:
    // 员工信息管理函数...
    void setName(string newName) { name = newName; }
    // ...

    // 不应在此类中处理的工作职责
    void setJobTitle(string title) { jobTitle = title; }
    void setIsWorking(bool status) { isWorking = status; }
    // ...
};
```

#### 1.2 开放封闭原则（OCP）

开放封闭原则（Open Closed Principle）是指一个软件实体应该是可以扩展的，但是不可修改的。也就是说，对于扩展是开放的，对于修改是封闭的。

**正例：**
```c++
// 正例：抽象基类Animal，后续添加新动物类型时无需修改已有代码
class Animal
{
public:
    virtual ~Animal() {}
    virtual void makeSound() const = 0; // 抽象方法
};

class Dog : public Animal
{
public:
    void makeSound() const override { 
     cout << "Woof!" << endl; 
     }
};

class Cat : public Animal
{
public:
    void makeSound() const override { 
     cout << "Meow!" << endl; 
     }

    // 新增动物类型只需要继承Animal并实现makeSound即可
};

// 使用时通过抽象基类Animal操作，轻松支持新类型的添加
void playWithAnimals(vector<shared_ptr<Animal>> animals)
{
    for (const auto& animal : animals)
    {
        animal->makeSound();
    }
}

// 当需要添加新动物如Bird时，只需创建新的Bird类而不必修改playWithAnimals函数
```

**反例：**
```c++
// 反例：直接使用具体类Animal，后续添加新动物类型时需要修改已有代码
void playWithAnimals(vector<Animal> animals)
{
     for (const auto& animal : animals)
     {
          if (typeid(animal) == typeid(Dog))
          {
               cout << "Woof!" << endl;
          }
          else if (typeid(animal) == typeid(Cat))
          {
               cout << "Meow!" << endl;
          }
          else if (typeid(animal) == typeid(Bird))
          {
               cout << "Chirp!" << endl;
          }
          else
          {
               cout << "Unknown animal!" << endl;
          }
     }
}
```

#### 1.3 里氏替换原则（LSP）

里氏替换原则（Liskov Substitution Principle）是指子类对象必须能够替换掉所有父类对象。也就是说，子类对象应该能够替代父类对象出现在程序中。

**正例：**
```c++
// 正例：Square是Rectangle的子类，遵守LSP
class Rectangle
{
protected:
    double width, height;

public:
    void setWidth(double w) { width = w; }
    void setHeight(double h) { height = h; }
    virtual double getArea() const { return width * height; }
};

class Square : public Rectangle
{
public:
    void setWidth(double w) override { width = height = w; } // 同时更新高度以保持方形
    void setHeight(double h) override { width = height = h; }
    double getArea() const override { return width * width; } // 重写面积计算，但不会改变Rectangle的行为
};

// 使用父类指针调用子类对象，不会违反原有约定
void calculateArea(Rectangle* rect)
{
    cout << "Area: " << rect->getArea() << endl;
}

int main()
{
    Square s;
    s.setWidth(5);
    calculateArea(&s); // 输出正确的面积
}
```

**反例：**
```c++
     // 反例：Rectangle是Square的父类，违反了LSP
     class Square : public Rectangle
     {
          public:
          void setWidth(double w) override { width = w; }
          void setHeight(double h) override { height = w; } // 只更新宽度，没有更新高度，违反原有约定
          double getArea() const override { return width * width; }
          void calculateArea(Rectangle* rect)
          {
               cout << "Area: " << rect->getArea() << endl;    
               // 输出错误的结果，因为Square没有正确实现setHeight
               calculateArea(&s);
               return 0;

          }
     }
```

#### 1.4 依赖倒置原则（DIP）
依赖倒置原则（Dependency Inversion Principle）是指高层模块不应该依赖低层模块，而是应该依赖其抽象。同时，抽象不应该依赖具体实现，而应该依赖其抽象。

依赖倒置原则的核心思想是：模块间的依赖关系应该建立在抽象之上，而不是具体实现之上。
依赖倒置原则的实现方式包括：
- 使用抽象接口，而不是具体实现类
- 避免使用继承，而是使用组合或依赖注入

**正例：**
```c++
// 正例：抽象接口，具体实现依赖于接口而非具体类
class IPaymentStrategy
{
public:
    virtual ~IPaymentStrategy() {}
    virtual void pay(double amount) = 0;
};

class CreditCardPayment : public IPaymentStrategy
{
public:
    void pay(double amount) override { 
     cout << "Paid using credit card: " << amount << endl; 
     }
};

class PayPalPayment : public IPaymentStrategy
{
public:
    void pay(double amount) override { 
     cout << "Paid using PayPal: " << amount << endl; 
     }
};

class ShoppingCart
{
private:
    shared_ptr<IPaymentStrategy> paymentMethod;

public:
    void setPaymentMethod(shared_ptr<IPaymentStrategy> strategy) { 
          paymentMethod = strategy;
     }

    void checkout(double totalAmount)
    {
        paymentMethod->pay(totalAmount); // 依赖抽象
    }
};

// 使用时注入不同的支付方式，不影响ShoppingCart的核心逻辑
```

**反例：**
```c++
// 反例：直接使用具体类，违反DIP
class ShoppingCartBadDIP
{
private:
    CreditCardPayment payment;

public:
    void checkout(double totalAmount)
    {
        payment.pay(totalAmount); // 直接依赖于CreditCardPayment
    }
};

// 若要改为PayPal支付，需要修改ShoppingCartBadDIP类的内部结构
```


#### 1.5 迪米特法则（Law of Demeter）
迪米特法则（Law of Demeter）是指一个对象应该尽可能少地与其他对象发生相互作用，即只与直接的朋友通信。
迪米特法则的核心思想是：降低对象之间的耦合度，降低对象之间的依赖关系。
迪米特法则的实现方式包括：
- 封装细节，提供公共接口
- 避免直接访问私有成员
- 避免使用全局变量和全局函数
- 尽量使用对象组合，而不是继承

**正例：**
```c++
// 正例：客户类只和直接的朋友类打交道
class Order
{
private:
    Customer customer;
    List<Product> products;

public:
    void addProduct(Product p) { products.push_back(p); }
    double getTotalPrice() const
    {
        double totalPrice = 0;
        for (const auto& product : products)
        {
            totalPrice += product.getPrice(); // 直接询问产品价格
        }
        return totalPrice;
    }
};

class Product
{
private:
    double price;

public:
    Product(double p) : price(p) {}
    double getPrice() const { return price; }
};

// Order类只直接与Product交互，而没有直接访问Customer的其它详细信息
```

**反例：**
```c++
// 反例：过度耦合，Order直接访问了Customer的私有信息
class OrderBadLoD
{
private:
    Customer customer;

public:
    void placeOrder(Customer c)
    {
        customer = c;
        // 违背了LoD，直接访问了客户的信用等级
        if (customer.getCreditRating() < MIN_CREDIT_RATING) 
        {
            throw Exception("Low credit rating");
        }
    }
};

class Customer
{
private:
    double creditRating;

public:
    double getCreditRating() const { return creditRating; } // 本应该是受保护的或者私有的
};
```

#### 1.6 接口隔离原则（ISP）
接口隔离原则（Interface Segregation Principle）是指客户端不应该依赖它不需要的接口。即一个类对另一个类的依赖应该建立在最小的接口上。

接口隔离原则的实现方式包括：
- 接口应该尽量小，但不要太小
- 尽量使用组合而不是继承
接口隔离原则的核心思想是：将臃肿庞大的接口拆分为更小的、更具体的接口，使得客户端只需要依赖它需要的接口，从而降低耦合度。

**正例：**
```c++
     // 正例：将大的接口拆分成更具体的独立接口
class IShape
{
public:
    virtual ~IShape() {}
    virtual double getArea() const = 0;
};

class IResizable
{
public:
    virtual ~IResizable() {}
    virtual void resize(double factor) = 0;
};

class Circle : public IShape, public IResizable
{
private:
    double radius;

public:
    double getArea() const override { return M_PI * radius * radius; }
    void resize(double factor) override { radius *= factor; }
};

// 使用时根据实际需求引用适当的接口
void processShapes(IShape* shape) { cout << "Area: " << shape->getArea() << endl; }
void resizeObjects(IResizable* resizable) { resizable->resize(1.5); }
```

**反例：**
```c++
// 反例：接口过于臃肿，导致客户端依赖不必要的接口
// 反例：强制使用者实现不必要的方法
class Shape
{
public:
    virtual ~Shape() {}
    virtual double getArea() const = 0;
    virtual void resize(double factor) = 0; // 所有形状都需要实现resize，即使某些形状不需要改变大小
};

class CircleBadISP : public Shape
{
private:
    double radius;

public:
    double getArea() const override { return M_PI * radius * radius; }
    // resize方法在这里显得冗余，对于圆形来说，缩放大小可能不是必需的功能
    void resize(double /*factor*/) override { throw runtime_error("Resizing is not supported for circles."); }
};

// 使用时，即使不关心Resize功能，也要处理resize方法
```

#### 1.7 合成复用原则（Composite Reuse Principle）
合成复用原则（Composite Reuse Principle）是指尽量使用组合而不是继承。

合成复用原则的实现方式包括：
- 使用继承来扩展类的行为
- 使用组合来组合对象，而不是继承
合成复用原则的核心思想是：尽量使用组合而不是继承，以实现代码的复用和扩展性。

**正例：**
```c++
// 正例：使用继承来扩展类的行为

// 正例：使用组合的方式实现复用
class Component
{
public:
    virtual ~Component() {}
    virtual void operation() = 0; // 基础组件的操作
};

class Leaf : public Component
{
private:
    string data;

public:
    explicit Leaf(string d) : data(d) {}
    void operation() override { cout << "Leaf operation with data: " << data << endl; }
};

class Composite : public Component
{
private:
    vector<shared_ptr<Component>> children;

public:
    void add(Component* child) { children.push_back(make_shared<Component>(child)); }
    void remove(Component* child) {...} // 实现删除子组件的方法
    void operation() override
    {
        for (const auto& child : children)
        {
            child->operation(); // 组合内调用子组件的操作
        }
    }
};

int main()
{
    Composite composite;
    Leaf leaf1("Leaf 1");
    Leaf leaf2("Leaf 2");

    composite.add(&leaf1);
    composite.add(&leaf2);

    composite.operation(); // 通过组合方式调用各个组件的操作

    return 0;
}
```

**反例：**
```c++
// 反例：使用继承来扩展类的行为
class Component
{
     virtual ~Component() {}
     virtual void operation() = 0;
     virtual void add(Component* child) = 0;
     virtual void remove(Component* child) = 0;
     virtual void operation() = 0;
};

class Leaf : public Component
{
     string data;
     void operation() override 
     { 
          cout << "Leaf operation with data: " << data << endl; 
     }
     void add(Component* child) override 
     { 
          throw runtime_error("Adding is not supported for leaves."); 
     }
     void remove(Component* child) override 
     { 
          throw runtime_error("Removing is not supported for leaves."); 
     }
     void operation() override 
     { 
          cout << "Leaf operation with data: " << data << endl; 
     }
};
class Composite : public Component
{
     vector<shared_ptr<Component>> children;
     void add(Component* child) override 
     { 
          children.push_back(make_shared<Component>(child)); 
     }
     void remove(Component* child) override {...} // 实现删除子组件的方法
     void operation() override
     {
          for (const auto& child : children)
          {
               child->operation(); // 组合内调用子组件的操作
               cout << "Composite operation" << endl;
          }
     }
}

int main()
{
     Composite composite;
     Leaf leaf1("Leaf 1");
     Leaf leaf2("Leaf 2");
     composite.add(&leaf1);
     composite.add(&leaf2);
     composite.operation(); // 通过继承方式调用各个组件的操作

     return 0;
}
```