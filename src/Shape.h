#ifndef _SHAPES_H_
#define _SHAPES_H_

typedef struct {
	GLuint VAO, VBO;
	GLuint program;
} Triangle;

// NOTE(__LUNA__): Passing the count/sizeof array solved the rendering problem... C requires clarity on size of array

void create_triangle(float *vertices, size_t vertices_count, Triangle *triangle);
void create_rgb_triangle(float *vertices, size_t vertices_count, Triangle *triangle);
void render_triangle(Triangle *triangle);
void render_triangle_with_uniform(float val, Triangle *triangle);
void delete_triangle(Triangle *triangle);

typedef struct {
	GLuint VAO, VBO, EBO;
	GLuint program;
} Rectangle;

void create_rectangle(float *vertices, size_t vertices_count, GLuint *indices, size_t indices_count, Rectangle *rectangle);
void create_rgb_rectangle(float *vertices, size_t vertices_count, GLuint *indices, size_t indices_count, Rectangle *rectangle);
void render_rectangle(Rectangle *rectangle);
void render_rectangle_with_uniform(float val, Rectangle *rectangle);
void delete_rectangle(Rectangle *rectangle);

typedef struct {
	GLuint VAO, VBO, EBO;
	GLuint program;
	GLuint texture1, texture2;
	float mix;
} Textured_Rectangle;

void create_textured_rectangle(float *vertices, size_t vertices_count, GLuint *indices, size_t indices_count, Textured_Rectangle *textured_rectangle);
void set_mix(float mix, Textured_Rectangle *textured_rectangle);
void render_textured_rectangle(Textured_Rectangle *textured_rectangle);
void delete_textured_rectangle(Textured_Rectangle *textured_rectangle);

void create_textured_rectangle_3d(float *vertices, size_t vertices_count, GLuint *indices, size_t indices_count, Textured_Rectangle *textured_rectangle);
void render_textured_rectangle_3d(Textured_Rectangle *textured_rectangle);

#endif //_SHAPES_H_
