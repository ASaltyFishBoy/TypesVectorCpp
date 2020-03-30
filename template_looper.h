#ifndef TEMPLATE_LOOPER_H
#define TEMPLATE_LOOPER_H
#include "template_types_base_class.h"
#include "template_if.h"
namespace template_type_traits
{

    //迭代器有效性转接
    template<typename Iterator, typename TypesVector>
    struct iterator_invalid_check
    {
        enum
        {
            value = Iterator::effect
        };
    };

    //默认循环变化
    template<typename LoopIterator, typename TypesVector>
    struct default_iterator_loop_change
    {
        using next = typename LoopIterator::template next<>;
    };

    //可变模板参数循环器，效验起始参数，参数为循环行为，截止方式(默认为Iterator失效)，效验参数变化(默认为迭代器后移)
    template <
        typename BeginIterator
        , typename BeginTypesVector
        //本身容器的迭代器，以及运算时的临时存储容器，两者不相关
        , template <typename LoopIterator, typename TypesVector> class LoopBehaivor
        , template <typename LoopIterator, typename TypesVector> class CheckClass = iterator_invalid_check
        , template <typename LoopIterator, typename TypesVector> class IteratorLoopChange = default_iterator_loop_change
        >
    struct template_looper
    {
private:
        template<typename LoopIterator, typename TypesVector>
        struct TrueBehaivor;
        template<typename LoopIterator, typename TypesVector>
        struct FalseBehaivor;

        template<typename LoopIterator, typename TypesVector>
        struct TrueBehaivor
        {
        private:
            using next = typename IteratorLoopChange <LoopIterator, TypesVector>::next;
            using processedVector = typename LoopBehaivor<LoopIterator, TypesVector>::result;
        public:
            using result = typename template_if <
                           TrueBehaivor<next, processedVector >
                           , FalseBehaivor<next, processedVector >
                           >
                           ::template result<CheckClass<next, processedVector >::value >;
        };

        template<typename LoopIterator, typename TypesVector>
        struct FalseBehaivor
        {
            using result = typename TypesVector::template apply<types_vector>;
        };

public:
        using result = typename template_if <
                       TrueBehaivor<BeginIterator, BeginTypesVector>
                       , FalseBehaivor<BeginIterator, BeginTypesVector>
                       >
                       ::template result<CheckClass<BeginIterator, BeginTypesVector>::value >;
    };
}
#endif // TEMPLATE_LOOPER_H
