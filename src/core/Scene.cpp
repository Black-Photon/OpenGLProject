void Scene::addInstance(Instance &instance) {
    Shader shader = instance.shader;
    int pos;
    bool found = false;
    for(int i = 0; i < shaders.size(); i++) {
        if(shaders.at(i).ID == shader.ID) {
            found = true;
            pos = i;
            break;
        }
    }

    if(!found) {
        pos = shaders.size();
        shaders.push_back(shader);
    }

    found = false;
    for(auto& pair : instances) {
        if(pair.first == pos) {
            pair.second.push_back(&instance);
            found = true;
        }
    }

    if(!found) {
        std::vector<Instance*> newInstances;
        newInstances.push_back(&instance);
        instances.insert(std::pair(pos, newInstances));
    }
}

bool Scene::removeInstance(Instance &instance) {
    Shader shader = instance.shader;
    int pos;
    bool found = false;
    for(int i = 0; i < shaders.size(); i++) {
        if(shaders.at(i).ID == shader.ID) {
            found = true;
            pos = i;
            break;
        }
    }

    if(!found) {
        return false;
    }

    for(auto& pair : instances) {
        if(pair.first == pos) {
            for(int i = 0; i < pair.second.size(); i++) {
                if(pair.second.at(i)->ID == instance.ID) {
                    pair.second.erase(pair.second.begin() + i);
                    
                    return true;
                }
            }
        }
    }

    return false;
}

void Scene::replaceShader(Shader &newShader, Shader &oldShader) {
    for(auto & shader : shaders) {
        if(shader.ID == oldShader.ID) {
            shader = newShader;
            break;
        }
    }
}

void Scene::drawScene(bool drawRoom, float size) {
    for(const auto pair : instances) {
        auto shader = shaders.at(pair.first);
        auto instanceList = pair.second;
        shader.use();

        for(auto &pair : lights) {
            shader.setLight(pair.first, pair.second);
        }

        core::makeModel(shader, *core::Data.camera);
        for(auto instance : instanceList) {
            Transformation sizedTrans = instance->transformation;
            sizedTrans.size *= size;
            if(drawRoom || !instance->inside) instance->draw(shader, sizedTrans);
        }
    }
}

void Scene::drawScene(bool drawRoom) {
    for(const auto pair : instances) {
        auto shader = shaders.at(pair.first);
        auto instanceList = pair.second;
        shader.use();

        for(auto &pair : lights) {
            shader.setLight(pair.first, pair.second);
        }

        core::makeModel(shader, *core::Data.camera);
        for(auto instance : instanceList) {
            if(drawRoom || !instance->inside) instance->draw(shader);
        }
    }
}

void Scene::addLight(std::string name, Light &light) {
    lights.insert(std::pair(name, light));
}

bool Scene::removeLight(std::string name) {
    return lights.erase(name) > 0;
}

Light& Scene::getLight(std::string name) {
    try {
        return lights.at(name);
    } catch (std::out_of_range &e) {
        throw sceneSearchException("Light '" + name + "' could not be found");
    }
}

Instance& Scene::getInstance(std::string name) {
    for(auto &pair : instances) {
        for(Instance *instance : pair.second) {
            if(instance->name == name) {
                return *instance;
            }
        }
    }
    throw sceneSearchException("Instance '" + name + "' could not be found");
}

void Scene::update(float deltaT) {
    for(auto &pair : instances) {
        for(auto &instance : pair.second) {
            instance->update(deltaT);
        }
    }
}