#include<iostream>
#include<glew.h>
#include<glfw3.h>
#include<math.h>
#include "glm/ext.hpp"
using namespace std;

const float PI = 3.14159265359;
const float DEG_TO_RAD = PI / 180.0;

class Matrix {
public:
	float matrix[4][4];
	Matrix() {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++)
				matrix[i][j] = 0;
		}
	}
	Matrix RotationX(float degree) {
		Matrix result;
		float radian = degree * DEG_TO_RAD;
		result.matrix[0][0] = 1;
		result.matrix[1][1] = cos(radian);
		result.matrix[1][2] = -1 * sin(radian);
		result.matrix[2][1] = sin(radian);
		result.matrix[2][2] = cos(radian);
		result.matrix[3][3] = 1;
		return result;
	}
	Matrix RotationY(float degree) {
		Matrix result;
		float radian = degree * DEG_TO_RAD;
		result.matrix[0][0] = cos(radian);
		result.matrix[0][2] = sin(radian);
		result.matrix[1][1] = 1;
		result.matrix[2][0] = -sin(radian);
		result.matrix[2][2] = cos(radian);
		result.matrix[3][3] = 1;
		return result;
	}
	Matrix RotationZ(float degree) {
		Matrix result;
		float radian = degree * DEG_TO_RAD;
		result.matrix[0][0] = cos(radian);
		result.matrix[0][1] = -sin(radian);
		result.matrix[1][0] = sin(radian);
		result.matrix[1][1] = cos(radian);
		result.matrix[2][2] = 1;
		result.matrix[3][3] = 1;
		return result;
	}
	Matrix operator+(Matrix another) {
		Matrix result;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++)
				result.matrix[i][j] = matrix[i][j] + another.matrix[i][j];
		}
		return result;
	}
	Matrix operator-(Matrix another) {
		Matrix result;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++)
				result.matrix[i][j] = matrix[i][j] - another.matrix[i][j];
		}
		return result;
	}
	Matrix operator*(Matrix another) {
		Matrix result;
		float sum = 0.0f;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				for (int k = 0; k < 4; k++)
					sum += (matrix[i][k] * another.matrix[k][j]);
				result.matrix[i][j] = sum;
				sum = 0.0f;
			}
		}
		return result;
	}
	Matrix TranslationMatrix(float x, float y, float z) {
		Matrix matrix_translation;
		matrix_translation.matrix[0][3] = x;
		matrix_translation.matrix[1][3] = y;
		matrix_translation.matrix[2][3] = z;
		matrix_translation.matrix[3][3] = 1;
		return matrix_translation;
	}
	void ResetMatrix() {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++)
				matrix[i][j] = 0;
		}
	}
	void ShowMatrix() {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++)
				cout << matrix[i][j] << " ";
			cout << endl;
		}
	}
	Matrix Scalling(float x, float y, float z) {
		Matrix result;
		result.matrix[0][0] = x;
		result.matrix[1][1] = y;
		result.matrix[2][2] = z;
		return result;
	}
};

class Vertex {
public:
	GLfloat x, y, z;
	Vertex(GLfloat _x = 0, GLfloat _y = 0, GLfloat _z = 0) {
		x = _x;
		y = _y;
		z = _z;
	}
	Vertex operator-(const Vertex& vertex) {
		Vertex temp(x, y, z);
		temp.x -= vertex.x;
		temp.y -= vertex.y;
		temp.z -= vertex.z;
		return temp;
	}
	Vertex operator-(float input) {
		Vertex temp;
		temp.x = x - input;
		temp.y = y - input;
		temp.z = z - input;
		return temp;
	}
	Vertex operator+(const Vertex& vertex) {
		Vertex temp(x, y, z);
		temp.x += vertex.x;
		temp.y += vertex.y;
		temp.z += vertex.z;
		return temp;
	}
	Vertex operator+(Matrix input) {
		Vertex v;
		v.x = this->x + input.matrix[0][3];
		v.y = this->y + input.matrix[1][3];
		v.z = this->z + input.matrix[2][3];
		return v;
	}
	Vertex operator+(float input) {
		Vertex temp;
		temp.x = x + input;
		temp.y = y + input;
		temp.z = z + input;
		return temp;
	}
	Vertex operator*(const Vertex& Another) {
		Vertex temp;
		temp.x = x * Another.x;
		temp.y = y * Another.y;
		temp.z = z * Another.z;
		return temp;
	}
	Vertex operator*(float number) {
		Vertex temp(x, y, z);
		temp.x *= number;
		temp.y *= number;
		temp.z *= number;
		return temp;
	}
	Vertex operator/(float input) {
		Vertex temp;
		temp.x = x / input;
		temp.y = y / input;
		temp.z = z / input;
		return temp;
	}
	void operator=(const Vertex& vertex) {
		x = vertex.x;
		y = vertex.y;
		z = vertex.z;
	}
	Vertex normalize() {
		float length = pow(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0), 0.5);
		x /= length;
		y /= length;
		z /= length;
		return Vertex(x, y, z);
	}
	float Dot(Vertex input) {
		return (x * input.x) + (y * input.y) + (z * input.z);
	}
	Vertex Cross(Vertex input) {
		Vertex temp;
		temp.x = x * input.x;
		temp.y = y * input.y;
		temp.z = z * input.z;
		return temp;
	}
	Vertex operator*(Matrix TransformationMatrix) {
		Vertex result;
		result.x = (TransformationMatrix.matrix[0][0] * x) + (TransformationMatrix.matrix[0][1] * y) + (TransformationMatrix.matrix[0][2] * z);
		result.y = (TransformationMatrix.matrix[1][0] * x) + (TransformationMatrix.matrix[1][1] * y) + (TransformationMatrix.matrix[1][2] * z);
		result.z = (TransformationMatrix.matrix[2][0] * x) + (TransformationMatrix.matrix[2][1] * y) + (TransformationMatrix.matrix[2][2] * z);
		return result;
	}
	Vertex Scalling(Matrix Another) {
		Vertex v;
		v.x = this->x * Another.matrix[0][0];
		v.y = this->y * Another.matrix[1][1];
		v.z = this->z * Another.matrix[2][2];
		return v;
	}
};

