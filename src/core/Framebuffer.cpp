Framebuffer::Framebuffer(int width, int height, bool cubemap, bool rw) : rw(rw), cubemap(cubemap) {
    updateSize(width, height);
}

Framebuffer::~Framebuffer() {
    glDeleteFramebuffers(1, &FBO);
    glDeleteTextures(1, &texture);
}

void Framebuffer::startWrite() {
    glViewport(0, 0, width, height);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); // NOLINT(hicpp-signed-bitwise)
}

void Framebuffer::endWrite() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, core::Data.SCR_WIDTH, core::Data.SCR_HEIGHT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); // NOLINT(hicpp-signed-bitwise)
}

void Framebuffer::updateSize(int width, int height) {
    if(width == this->width && height == this->height) return;
    this->width = width;
    this->height = height;
    glDeleteFramebuffers(1, &FBO);
    glDeleteTextures(1, &texture);

    GLenum texType;
    if(cubemap) {
        texType = GL_TEXTURE_CUBE_MAP;
    } else {
        texType = GL_TEXTURE_2D;
    }

    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);

    glGenTextures(1, &texture);
    glBindTexture(texType, texture);

    if(rw) {
        if(cubemap) {
            for (unsigned int i = 0; i < 6; ++i) {
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB,
                             width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

            }
            glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture, 0);
        } else {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                         width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
        }
        unsigned int rbo;
        glGenRenderbuffers(1, &rbo);
        glBindRenderbuffer(GL_RENDERBUFFER, rbo);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
    } else {
        if(cubemap) {
            for (unsigned int i = 0; i < 6; ++i) {
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT,
                             width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

            }
            glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture, 0);
        } else {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
                         width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture, 0);
        }
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
    }
    glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        throw framebufferException("Could not generate Framebuffer");
    }
}