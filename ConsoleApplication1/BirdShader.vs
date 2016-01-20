                                                                                  
attribute vec3 Position;                                            
attribute vec2 TexCoord;
uniform float u_time;                                             
                                                                                   
                                                                                    
varying vec2 TexCoord0;                                                                 
                                                                                    
void main()                                                                        
{                                                              
    gl_Position =  vec4(vec3(Position.x, Position.y - u_time, Position.z), 1.0);                                       
    TexCoord0 = TexCoord;                                                          
}