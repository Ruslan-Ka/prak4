template <typename T1, typename T2>
auto myfilter(const T1 &cont, T2 pred)
{
    T1 tmp;
    for(auto i: cont) {
        if (pred(i)) {
            tmp.insert(tmp.end(), i);
        }
    }
    return tmp;
}