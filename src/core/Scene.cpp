void Scene::drawScene(float size) {
    for(const auto pair : instances) {
        auto shader = assignment.getShader(assignment.getGroup(pair.second));
        auto instance = pair.first;
        shader.use();

        for(auto &pair : lights) {
            shader.setLight(pair.first, pair.second);
        }

        core::makeModel(shader, *core::Data.camera);
        Transformation sizedTrans = instance.transformation;
        sizedTrans.size *= size;
        instance.draw(shader, sizedTrans);
    }
}

void Scene::drawScene() {
    for(const auto pair : instances) {
        auto shader = assignment.getShader(assignment.getGroup(pair.second));
        auto instance = pair.first;
        shader.use();

        for(auto &pair : lights) {
            shader.setLight(pair.first, pair.second);
        }

        core::makeModel(shader, *core::Data.camera);
        instance.draw(shader);
    }
}

void Scene::update(float deltaT) {
    for(auto &pair : instances) {
        auto instance = pair.first;
        instance.update(deltaT);
    }
}

void Scene::addInstance(Instance &instance, std::string group) {
    instances.insert(std::pair(instance, group));
}

Instance& Scene::getInstance(std::string name) {
    for(auto &pair: instances) {
        if (pair.first.name == name) {
            return const_cast<Instance &>(pair.first);
        }
    }
    throw sceneSearchException("Instance '" + name + "' could not be found");
}

void Scene::removeInstance(Instance &instance) {
    instances.erase(instance);
}

void Scene::addLight(std::string name, Light &light) {
    lights.insert(std::pair(name, light));
}

Light& Scene::getLight(std::string name) {
    try {
        return lights.at(name);
    } catch (std::out_of_range &e) {
        throw sceneSearchException("Light '" + name + "' could not be found");
    }
}

void Scene::removeLight(std::string name) {
    lights.erase(name);
}

void Scene::setAssignment(Assignment &a) {
    this->assignment = a;
}
Assignment& Scene::getAssignment() {
    return this->assignment;
}