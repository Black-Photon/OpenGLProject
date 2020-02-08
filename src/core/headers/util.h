#pragma once

namespace core {
    /**
     * Checks if the window has received a close signal
     * @return True if the window should close
     */
    bool shouldClose();

    /**
     * Closes the program by deleting any references
     */
    void close();
}
