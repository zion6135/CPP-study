#include "father.h"

std::shared_ptr<father> father::create(string name) {
    static std::shared_ptr<father> pp(new fatherImpl(name));
    std::cout << "111  " << pp.use_count() << std::endl;
    return pp;
}
