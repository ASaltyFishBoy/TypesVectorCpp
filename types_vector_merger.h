#ifndef TYPES_HANDLER_MERGER_H
#define TYPES_HANDLER_MERGER_H
#include "template_types_base_class.h"
#include "template_looper.h"
#include "template_if.h"

namespace template_type_traits
{

    template<typename FrontTypesVector, typename BackTypesVector>
    struct two_types_vector_merge;
    template< typename ...FrontArgs, typename ...BackArgs>
    struct two_types_vector_merge<types_vector<FrontArgs...>, types_vector<BackArgs...>>
    {
        using result = types_vector<FrontArgs..., BackArgs...>;
    };

    template <typename ...TypesVectors>
    struct types_vector_merge
    {
        template<typename Iterator, typename TypesVector>
        struct LoopBehaivor
        {
        public:
            using result = types_vector <
                           typename two_types_vector_merge <
                           typename TypesVector::template arg<0>,
                                    typename Iterator::arg
                                    >::result
                                    >;
        };

    public:
        using result = typename template_looper <
                       typename types_vector<TypesVectors...>::template Iterator<0>,
                                types_vector<types_vector<>>,
                                LoopBehaivor
                                >
                                ::result::template arg<0>;
    };
}
#endif // TYPES_HANDLER_MERGER_H