float GetLength(const Vertex& vector)
{
	float length = pow(vector.x, 2) + pow(vector.y, 2) + pow(vector.z, 2);
	length = pow(length, 0.5);
	return length;
}

Vertex GetNormal(Vertex& a, Vertex& b, Vertex& c, bool clockwise = true)
{
	Vertex v0 = b - a;
	Vertex v1 = c - a;

	Vertex normal;

	normal.x = (v0.y * v1.z) - (v0.z * v1.y);
	normal.y = -1.0f * ((v0.x * v1.z) - (v0.z * v1.x));
	normal.z = (v0.x * v1.y) - (v0.y - v1.x);

	float length = GetLength(normal);

	normal.x = normal.x * (clockwise ? 1.0f : -1.0f) / length;
	normal.y = normal.y * (clockwise ? 1.0f : -1.0f) / length;
	normal.z = normal.z * (clockwise ? 1.0f : -1.0f) / length;
	return normal;
}

Vertex GetCrossProduct(Vertex& a, Vertex& b, Vertex& c)
{
	Vertex v0 = b - a;
	Vertex v1 = c - a;

	Vertex normal;

	normal.x = (v0.y * v1.z) - (v0.z * v1.y);
	normal.y = -1.0f * ((v0.x * v1.z) - (v0.z * v1.x));
	normal.z = (v0.x * v1.y) - (v0.y - v1.x);
	return normal;
}

float GetDotProduct(const Vertex& a, const Vertex& b)
{
	float dot = a.x * b.x + a.y * b.y + a.z * b.z;
	return dot;
}

float GetDistance(const Vertex& a, const Vertex& b)
{
	float distance = pow((a.x - b.x), 2.0) + pow((a.y - b.y), 2.0) + pow((a.z - b.z), 2.0);
	distance = pow(distance, 0.5);
	return distance;
}

Vertex GetRotationResult(const Vertex& pivot, const Vertex* matrix, Vertex point, bool isEuler = false)
{
	Vertex temp, newPosition;
	temp = (isEuler) ? point : point - pivot;

	newPosition.x = temp.x * matrix[0].x + temp.y * matrix[0].y + temp.z * matrix[0].z;
	newPosition.y = temp.x * matrix[1].x + temp.y * matrix[1].y + temp.z * matrix[1].z;
	newPosition.z = temp.x * matrix[2].x + temp.y * matrix[2].y + temp.z * matrix[2].z;

	temp = (isEuler) ? newPosition : newPosition + pivot;
	return temp;
}

void GetRotationMatrix(const Vertex& vector, float angle, Vertex* matrix)
{
	matrix[0].x = (cos(angle) + pow(vector.x, 2.0f) * (1.0f - cos(angle)));
	matrix[0].y = (vector.x * vector.y * (1.0f - cos(angle)) - vector.z * sin(angle));
	matrix[0].z = (vector.x * vector.z * (1.0f - cos(angle)) + vector.y * sin(angle));

	matrix[1].x = (vector.x * vector.y * (1.0f - cos(angle)) + vector.z * sin(angle));
	matrix[1].y = (cos(angle) + pow(vector.y, 2.0f) * (1.0f - cos(angle)));
	matrix[1].z = (vector.y * vector.z * (1.0f - cos(angle)) - vector.x * sin(angle));

	matrix[2].x = (vector.x * vector.z * (1.0f - cos(angle)) - vector.y * sin(angle));
	matrix[2].y = (vector.y * vector.z * (1.0f - cos(angle)) + vector.x * sin(angle));
	matrix[2].z = (cos(angle) + pow(vector.z, 2.0f) * (1.0f - cos(angle)));
}

int getPascal(int row, int col) {
	if (col > row)
		return 0;
	else if (col == 0 || row == 0)
		return 1;
	return getPascal(row - 1, col - 1) + getPascal(row - 1, col);
}

