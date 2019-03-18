#ifndef MODEL_H
#define MODEL_H

class Model {
public:
	Model(float vertices[], const int size);
	~Model(void);

	float* getVertices(void);
	int getSize(void);
	
	void draw(void);
private:
	float* vertices;
	int size;
};

#endif