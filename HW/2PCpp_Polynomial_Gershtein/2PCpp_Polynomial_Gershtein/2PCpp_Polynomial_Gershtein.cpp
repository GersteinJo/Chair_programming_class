// 2PCpp_Polynomial_Gershtein.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>


class Polynomial
{
public:
    Polynomial()
    {
        coefficients = { 0. };
    }

    Polynomial(const std::vector<double>& coefs) : coefficients(coefs)
    { 
        if(coefficients.size() == 0) coefficients.push_back(0.0);
    }
    

    Polynomial operator-() const;

    Polynomial operator-(const Polynomial& other);
    Polynomial operator+(const Polynomial& other);
    Polynomial operator*(const Polynomial& other);

    Polynomial& operator+=(const Polynomial& other);
    Polynomial& operator-=(const Polynomial& other);
    Polynomial& operator*=(const Polynomial& other);

    Polynomial derivative() const;
    double derivative(double x) const;

    double operator()(double x);

    friend std::ostream& operator<<(std::ostream& out, const Polynomial& other);

private:
    std::vector<double> coefficients;
};

Polynomial Polynomial::operator-() const
{
    std::vector<double> new_coefs;
    std::copy(coefficients.begin(), coefficients.end(), std::back_inserter(new_coefs));
    std::for_each(new_coefs.begin(), new_coefs.end(), [](double& x) { x = -x; });
    Polynomial res(new_coefs);
    return res;
}

Polynomial Polynomial::operator-(const Polynomial& other)
{
    std::vector<double> new_coefs(std::max(other.coefficients.size(), coefficients.size()));
    if (other.coefficients.size() > coefficients.size())
    {
        int tmp = other.coefficients.size() - coefficients.size();
        for (int i = 0; i < tmp; i++) coefficients.push_back(0.0);
    }
    for (int i = 0; i < other.coefficients.size(); i++)
    {
        new_coefs[i] = coefficients[i] - other.coefficients[i];
    }
    Polynomial res(new_coefs);
    return res;
}

Polynomial Polynomial::operator+(const Polynomial& other)
{
    std::vector<double> new_coefs(std::max(other.coefficients.size(), coefficients.size()));
    if (other.coefficients.size() > coefficients.size())
    {
        int tmp = other.coefficients.size() - coefficients.size();
        for (int i = 0; i < tmp; i++) coefficients.push_back(0.0);
    }
    for (int i = 0; i < other.coefficients.size(); i++)
    {
        new_coefs[i] = coefficients[i] + other.coefficients[i];
    }
    Polynomial res(new_coefs);
    return res;
}

Polynomial Polynomial::operator*(const Polynomial& other)
{
    size_t n = coefficients.size() + other.coefficients.size() - 1;
    std::vector<double> new_coefs(n, 0.0);
    for (int i = 0; i < coefficients.size(); i++)
    {
        for (int j = 0; j < other.coefficients.size(); j++)
        {
            new_coefs[i + j] += coefficients[i] * other.coefficients[j];
        }
    }
    Polynomial res(new_coefs);
    return res;
}

Polynomial& Polynomial::operator-=(const Polynomial& other)
{
    *this = *this - other;
    return *this;
}

Polynomial& Polynomial::operator+=(const Polynomial& other)
{
    *this = *this + other;
    return *this;
}

Polynomial& Polynomial::operator*=(const Polynomial& other)
{
    *this = *this * other;
    return *this;
}

Polynomial Polynomial::derivative() const
{
    if (coefficients.size() == 1)
    {
        Polynomial res;
        return res;
    }
    std::vector<double>vec(coefficients.size() - 1);
    for (int i = 1; i < coefficients.size(); i++)
    {
        vec[i - 1] = (double)i * coefficients[i];
    }
    Polynomial res(vec);
    return res;
}

double Polynomial::derivative(double x) const
{
    Polynomial res = derivative();
    return res(x);
}

double Polynomial::operator()(double x)
{
    double sum = coefficients[coefficients.size() - 1];
    for (int i = coefficients.size()-2; i>-1; i--) sum = sum * x + coefficients[i];
    return sum;
}

std::ostream& operator<<(std::ostream& out, const Polynomial& other)
{
    bool not_first = false;
    if (other.coefficients[0] != 0)
    {
        out << other.coefficients[0];
        not_first = true;
    }
    if (other.coefficients.size() > 1)
    {
        if (other.coefficients[1] > 0 && not_first)
        {
            if (other.coefficients[1] == 1.) out << "+" << "x";
            else out << "+" << other.coefficients[1]<<"x";
        }
        else if (other.coefficients[1] < 0 || !not_first)
        {
            if (other.coefficients[1] == -1.) out << "-" << "x";
            else out << other.coefficients[1] <<"x";
            not_first = true;
        }
    }
    for (int i = 2; i < other.coefficients.size(); i++)
    {
        if (other.coefficients[i] > 0 && not_first)
        {
            if (other.coefficients[i] == 1.) out << "+" << "x^" << i;
            else out << "+" << other.coefficients[i] << "x^" << i;
        }
        else if (other.coefficients[i] < 0 || !not_first)
        {
            if(other.coefficients[i]==-1)out <<  "-x^" << i;
            else out << other.coefficients[i] << "x^" << i;
            not_first = true;
        }
    }
    if (!not_first) out << 0;
    return out;
}

double ln(double x)
{
    return std::log(x + 1.);
}
double d_ln(double x)
{
    return 1. / (x + 1.);
}

double sinx(double x)
{
    return std::sin(x) / x;
}

double d_sinx(double x)
{
    return std::cos(x) / x - std::sin(x)/x/x;
}

int main()
{
    Polynomial T({ 1,2,3 });
    Polynomial dT = T.derivative();
    for (size_t i = 1; i < 10; i++) {
        std::cout << " dT(" << i << ")= " << dT << std::endl;
        dT = dT.derivative();
    }
    std::vector<double> vln = { 0., 1., -1. / 2., 1. / 3., -1. / 4., 1. / 5. };
    std::vector<double> vsn = { 1., 0., -1. / 6., 0., -1. / 120., 0., 1./5040.};
    Polynomial ln_pol(vln);
    Polynomial other = -ln_pol;
    std::cout << ln_pol << "\t" << other << "\n";
    Polynomial sn_pol(vsn);
    std::cout << ln_pol << " " << sn_pol << "\n";
    std::cout << ln_pol + sn_pol << "\n";
    std::cout << ln_pol - sn_pol << "\n";
    std::cout << ln_pol * sn_pol << "\n";
    double x = 0.05;
    std::cout << ln_pol.derivative() << "=" << ln_pol.derivative(x) << " || " << d_ln(x) << "\n";
    std::cout << sn_pol.derivative() << "=" << sn_pol.derivative(x) << " || " << d_sinx(x) << "\n";
    std::cout << ln_pol(x) << " " << ln(x) << " || " << sn_pol(x) << " " << sinx(x) << "\n";
    std::cout << (ln_pol * sn_pol)(x) << " " << ln(x) * sinx(x) << "\n";
    std::cout << (ln_pol + sn_pol)(x) << " " << ln(x) + sinx(x) << "\n";
    std::cout << (ln_pol - sn_pol)(x) << " " << ln(x) - sinx(x) << "\n";

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
