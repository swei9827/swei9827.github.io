precision mediump float;
varying vec4 fColor;
varying vec2 fTexCoord;

uniform sampler2D sampler2d;
uniform float Factor1;
uniform float specL1;
uniform float specR;
uniform vec2 u_resolution;

const float dots = 60.; //number of lights
const float radius = .35; //radius of light ring
const float brightness = 0.02;

vec3 hsv2rgb(vec3 c){
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

void main()                           
{
	vec2 p=(gl_FragCoord.xy-.5*u_resolution.xy)/min(u_resolution.x,u_resolution.y);
	vec3 final_color = vec3(1.0);
	vec3 c = vec3(0.0,0.0,0.1);
	vec3 bg_color = vec3(0.0);
	vec3 wave_color = vec3(0.0);
	                   
	/*float r = abs(cos(gl_FragCoord.x*0.05));
	float g = abs(cos(gl_FragCoord.y*0.05));
	float b = abs(sin(gl_FragCoord.x * gl_FragCoord.y));*/
                                   
	//gl_FragColor = vec4 ( r, g, 0, 1.0 );

	float r = cos(gl_FragCoord.x*0.02+4.0)*0.5+0.5;
	float g = cos(gl_FragCoord.x*0.02+2.0)*0.5+0.5;
	float b = cos(gl_FragCoord.x*0.02+0.0)*0.5+0.5;
	
	vec3 ringCol= vec3(r,g,b);
	//sin wave
	vec2 uv = gl_FragCoord.xy/u_resolution.xy;
	float wave_width = 0.01;
	uv = 20.0*uv;
	uv.y += -10.1;
	uv.y += (specR*4.0 * sin(uv.x + 9.0/7.0 + Factor1*5.0 ));
	wave_width = abs(10.5 / (300.0 * uv.y));
	wave_color += vec3(wave_width * 3.9, wave_width, wave_width * 1.5);
	final_color = bg_color + wave_color;	
	gl_FragColor = vec4(final_color,1.0);
	
	vec4 texColor = texture2D(sampler2d,fTexCoord);
	vec3 dotCol = vec3(0.0);
	for(float i=0.;i<dots; i++)
	{
		float vol =  texture2D(sampler2d, vec2(i/dots, 0.0)).x;
		float b = vol * brightness;
		
		//get location of dot
        	float x = radius*cos(2.*3.14*float(i)/dots);
        	float y = radius*sin(2.*3.14*float(i)/dots);
        	vec2 o = vec2(x,y);
	    
		//get color of dot based on its index in the 
		//circle + time to rotate colors
		dotCol = hsv2rgb(vec3((i + Factor1*10.)/dots,1.,1.0));
	    
        //get brightness of this pixel based on distance to dot
		c += b/(length(p-o))*dotCol*2.0*specL1;
    }
	
	gl_FragColor = texColor + vec4(final_color+c,1.0);
	float radius1 = 220.0+50.0*specR;
	float radius2 = 215.0+50.0*specR;
	float distance1 = sqrt(pow(gl_FragCoord.x - u_resolution.x/2.0,2.0) + pow(gl_FragCoord.y - u_resolution.y/2.0,2.0));
	if(distance1 < radius1 && distance1 > radius2)
	{	
		gl_FragColor =  vec4(dotCol,1.0);
	}
}