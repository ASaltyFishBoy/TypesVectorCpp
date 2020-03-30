#ifndef TYPES_CONDITION_REMOVE_CHECKER_H
#define TYPES_CONDITION_REMOVE_CHECKER_H
#include "template_types_base_class.h"
#include "template_looper.h"
#include "template_if.h"
namespace template_type_traits
{
    template <template <typename Arg, typename TypesVector = void> class CheckClass>
    struct types_condition_remove_checker
    {
    private:
        template<typename Iterator, typename TypesVector>
        struct LoopBehaivor;
        template<typename Iterator, typename ...Args>
        struct LoopBehaivor<Iterator, types_vector<Args...>>
        {
        private:
            struct TrueBehaivor
            {
                using result = types_vector<Args...>;
            };

            struct FalseBehaivor
            {
                using result = types_vector<Args..., typename Iterator::arg>;
            };

        public:
            using result = typename template_if<TrueBehaivor, FalseBehaivor>
                           ::template result<CheckClass<Iterator, types_vector<Args...>>::value>;
        };

    public:
        template<typename Iterator>
        using result = typename template_looper<Iterator, types_vector<>, LoopBehaivor>::result;
    };
}
#endif // TYPES_CONDITION_REMOVE_CHECKER_H
