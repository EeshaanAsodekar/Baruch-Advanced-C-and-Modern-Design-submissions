#include <iostream>
#include <functional>
#include <cmath>

// given function classes
// Function maps Domain to Range
template <typename R, typename D>
using FunctionType = std::function<R(const D x)>;
// Working function type
using ScalarFunction = FunctionType<double, double>;

// Subquestion (a)
template <typename R, typename D>
FunctionType<R, D> operator + (const FunctionType<R, D>& f,
    const FunctionType<R, D>& g)
{
    // Addition of functions
    return [=](const D& x)
        {
            return f(x) + g(x);
        };
}

template <typename R, typename D>
FunctionType<R, D> operator - (const FunctionType<R, D>& f,
    const FunctionType<R, D>& g)
{
    // Subtraction of functions
    return [=](const D& x)
        {
            return f(x) - g(x);
        };
}

template <typename R, typename D>
FunctionType<R, D> operator * (const FunctionType<R, D>& f,
    const FunctionType<R, D>& g)
{
    // Multiplication of functions
    return [=](const D& x)
        {
            return f(x) * g(x);
        };
}

template <typename R, typename D>
FunctionType<R, D> operator / (const FunctionType<R, D>& f,
    const FunctionType<R, D>& g)
{
    // Division of functions
    return [=](const D& x)
        {
            return f(x) / g(x);
        };
}

template <typename R, typename D>
FunctionType<R, D> operator * (const double& scale,const FunctionType<R, D>& f)
{
    // Multiplication of function and scalar
    return [=](const D& x)
        {
            return scale*f(x);
        };
}

template <typename R, typename D>
FunctionType<R, D> operator - (const FunctionType<R, D>& f)
{
    // Unary inverse of a function
    return [=](const D& x)
        {
            return -f(x);
        };
}

template <typename R, typename D>
FunctionType<R, D> operator << (const FunctionType<R, D>& f,
    const FunctionType<R, D>& g)
{
    // composition
    return [=](const D& x)
        {
            return f(g(x));
        };
}

// Subquestion (b)
template <typename R, typename D>
FunctionType<R, D> exp(const FunctionType<R, D>& f)
{
    // The exponential function
    return [=](const D& x)
        {
            return std::exp(f(x));
        };
}

template <typename R, typename D>
FunctionType<R, D> log(const FunctionType<R, D>& f)
{
    // The log function
    return [=](const D& x)
        {
            return std::log(f(x));
        };
}

template <typename R, typename D>
FunctionType<R, D> cos(const FunctionType<R, D>& f)
{
    // The cosine function
    return [=](const D& x)
        {
            return std::cos(f(x));
        };
}

template <typename R, typename D>
FunctionType<R, D> abs(const FunctionType<R, D>& f)
{
    // The absolute function
    return [=](const D& x)
        {
            return std::abs(f(x));
        };
}

template <typename R, typename D>
FunctionType<R, D> sqrt(const FunctionType<R, D>& f)
{
    // The absolute function
    return [=](const D& x)
        {
            return std::sqrt(f(x));
        };
}

// Subquestion (c)
template <typename R, typename D>
FunctionType<R, D> max(const FunctionType<R, D>& f,
    const FunctionType<R, D>& g)
{
    // max of the two fucntions
    return [=](const D& x)
        {
            if (f(x) >= g(x)) return f(x);
            else return g(x);
        };
}

template <typename R, typename D>
FunctionType<R, D> min(const FunctionType<R, D>& f,
    const FunctionType<R, D>& g)
{
    // min of the two fucntions
    return [=](const D& x)
        {
            if (f(x) <= g(x)) return f(x);
            else return g(x);
        };
}

int main()
{
    // Scalar functions: double to double
    ScalarFunction f = [](double x) {return x* x; };
    ScalarFunction g = [=](double x) { return x; };

    double x = 4.0;
    std::cout << "x: " << x << std::endl;
    std::cout << "ScalarFunction f = [](double x) {return x* x; };" << std::endl;
    std::cout << "ScalarFunction g = [=](double x) { return x; };" << std::endl;

    std::cout << "\n\nSubquestion (a)\n\n";

    // Subquestion (a)

    auto func_f_plus_g = (f + g);
    auto func_f_minus_g = (f - g);
    auto func_f_multipled_g = (f * g);
    auto func_f_divided_g = (f / g);
    auto func_f_unaryInverse = -f;
    auto func_f_sclar_mulp = 2 * f;
    auto func_f_comp_f_comp_g = f<<f<<g;


    std::cout << "\nfunc_f_plus_g(x): " << func_f_plus_g(x);
    std::cout << "\nfunc_f_minus_g(x): " << func_f_minus_g(x);
    std::cout << "\nfunc_f_multipled_g(x): " << func_f_multipled_g(x);
    std::cout << "\nfunc_f_divided_g(x): " << func_f_divided_g(x);
    std::cout << "\nfunc_f_unaryInverse(x): " << func_f_unaryInverse(x);
    std::cout << "\nfunc_f_sclar_mulp(x): " << func_f_sclar_mulp(x);
    std::cout << "\nfunc_f_comp_f_comp_g(x): " << func_f_comp_f_comp_g(x);

    std::cout << "\n\nSubquestion (b)\n\n";

    // Subquestion (b)
    auto func_exp_f = exp(f);
    auto func_log_f = log(f);
    auto func_cos_f = cos(f);
    auto func_abs_f = abs(f);
    auto func_sqrt_f = sqrt(f);

    std::cout << "\nfunc_exp_f(x): " << func_exp_f(x);
    std::cout << "\nfunc_log_f(x): " << func_log_f(x);
    std::cout << "\nfunc_cos_f(x): " << func_cos_f(x);
    std::cout << "\nfunc_abs_f(x): " << func_abs_f(x);
    std::cout << "\nfunc_sqrt_f(x): " << func_sqrt_f(x);

    std::cout << "\n\n\ntesting using the given code snippets: \n\n";
    // Subquestion (a)
    double scale = 2.0;
    auto fA = 2.0 * (f + g);
    auto fM = f - g;
    auto fD = f / g;
    auto fMul = f * g;
    auto fC = g << g << 4.0 * g;// Compose
    auto fMinus = -(f + g);

    x = 5.0;

    std::cout << fA(x) << ", " << fM(x) << ", " << fD(x) << ", "
        << fMul(x) << ", compose: " << fC(x) << ", " << fMinus(x);
    // Subquestion (b)
    
    auto ftmp = log(g);
    auto ftmp2 = cos(f);
    auto f2 = (abs(exp(g)) * log(g) + sqrt(ftmp)) / ftmp2;
    std::cout << "\nf2(x): " << f2(x) << std::endl;


    // Subquestion (c)
    auto h1 = min(f, g);
    auto h2 = max(f, g);
    std::cout << "min(f,g): " << h1(2.0) << '\n';
    std::cout << "max(f,g): " << h2(2.0) << '\n';
    auto h3 = min(h1, max(2 * f, 3 * g));
    auto h4 = max(h2, max(-2 * f, 3 * g));
    std::cout << "min(h1, max(2 * f, 3 * g)): " << h3(2.0) << '\n';
    std::cout << "max(h2, max(-2 * f, 3 * g)): " << h4(2.0) << '\n';
    return 0;
}
