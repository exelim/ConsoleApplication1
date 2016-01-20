                                                                                 
attribute vec3 Position;                                            
attribute vec2 TexCoord;                                             
                                                                                   
                                                                                    
varying vec2 TexCoord0;                                                                 
                                                                                    
void main()                                                                        
{                                                                                   
    gl_Position =  vec4(Position, 1.0);                                       
    TexCoord0 = TexCoord;                                                          
}