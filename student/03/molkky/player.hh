#ifndef PLAYER_HH
#define PLAYER_HH

#include <string>


class Player
{
public:
    Player(const std::string& name);
    const std::string& get_name();
    int get_points();
    void add_points(int points);
    bool has_won();

private:
    const std::string name_;
    int points_;
};


#endif // PLAYER_HH
