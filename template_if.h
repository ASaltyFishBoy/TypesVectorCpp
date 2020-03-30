#ifndef TEMPLATE_IF_H
#define TEMPLATE_IF_H
#include "template_types_base_class.h"
namespace template_type_traits
{
    template<typename TrueBehaivor, typename FalseBehaivor = non_behaivor>
    struct template_if
    {
    private:
        template<bool, typename BrachTrueBehaivor = TrueBehaivor, typename BrachFalseBehaivor = FalseBehaivor >
        struct Brach
        {
            using result = typename BrachTrueBehaivor::result;
        };

        template<typename BrachTrueBehaivor, typename BrachFalseBehaivor >
        struct Brach<false, BrachTrueBehaivor, BrachFalseBehaivor>
        {
            using result = typename BrachFalseBehaivor::result;
        };

    public:
        template<bool flag>
        using result = typename Brach<flag>::result;
    };
}
#endif // TEMPLATE_IF_H
