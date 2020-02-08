#pragma once

namespace core {
    bool shouldClose() {
        return glfwWindowShouldClose(Data.window);
    }

    void close() {
        glfwTerminate();
    }
}