class Shape
{
protected:
	int point_size;
	int outline_point_size;
	int color_size;
	int normal_count;
	Vertex* points;
	Vertex* outline_points;
	Vertex* base_colors;
	Vertex* colors;
	Vertex* normals;
	Vertex position;
	Vertex euler[3]; //euler X, euler Y, euler Z
	GLuint buffer;
	GLuint outlineBuffer;
	GLuint shader, outlineShader;
	GLuint MatrixID;
	GLuint colorBuffer;
	glm::mat4 mvp;
public:
	Shape(float _x = 0, float _y = 0, float _z = 0)
	{
		position = Vertex(_x, _y, _z);
		euler[0] = Vertex(1, 0, 0);
		euler[1] = Vertex(0, 1, 0);
		euler[2] = Vertex(0, 0, 1);
		normal_count = 0;
	}

	Vertex GetPosition()
	{
		return position;
	}

	int GetPointSize()
	{
		return point_size;
	}

	int GetOutlinePointSize()
	{
		return outline_point_size;
	}

	Vertex* GetPoints()
	{
		return points;
	}

	Vertex* GetOutlinePoints()
	{
		return outline_points;
	}

	void ShowPoints()
	{
		for (int i = 0; i < point_size; i++)
		{
			printf("%f, %f, %f\n", points[i].x, points[i].y, points[i].z);
		}
	}

	void InitializeBuffer()
	{
		glGenBuffers(1, &buffer);
		glGenBuffers(1, &outlineBuffer);
		glGenBuffers(1, &colorBuffer);
		SetArrayBuffer();
	}

	void SetArrayBuffer()
	{
		SetBuffer();
		SetOutlineBuffer();
		SetColorBuffer();
	}

	void SetBuffer()
	{
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBufferData(GL_ARRAY_BUFFER, GetPointSize() * sizeof(GL_FLOAT) * 3, GetPoints(), GL_STATIC_DRAW);
	}

	void SetOutlineBuffer()
	{
		glBindBuffer(GL_ARRAY_BUFFER, outlineBuffer);
		glBufferData(GL_ARRAY_BUFFER, GetOutlinePointSize() * sizeof(GL_FLOAT) * 3, GetOutlinePoints(), GL_STATIC_DRAW);
	}

	void SetColorBuffer()
	{
		glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
		glBufferData(GL_ARRAY_BUFFER, color_size * sizeof(GL_FLOAT) * 3, colors, GL_STATIC_DRAW);
	}

	void InitializeShader(const char vertex[], const char fragment[])
	{
		shader = LoadShaders(vertex, fragment);

		glm::mat4 Projection = glm::perspective(90.0f * DEG_TO_RAD, 1.0f, 0.1f, 100.0f);

		// Camera matrix
		glm::mat4 View = glm::lookAt(
			glm::vec3(0, 1, 2), //Eye position at (0, 1, 2)
			glm::vec3(0, 0, 0), // and looks at the origin
			glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
		);

		// Model matrix : an identity matrix (model will be at the origin)
		glm::mat4 Model = glm::mat4(1.0f);

		// Our ModelViewProjection : multiplication of our 3 matrices
		mvp = Projection * View * Model;

		MatrixID = glGetUniformLocation(shader, "MVP");
	}

	void InitializeOutlineShader(const char vertex[], const char fragment[])
	{
		outlineShader = LoadShaders(vertex, fragment);
	}

	void BindBuffer()
	{
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glVertexAttribPointer(
			0, //Set to 0 for coordinates
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			0
		);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
		glVertexAttribPointer(
			1, //Set to 1 for colors
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			0
		);
	}

	void BindOutlineBuffer()
	{
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, outlineBuffer);
		glVertexAttribPointer(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			0
		);
	}

	void DrawPolygon()
	{
		glUseProgram(shader);
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
		BindBuffer();
		glDrawArrays(GL_TRIANGLES, 0, GetPointSize());
	}

	void DrawPolyline()
	{
		glUseProgram(outlineShader);
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
		BindOutlineBuffer();
		glDrawArrays(GL_LINES, 0, GetOutlinePointSize());
	}

	void Rotate(const Vertex& pivot, const Vertex& vector, float angle)
	{
		angle = angle * DEG_TO_RAD;

		Vertex* rotation_matrix = new Vertex[3];
		GetRotationMatrix(vector, angle, rotation_matrix);

		//Rotate all the points
		for (int i = 0; i < point_size; i++)
		{
			points[i] = GetRotationResult(pivot, rotation_matrix, points[i]);
		}

		for (int i = 0; i < outline_point_size; i++)
		{
			outline_points[i] = GetRotationResult(pivot, rotation_matrix, outline_points[i]);
		}

		//Rotate the euler direction
		for (int i = 0; i < 3; i++)
		{
			euler[i] = GetRotationResult(pivot, rotation_matrix, euler[i], true);
			euler[i].normalize(); //Normalize the euler since we only need the euler's direction
		}

		//Rotate the normals
		for (int i = 0; i < normal_count; i++)
		{
			normals[i] = GetRotationResult(pivot, rotation_matrix, normals[i], true);
		}

		position = GetRotationResult(pivot, rotation_matrix, position);

		SetArrayBuffer();
	}

	void Translate(const Vertex& movement)
	{
		for (int i = 0; i < point_size; i++)
		{
			points[i] = points[i] + movement;
		}

		for (int i = 0; i < outline_point_size; i++)
		{
			outline_points[i] = outline_points[i] + movement;
		}

		position = position + movement;

		SetArrayBuffer();
	}

	Vertex GetEuler(int index)
	{
		return euler[index];
	}

	void ResetEuler()
	{
		euler[0] = Vertex(1, 0, 0);
		euler[1] = Vertex(0, 1, 0);
		euler[2] = Vertex(0, 0, 1);
	}

	~Shape()
	{
		delete points;
		glDeleteBuffers(1, &buffer);
	}
};

