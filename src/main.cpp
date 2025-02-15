#include "engine/engine.h"

bool forward = false;
bool back = false;
bool left = false;
bool right = false;

glm::vec2 prev_mos = {0.0f, 0.0f};
glm::vec2 rel_mos = { 0.0f, 0.0f };
double mousx, mousy;
bool init_mouse = false;

void movement_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		forward = true;
	}

	if (key == GLFW_KEY_W && action == GLFW_RELEASE) {
		forward = false;
	}

	if (key == GLFW_KEY_S && action == GLFW_PRESS) {
		back = true;
	}

	if (key == GLFW_KEY_S && action == GLFW_RELEASE) {
		back = false;
	}

	if (key == GLFW_KEY_A && action == GLFW_PRESS) {
		left = true;
	}

	if (key == GLFW_KEY_A && action == GLFW_RELEASE) {
		left = false;
	}

	if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		right = true;
	}

	if (key == GLFW_KEY_D && action == GLFW_RELEASE) {
		right = false;
	}
}

int main(void)
{
    Window root = Window(1280, 720, "Hello world");

	// Format: {x, y, z, r, g, b, a, tx, ty}
	float positions[] = {
		// Front Face (Red)
		-0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,1.0f,  0.0f, 0.0f, 0.0f,  // Bottom-left
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,1.0f,  1.0f, 0.0f, 0.0f, // Bottom-right
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,1.0f,  1.0f, 1.0f, 0.0f, // Top-right
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,1.0f,  0.0f, 1.0f, 0.0f, // Top-left

		// Back Face (Green)
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,1.0f,  0.0f, 0.0f,  0.0f,// Bottom-left
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,1.0f,  1.0f, 0.0f, 0.0f, // Bottom-right
		 0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,1.0f,  1.0f, 1.0f,  0.0f,// Top-right
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,1.0f,  0.0f, 1.0f,  0.0f,// Top-left

		// Left Face (Blue)
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,1.0f,  0.0f, 0.0f, 0.0f, // Bottom-left
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,1.0f,  1.0f, 0.0f,  0.0f,// Bottom-right
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,1.0f,  1.0f, 1.0f,  0.0f,// Top-right
		-0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,1.0f,  0.0f, 1.0f,  0.0f,// Top-left

		// Right Face (Yellow)
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,1.0f,  0.0f, 0.0f,0.0f,  // Bottom-left
		 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,1.0f,  1.0f, 0.0f,0.0f,  // Bottom-right
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,1.0f,  1.0f, 1.0f, 0.0f, // Top-right
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,1.0f,  0.0f, 1.0f, 0.0f, // Top-left

		 // Top Face (Magenta)
		 -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f,1.0f,  0.0f, 0.0f,0.0f,  // Bottom-left
		  0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f,1.0f,  1.0f, 0.0f,0.0f,  // Bottom-right
		  0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,1.0f,  1.0f, 1.0f, 0.0f, // Top-right
		 -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,1.0f,  0.0f, 1.0f, 0.0f, // Top-left

		 // Bottom Face (Cyan)
		 -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,1.0f,  0.0f, 0.0f,0.0f,  // Bottom-left
		  0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,1.0f,  1.0f, 0.0f,0.0f,  // Bottom-right
		  0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,1.0f,  1.0f, 1.0f,0.0f,  // Top-right
		 -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,1.0f,  0.0f, 1.0f, 0.0f,  // Top-left

		  -5.0f, -0.5f, -5.0f,  0.5f, 0.5f, 0.5f, 1.0f,  0.0f, 0.0f, 1.0f,  // Bottom-left
		5.0f, -0.5f, -5.0f,  0.5f, 0.5f, 0.5f, 1.0f,  1.0f, 0.0f, 1.0f, // Bottom-right
		5.0f, -0.5f,  5.0f,  0.5f, 0.5f, 0.5f, 1.0f,  1.0f, 1.0f, 1.0f,  // Top-right
		-5.0f, -0.5f,  5.0f,  0.5f, 0.5f, 0.5f, 1.0f,  0.0f, 1.0f, 1.0f  // Top-left
	};
	// Indices for the cube
	unsigned int indexs[] = {
		// Front face
		0, 1, 2,  // First triangle
		0, 2, 3,  // Second triangle

		// Back face
		4, 5, 6,  // First triangle
		4, 6, 7,  // Second triangle

		// Left face
		8, 9, 10, // First triangle
		8, 10, 11, // Second triangle

		// Right face
		12, 13, 14, // First triangle
		12, 14, 15, // Second triangle

		// Top face
		16, 17, 18, // First triangle
		16, 18, 19, // Second triangle

		// Bottom face
		20, 21, 22, // First triangle
		20, 22, 23,  // Second triangle
		// Ground Plane
	24, 25, 26, // First triangle
	24, 26, 27  // Second triangle

	};

	const char* vertex_shader =
		"#version 330 core\n"
		"layout(location = 0) in vec3 position;\n" // taking data in from vertex buffer and attribute 0
		"uniform mat4 mvp;\n"
		"uniform mat4 trans;\n"
		"uniform mat4 cam;\n"
		"layout(location = 1) in vec4 vert_color;\n"
		"layout(location = 2) in vec2 tex_cord;\n"
		"layout(location = 3) in float tex_id;\n"

		"out vec4 v_vert_color;\n"
		"out vec2 v_tex_cord;\n"
		"out float v_tex_id;\n"
		
		"void main(){\n"
		"	gl_Position = mvp * cam * trans * vec4(position, 1.0f);\n"
		"	v_vert_color = vert_color;\n"
		"	v_tex_cord = tex_cord;\n"
		"	v_tex_id = tex_id;\n"
		"}\n";

	const char* fragment_shader =
		"#version 330 core\n"
		"layout(location = 0) out vec4 color;\n" // Putting data out from fragment shader to color 
		"in vec4 v_vert_color;\n" // The texture co-ordinate 
		"in vec2 v_tex_cord;\n"
		"in float v_tex_id;\n"
		"uniform sampler2D u_textures[2];\n" // The texture data that we sent!
		"vec4 tex_color;\n"
		"void main(){\n"
		"	if(v_tex_id == 0.0f){ tex_color = texture(u_textures[0], v_tex_cord);}\n"
		"	else{tex_color = texture(u_textures[1], v_tex_cord);}\n"
		"	color = tex_color;\n"
		"}\n";

	glc(glEnable(GL_DEPTH_TEST));

	VertexArrayObject vao = VertexArrayObject();
	vao.bind();

    VertexBuffer vb = VertexBuffer(&positions, 10 * 4 * 7 * sizeof(GL_FLOAT), false);
	vb.bind();

	VertexAttribLayout val = VertexAttribLayout();
	val.push(0, 3, GL_FLOAT); // Position
	val.push(1, 4, GL_FLOAT); // Color
	val.push(2, 2, GL_FLOAT); // Tex-coord
	val.push(3, 1, GL_FLOAT); // TEX-TYPE
	
	val.bind();

	IndexBuffer ib = IndexBuffer(&indexs, 6 * 7 * sizeof(unsigned int), false);
	ib.bind();

	Shader shdr = Shader(vertex_shader, fragment_shader);
	shdr.bind();

	Texture dirt_text = Texture("error.png");
	Texture error_tex = Texture("grass.jpg");

	dirt_text.bind(0);
	error_tex.bind(1);
	
	int samplers[2] = { 0 , 1 };

	glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f));
	glm::mat4 proj = glm::perspective(glm::radians(45.0f), ((float)root.width/(float)root.height), 0.1f, 100.0f);
	
	glm::vec3 cam_pos = { 0.0f, 0.0f, 0.0f};
	glm::vec3 view_dir = {0.0f , 0.0f, -1.0f};
	glm::vec3 up_vec = {0.0f, 1.0f, 0.0f};
	glm::vec3 hor_vec = { 1.0f, 0.0f, 0.0f };
	

	shdr.uniformmat4f("mvp", proj, 1);
	shdr.uniform1iv("u_textures", &samplers[0], 2);
	glfwSetInputMode(root.glfw_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	vao.unbind();
	vb.unbind();
	shdr.unbind();
	ib.unbind();

	vao.bind();
	shdr.bind();
	float degress = 0.0f;
	while (!root.closed){
		clear_color_buffer();

		glfwSetKeyCallback(root.glfw_window, movement_callback);
		glfwGetCursorPos(root.glfw_window, &mousx, &mousy);

		
		if (!init_mouse) {
			prev_mos = {mousx, mousy};
			init_mouse = true;
		}
		rel_mos = { prev_mos.x - mousx, prev_mos.y - mousy };
		prev_mos = { mousx, mousy };

		glm::mat4 cam_proj = glm::lookAt(cam_pos, cam_pos + view_dir, up_vec);
		glm::mat4 rotat = glm::rotate(trans, glm::radians(0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
		glm::vec3 lrv = glm::cross(view_dir, up_vec);
		view_dir = glm::rotate(view_dir, glm::radians(rel_mos.y * 0.4f), lrv);
		view_dir = glm::rotate(view_dir, glm::radians(rel_mos.x * 0.4f), up_vec);
		std::cout << view_dir.x << " " << view_dir.y << " " << view_dir.z << std::endl;


		shdr.uniformmat4f("cam", cam_proj, 1);
		shdr.uniformmat4f("trans", rotat, 1);
		
		if (forward) {
			cam_pos += view_dir * 0.004f;
		}
		else if (back) {
			cam_pos -= view_dir * 0.004f;
		}

		if (left) {
			cam_pos -= glm::cross(view_dir, up_vec) * 0.004f;
		}
		
		if (right) {
			cam_pos += glm::cross(view_dir, up_vec) * 0.004f;
		}
		drawcall(12 * 6);
		root.swap();
	}
	exit(0);
}