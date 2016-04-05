#ifndef POSITIONPICKER_H
#define POSITIONPICKER_H

class IPositionPicker
{
public:
    virtual int Pick(std::vector<int> positions) = 0;
};

#endif // POSITIONPICKER_H
