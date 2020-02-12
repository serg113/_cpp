/**
 * we can define custom deleters for std::unique_ptr and std::shared_ptr
 * for std::shared_ptr we get generic "by deleter" pointer
 * so we can exchange pointers with different deleters
 *
 * ref. -> pages 120, 127, "Effective Modern C++" by Scott Meyers
 */

 #include <iostream>
 #include <string>
 #include <memory>

 class A
 {

 public:
     A(const std::string& name): name_{name}{};

     std::string GetName() const
     {
         return name_;
     }

 private:
     std::string name_;
 };


 int main()
 {
    auto deleter_1 = [](A* a)
                     {
                        std::cout << "deleter 1: " << a->GetName() << std::endl;
                        delete a;
                     };
                     
    auto deleter_2 = [](A* a)
                     {
                        std::cout << "deleter 2: " << a->GetName() << std::endl;
                        delete a;
                     };

    std::unique_ptr<A, decltype(deleter_1)> upa(new A("object A1"), deleter_1);

    std::shared_ptr<A> pa1(new A("object A2"), deleter_1);
    std::shared_ptr<A> pa2(new A("object A3"), deleter_2);
    
    pa1 = pa2;
 }
