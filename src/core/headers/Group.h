#ifndef OPENGLPROJECT_GROUP_H
#define OPENGLPROJECT_GROUP_H


class Group {
public:
    int groupID;
    std::string name;
    Group(const std::string name, int groupID): groupID(groupID), name(name) {}
    Group(int groupID, const std::string name): groupID(groupID), name(name) {}
};


#endif //OPENGLPROJECT_GROUP_H
