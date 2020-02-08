/**
 * Methods used from frame to frame
 */

namespace core {

    /**
    * Polls and processes any user input
    * @param deltaT Time since last frame
    */
    void processInput(float deltaT);
    /**
     * Pre-renders the screen creating the background and clearing the colour buffer
     * @param r Red
     * @param g Green
     * @param b Blue
     */
    void prerender(float r, float g, float b);
    /**
     * Builds the model and transforms to the view space
     * Sets 'view' and 'projection' mat4's in Shader
     * @param shader Shader to transform
     * @param camera Camera to build from the perspective of
     */
    void makeModel(const Shader &shader, const Camera &camera);
}