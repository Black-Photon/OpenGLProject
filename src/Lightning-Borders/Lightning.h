#ifndef SPACIALFREEZE_LIGHTNING_H
#define SPACIALFREEZE_LIGHTNING_H

class Lightning {
public:
    void update(float std);
    [[nodiscard]] unsigned int getTexture() const;
    Lightning();

private:
    std::random_device rd;
    static unsigned const int dataLength = 1024;
    float data[dataLength];

    float update(float initial, float std);
};


#endif //SPACIALFREEZE_LIGHTNING_H