class Mesh : public Shape {
	vector<unsigned int> VertexIndices, uvIndices, NormalIndices;
public:
	Mesh(const char* Obj_path = "", int scale = 1, Vertex _color = (0.9f, 0.2f, 0.8f), int _x = 0, int _y = 0, int _z = 0) : Shape(_x, _y, _z) {
		point_size = 0;
		bool v = false, vt = false, vn = false;
		FILE* objFile = fopen(Obj_path, "r");
		if (!objFile)
			return;
		vector<Vertex> temp_vertices, temp_uvs, temp_normals;
		while (true) {
			char lines[1000000];
			int res = fscanf(objFile, "%s", lines);
			if (res == EOF)
				break;
			if (strcmp(lines, "v") == 0) {
				v = true;
				Vertex v;
				fscanf(objFile, "%f %f %f\n", &v.x, &v.y, &v.z);
				temp_vertices.push_back(v);
			}
			else if (strcmp(lines, "vn") == 0) {
				vn = true;
				Vertex normal;
				fscanf(objFile, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
				temp_normals.push_back(normal);
			}
			else if (strcmp(lines, "vt") == 0) {
				vt = true;
				Vertex uv; uv.z = 0;
				fscanf(objFile, "%f %f\n", &uv.x, &uv.y);
				temp_uvs.push_back(uv);
			}
			else if (strcmp(lines, "f") == 0) {
				string vertex1, vertex2, vertex3;
				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
				if (v && vt && vn) {
					if (fscanf(objFile, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2])) {
						VertexIndices.push_back(vertexIndex[0]);
						VertexIndices.push_back(vertexIndex[1]);
						VertexIndices.push_back(vertexIndex[2]);
						uvIndices.push_back(uvIndex[0]);
						uvIndices.push_back(uvIndex[1]);
						uvIndices.push_back(uvIndex[2]);
						NormalIndices.push_back(normalIndex[0]);
						NormalIndices.push_back(normalIndex[1]);
						NormalIndices.push_back(normalIndex[2]);
					}
				}
				else if (v && vt && !vn) {
					if (fscanf(objFile, "%d/%d %d/%d %d/%d\n", &vertexIndex[0], &uvIndex[0], &vertexIndex[1], &uvIndex[1], &vertexIndex[2], &uvIndex[2])) {
						VertexIndices.push_back(vertexIndex[0]);
						VertexIndices.push_back(vertexIndex[1]);
						VertexIndices.push_back(vertexIndex[2]);
						uvIndices.push_back(uvIndex[0]);
						uvIndices.push_back(uvIndex[1]);
						uvIndices.push_back(uvIndex[2]);
					}
				}
				else if (v && !vt && vn) {
					if (fscanf(objFile, "%d//%d %d//%d %d//%d\n", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2])) {
						VertexIndices.push_back(vertexIndex[0]);
						VertexIndices.push_back(vertexIndex[1]);
						VertexIndices.push_back(vertexIndex[2]);
						NormalIndices.push_back(normalIndex[0]);
						NormalIndices.push_back(normalIndex[1]);
						NormalIndices.push_back(normalIndex[2]);
					}
				}
				else {
					if (fscanf(objFile, "%d %d %d\n", &vertexIndex[0], &vertexIndex[1], &vertexIndex[2])) {
						VertexIndices.push_back(vertexIndex[0]);
						VertexIndices.push_back(vertexIndex[1]);
						VertexIndices.push_back(vertexIndex[2]);
					}
				}
			}
		}
		if (v && vt && vn) {
			unsigned int vertexIndex, uvIndex, normalIndex;
			point_size = VertexIndices.size();
			points = new Vertex[point_size];
			normals = new Vertex[point_size];
			for (unsigned int i = 0; i < VertexIndices.size(); i++) {
				vertexIndex = VertexIndices[i];
				uvIndex = uvIndices[i];
				normalIndex = NormalIndices[i];

				Vertex vertex = temp_vertices[vertexIndex - 1] / scale;
				Vertex uv = temp_uvs[uvIndex - 1];
				Vertex normal = temp_normals[normalIndex - 1];

				points[i].x = vertex.x * 0.1f;
				points[i].y = vertex.y * 0.1f;
				points[i].z = vertex.z * 0.1f;

				normals[i].x = normal.x;
				normals[i].y = normal.y;
				normals[i].z = normal.z;
			}
		}
		else if (v && vt && !vn) {
			int counter = 0, ctr = 0;
			unsigned int vertexIndex, uvIndex;
			point_size = VertexIndices.size();
			points = new Vertex[point_size];
			normals = new Vertex[point_size];
			for (unsigned int i = 0; i < VertexIndices.size(); i++) {
				vertexIndex = VertexIndices[i];
				uvIndex = uvIndices[i];

				Vertex vertex = temp_vertices[vertexIndex - 1] / scale;
				Vertex uv = temp_uvs[uvIndex - 1];

				points[i].x = vertex.x * 0.1f;
				points[i].y = vertex.y * 0.1f;
				points[i].z = vertex.z * 0.1f;

				if ((i % 3 == 0 || i == VertexIndices.size() - 1) && i != 0) {
					normals[ctr] = GetCrossProduct(points[3 * counter + 1], points[3 * counter], points[3 * counter + 2]);
					normals[ctr + 1] = GetCrossProduct(points[3 * counter + 1], points[3 * counter], points[3 * counter + 2]);
					normals[ctr + 2] = GetCrossProduct(points[3 * counter + 1], points[3 * counter], points[3 * counter + 2]);
					counter++;
					ctr += 3;
				}
			}
		}
		else if (v && !vt && vn) {
			unsigned int vertexIndex, normalIndex;
			point_size = VertexIndices.size();
			points = new Vertex[point_size];
			normals = new Vertex[point_size];
			for (unsigned int i = 0; i < VertexIndices.size(); i++) {
				vertexIndex = VertexIndices[i];
				normalIndex = NormalIndices[i];

				Vertex vertex = temp_vertices[vertexIndex - 1] / scale;
				Vertex normal = temp_normals[normalIndex - 1];

				points[i].x = vertex.x * 0.1f;
				points[i].y = vertex.y * 0.1f;
				points[i].z = vertex.z * 0.1f;

				normals[i].x = normal.x;
				normals[i].y = normal.y;
				normals[i].z = normal.z;
			}
		}
		else {
			int counter = 0, ctr = 0;
			unsigned int vertexIndex;
			point_size = VertexIndices.size();
			points = new Vertex[point_size];
			normals = new Vertex[point_size];
			for (unsigned int i = 0; i < VertexIndices.size(); i++) {
				vertexIndex = VertexIndices[i];

				Vertex vertex = temp_vertices[vertexIndex - 1] / scale;

				points[i].x = vertex.x * 0.1f;
				points[i].y = vertex.y * 0.1f;
				points[i].z = vertex.z * 0.1f;

				if ((i % 3 == 0 || i == VertexIndices.size() - 1) && i != 0) {
					normals[ctr] = GetCrossProduct(points[3 * counter + 1], points[3 * counter], points[3 * counter + 2]);
					normals[ctr + 1] = GetCrossProduct(points[3 * counter + 1], points[3 * counter], points[3 * counter + 2]);
					normals[ctr + 2] = GetCrossProduct(points[3 * counter + 1], points[3 * counter], points[3 * counter + 2]);
					counter++;
					ctr += 3;
				}
			}
		}
		fclose(objFile);
		normal_count = point_size;
		GenerateOutlinePoints();
		GenerateColors(_color);
	}

	void GenerateColors(Vertex color)
	{
		color_size = point_size;
		base_colors = new Vertex[color_size];
		colors = new Vertex[color_size];
		for (int i = 0; i < color_size; i++)
		{
			base_colors[i] = color;
		}
	}

	void CalculateColors(Vertex& light_source, Vertex& light_color, const Vertex& ambience_multiplier, Vertex& eye_pos, const float& specular_multiplier, const float& shinyness, const float& light_intensity)
	{
		for (int i = 0; i < point_size; i++)
		{
			int normal_index = i;

			//Ambience
			Vertex ambience = base_colors[i] * ambience_multiplier;

			//Diffuse
			Vertex light_vec = light_source - points[i];
			float light_distance = GetLength(light_vec);
			light_vec = light_vec * (1.0f / light_distance);
			float cos_angle = GetDotProduct(light_vec, normals[normal_index]);
			Vertex diffuse = base_colors[i] * ((cos_angle < 0) ? 0 : cos_angle);

			//Specular
			Vertex eye_vec = eye_pos - points[i];
			float eye_distance = GetLength(eye_vec);
			eye_vec = eye_vec * (1.0f / eye_distance);
			Vertex R = normals[normal_index] * cos_angle * 2.0 - light_vec;
			R = R * (1.0f / GetLength(R));
			float spec = GetDotProduct(eye_vec, R);
			spec = (spec < 0) ? 0 : pow(spec, shinyness);
			Vertex specular = Vertex(0, 0, 0);
			if (spec > 0)
			{
				specular = light_color * specular_multiplier * spec;
				diffuse = diffuse * (1 - spec);
			}

			//Combined
			colors[i] = (ambience + diffuse + specular) * (light_intensity / (pow(light_distance, 2.0)));
		}
		SetColorBuffer();
	}

	void RandomizeColors()
	{
		for (int i = 0; i < color_size; i++)
		{
			float red = (float)(rand() % 100) / 100.0f;
			float green = (float)(rand() % 100) / 100.0f;
			float blue = (float)(rand() % 100) / 100.0f;
			colors[i] = Vertex(red, green, blue);
		}
		SetColorBuffer();
	}

	/*void GenerateNormals()
	{
		normal_count = point_size / 3;
		normals = new Vertex[normal_count];
		for (int i = 0, j = 0; i < point_size; i += 3, j++)
		{
			normals[j] = GetNormal(points[i], points[i + 1], points[i + 2], true);
			normals[j].x = abs(normals[j].x);
			normals[j].y = abs(normals[j].y);
			normals[j].z = abs(normals[j].z);
		}
	}*/

	void GenerateOutlinePoints()
	{
		outline_point_size = point_size * 2;
		outline_points = new Vertex[outline_point_size];
		for (int i = 0, j = 0; i < point_size; i += 3, j += 6)
		{
			int first_index = i;
			int second_index = i + 1;
			int third_index = i + 2;

			outline_points[j] = points[first_index];
			outline_points[j + 1] = points[second_index];
			outline_points[j + 2] = points[second_index];
			outline_points[j + 3] = points[third_index];
			outline_points[j + 4] = points[third_index];
			outline_points[j + 5] = points[first_index];
		}
	}

};

