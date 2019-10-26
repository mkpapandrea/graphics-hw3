#define _USE_MATH_DEFINES
#include "Predator.hh"

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

extern vector <Flocker *> flocker_array;   
vector <Predator*> predator_array; 
int predator_history_length = 30;
int predator_draw_mode= DRAW_MODE_POLY_PREDATOR;
extern glm::mat4 ViewMat;
extern glm::mat4 ProjectionMat;
extern int num_flockers;

extern GLuint ModelMatrixID;
extern GLuint ViewMatrixID;
extern GLuint MatrixID;
glm::vec3 hunger_force;


//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

Predator::Predator(int _index,
		 double init_x, double init_y, double init_z,
		 double init_vx, double init_vy, double init_vz,
		 double rand_force_limit, 
		 double min_hung_distance, double max_hung_distance, double hung_weight,
		 float r, float g, float b,
		 int max_hist) : Creature(_index, init_x, init_y, init_z, init_vx, init_vy, init_vz, r, g, b, max_hist)
{ 
	
	


}

//----------------------------------------------------------------------------

void Predator::draw(glm::mat4 Model)
{


	int draw_mode, num_vertices;

	GLfloat* vertex_data;
	GLfloat* color_data;


		num_vertices = 12;
		draw_mode = GL_TRIANGLES;

		vertex_data = (GLfloat*)malloc(3 * num_vertices * sizeof(GLfloat));
		color_data = (GLfloat*)malloc(3 * num_vertices * sizeof(GLfloat));

		double width = 0.4f;
		double height = 0.4f;
		double length = 0.7f;

		// horizontal

		vertex_data[0] = position.x - 0.5f * width * frame_x.x;
		vertex_data[1] = position.y - 0.5f * width * frame_x.y;
		vertex_data[2] = position.z - 0.5f * width * frame_x.z;

		vertex_data[3] = position.x - 0.8f * length * frame_z.x;
		vertex_data[4] = position.y - 0.8f * length * frame_z.y;
		vertex_data[5] = position.z - 0.8f * length * frame_z.z;

		vertex_data[6] = position.x + 0.2f * length * frame_z.x;
		vertex_data[7] = position.y + 0.2f * length * frame_z.y;
		vertex_data[8] = position.z + 0.2f * length * frame_z.z;


		vertex_data[9] = position.x + 0.5f * width * frame_x.x;
		vertex_data[10] = position.y + 0.5f * width * frame_x.y;
		vertex_data[11] = position.z + 0.5f * width * frame_x.z;

		vertex_data[12] = position.x + 0.2f * length * frame_z.x;
		vertex_data[13] = position.y + 0.2f * length * frame_z.y;
		vertex_data[14] = position.z + 0.2f * length * frame_z.z;

		vertex_data[15] = position.x - 0.8f * length * frame_z.x;
		vertex_data[16] = position.y - 0.8f * length * frame_z.y;
		vertex_data[17] = position.z - 0.8f * length * frame_z.z;
		// vertical

		vertex_data[18] = position.x + 0.5f * height * frame_y.x;
		vertex_data[19] = position.y + 0.5f * height * frame_y.y;
		vertex_data[20] = position.z + 0.5f * height * frame_y.z;

		vertex_data[21] = position.x - 0.8f * length * frame_z.x;
		vertex_data[22] = position.y - 0.8f * length * frame_z.y;
		vertex_data[23] = position.z - 0.8f * length * frame_z.z;

		vertex_data[24] = position.x + 0.2f * length * frame_z.x;
		vertex_data[25] = position.y + 0.2f * length * frame_z.y;
		vertex_data[26] = position.z + 0.2f * length * frame_z.z;


		vertex_data[27] = position.x - 0.5f * height * frame_y.x;
		vertex_data[28] = position.y - 0.5f * height * frame_y.y;
		vertex_data[29] = position.z - 0.5f * height * frame_y.z;

		vertex_data[30] = position.x + 0.2f * length * frame_z.x;
		vertex_data[31] = position.y + 0.2f * length * frame_z.y;
		vertex_data[32] = position.z + 0.2f * length * frame_z.z;

		vertex_data[33] = position.x - 0.8f * length * frame_z.x;
		vertex_data[34] = position.y - 0.8f * length * frame_z.y;
		vertex_data[35] = position.z - 0.8f * length * frame_z.z;

		// color

		int i;

		for (i = 0; i < 6; i++) {
			color_data[3 * i] = 0.0f;
			color_data[3 * i + 1] = 1.0f;
			color_data[3 * i + 2] = 1.0f;
		}

		for (i = 6; i < 9; i++) {
			color_data[3 * i] = 0.5f;
			color_data[3 * i + 1] = 0.0f;
			color_data[3 * i + 2] = 1.0f;
		}

		for (i = 9; i < 12; i++) {
			color_data[3 * i] = 0.9f;
			color_data[3 * i + 1] = 1.0f;
			color_data[3 * i + 2] = 0.8f;
		}
	

	// Our ModelViewProjection : multiplication of our 3 matrices

	glm::mat4 MVP = ProjectionMat * ViewMat * Model;

	// make this transform available to shaders  

	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

	// 1st attribute buffer : vertices

	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, 3 * num_vertices * sizeof(GLfloat), vertex_data, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(0,                  // attribute. 0 to match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// 2nd attribute buffer : colors

	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, 3 * num_vertices * sizeof(GLfloat), color_data, GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glVertexAttribPointer(1,                                // attribute. 1 to match the layout in the shader.
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// Draw the flocker!

	glDrawArrays(draw_mode, 0, num_vertices);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	free(vertex_data);
	free(color_data);
}







//----------------------------------------------------------------------------

void Predator::update()
{

//hunger force calulaotions

hunger_force=glm::vec3(0,0,0);
double F;
glm::vec3 diff;


for(int i=0; i<num_flockers-1; i++){
	diff= position-flocker_array[i]->position;
	F=.5/ glm::length2(diff) -1;
	hunger_force+= (float) F *glm::normalize(position -flocker_array[i]->position);
}






	// set accelerations (aka forces)

	//acceleration = glm::vec3(0, 0, 0);

	// deterministic behaviors

	float percentthing= .90;
	float hungerpercent=.10;
	acceleration = (percentthing*acceleration)+(hungerpercent*hunger_force);

	draw_color.r = glm::length(hunger_force);
	if (draw_color.r > 0) {
		draw_color = glm::normalize(draw_color);
	}
	else {
		draw_color = base_color;
	}


	// update velocity

	new_velocity = velocity + acceleration;   

	// limit velocity

	double mag = glm::length(new_velocity);
	if (mag > MAX_FLOCKER_SPEED)
		new_velocity *= (float)(MAX_FLOCKER_SPEED / mag);

	// update position

	new_position = position + new_velocity;   // scale new_velocity by dt?
}

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------