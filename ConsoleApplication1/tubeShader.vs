#version 330                                                                       
                                                                                  
layout (location = 0) in vec3 Position;                                            
layout (location = 1) in vec2 TexCoord;
uniform float u_time;                                             
                                                                                   
                                                                                    
out vec2 TexCoord0;                                                                 
                                                                                    
void main()                                                                        
{                                                              
    gl_Position =  vec4(vec3(Position.x - u_time, Position.y, Position.z), 1.0);                                       
    TexCoord0 = TexCoord;                                                          
}