class Triangle : public Shape {
public:
	Triangle() {
		point_size = 3;
		points = new Vertex[point_size];
	}
	Triangle(Vertex _points[3], GLfloat _x = 0, GLfloat _y = 0, GLfloat _z = 0) : Shape(_x, _y, _z) {
		point_size = 3;
		points = new Vertex[point_size];
		for (int i = 0; i < point_size; i++) {
			points[i] = _points[i];
		}
	}
	void setPoints(const Vertex pts[3]) {
		for (int i = 0; i < 3; i++) {
			points[i] = pts[i];
		}
	}
	void setPosition(const Vertex& _position) {
		position = _position;
	}
};

class Circle : public Shape {
	float radius;
	float step;
	float scale;
public:
	Circle(float _x = 0, float _y = 0, float _z = 0, int _pointSize = 1, float _radius = 1, float _scale = 1) : Shape(_x, _y, _z) {
		scale = _scale;
		point_size = _pointSize * 3;
		points = new Vertex[point_size];
		radius = _radius;
		step = 2 * PI * scale / _pointSize;
		generate();
	}
	void generate() {
		float i = -PI;
		float end = i + 2 * PI * scale;
		int j = 0;
		for (; i <= end; i += step, j += 3) {
			float x = cos(i) * radius + position.x;
			float y = sin(i) * radius + position.y;
			float z = 0;

			float next_x = cos(i + step) * radius + position.x;
			float next_y = sin(i + step) * radius + position.y;
			float next_z = 0;

			points[j] = Vertex(x, y, z);
			points[j + 1] = position;
			points[j + 2] = Vertex(next_x, next_y, next_z);
		}
	}
};

