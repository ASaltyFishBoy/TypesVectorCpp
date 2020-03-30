# TypesVectorCpp
Type vector based on variable parameter template

This is my personal exercise code for templates, so I did n’t really consider it a mature project
，so it is imperfect
, and I also didn't consider the actual use of this project.

The the most important header file is types_vectors.h ,other header files are only used for implementation.

Provides the following interfaces


::arg<i>            
      
Read the type of the nth parameter


::apply<template <typename ...HandledArgs> class ApplyClass, typename ...ExtraArgs>      
      
Put all types inside into another template，and at the same time put other types in front       
   
   
::apply_extra_back<template <typename ...HandledArgs> class ApplyClass, typename ...ExtraArgs>
      
Put all types inside into another template，and at the same time put other types in back


::remove_if_by_iterator<template <typename Arg, typename TypesVector = void> class CheckClass>


::remove_if<template <typename Arg> class CheckClass>
      
Need a class with a value enum


::merge<typename ...TypesVectors>
      
Merge multiple containers


::erase<from,to = from + 1>

Half-closed half-open interval


::insert<i, typename ...InsertArgs>

index i arg will become insertArg


::change_if_by_iterator<template <typename Iterator, typename TypesVector = void> class Converter
                 , template <typename Iterator, typename TypesVector = void> class CheckClass>
                 
                 
::change<n,typename Arg>


::foreach<template <typename Arg> class Converter>
      
Change parameter，foreach need a class has "using result";
