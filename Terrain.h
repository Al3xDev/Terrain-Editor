/*

Author: Stoica Alexandru ( Al3xDev )
Contact al3xdev@gmail.com
License: GPL v2.0, see LICENSE file

*/


#ifndef TERRAIN_H
#define TERRAIN_H
#define PI 3.14159
struct Terrain_Header
{
    uint16_t vertices_on_x;
    uint16_t vertices_on_z;
    float distance_unit;
    uint32_t indices_nr;

};
inline float points_distance(float z1,float x1,float z2,float x2)
{
    return sqrt((z1-z2)*(z1-z2)+(x1-x2)*(x1-x2));
}
struct PointEdit
{
    GLfloat x,z;
    PointEdit& operator=(const PointEdit& pointEdit)
    {
        x=pointEdit.x;
        z=pointEdit.z;
        return *this;
    }
};

class Terrain
{
private:
    /// Data
    GLuint VBO,EBO;
    Terrain_Header terrain_header;
    std::vector<glm::vec3> vertices;
    std::vector<uint32_t> indices;
    GLuint VAO;
    void Setup()
    {
    	glGenVertexArrays(1,&VAO);
    	glGenBuffers(1,&VBO);
    	glGenBuffers(1,&EBO);
    	glBindVertexArray(VAO);
    	glBindBuffer(GL_ARRAY_BUFFER,VBO);
    	glBufferData(GL_ARRAY_BUFFER,vertices.size()*sizeof(glm::vec3),&vertices[0],GL_DYNAMIC_DRAW);
    	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    	glBufferData(GL_ELEMENT_ARRAY_BUFFER,indices.size()*4,&indices[0],GL_DYNAMIC_DRAW);
    	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(glm::vec3),(GLvoid*)0);
    	glEnableVertexAttribArray(0);
    	glBindBuffer(GL_ARRAY_BUFFER, 0);
    	glBindVertexArray(0);
    }
    void Edit(float x,float z)
    {
        float _z_stop=z+ray;
        float _x_stop=x+ray;
        for(float _z=z-ray; _z<=_z_stop; _z+=terrain_header.distance_unit)
        {
            for(float _x=x-ray; _x<=_x_stop; _x+=terrain_header.distance_unit)
            {
                 if(_x<=(terrain_header.vertices_on_x)*terrain_header.distance_unit and _x>=0 and
                    _z<=(terrain_header.vertices_on_z)*terrain_header.distance_unit and _z>=0)
                {
                        float distance=points_distance(z,x,_z,_x)/terrain_header.distance_unit;
		                if(distance<=ray)
		                {
                            if(positive_strength)
                            {
                                vertices[uint32_t(_z/terrain_header.distance_unit)*terrain_header.vertices_on_x+uint16_t(_x/terrain_header.distance_unit)].y
                                += cos(distance/ray*1.57)*strength;
                            }
                            else
                            {
                                vertices[uint32_t(_z/terrain_header.distance_unit)*terrain_header.vertices_on_x+uint16_t(_x/terrain_header.distance_unit)].y
                                -= cos(distance/ray*1.57)*strength;
                            }
                        }
                }
            }
        }
    }
    bool Inside(float x,float z)
    {
        if(x>=0 and z>=0 and (terrain_header.vertices_on_x-1)*terrain_header.distance_unit>=x
            && (terrain_header.vertices_on_z-1)*terrain_header.distance_unit>=z)
    		return true;
        return false;
    }