class Box : public Shape {
	Vertex position;
	Vertex pts[12][3];
	Triangle* triangles;
	float length, width, height;
	float scale;
	int smoothing, baris, kolom;
public:
	Box(float _x = 0, float _y = 0, float _z = 0, float _length = 0.25, float _width = 0.25, float _height = 0.25) : Shape(_x, _y, _z) {
		position = Vertex(_x, _y, _z);
		length = _length;
		width = _width;
		height = _height;
		triangles = new Triangle[12];
		scale = 1.0;
		point_size = 36;
		points = new Vertex[point_size];
		smoothing = 10;
		Vertex pts[12][3] = {
			{//Front - 1
				Vertex(position.x - length / 2, position.y + height / 2, position.z - width / 2),
				Vertex(position.x + length / 2, position.y + height / 2, position.z - width / 2),
				Vertex(position.x - length / 2, position.y - height / 2, position.z - width / 2)
			},
			{//Front - 2
				Vertex(position.x + length / 2, position.y + height / 2, position.z - width / 2),
				Vertex(position.x - length / 2, position.y - height / 2, position.z - width / 2),
				Vertex(position.x + length / 2, position.y - height / 2, position.z - width / 2)
			},
			{//Back - 1
				Vertex(position.x - length / 2, position.y + height / 2, position.z + width / 2),
				Vertex(position.x + length / 2, position.y + height / 2, position.z + width / 2),
				Vertex(position.x - length / 2, position.y - height / 2, position.z + width / 2)
			},
			{//Back - 2
				Vertex(position.x + length / 2, position.y + height / 2, position.z + width / 2),
				Vertex(position.x - length / 2, position.y - height / 2, position.z + width / 2),
				Vertex(position.x + length / 2, position.y - height / 2, position.z + width / 2)
			},
			{//Top - 1
				Vertex(position.x - length / 2, position.y + height / 2, position.z + width / 2),
				Vertex(position.x + length / 2, position.y + height / 2, position.z + width / 2),
				Vertex(position.x - length / 2, position.y + height / 2, position.z - width / 2)
			},
			{//Top - 2
				Vertex(position.x + length / 2, position.y + height / 2, position.z + width / 2),
				Vertex(position.x - length / 2, position.y + height / 2, position.z - width / 2),
				Vertex(position.x + length / 2, position.y + height / 2, position.z - width / 2)
			},
			{//Bottom - 1
				Vertex(position.x - length / 2, position.y - height / 2, position.z + width / 2),
				Vertex(position.x + length / 2, position.y - height / 2, position.z + width / 2),
				Vertex(position.x - length / 2, position.y - height / 2, position.z - width / 2)
			},
			{//Bottom - 2
				Vertex(position.x + length / 2, position.y - height / 2, position.z + width / 2),
				Vertex(position.x - length / 2, position.y - height / 2, position.z - width / 2),
				Vertex(position.x + length / 2, position.y - height / 2, position.z - width / 2)
			},
			{//Left - 1
				Vertex(position.x - length / 2, position.y + height / 2, position.z + width / 2),
				Vertex(position.x - length / 2, position.y + height / 2, position.z - width / 2),
				Vertex(position.x - length / 2, position.y - height / 2, position.z + width / 2)
			},
			{//Left - 2
				Vertex(position.x - length / 2, position.y + height / 2, position.z - width / 2),
				Vertex(position.x - length / 2, position.y - height / 2, position.z + width / 2),
				Vertex(position.x - length / 2, position.y - height / 2, position.z - width / 2)
			},
			{//Right - 1
				Vertex(position.x + length / 2, position.y + height / 2, position.z + width / 2),
				Vertex(position.x + length / 2, position.y + height / 2, position.z - width / 2),
				Vertex(position.x + length / 2, position.y - height / 2, position.z + width / 2)
			},
			{//Right - 2
				Vertex(position.x + length / 2, position.y + height / 2, position.z - width / 2),
				Vertex(position.x + length / 2, position.y - height / 2, position.z + width / 2),
				Vertex(position.x + length / 2, position.y - height / 2, position.z - width / 2)
			}
		};
		int index = 0;
		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < 3; j++)
				points[index++] = pts[i][j];
		}
	}
	Vertex getPosition() {
		return position;
	}
	void initiateBuffer() {
		for (int i = 0; i < 12; i++)
			triangles[i].InitializeBuffer();
	}
	void initiateShader(char vertex[], char fragment[]) {
		for (int i = 0; i < 12; i++)
			triangles[i].InitializeShader(vertex, fragment);
	}
	void initiateOutlineShader(char vertex[], char fragment[]) {
		for (int i = 0; i < 12; i++)
			triangles[i].InitializeOutlineShader(vertex, fragment);
	}
	void drawPolygon() {
		for (int i = 0; i < 12; i++)
			triangles[i].DrawPolygon();
	}
	void drawPolyline() {
		for (int i = 0; i < 12; i++)
			triangles[i].DrawPolyline();
	}
	void rotate(const Vertex& pivot, const Vertex& vector, float angle) {
		for (int i = 0; i < 12; i++)
			triangles[i].Rotate(pivot, vector, angle);
	}
};

