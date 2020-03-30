#include <iostream>
#include <list>
#include <vector>
#include <numeric>
#include "types_vector.h"
using namespace template_type_traits;
template<typename Arg>
struct Changer
{
    using result = std::vector<Arg>;
};

int main()
{
    using typeArgA = types_vector<std::vector<int>, bool, char>;
    typeArgA::foreach<Changer> a;
    std::cout << typeid (decltype (a) ::arg<1>).name() << "\n";

    return 0;
}
