long Instance::lastID = 0;

Instance::Instance(Model &model, Shader &shader, std::string name) : shader(shader), model(&model), name(name) {
    ID = lastID++;
}
void Instance::draw() {
    shader.use();
    core::makeModel(shader, *core::Data.camera);
    draw(shader);
}

void Instance::draw(Shader &altShader) {
    draw(altShader, transformation);
}

void Instance::draw(Shader &altShader, Transformation altTrans) {
    altShader.setMat4("model", altTrans.getMatrix());
    altShader.setCamera("camera", *core::Data.camera);
    altShader.setBool("inside", inside);
    model->draw(altShader);
}

void Instance::update(float deltaT) {
    for(std::pair<string, Component*> component : components) {
        component.second->update(deltaT);
    }
}

void Instance::addComponent(string name, Component *component) {
    std::pair<string, Component*> pair(name, component);
    components.insert(pair);
}

Component* Instance::getComponent(std::string name) {
    for(auto pair : components) {
        Component* component = pair.second;
        if(pair.first == name) {
            return component;
        }
    }
    throw componentSearchException("Component '" + name + "' could not be found");
}