class Ovaloid : public Shape {
	Vertex radius;
	float step, stepInner;
	float scale;
	int smoothing;
public:
	Ovaloid(float _x = 0, float _y = 0, float _z = 0, int _pointSize = 10, Vertex _radius = Vertex(0.3, 0.3), float _scale = 1.0, float _smoothing = 10) : Shape(_x, _y, _z) {
		scale = _scale;
		smoothing = _smoothing;
		radius = _radius;
		point_size = _pointSize * _smoothing * 3.0f * 2.0f;
		points = new Vertex[point_size];
		step = 2.0 * PI * scale / (float)_pointSize;
		stepInner = PI / (float)smoothing;
		generate();
	}
	void generate() {
		float i = -PI;
		float end = i + 2.0 * PI * scale;
		int l = 0, j = 1;
		for (; i < end && l < point_size; i += step, j++) {
			float k = -PI;
			float endInner = k + PI;
			for (; k < endInner; k += stepInner, l += 6) {
				float cur_x = cos(k) * radius.x + position.x;
				float cur_y = sin(k) * radius.y + position.y;
				float cur_z = position.z;

				float next_x = cos(k + stepInner) * radius.x + position.x;
				float next_y = sin(k + stepInner) * radius.y + position.y;
				float next_z = position.z;

				Vertex* rotation_matrix = new Vertex[3], * rotation_matrix2 = new Vertex[3];
				GetRotationMatrix(Vertex(1, 0, 0), i, rotation_matrix);
				GetRotationMatrix(Vertex(1, 0, 0), i + step, rotation_matrix2);
				points[l] = GetRotationResult(position, rotation_matrix, Vertex(cur_x, cur_y, cur_z));
				points[l + 1] = GetRotationResult(position, rotation_matrix, Vertex(next_x, next_y, next_z));
				points[l + 2] = GetRotationResult(position, rotation_matrix2, Vertex(cur_x, cur_y, cur_z));
				points[l + 3] = GetRotationResult(position, rotation_matrix, Vertex(next_x, next_y, next_z));
				points[l + 4] = GetRotationResult(position, rotation_matrix2, Vertex(cur_x, cur_y, cur_z));
				points[l + 5] = GetRotationResult(position, rotation_matrix2, Vertex(next_x, next_y, next_z));
			}
			if (!(l <= 6 * smoothing * j))
				l = l - 6;
		}
		point_size = l;
	}
};

