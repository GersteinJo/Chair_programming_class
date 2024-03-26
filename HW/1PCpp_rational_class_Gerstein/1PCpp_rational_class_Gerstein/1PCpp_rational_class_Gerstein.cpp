// 1PCpp_rational_class_Gerstein.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cmath>

int euclidean_algorithm(int a, int b)
{
    a = std::abs(a);
    b = std::abs(b);
    while (b != 0)
    {
        int tmp = b;
        b = a % b;
        a = tmp;
    }

    return a;
}

class Rational
{
private:
    unsigned _n;
    int _m;

    void Standardize()
    {
        int greatest_common_denominator = euclidean_algorithm(this->_m, this->_n);
        this->_m /= greatest_common_denominator;
        this->_n /= greatest_common_denominator;
    }




public:
    Rational() = default;
    Rational(int m)
    {
        this->_n = 1;
        this->_m = m;
    }
    Rational(int m, unsigned n)
    {
        this->_m = m;
        this->_n = n;
        this->Standardize();
    }

    Rational(double d, double eps = 1e-8)
    {
        float t = 1;

        while (std::abs(((int)(t * d) / t) - d) > eps)
        {
            t *= 10.0;
        }
        this->_m = t * d;
        this->_n = t;
        this->Standardize();
    }


    friend std::ostream& operator << (std::ostream& out, Rational r)
    {
        return out << r._m << "/" << r._n;
    }

    Rational& operator++(int)
    {
        Rational res = *this;
        _m += _n;
        return res;
    }

    Rational& operator++()
    {
        _m += _n;
        return *this;
    }

    Rational operator--(int)
    {
        Rational res = *this;
        _m -= _n;
        return res;
    }
    Rational& operator--()
    {
        _m -= _n;
        return *this;
    }

    Rational& operator-()
    {
        _m = -_m;
        return *this;
    }

    Rational operator-(Rational& other)
    {
        Rational new_r(_m * other._n - other._m * _n, _n * other._n);
        return new_r;
    }

    Rational operator+(Rational& other)
    {
        Rational new_r(_m * other._n + other._m * _n, _n * other._n);
        return new_r;
    }

    Rational operator*(Rational& other)
    {
        Rational new_r(_m * other._m, _n * other._n);
        return new_r;
    }

    Rational operator/(Rational& other)
    {
        Rational new_r(_m * other._n, _n * other._m);
        return new_r;
    }

    Rational& operator-=(Rational& other)
    {
        _m = _m * other._n - other._m * _n;
        _n = _n * other._n;
        this->Standardize();
        return *this;
    }

    Rational& operator+=(Rational& other)
    {
        _m = _m * other._n + other._m * _n;
        _n = _n * other._n;
        this->Standardize();
        return *this;
    }

    Rational& operator*=(Rational& other)
    {
        _m *= other._m;
        _n *= other._n;
        this->Standardize();
        return *this;
    }

    Rational& operator/=(Rational& other)
    {
        _m *= other._n;
        _n *= other._m;
        this->Standardize();
        return *this;
    }

    bool operator=(Rational other)
    {
        this->_m = other._m;
        this->_n = other._n;
        return true;
    }

    /* in visual studio also works declaration of operator Rational& operator + (Rational& other) and bool operator=(Rational& other), but other compilers
    complain that a reference to a soon be freed memory is given*/

    bool operator==(Rational& other)
    {
        return (_m == other._m) && (_n == other._n);
    }

    Rational& pow(int n)
    {
        Rational new_r(1);
        for (int i = 0; i < n; i++)
        {
            new_r *= *this;
        }
        new_r.Standardize();
        return new_r;
    }

    double To_Double()
    {
        return (double)this->_m / (double)this->_n;
    }

    ~Rational() = default;
};

Rational Bernully(int n)
{
    Rational* my_rs = new Rational[n];
    for (int i = 0; i < n; i++)
    {
        Rational new_r(1, 1 + i);
        my_rs[i] = new_r;

        for (int j = i; j > 0; j--)
        {
            Rational j_r(j);
            my_rs[j - 1] -= my_rs[j];
            my_rs[j - 1] *= j_r;
        }

        /*{
            for (int j = i; j >= 0; j--)
            {
                std::cout << my_rs[j] << "\t";
            }
            std::cout << "\n";
        }*/
    }
    Rational out = my_rs[0];
    return out;
}

Rational* Bernully_sequence(int depth)
{
    Rational* bs = new Rational[depth];
    for (int n = 0; n < depth; n++)
    {
        Rational tmp = Bernully(n + 1);;
        bs[n] = tmp;
    }
    return bs;
}

int main()
{
    {
        Rational r1(15, 25);
        Rational r2(0.25);
        Rational r3 = r1 + r2;
        r1 *= r3;
        r3 /= r1;
        std::cout << r1 << " " << r3 << "\n";
        r1 += r2;
        r2 -= r1;
        std::cout << r1 << " " << r2 << "\n";
        Rational r4 = --r2++;
        std::cout << r1 << " " << r2 << " " <<r4<<"\n";
        r3 = r1 / r2;
        std::cout << r3 << "\n";
        r3 = r1 - r2;
        std::cout << r3 << "\n";
        r3 = r1 * r2;
        std::cout << r3 << "\n";
        std::cout << (r1 == r2) << "\n";
        r3 = r1.pow(4);
        std::cout << r3 << "\n";
        std::cout << r3.To_Double() << "\n *** \n";
    }


    int bs_depth;
    std::cout << "Enter the expected depth of the sequence: ";
    std::cin >> bs_depth;
    Rational* bs = Bernully_sequence(bs_depth + 1);
    std::cout << "Bernully sequence of " << bs_depth << " elements:\n";
    for (int n = 0; n < bs_depth + 1; n++) std::cout << bs[n] << " ";
    std::cout << "\n B_2k sequence of " << bs_depth / 2 << " elements:\n";
    Rational* bs_2k = new Rational[bs_depth / 2 + 1];
    for (int n = 0; n < bs_depth / 2 + 1; n++)
    {
        bs_2k[n] = bs[2 * n];
        std::cout << bs_2k[n] << " ";
    }
    std::cout << "\n";


}

