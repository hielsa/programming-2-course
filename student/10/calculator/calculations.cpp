// Note that there is no need for "using namespace std",
// since no C++ standard libraries are used.

double addition(double left, double right) {
    return left + right;
}


double subtraction(double left, double right) {
    return left - right;
}


double multiplication(double left, double right) {
    return left * right;
}


double division(double left, double right) {
    return left / right;
}

double exp(double left, double right)
{
    double pwr = left;
    for (double d = 1; d < right; ++d)
    {
        double t = pwr;
        pwr = t * left;
    }
    return pwr;
}