class Vase : public Shape {
	Vertex* pts;
	int ptsCount;
	float* berzierConst, step, stepInner;
	float scale;
	int smoothing;
public:
	Vase(Vertex _pts[], int _ptsCount, float _x = 0, float _y = 0, float _z = 0, int _pointSize = 10, float _scale = 1.0, float _smoothing = 10) : Shape(_x, _y, _z) {
		scale = _scale;
		smoothing = _smoothing;
		point_size = _pointSize * smoothing * 3.0 * 2.0;
		points = new Vertex[point_size];
		step = 2.0 * PI * scale / (float)_pointSize;
		stepInner = 1.0 / (float)(smoothing - 1);

		//Control points
		ptsCount = _ptsCount;
		pts = new Vertex[ptsCount];
		for (int i = 0; i < ptsCount; i++)
			pts[i] = _pts[i] + position;
		berzierConst = new float[ptsCount];
		for (int i = 0; i < ptsCount; i++)
			berzierConst[i] = getPascal(ptsCount - 1, i);
		generate();
	}
	void generate() {
		float i = -PI;
		float end = i + 2.0 * PI * scale;
		int l = 0, j = 1;
		for (int; i < end && l < point_size; i += step, j++) {
			float k = 0;
			float endInner = 1.0;
			for (; k <= endInner; k += stepInner, l += 6) {
				float cur_x = 0, cur_y = 0, cur_z = 0;
				for (int a = 0; a < ptsCount; a++) {
					float multiplier = pow(1.0 - k, ptsCount - a - 1) * pow(k, a) * berzierConst[a];
					cur_x += multiplier * pts[a].x;
					cur_y += multiplier * pts[a].y;
					cur_z += multiplier * pts[a].z;
				}

				float next_x = 0, next_y = 0, next_z = 0;
				for (int a = 0; a < ptsCount; a++) {
					float multiplier = pow(1.0 - (k + stepInner), ptsCount - a - 1) * pow((k + stepInner), a) * berzierConst[a];
					next_x += multiplier * pts[a].x;
					next_y += multiplier * pts[a].y;
					next_z += multiplier * pts[a].z;
				}

				Vertex* rotation_matrix = new Vertex[3], * rotation_matrix2 = new Vertex[3];
				GetRotationMatrix(Vertex(0, 1, 0), i, rotation_matrix);
				GetRotationMatrix(Vertex(0, 1, 0), i + step, rotation_matrix2);
				points[l] = GetRotationResult(position, rotation_matrix, Vertex(cur_x, cur_y, cur_z));
				points[l + 1] = GetRotationResult(position, rotation_matrix, Vertex(next_x, next_y, next_z));
				points[l + 2] = GetRotationResult(position, rotation_matrix2, Vertex(cur_x, cur_y, cur_z));
				points[l + 3] = GetRotationResult(position, rotation_matrix, Vertex(next_x, next_y, next_z));
				points[l + 4] = GetRotationResult(position, rotation_matrix2, Vertex(cur_x, cur_y, cur_z));
				points[l + 5] = GetRotationResult(position, rotation_matrix2, Vertex(next_x, next_y, next_z));
			}
			if (!(l <= 6 * smoothing * j))
				l = l - 6;
		}
		point_size = l;
	}
};

class Hierarchy {
	Shape* parent;
	Hierarchy** children;
	int childCount;
public:
	Hierarchy(Shape* _parent = NULL) {
		parent = _parent;
		childCount = 0;
	}
	void setParent(Shape* _parent) {
		parent = _parent;
	}
	void addChild(Hierarchy* child) {
		Hierarchy** temp = children;
		children = new Hierarchy * [childCount + 1];
		for (int i = 0; i < childCount; i++)
			children[i] = temp[i];
		children[childCount] = child;
		childCount++;
	}
	void translate(const Vertex& movement) {
		parent->Translate(movement);
		for (int i = 0; i < childCount; i++)
			children[i]->translate(movement);
	}
	void rotate(const Vertex& pivot, const Vertex& vector, float angle) {
		parent->Rotate(pivot, vector, angle);
		for (int i = 0; i < childCount; i++)
			children[i]->rotate(pivot, vector, angle);
	}
	void drawPolygon() {
		parent->DrawPolygon();
		for (int i = 0; i < childCount; i++)
			children[i]->drawPolygon();
	}
	void drawPolyline() {
		parent->DrawPolyline();
		for (int i = 0; i < childCount; i++)
			children[i]->drawPolyline();
	}
	void initiateBuffer() {
		parent->InitializeBuffer();
		for (int i = 0; i < childCount; i++)
			children[i]->initiateBuffer();
	}
	void initiateShader(char vertex[], char fragment[]) {
		parent->InitializeShader(vertex, fragment);
		for (int i = 0; i < childCount; i++)
			children[i]->initiateShader(vertex, fragment);
	}
	void initiateOutlineShader(char vertex[], char fragment[]) {
		parent->InitializeOutlineShader(vertex, fragment);
		for (int i = 0; i < childCount; i++)
			children[i]->initiateOutlineShader(vertex, fragment);
	}
	void resetEuler() {
		parent->ResetEuler();
		for (int i = 0; i < childCount; i++)
			children[i]->resetEuler();
	}
	Shape* getParent() {
		return parent;
	}
	Hierarchy* getChild(int index) {
		return children[index];
	}
};