#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Examlple
{
public:
    void ex1()
    {
        std::vector<int> vect = {1, 2, 3};
        for (std::vector<int>::iterator itr = vect.begin(); itr != vect.end(); ++itr)
            cout << *itr;
        cout << endl;
        for (auto itr = vect.begin(); itr != vect.end(); itr++)
            cout << *itr;
        cout << endl;
        for (auto itr : vect)
            cout << itr;
        cout << endl;
    }

    void ex2()
    { //auto는 기본적인 type만 남겨놓고 제거함.
        int x = int();
        auto auto_x = x;

        const int &crx = x;
        auto auto_crx1 = crx;
        const auto &auto_crx2 = crx;

        volatile int vx = 1024;
        auto avx = vx;
        volatile auto vavx = vx;
    }

    // template <class T>
    // void func_ex3(T arg)
    // {
    // }

    //template도 auto랑 동일하게 기본적인 type만 남겨놓고 제거함.
    template <class T>
    void func_ex3(const T &arg)
    {
    }

    void ex3()
    {
        const int &crx = 123;
        func_ex3(crx);
    }

    void ex4()
    {
        const int c = 0;
        auto &rc = c;
        //rc = 100; // error
    }

    void ex5() //amendment
    {
        int i = 42;
        auto &&ri_1 = i;  // L-value
        auto &&ri_2 = 42; // R-value
    }

    void ex6()
    {
        int x = 42;
        const int *p1 = &x;
        auto p2 = p1;
        // *p2 = 43; // error
    }

    template <typename T, typename S>
    void func_ex7(T lhs, S rhs)
    {
        auto prod1 = lhs * rhs;

        //typedef typeof(lhs * rhs) product_type; // pre-c++11 'some' compilers
        typedef decltype(lhs * rhs) product_type;

        product_type prod2 = lhs * rhs;

        decltype(lhs * rhs) prod3 = lhs * rhs;
    }

    template <typename T, typename S>
    //decltype(lhs * rhs) func_ex8(T lhs, S rhs) // 이건 컴파일러가 반환값을 알수가 없음
    auto func_ex8(T lhs, S rhs) -> decltype(lhs * rhs)
    {
        return lhs * rhs;
    }

    void ex7_8()
    {

        //std::cout << func_ex7(1.0, 345) << std::endl;
        std::cout << func_ex8(1.3, 345) << std::endl;
    }

    struct S
    {
        int m_x;

        S()
        {
            m_x = 42;
        }
    };

    void ex9()
    {
        int x;
        const int cx = 42;
        const int &crx = x;
        const S *p = new S();
        //S *p = new S();

        auto a = x;
        auto b = cx;
        auto c = crx;
        auto d = p;
        auto e = p->m_x;

        typedef decltype(x) x_type;
        typedef decltype(cx) cx_type;
        typedef decltype(crx) crx_type;
        // 'declared' type. int m_x;가 선언될때 const가 아니기 때문임.
        typedef decltype(p->m_x) m_x_type;

        // add references to L-values. reference를 만들기 위해 괄호를 침
        typedef decltype((x)) x_with_parents_type;
        typedef decltype((cx)) cx_with_parents_type;
        typedef decltype((crx)) crx_with_parents_type;
        //()를 붙여 reference가 되기때문에 const가 붙음
        //그래서 const S *p = new S();에서 const를 없애면 const가 사라짐
        typedef decltype((p->m_x)) m_x_with_parents_type;
    }

    const S foo()
    {
        return S();
    }
    const int &foobar()
    {
        const int &a = 123;
        return a;
    }
    void ex10()
    {
        std::vector<int> vect = {42, 43};

        auto a = foo();
        typedef decltype(foo()) foo_type;

        auto b = foobar();
        typedef decltype(foobar()) foobar_type;

        auto itr = vect.begin();
        typedef decltype(vect.begin()) iterator_type;

        auto first_element = vect[0];
        decltype(vect[1]) second_element = vect[1];
    }

    void ex11()
    {
        int x = 0;
        int y = 0;
        const int cx = 42;
        const int cy = 43;
        double d1 = 3.14;
        double d2 = 2.72;

        typedef decltype(x * y) prod_xy_type;
        auto a = x * y;

        typedef decltype(cx * cy) prod_cxcy_type; // result is prvalue
        auto b = cx * cy;

        typedef decltype(d1 < d2 ? d1 : d2) cond_type; // result is L-value. & is added;
        auto c = d1 < d2 ? d1 : d2;

        typedef decltype(x < d2 ? x : d2) cond_type_mixed; // promotion of x to double
        auto d = x < d2 ? x : d2;

        //auto d = std::min(x, d1); //error. std::min(a, b);은 타입이 같을 경우에만 작동함
    }

    // template <typename T, typename S>
    // auto fpmin_wrong(T x, S y) -> decltype(x < y ? x : y)
    // {
    //     return x < y ? x : y;
    // }

    template <typename T, typename S>
    auto fpmin_wrong(T x, S y) ->
        typename std::remove_reference<decltype(x < y ? x : y)>::type
    {
        return x < y ? x : y;
    }

    void ex12()
    {
        int i = 42;
        double d = 45.1;
        //auto a = std::min(i, d); //error : 'std::min' : no matching overloaded function found
        auto a = std::min(static_cast<double>(i), d);

        int &j = i;

        typedef decltype(fpmin_wrong(d, d)) fpmin_return_type1;
        typedef decltype(fpmin_wrong(i, d)) fpmin_return_type2;
        typedef decltype(fpmin_wrong(j, d)) fpmin_return_type3;
    }

    void ex13()
    {
        std::vector<int> vect;              //vect is empty
        typedef decltype(vect[0]) interger; //vect가 비어있어도 에러라고 표현안함.
                                            //이유는 실제 실행하지 않기때문
    }

    template <typename R>
    class SomeFunctor
    {
    public:
        typedef R result_type;

        SomeFunctor()
        {
        }
        result_type operator()()
        {
            return R();
        }
    };

    void ex14()
    {
        SomeFunctor<int> func;
        typedef decltype(func)::result_type integer; // nested type
    }

    void ex15()
    {
        auto lambda = []()
        { return 42; };
        decltype(lambda) lambda2(lambda);
        decltype((lambda)) lambda3(lambda);

        cout << "Lambda functions" << endl;
        cout << &lambda << " " << &lambda2 << endl;
        cout << &lambda << " " << &lambda3 << endl;
    }

    void ex16()
    {
        //generic lambda
        auto lambda = [](auto x, auto y)
        {
            return x + y;
        };

        cout << lambda(1.1, 2) << " " << lambda(3, 4) << " " << lambda(4.5, 2.2) << endl;
    }
};

int main(void)
{
    Examlple test;
    //test.ex1();
    //test.ex7_8();
    //test.ex15();
    test.ex16();

    return 0;
}