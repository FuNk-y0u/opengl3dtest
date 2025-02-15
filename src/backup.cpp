//#include<stdio.h>
//#include<stdlib.h>
//
//#include<GL/glew.h>
//
//#include<SDL2/SDL.h>
//#include<SDL2/SDL_opengl.h>
//
//#include<stb_image/stb_image.h>
//#include<Math/math.h>
//
//#define glc(x)\
//        (\
//                gl_clear_error(), \
//                x\
//        );\
//        gl_get_error(#x, __FILE__, __LINE__);\
//
//void gl_clear_error()
//{
//	while (glGetError() != GL_NO_ERROR) {
//	}
//}
//
//int gl_get_error(const char* function, const char* file, int line) {
//	GLenum error = glGetError();
//	while (error) {
//		printf("OPENGL ERR CODE: %x\n", error);
//		printf("OPENGL ERR: %s\n", gluErrorString(error));
//		printf("OPENGL ERR: %s %s %d\n", function, file, line);
//		return 0;
//	}
//}
//
//int main(void) {
//	SDL_Init(SDL_INIT_EVERYTHING);
//
//	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
//	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
//	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
//
//	SDL_Window* window = SDL_CreateWindow(
//		"Arsenic",
//		SDL_WINDOWPOS_CENTERED,
//		SDL_WINDOWPOS_CENTERED,
//		800,
//		600,
//		SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_OPENGL
//	);
//
//	if (window == NULL) {
//		printf("Unable to create sdl window.\n");
//	}
//
//	SDL_GLContext glContext = SDL_GL_CreateContext(window);
//	SDL_GL_SetSwapInterval(1);
//
//	if (glewInit() != GLEW_OK) {
//		printf("Unable to initialize glew\n");
//	}
//
//	int running = 1;
//
//	SDL_Event window_event;
//
//	float positions[] = {
//		0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
//		100.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
//		100.0f, 100.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f,
//		0.0f, 100.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
//
//		150.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
//		250.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
//		250.0f, 100.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
//		150.0f, 100.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
//	};
//
//	unsigned int indexs[] = {
//		0,1,2,
//		2,3,0,
//
//		4,5,6,
//		6,7,4
//	};
//
//	const char* vertex_shader =
//		"#version 330 core\n"
//		"layout(location = 0) in vec4 position;\n" // taking data in from vertex buffer and attribute 0
//		"uniform mat4 mvp;\n"
//		"layout(location = 1) in vec4 vert_color;\n"
//		"layout(location = 2) in vec2 tex_cord;\n"
//		"layout(location = 3) in float tex_id;\n"
//
//		"out vec4 v_vert_color;\n"
//		"out vec2 v_tex_cord;\n"
//		"out float v_tex_id;\n"
//
//		"void main(){\n"
//		"	gl_Position = mvp * position;\n"
//		"	v_vert_color = vert_color;\n"
//		"	v_tex_cord = tex_cord;\n"
//		"	v_tex_id = tex_id;\n"
//		"}\n";
//
//
//	const char* fragment_shader =
//		"#version 330 core\n"
//		"layout(location = 0) out vec4 color;\n" // Putting data out from fragment shader to color buffer
//		"uniform sampler2D u_textures[2];\n" // The texture data that we sent!
//		"in vec4 v_vert_color;\n" // The texture co-ordinate from vb
//		"in float v_tex_id;\n"
//		"in vec2 v_tex_cord;\n"
//
//		"void main(){\n"
//		"	int index = int(v_tex_id);\n"
//		"	vec4 tex_color;\n"
//		"	switch(index){\n"
//		"		case 0:\n"
//		"			tex_color = texture(u_textures[0], v_tex_cord);\n"
//		"			break;\n"
//		"		case 1:\n"
//		"			tex_color = texture(u_textures[1], v_tex_cord);\n"
//		"			break;\n"
//		"	}\n"
//		"	color = tex_color;\n"
//		//		"	color = v_vert_color;\n"
//		"}\n";
//
//	// Camera position
//	vec2 camera_pos = {
//		0,
//		0
//	};
//
//	// Normalized camera pos
//	vec2 gl_camera_pos;
//
//	// creating projection matrix
//	mat4 projection = orthro_projection(0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);
//
//	glc(glEnable(GL_BLEND));
//	glc(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
//
//	unsigned int vert_arr_obj;
//	glc(glGenVertexArrays(1, &vert_arr_obj));
//	glc(glBindVertexArray(vert_arr_obj));
//
//	unsigned int vertex_buffer;
//	glc(glGenBuffers(1, &vertex_buffer));
//	glc(glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer));
//	glc(glBufferData(GL_ARRAY_BUFFER, 9 * 4 * 2 * sizeof(GL_FLOAT), positions, GL_STATIC_DRAW));
//
//	glc(glEnableVertexAttribArray(0));
//	glc(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(GL_FLOAT), 0));
//
//	glc(glEnableVertexAttribArray(1));
//	glc(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(GL_FLOAT), (const void*)(2 * sizeof(GL_FLOAT))));
//
//	glc(glEnableVertexAttribArray(2));
//	glc(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(GL_FLOAT), (const void*)(6 * sizeof(GL_FLOAT))));
//
//	glc(glEnableVertexAttribArray(3));
//	glc(glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 9 * sizeof(GL_FLOAT), (const void*)(8 * sizeof(GL_FLOAT))));
//
//	unsigned int program = glc(glCreateProgram());
//
//	unsigned int vert_id = glc(glCreateShader(GL_VERTEX_SHADER));
//	glc(glShaderSource(vert_id, 1, &vertex_shader, NULL));
//	glc(glCompileShader(vert_id));
//
//	int result, length;
//	glc(glGetShaderiv(vert_id, GL_COMPILE_STATUS, &result));
//
//	unsigned int index_buffer;
//	glc(glGenBuffers(1, &index_buffer));
//	glc(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer));
//	glc(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 2 * 6 * sizeof(unsigned int), indexs, GL_STATIC_DRAW));
//
//
//	if (result == GL_FALSE) {
//		glc(glGetShaderiv(vert_id, GL_INFO_LOG_LENGTH, &length));
//		char* message_vert = (char*)alloca(length * sizeof(char));
//		glc(glGetShaderInfoLog(vert_id, length, &length, message_vert));
//
//		printf("Failed to compile vert shader.\n");
//		printf("%s\n", message_vert);
//		free(message_vert);
//		glc(glDeleteShader(vert_id));
//		return 0;
//	}
//
//	unsigned int frag_id = glc(glCreateShader(GL_FRAGMENT_SHADER));
//	glc(glShaderSource(frag_id, 1, &fragment_shader, NULL));
//	glc(glCompileShader(frag_id));
//
//	glc(glGetShaderiv(frag_id, GL_COMPILE_STATUS, &result));
//
//	if (result == GL_FALSE) {
//		glc(glGetShaderiv(vert_id, GL_INFO_LOG_LENGTH, &length));
//		char* message_frag = (char*)alloca(length * sizeof(char));
//		glc(glGetShaderInfoLog(vert_id, length, &length, message_frag));
//
//		printf("Failed to compile frag shader.\n");
//		printf("%s\n", message_frag);
//		free(message_frag);
//		glc(glDeleteShader(frag_id));
//		return 0;
//	}
//
//
//	glc(glAttachShader(program, vert_id));
//	glc(glAttachShader(program, frag_id));
//	glc(glLinkProgram(program));
//	glc(glValidateProgram(program));
//
//	glc(glDeleteShader(vert_id));
//	glc(glDeleteShader(frag_id));
//
//	glc(glUseProgram(program));
//
//	// Texture stuff
//
//	// reading image
//	int texture_width;
//	int texture_height;
//
//	int texture_width2;
//	int texture_height2;
//
//	int channels;
//	int channels2;
//
//	stbi_set_flip_vertically_on_load(1); // flipping texture cus opengl kinda stubborn
//
//	unsigned char* texture_data = stbi_load("assets/error.png", &texture_width, &texture_height, &channels, 4); // loading and writing data
//	unsigned char* texture_data2 = stbi_load("assets/block.jpg", &texture_width2, &texture_height2, &channels2, 4); // loading and writing data
//
//	unsigned int texture_buffer;
//	unsigned int texture_buffer2;
//
//	glc(glGenTextures(1, &texture_buffer));
//
//
//	glc(glBindTexture(GL_TEXTURE_2D, texture_buffer));
//
//	// Setting behaviours
//	glc(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
//	glc(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
//	glc(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
//	glc(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
//
//	// Setting attributes and data to gpu
//	glc(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, texture_width, texture_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_data));
//
//	glc(glGenTextures(1, &texture_buffer2));
//	glc(glBindTexture(GL_TEXTURE_2D, texture_buffer2));
//
//	// Setting behaviours 2
//	glc(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
//	glc(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
//	glc(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
//	glc(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
//
//	// Setting attributes and data to gpu
//	glc(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, texture_width2, texture_height2, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_data2));
//
//	glc(glBindTexture(GL_TEXTURE_2D, 0));
//
//	if (texture_buffer) {
//		stbi_image_free(texture_data);
//	}
//
//	if (texture_buffer2) {
//		stbi_image_free(texture_data2);
//	}
//
//	glc(glBindTextureUnit(0, texture_buffer));
//	glc(glBindTextureUnit(1, texture_buffer2));
//
//	int uniform_location_tex = glc(glGetUniformLocation(program, "u_textures"));
//	if (uniform_location_tex == -1) {
//		printf("UNIFORM ERROR: Uniform doesnot exists!");
//	}
//
//	int samplers[2] = { 0 , 1 };
//	glc(glUniform1iv(uniform_location_tex, 2, &samplers[0])); // sending texture coords to shader
//	int uniform_location_mvp = glc(glGetUniformLocation(program, "mvp"));
//	if (uniform_location_mvp == -1) {
//		printf("UNIFORM ERROR: Uniform doesnot exists!");
//	}
//
//
//	// un binding everything
//	glc(glBindVertexArray(0)); // unbinding vertex array
//	glc(glUseProgram(0)); // unbinding shaders
//	glc(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0)); // unbinding ib
//	glc(glBindBuffer(GL_ARRAY_BUFFER, 0)); // unbinding vb
//
//	float fudge_factor = 10.0f;
//
//	while (running == 1) {
//		if (SDL_PollEvent(&window_event)) {
//			if (SDL_QUIT == window_event.type) {
//				running = 0;
//			}
//		}
//		glc(glClear(GL_COLOR_BUFFER_BIT));
//
//		gl_camera_pos = pixel_to_gl_coords(camera_pos, 800, 600);
//		mat4 transform = mat4_translate(
//			mat4_identity(),
//			(vec3) {
//			gl_camera_pos.x,
//				gl_camera_pos.y,
//				0
//		}
//		);
//		mat4 transpose = mat4_transpose(transform);
//		mat4 view_mat = mat4_inverse(transpose);
//		mat4 mvp = mat4_transpose(mat4_mul(projection, view_mat));
//		// binding vertex array object and shader and texture
//		glc(glBindVertexArray(vert_arr_obj));
//		glc(glUseProgram(program));
//		glc(glUniformMatrix4fv(uniform_location_mvp, 1, GL_TRUE, &mvp.m[0][0]));
//
//
//		glc(glActiveTexture(GL_TEXTURE0)); // Enabling texture slot 0
//		glc(glBindTexture(GL_TEXTURE_2D, texture_buffer)); // Binding data to texture slot 0
//
//		// draw call
//		glc(glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, NULL));
//
//		SDL_GL_SwapWindow(window);
//	}
//	glc(glDeleteTextures(1, &texture_buffer));
//	return 0;
//}