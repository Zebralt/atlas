#include "rolling_numbers.hpp"
#include "../graphic_obj.hpp"

/// ROLLINGNUMBERS

RollingNumbers::RollingNumbers(sf::Text* target, int goal, int interval, int wait) : Animation(interval,wait) {
    this->target = target;
    this->goal = goal;
    this->size = target->getString().toAnsiString().length();
}

void RollingNumbers::update() {
    int now = clock.getElapsedTime().asMilliseconds();
    if (isRunning() && now - past >= interval) {
        past = now;
        int x = atoi(target->getString().toAnsiString().c_str());
        if (x >= goal) {
            status = TERMINATED;
            if (x > goal) {
                target->setString(std::to_string(goal));
            }
            return;
        }
        else {
            std::string sx = target->getString();
            std::string s = std::to_string(x);
            std::string gl = std::to_string(goal);
            if (gl.length() > s.length()) {
                for (int i=0;i<gl.length()-s.length();i++) {
                    s.insert(0,"0");
                }
            }
            for (int i=0;i<s.length();i++) {
                if (s[i] != gl[i]) {
                    s[i]++;
                    s[i] = char(48 +
                        ((int) s[i] - 48)%10
                            );
                }
            }
            if (s.length() < this->size) {
                int t = s.length();
                for (int i=0;i<this->size-t;i++) {
                    s.insert(0,"0");
                }
            }
            target->setString(s);

        }
    }
}
