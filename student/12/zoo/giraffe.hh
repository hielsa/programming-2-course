#ifndef GIRAFFE_HH
#define GIRAFFE_HH
#include"mammal.hh"


class Giraffe: public Mammal
{
public:
    Giraffe();
    void make_noise(std::ostream& ouput) const;
};

#endif // GIRAFFE_HH
