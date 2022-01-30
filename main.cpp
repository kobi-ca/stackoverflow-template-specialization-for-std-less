#include <vector>
#include <algorithm>
#include <map>

namespace {

    template<typename T,int _Rows, int _Cols>
    struct M {};

    template<typename T,
            int _Rows,
            int _Cols>
    class Matrix : public M<T, _Rows, _Cols> {
    public:
        bool operator<(const Matrix& m) const { /* impl here returning true or false */}

    };

    template<typename T,
            int _Rows,
            int _Cols>
    class Matrix1 : public M<T, _Rows, _Cols> {
    public:
        friend bool operator<(const Matrix1& m1, const Matrix1& m2) { /* impl here returning true or false */}
    };

    template<typename T,
            int _Rows,
            int _Cols>
    class Matrix2 : public M<T, _Rows, _Cols> {};

    /*
    template<typename Matrix<typename T, // <-- this is not going to compile
            int _Rows = Eigen::Dynamic,
            int _Cols = Eigen::Dynamic> > >
    struct less
    {
        bool operator()(const Matrix<T,
                Rows,
                Cols>& lhs,
                        const Matrix<T,
                                Rows,
                                Cols>& rhs) const // there was a ; here
        {
            Matrix<T,
                    Rows,
                    Cols>::const_iterator lhsIt = lhs.begin();
            Matrix<T,
                    Rows,
                    Cols>::const_iterator rhsIt = rhs.begin();
            for (;
                    lhsIt != lhs.end();
                    ++lhsIt, ++rhsIt)
            {
                if (*lhsIt < *rhsIt)
                {
                    return true;
                }
            }
            return false;
        }
    };
    */

    bool Comp(const Matrix<int, 3, 3>& m1, const Matrix<int, 3, 3>& m2) { /* return something */ }

    struct Compare {
        bool operator()(const Matrix<int, 3, 3> &m1, const Matrix<int, 3, 3> &m2) const { /* return something */ }
    };
}

// https://stackoverflow.com/a/58889891/1442880
// https://stackoverflow.com/a/32265690/1442880
namespace std {
    template<typename T, int _Rows, int _Cols>
    struct less<Matrix2 <T, _Rows, _Cols>> {
        bool operator()(const Matrix2 <T, _Rows, _Cols> &lhs,
                        const Matrix2 <T, _Rows, _Cols> &rhs) const {
            return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
        }
    };
}

int main() {

    // note the * in the decltype
    //https://stackoverflow.com/a/57105040/1442880
    {
        std::map<Matrix<int, 3, 3>, int, decltype(Comp) *> m(&Comp); // without &Comp it will compile but segfault!
        m[Matrix<int, 3, 3>{}] = 3;
        m[Matrix<int, 3, 3>{}] = 4;
    }
    {
        std::map<Matrix<int, 3, 3>, int, Compare> m;
    }

    {
        std::map<Matrix<int, 3, 3>, int> m;
    }

    {
        std::map<Matrix2<int, 3, 3>, int> m;
    }

    std::vector<Matrix<int, 3, 3>> v(10);
    std::sort(v.begin(), v.end());
    return 0;
}
