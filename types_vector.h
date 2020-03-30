#ifndef TYPES_HANDLER_H
#define TYPES_HANDLER_H

#include "template_types_base_class.h"
#include "types_condition_remove_checker.h"
#include "types_vector_merger.h"
#include "types_condition_changer.h"
namespace template_type_traits
{
    //条件转接器
    template<template<typename Arg> class CheckClass>
    struct type_check_to_iterator_check
    {
        template<typename Iterator>
        struct check
        {
            enum
            {
                value = CheckClass<typename Iterator::arg>::value
            };
        };
    };

    template<template<typename Arg> class Converter>
    struct type_changer_to_iterator_changer
    {
        template<typename Iterator, typename TypesVector>
        struct changer
        {
            using result = typename TypesVector::template insert<TypesVector::ARGS_NUM
                           , typename Converter<typename Iterator::arg>::result>;
        };
    };

    template <template<typename Arg> class CheckClass>
    struct type_check_operator_not
    {
        template<typename Iterator>
        struct check
        {
            enum
            {
                value = !CheckClass<Iterator>::value
            };
        };
    };

    //可变类型参数处理器
    template<typename ...Args>
    struct types_vector
    {
        enum
        {
            ARGS_NUM = sizeof... (Args)
        };

        //索引效验器
        template<size_t from = 0, size_t to = ARGS_NUM>
        struct index_check
        {
            template<typename Iterator, typename TypesVector = void>
            struct check
            {
                enum
                {
                    value = Iterator::effect && Iterator::index >= from && Iterator::index < to
                };
            };
        };

        template < size_t i, bool isEffect>
        struct IteratorBase;

        template < size_t i, bool isEffect = (ARGS_NUM > i) >
        struct Iterator: IteratorBase<i, isEffect> {};

        template<size_t i>
        struct Iterator<i, true>: IteratorBase<i, true>
        {
            using arg = typename std::tuple_element<i, std::tuple<Args...>>::type;
        };

        //返回值
        template<template <typename ...HandledArgs> class ApplyClass, typename ...ExtraArgs>
        using apply = ApplyClass<ExtraArgs..., Args...>;
        template<template <typename ...HandledArgs> class ApplyClass, typename ...ExtraArgs>
        using apply_extra_back = ApplyClass<Args..., ExtraArgs...>;

        //读取
        template<size_t i>
        using arg = typename Iterator<i>::arg;

        //条件移除
        template<template <typename Arg, typename TypesVector = void> class CheckClass>
        using remove_if_by_iterator = typename types_condition_remove_checker<CheckClass>
                                      ::template result<Iterator<0>>;
        template<template <typename Arg> class CheckClass>
        using remove_if = remove_if_by_iterator<type_check_to_iterator_check<CheckClass>::template check>;

        //合并
        template<typename ...TypesVectors>
        using merge = typename types_vector_merge<types_vector<Args...>, TypesVectors...>::result;

        //移除，闭开区间
        template < size_t from, size_t to = from + 1 >
        using erase = remove_if_by_iterator <index_check<from, to>::template check>;

        //插入
        template<size_t i = ARGS_NUM, typename ...InsertArgs>
        using insert = typename erase < i, ARGS_NUM >
                       ::template apply_extra_back<types_vector, InsertArgs...>
        ::template merge < erase < 0, i >>;

        //改变
        template<template <typename Iterator, typename TypesVector = void> class Converter
                 , template <typename Iterator, typename TypesVector = void> class CheckClass>
        using change_if_by_iterator = typename types_condition_changer<Converter, CheckClass>
                                      ::template result<Iterator<0>>;
        template<size_t i, typename Arg>
        using change = typename erase <i>::template insert<i, Arg>;
        template<template <typename Arg> class Converter>
        using foreach = change_if_by_iterator<type_changer_to_iterator_changer<Converter>::template changer, true_condition>;

        //某项拆解，从容器的角度来说这并不该提供，但是对于连续处理这十分方便
        template<size_t i>
        using explos = typename type_exploser<arg<i>>::template apply<types_vector>;


    };

    template<typename ...Args>
    template<size_t i, bool isEffect>
    struct types_vector<Args...>::IteratorBase
    {
        enum
        {
            index = i,
            effect = isEffect
        };
        template<size_t step = 1>
        using next = typename types_vector<Args...>::template Iterator < i + step >;
        template<size_t step = 1>
        using prev = typename types_vector<Args...>::template Iterator < i - step >;
    };
}
#endif // TYPES_HANDLER_H
