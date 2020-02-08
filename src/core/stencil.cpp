namespace stencil {
    void startTrace(int channel) {
        glDepthMask(GL_FALSE);
        glStencilFunc(GL_ALWAYS, channel, 0xFF); // Always draw
    }

    void startDraw(int channel) {
        glDepthMask(GL_TRUE);
        glStencilFunc(GL_EQUAL, channel, 0xFF); // Only draw on stencil
    }

    void startDrawInvert(int channel) {
        glDepthMask(GL_TRUE);
        glStencilFunc(GL_NOTEQUAL, channel, 0xFF); // Only draw on stencil
    }

    void enable() {
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
        glEnable(GL_STENCIL_TEST);
        glStencilMask(0xFF);
    }

    void disable() {
        glDisable(GL_STENCIL_TEST);
    }
}