#include <iostream>

using namespace std;

// Before passing automated tests, do not touch the values of the following
// constants, even if they differ from those you see in Plussa.
// At the end of the course, if you use this program to count your final grade,
// you should update the constants to make them identical with those in Plussa.
unsigned int MAX_N_POINTS = 780;
unsigned int MAX_G_POINTS = 100;


unsigned int weekly_exercises(unsigned n, unsigned g)
{
    float n_only = (n * 100.0) / MAX_N_POINTS;
    float n_and_g = ((n + g) * 100.0) / (MAX_N_POINTS + MAX_G_POINTS);
    float better_score = max(n_only, n_and_g);
    if (better_score < 50.0) return 0;
    if (better_score < 60.0) return 1;
    if (better_score < 70.0) return 2;
    if (better_score < 80.0) return 3;
    if (better_score < 90.0) return 4;
    return 5;
}

unsigned int gui_exercises(unsigned int g)
{
    float score_g = (g * 100.0) / MAX_G_POINTS;
    if(score_g < 30.0) return 2;
    if(score_g < 40.0) return 3;
    if(score_g < 50.0) return 4;
    return 5;
}

unsigned int projects(unsigned int p)
{
    if(p < 51) return 0;
    if(p < 75) return 1;
    if(p < 125) return 2;
    if(p < 150) return 3;
    if(p < 175) return 4;
    return 5;
}

unsigned int round(float fp)
{
    unsigned int rounded_value = static_cast<unsigned int>(fp);
    if(fp - rounded_value > 0.5)
    {
        return rounded_value + 1;
    }
    return rounded_value;
}

unsigned int final_grade(float mean, unsigned int g)
{
    unsigned int rounded_mean = round(mean);
    if(rounded_mean < 3)
    {
        return rounded_mean;
    }
    if(rounded_mean < 4 && g >= 3)
    {
        return rounded_mean;
    }
    if(rounded_mean < 5 && g >= 4)
    {
        return rounded_mean;
    }
    if(rounded_mean == 5 && g == 5)
    {
        return rounded_mean;
    }
    return g;
}

int main()
{
    unsigned int n = 0;
    unsigned int g = 0;
    unsigned int p = 0;
    unsigned int e = 0;
    cout << "Enter N points, G points, P points: ";
    cin >> n;
    cin >> g;
    cin >> p;
    cout << "Enter exam grade (if no exam, enter zero): ";
    cin >> e;

    float mean = 0.0;
    int score_w = weekly_exercises(n, g);
    int score_p = projects(p);

    if(score_w == 0 || score_p == 0)
    {
        cout << "The final grade is 0" << endl;
        return 0;
    }
    if (e==0)
    {
        mean = ((score_w + score_p) / 2.0) - 2.0;
    }
    else
    {
        mean = (score_w + score_p + e) / 3.0;
    }

    cout << "The final grade is " << final_grade(mean, gui_exercises(g)) << endl;

    return 0;

    return 0;
}
