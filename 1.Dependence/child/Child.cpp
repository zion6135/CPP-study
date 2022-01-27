#include "Child.h"

std::shared_ptr<Child> Child::create(string name) {
    static std::shared_ptr<Child> pp(new ChildImpl(name));
    std::cout << "111  " << pp.use_count() << std::endl;
    return pp;
}
