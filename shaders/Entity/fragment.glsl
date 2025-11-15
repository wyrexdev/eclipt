#version 450 core
uniform vec4 backgroundColor;

out vec4 FragColor;
void main() {
    FragColor = backgroundColor;
}