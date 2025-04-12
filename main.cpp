#include<array>
#include<iostream>

template<class T, class... Ts>
struct finder
{
    static constexpr std::size_t value = -1u;
};

template<class T, class U, class... Ts>
struct finder<T, U, Ts...>
{
    static constexpr const std::size_t value = 1 + finder<T, Ts...>::value;
};

template<class T, class... Ts>
struct finder<T, T, Ts...>
{
    static constexpr std::size_t value = 0u;
};

template<class T, class... Ts>
constexpr auto find_index() -> std::size_t 
{
    return finder<T, Ts...>::value;
}

//Value-based TMP
template<class T>
struct type 
{
    static void id() {}
};

template<class T> 
inline constexpr auto meta = type<T>::id;

template<typename T, typename... Ts>
std::size_t find_vb()
{
    std::array ts{meta<Ts>...};
    for(auto i = 0u; i != ts.size(); ++i)
    {
        if(ts[i] == meta<T>)
        {
            return i;
        }
    }
    return ts.size();
}

int main()
{
    static_assert(0u == find_index<int, int, float, short>());
    static_assert(1u == find_index<int, char, int, float>());
    static_assert(2u == find_index<char, int, float, char, double>());

    static_assert(meta<int> != meta<void>);
    static_assert(meta<char> == meta<char>);
    std::cout << find_vb<int, char, float, double, int>() << std::endl; 
    return 0;
}