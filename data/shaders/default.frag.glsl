#version 120

//uniform vec3 uniColor;
varying vec3 fragColor;
void main()
{
//	gl_FragColor = vec4(uniColor, 1.0);
	gl_FragColor = vec4(fragColor, 1.0);
}

