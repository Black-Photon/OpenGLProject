#ifndef OPENGLPROJECT_ASSIGNMENT_H
#define OPENGLPROJECT_ASSIGNMENT_H

#include "Group.h"

class Assignment {
private:
    int i;
    std::vector<Shader> shaders;
    std::map<int, int> elements;
    std::vector<Group> groups;
public:
    Assignment(): i(1) {}
    void addShader(Shader &shader);
    Shader& getShader(std::string name);
    Shader& getShader(Group &group);
    void removeShader(std::string name);

    Group createGroup(std::string name);
private:
    void addGroup(Group &group);
public:
    Group& getGroup(std::string name);
    void deleteGroup(Group &group);

    Group& setPair(Group &group, Shader &shader);

    /**
     * Indicated an error occurred in searching for an assignment object
     */
    struct assignmentSearchException : public std::exception {
        std::string s;

        explicit assignmentSearchException(const std::string &string) {
            s = string;
        }

        const char *what() const noexcept(true) override {
            return s.c_str();
        }
    };
};


#endif //OPENGLPROJECT_ASSIGNMENT_H
