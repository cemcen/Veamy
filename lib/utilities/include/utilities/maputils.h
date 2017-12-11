#ifndef UTILITIES_MAPUTILS_H
#define UTILITIES_MAPUTILS_H

/*
 * Namespace containing functions related to maps (pairs of key, value)
 */
namespace map_utils{
    /*
     * Structure that contains the operator that returns all keys of a map
     */
    struct GetKeys {
        template <typename T>
        typename T::first_type operator()(T keyValuePair) const {
            return keyValuePair.first;
        }
    };

    /*
    * Structure that contains the operator that returns all values of a map
    */
    struct GetValues {
        template <typename T>
        typename T::first_type operator()(T keyValuePair) const {
            return keyValuePair.second;
        }
    };
}

#endif 
