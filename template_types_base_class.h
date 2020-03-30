#ifndef TYPES_TRAITS_H
#define TYPES_TRAITS_H

#include <type_traits>
#include <tuple>

namespace template_type_traits
{
    template<typename ClassName>
    struct is_type_template
    {
        enum
        {
            value = false
        };
    };

    template<template<typename ...Args> class TemplateClass, typename ...Args>
    struct is_type_template<TemplateClass<Args...>>
    {
        enum
        {
            value = true
        };
    };

    //无行为
    struct non_behaivor
    {
        using result = void;
    };

    template <typename Iterator, typename TypesVector = void>
    struct true_condition
    {
        enum
        {
            value = true
        };
    };

    template <typename Iterator, typename TypesVector = void>
    struct false_condition
    {
        enum
        {
            value = false
        };
    };

    //类型容器
    template<typename ...Args>
    struct types_vector;

    //模板裂解器
    template<typename ClassName>
    struct type_exploser;

    //条件效验器
    template <template <typename Arg, typename TypesVector> class CheckClass>
    struct types_condition_remove_checker;

    //变换器
    template <template <typename Iterator, typename TypesVector> class Converter
              , template <typename Iterator, typename TypesVector> class CheckClass>
    struct types_condition_changer;

}
#endif // TYPES_TRAITS_H
