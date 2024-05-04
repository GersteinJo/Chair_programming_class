// 1PCpp_rational_class_Gerstein.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cmath>
#include <vector>

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
    
    Rational(int m = 0)
    {
        this->_n = 1;
        this->_m = m;
    }
    Rational(int m, unsigned n)
    {
        this->_m = m;
        if (n == 0) throw std::overflow_error("DEVISION BY ZERO!");
        else this->_n = n;
        this->Standardize(); // usage of try catch in this line would also work
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

    Rational operator++(int)
    {
        Rational res = *this;
        this->_m += _n;
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

    Rational operator-() const
    {
        Rational res(-_m, _n);
        return res;
    }

    Rational operator-(const Rational& other) const
    {
        Rational new_r(_m * other._n - other._m * _n, _n * other._n);
        return new_r;
    }

    Rational operator+(const Rational& other) const
    {
        Rational new_r(_m * other._n + other._m * _n, _n * other._n);
        return new_r;
    }

    Rational operator*(const Rational& other) const
    {
        Rational new_r(_m * other._m, _n * other._n);
        return new_r;
    }

    Rational operator/(const Rational& other) const
    {
        Rational new_r(_m * other._n, _n * other._m);
        return new_r;
    }

    Rational& operator-=(const Rational& other)
    {
        *this = *this - other;
        return *this;
    }

    Rational& operator+=(const Rational& other)
    {
        *this = *this + other;
        return *this;
    }

    Rational& operator*=(const Rational& other)
    {
        *this = *this * other;
        return *this;
    }

    Rational& operator/=(const Rational& other)
    {
        *this = *this / other;
        return *this;
    }

    /* in visual studio also works declaration of operator Rational& operator + (Rational& other) and bool operator=(Rational& other), but other compilers
    complain that a reference to a soon be freed memory is given*/

    bool operator==(const Rational& other) const
    {
        return (_m == other._m) && (_n == other._n);
    }

    Rational pow(int n) const
    {
        Rational new_r(1);
        for (int i = 0; i < n; i++)
        {
            new_r *= *this;
        }
        for (int i = 0; i > n; i--)
        {
            new_r /= *this;
        }
        new_r.Standardize();
        return new_r;
    }

    double To_Double()
    {
        return (double)this->_m / (double)this->_n;
    }

    explicit operator double() const
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
    delete[] my_rs;
    return out;
}

std::vector<Rational> Bernully_sequence(int depth)
{
    std::vector<Rational> bs;
    for (int n = 0; n < depth; n++)
    {
        bs.push_back(Bernully(n + 1));
    }
    return bs;
}

int main()
{
    {
        Rational r1(15, 25);
        std::cout << double(r1) << "\n";
        Rational other = Rational(0.25);
        std::cout << other << "\n";
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
    std::vector<Rational> bs = Bernully_sequence(bs_depth + 1);
    std::cout << "Bernully sequence of " << bs_depth << " elements:\n";
    for (int n = 0; n < bs_depth + 1; n++) std::cout << bs[n] << " ";
    std::cout << "\n B_2k sequence of " << bs_depth / 2 << " elements:\n";
    std::vector<Rational> bs_2k;
    for (int n = 0; n < bs_depth / 2 + 1; n++)
    {
        bs_2k.push_back(bs[2 * n]);
        std::cout << bs_2k[n] << " ";
    }
    std::cout << "\n";
}

