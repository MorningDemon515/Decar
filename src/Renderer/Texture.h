#ifndef TEXTURE_H
#define TEXTURE_H

class Texture
{
public:
	Texture() { };
	Texture(const char* file);
	~Texture();

	void Bind(unsigned int id);

private:
	unsigned int texture;
};


#endif // !TEXTURE_H
