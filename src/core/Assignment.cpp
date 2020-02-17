#include <vector>

void Assignment::addShader(Shader &shader) {
    for (auto &s: shaders) {
        if (s.name == shader.name) {
            throw assignmentSearchException("Shader '" + shader.name + "' already exists");
        }
    }
    shaders.push_back(shader);
}

Shader& Assignment::getShader(const std::string name) {
    for (auto &s: shaders) {
        if (s.name == name) {
            return s;
        }
    }
    throw assignmentSearchException("Shader '" + name + "' could not be found");
}

Shader& Assignment::getShader(Group &group) {
    int shaderID = elements.at(group.groupID);
    for (auto &s: shaders) {
        if (s.ID == shaderID) {
            return s;
        }
    }
    throw assignmentSearchException("Group '" + group.name + "' could not be found");
}

void Assignment::removeShader(std::string name) {
    for (auto &pair: elements) {
        if (pair.second == getShader(name).ID) {
            throw assignmentSearchException("Couldn't remove shader '" + name + "' which is still linked to a group");
        }
    }

    for (int i = 0; i < shaders.size(); i++) {
        if (shaders.at(i).name == name) {
            shaders.erase(shaders.begin() + i);
            break;
        }
    }
}

Group Assignment::createGroup(const std::string name) {
    Group group(name, i++);
    groups.push_back(group);
    return group;
}

void Assignment::addGroup(Group &group) {
    for (auto &g: groups) {
        if (g.groupID == group.groupID) {
            throw assignmentSearchException("Group '" + group.name + "' already exists");
        }
    }
    groups.push_back(group);
}

Group& Assignment::getGroup(const std::string name) {
    for (auto &g: groups) {
        if (g.name == name) {
            return g;
        }
    }
    throw assignmentSearchException("Group '" + name + "' could not be found");
}

void Assignment::deleteGroup(Group &group) {
    elements.erase(group.groupID);

    for (int i = 0; i < groups.size(); i++) {
        if (groups.at(i).groupID == group.groupID) {
            groups.erase(groups.begin() + i);
            break;
        }
    }
}

Group& Assignment::setPair(Group &group, Shader &shader) {
    // Ensure shader and group are stored
    try {
        addShader(shader);
    // Want to continue if shader/group is already there
    } catch (assignmentSearchException &e) {}
    try {
        addGroup(group);
    } catch (assignmentSearchException &e) {}

    elements.insert(std::pair(group.groupID, shader.ID));
}