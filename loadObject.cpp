#include "game.h"

#include <fstream>
#include <sstream>

void game::load_obj(const char* filename, vector<glm::vec4> &vertices, vector<glm::vec3> &normals, vector<GLushort> &elements) {
  ifstream in(filename, ios::in);
  if (!in) { cerr << "Cannot open " << filename << endl; exit(1); }
 
  string line;
  while (getline(in, line)) {
    if (line.substr(0,2) == "v ") {
      istringstream s(line.substr(2));
      glm::vec4 v; s >> v.x; s >> v.y; s >> v.z; v.w = 1.0f;
      vertices.push_back(v);
    }  else if (line.substr(0,2) == "f ") {
      istringstream s(line.substr(2));
      GLushort a,b,c;
      s >> a; s >> b; s >> c;
      a--; b--; c--;
      elements.push_back(a); elements.push_back(b); elements.push_back(c);
    }
    else if (line[0] == '#') { /* ignoring this line */ }
    else { /* ignoring this line */ }
  }
 
  normals.resize(vertices.size(), glm::vec3(0.0, 0.0, 0.0));
  for (int i = 0; i < elements.size(); i+=3) {
    GLushort ia = elements[i];
    GLushort ib = elements[i+1];
    GLushort ic = elements[i+2];
    glm::vec3 normal = glm::normalize(glm::cross(
      glm::vec3(vertices[ib]) - glm::vec3(vertices[ia]),
      glm::vec3(vertices[ic]) - glm::vec3(vertices[ia])));
    normals[ia] = normals[ib] = normals[ic] = normal;
  }
}

void game::loadOBJ(const char* filename, vector<glm::vec3> &vertices,vector<glm::vec3> &NVs,vector<GLuint> &elements)
{
	std::ifstream file(filename,std::ios::in);
	std::string line;
	
	while(!file.eof()){
	
		std::getline(file,line);
		stringstream ss (line);

		std::string header;
		ss>>header;	
		if(header == "v")
		{
			glm::vec3 tmp;
			ss>>tmp.x>>tmp.y>>tmp.z;
			vertices.push_back(tmp);
		}

		if(header == "vn")
		{
			glm::vec3 tmp;
			ss>>tmp.x>>tmp.y>>tmp.z;
			NVs.push_back(tmp);
		}

		if(header == "f")
		{
			GLuint tmp;
			for(int i = 0; i<3 ; i++)
			{
				string t;
				ss>>t;
				stringstream st(t);
				st>>tmp;
				elements.push_back(tmp-1);
			}
		}
	}
}

void game::loadOBJ2(const char* filename, vector<glm::vec3> &vertices,vector<glm::vec3> &NVs,vector<glm::vec2> &UVs,vector<GLuint> &elements)
{
	std::ifstream file(filename,std::ios::in);
	std::string line;
	
	vector<glm::vec2> tmp_uvs;
	while(!file.eof()){
	
		std::getline(file,line);
		stringstream ss (line);

		std::string header;
		ss>>header;	
		if(header == "v")
		{
			glm::vec3 tmp;
			ss>>tmp.x>>tmp.y>>tmp.z;
			vertices.push_back(tmp);
		}

		if(header == "vn")
		{
			glm::vec3 tmp;
			ss>>tmp.x>>tmp.y>>tmp.z;
			NVs.push_back(tmp);
		}

		if(header == "vt")
		{
			glm::vec2 tmp;
			ss>>tmp.x>>tmp.y;
			tmp_uvs.push_back(tmp);
		}

		if(header == "f")
		{
			GLuint tmp;
			GLuint uv;
			for(int i = 0; i<3 ; i++)
			{
				string t;
				ss>>t;
				stringstream st(t);
				st>>tmp;
				elements.push_back(tmp-1);

				st.ignore(1,' ');
				st>>uv;
				UVs.push_back(tmp_uvs[uv-1]);
			}
		}
	}
}