public:

    Terrain():
        ray(1),strength(0),positive_strength(true),alive(false),max_ray(1)
    {}
    void Load(std::string file_name)
    {
    	if(alive)
    	{
    		glDeleteVertexArrays(1,&VAO);
    		glDeleteBuffers(1,&VBO);
    		glDeleteBuffers(1,&EBO);
    		ray=1;
            strength=0;
    		positive_strength=true;
    	}
        std::fstream file_in;
        file_in.open(file_name.c_str(),std::ios::in | std::ios::binary);
        if(file_in.fail())
        {
            std::cerr<<"Error: The file "<<file_name<<" does not exist\n";
            return;
        }
        alive=true;
        /// Read file header
        file_in.read((char *)&terrain_header,sizeof(Terrain_Header));
        vertices.resize(terrain_header.vertices_on_x*terrain_header.vertices_on_z);
        indices.resize(terrain_header.indices_nr);
        /// Read vertices
        file_in.read((char*)&vertices[0],sizeof(glm::vec3)*vertices.size());
        /// Read indices
        file_in.read((char*)&indices[0],4*indices.size());
        file_in.close();
        max_ray=std::min((terrain_header.vertices_on_x-1)*terrain_header.distance_unit,
                           (terrain_header.vertices_on_z-1)*terrain_header.distance_unit)/2;
        Setup();
    }
    void Create(uint16_t vertices_on_x, uint16_t vertices_on_z, float distance_unit)
    {
    	if(alive)
    	{
    		glDeleteVertexArrays(1,&VAO);
    		glDeleteBuffers(1,&VBO);
    		glDeleteBuffers(1,&EBO);
    		ray=1;
            strength=0;
    		positive_strength=true;
    	}
    	alive=true;
        /// File header
        terrain_header.vertices_on_x=vertices_on_x;
        terrain_header.vertices_on_z=vertices_on_z;
        terrain_header.distance_unit=distance_unit;
        terrain_header.indices_nr=(vertices_on_x-1)*(vertices_on_z-1)*6;
        vertices.resize(vertices_on_x*vertices_on_z);
        indices.resize(terrain_header.indices_nr);
        /// Indices
        uint32_t index=-1;
        for(uint16_t z=0; z<vertices_on_z-1; ++z)
        {
            for(uint16_t x=0; x<vertices_on_x-1; ++x)
            {
                /// I
                indices[++index]=z*vertices_on_x+x;
                indices[++index]=z*vertices_on_x+x+1;
                indices[++index]=(z+1)*vertices_on_x+x;
                /// II
                indices[++index]=z*vertices_on_x+x+1;
                indices[++index]=(z+1)*vertices_on_x+x;
                indices[++index]=(z+1)*vertices_on_x+x+1;
            }
        }
        /// Vertices
        for(uint16_t z=0; z<vertices_on_z; ++z)
        {
            for(uint16_t x=0; x<vertices_on_x; ++x)
            {
                vertices[z*vertices_on_x+x].x=x*distance_unit;
                vertices[z*vertices_on_x+x].y=0;
                vertices[z*vertices_on_x+x].z=z*distance_unit;
            }
        }
        max_ray=std::min((terrain_header.vertices_on_x-1)*terrain_header.distance_unit,
                           (terrain_header.vertices_on_z-1)*terrain_header.distance_unit)/2;
        Setup();
    }

    PointEdit Tracing(glm::vec3 camera_pos, glm::vec3 camera_dir,bool edit)
    {
        PointEdit pointEdit;
    	if(alive)
	        if(Inside(camera_pos.x,camera_pos.z) and camera_dir.y<0)
	        {
                if(camera_pos.y>vertices[uint32_t(camera_pos.z/terrain_header.distance_unit)*terrain_header.vertices_on_x+uint32_t(camera_pos.x/terrain_header.distance_unit)].y)/// camera_pos>terrain[][].y
	       		{
                    for(;camera_pos.y>vertices[uint32_t(camera_pos.z/terrain_header.distance_unit)*terrain_header.vertices_on_x+uint32_t(camera_pos.x/terrain_header.distance_unit)].y;
                        camera_pos+=camera_dir)
                    {
                        if(!Inside(camera_pos.x+camera_dir.x,camera_pos.z+camera_dir.z))
                        {
                            pointEdit.x=-1.0;
                            pointEdit.z=-1.0;
                            return pointEdit;
                        }
                    }
                    if(Inside(camera_pos.x,camera_pos.z) && edit)
	       			{
                        Edit(camera_pos.x,camera_pos.z);
	       				glBindBuffer(GL_ARRAY_BUFFER,VBO);
	       				glBufferData(GL_ARRAY_BUFFER,vertices.size()*sizeof(glm::vec3),&vertices[0],GL_DYNAMIC_DRAW);
	       			}
	       		}
	        }
	        else
	        {
	        	std::cerr<<"Camera_pos outside or underground\n";
	        }
	    else
	    {
            std::cerr<<"Error: Tracing: void object\n";
	    }
        pointEdit.x=camera_pos.x;
        pointEdit.z=camera_pos.z;
        return pointEdit;
    }

    void Draw()
    {
    	if(alive)
    	{
    		glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, indices.size() , GL_UNSIGNED_INT, 0);
	        glBindVertexArray(0);
    	}
    	else
    	{
            std::cerr<<"Error: Draw: void object\n";
    	}
    }
    void Save(std::string file_name)
    {
    	if(alive)
    	{
	        std::fstream file_out;
            file_out.open(file_name.c_str(),std::ios::out | std::ios::binary);
	        file_out.write((char*)&terrain_header,sizeof(Terrain_Header));
	        file_out.write((char*)&vertices[0],sizeof(glm::vec3)*vertices.size());
	        file_out.write((char*)&indices[0],4*indices.size());
	        file_out.close();
    	}
    	else
    	{
            std::cerr<<"Error: Save: void object\n";
    	}
    }
    ~Terrain()
    {
    	if(alive)
    	{
    		glDeleteVertexArrays(1, &VAO);
		    glDeleteBuffers(1, &VBO);
		    glDeleteBuffers(1, &EBO);
    	}
    }
    float max_ray;
    bool alive;
    float ray;
    float strength;
    bool positive_strength;

};
#endif // TERRAIN_H

