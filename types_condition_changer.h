#ifndef TYPES_CONDITION_CHANGER_H
#define TYPES_CONDITION_CHANGER_H
#include "template_types_base_class.h"
#include "template_looper.h"
#include "template_if.h"
namespace template_type_traits
{

    template <template <typename Iterator, typename TypesVector = void> class Converter
              , template <typename Iterator, typename TypesVector = void> class CheckClass>
    struct types_condition_changer
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
                using result = typename Converter<Iterator, types_vector<Args...>>::result;
            };

            struct FalseBehaivor
            {
                using result = types_vector<Args...>;
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
#endif // TYPES_CODNITION_CHANGER_H
