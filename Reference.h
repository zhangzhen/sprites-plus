#ifndef REFERENCE_H
#define REFERENCE_H

class Reference
{
public:
    Reference(int id, std::string &name);
    int GetId() const { return id; }
    std::string GetName() const { return name; }

private:
    int id;
    std::string name;
};

#endif // REFERENCE_H
