#version 120
uniform sampler3D tx3d_0;
uniform vec2 u_resolution;
uniform float u_time;

void main () {
    vec2 st = gl_FragCoord.st / u_resolution;

    st.y = 1.0 - st.y;

    float x1 = (gl_FragCoord.x - 0.5) * 2.0;
    float y1 = (gl_FragCoord.y - 0.5) * 2.0;
    float z0 = (x1*x1 + y1*y1) * 0.0009765625 + 0.015625;
    

    vec4 color_3d = texture3D(tx3d_0, vec3(st.x, st.y, z0)); 

    gl_FragColor = color_3d;
    //gl_FragColor = vec4(vec3(st.y), 1.0);
}
