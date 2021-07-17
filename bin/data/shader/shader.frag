#version 120
uniform sampler3D tx3d_0;
uniform vec2 u_resolution;
uniform float u_time;
uniform float u_zoffset;
uniform float u_depth;

void main () {
    vec2 st = gl_FragCoord.st / u_resolution;


    

    
    // Draw normal except for delay
    float current_frame_normalized = (1.0 / u_depth)*(u_zoffset);
    //vec4 color_3d = texture3D(tx3d_0, vec3(st.x, st.y, current_frame_normalized)); 

    // ripple
    float x1 = (st.x - 0.5) * 2.0;
    float y1 = (st.y + 0.5) * 2.0;
    float z0 = sqrt(x1 * x1 +  y1 * y1) * 10.0 + 0.0078125;

    // moire
    //float x1 = gl_FragCoord.x;
    //float y1 = gl_FragCoord.y;
    //float z0 = (x1*x1 + y1*y1) * 0.0009765625 + 0.015625; // not normalized?
    //z0 = fract(z0); // tesselate

    // sine & y
    z0 = 2.0*abs(st.y - 0.5 - (sin(u_time/3.0)));
    // smoothest i could shape this scanline...
    z0 = 3.0*abs(1.0 - st.y - mod(u_time/8.0, 2.0) + 0.5);
    z0 = clamp(0.0, 1.0, z0);


    // base on y
    //z0 = st.y;
    vec4 color_3d = texture3D(tx3d_0, vec3(st.x, st.y, current_frame_normalized+ z0)); 

    gl_FragColor = color_3d;
    //gl_FragColor = vec4(vec3(z0), 1.0); // for debug

}
