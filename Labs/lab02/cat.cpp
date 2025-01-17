#include <iostream>

class Cat {
    private: 
        int lives;
    public: 
    Cat(int initialLives){
        lives = initialLives;
    }
    void reportLives(){
        std::cout << lives;
    }
    void loseLife(){
        lives -= 1;
    }

    Cat& operator+=(int additionalLives){
        lives += additionalLives;
        return *this;
    }
};

int main(){
    Cat myCat(9);
    myCat.loseLife();
    myCat += 1;
    myCat.reportLives();
    return 0;
}