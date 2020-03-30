#ifndef TYPE_EXTRACTOR_H
#define TYPE_EXTRACTOR_H
#include "template_types_base_class.h"
namespace template_type_traits
{
    template<template<typename ...Args> class ClassName, typename ...Args>
    struct type_exploser<ClassName<Args...>>
    {
        enum
        {
            ARGS_NUM = sizeof... (Args)
        };

        //读取
        template<size_t i>
        using arg = typename std::tuple_element<i, std::tuple<Args...> >::type;

        //获得原有类型
        template<typename ...InputArgs>
        using class_type = ClassName<InputArgs...>;

        //返回值
        template<template <typename ...HandledArgs> class ApplyClass, typename ...ExtraArgs>
        using apply = ApplyClass<Args..., ExtraArgs...>;
    };
}
#endif // TYPE_EXTRACTOR_H
